;/*
; * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/ 
; * 
; * 
; *  Redistribution and use in source and binary forms, with or without 
; *  modification, are permitted provided that the following conditions 
; *  are met:
; *
; *    Redistributions of source code must retain the above copyright 
; *    notice, this list of conditions and the following disclaimer.
; *
; *    Redistributions in binary form must reproduce the above copyright
; *    notice, this list of conditions and the following disclaimer in the 
; *    documentation and/or other materials provided with the   
; *    distribution.
; *
; *    Neither the name of Texas Instruments Incorporated nor the names of
; *    its contributors may be used to endorse or promote products derived
; *    from this software without specific prior written permission.
; *
; *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
; *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
; *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
; *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
; *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
; *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
; *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
; *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
; *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
; *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; *
;*/

;***********************************************************
; Version 3.00.00                                           
;***********************************************************
; Function:    firdec
; Processor:   C55xx
; Description: Decimation filter with user specified FIR coefficients
;
;					
; Usage:   ushort firdec(DATA *x,	XAR0 
;			DATA *h,	XAR1 
;			DATA *r,	XAR2
;			DATA *dbuffer,	XAR3 
;			ushort nh,	T0 
;			ushort nx,	T1 
;			ushort D);	XAR4
;
; Benchmarks:
;   Cycles:       ((nx/D) * (nh + D + 9)) + 64
;   Code Size (in bytes):  139
;
; History:
;  Craig Leeds 06/15/2012  3.00.00:
;    Clean up housekeeping
;
;****************************************************************

	.ARMS_off		;enable assembler for ARMS=0
	.CPL_on			;enable assembler for CPL=1
	.mmregs			;enable mem mapped register names

; Stack frame
; -----------
RET_ADDR_SZ	.set	1	;return address
REG_SAVE_SZ	.set	1	;save-on-entry registers saved
FRAME_SZ	.set	0	;local variables
ARG_BLK_SZ	.set	0	;argument block

PARAM_OFFSET	.set	ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
	.asg	AR0, x_ptr	;linear pointer
	.asg	AR1, h_ptr	;circular pointer
	.asg	AR2, r_ptr	;linear pointer
	.asg	AR4, db_ptr	;circular pointer

	.asg	BSA01, h_base	;base addr for h_ptr
	.asg	BK03, h_sz	;circ buffer size for h_sz
	.asg	BSA45, db_base	;base addr for db_ptr
	.asg	XAR4, xdb_base	;extended base addr for db_ptr
	.asg	BK47, db_sz	;circ buffer size for db_ptr
	.asg	BK47_L, db_sz_L	;for memory mapped access

	.asg	CSR, inner_cnt	;inner loop count
	.asg	BRC0, outer_cnt	;outer loop count

	.asg	T0, oflag	;returned value
	.asg	T2, DecFac	;decimation factor

ST2mask	.set	0000000000010010b	;circular/linear pointers (AR1LC, AR4LC)


	.global	_firdec

	.text
_firdec:

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
;      SP = SP - #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

;
; Save any save-on-entry registers that are used
;----------------------------------------------------------------
; - nothing to save for this function

;
; Configure the status registers as needed.
;----------------------------------------------------------------
        PSH     T2
     || BCLR    ARMS
        BSET    FRCT
        BCLR    SMUL
        BCLR    ACOV0
;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; h pointer
        MOV     AR1, mmap(h_base)          ;base address of coefficients
        MOV     #0,h_ptr                   ;point to first coefficient
        MOV     T0, mmap(h_sz)             ;coefficient array size h_sz = nh

; r pointer - already passed in its destination register

; db pointer
        MOV     AR4,DecFac                 ;save DecFac = D
        MOV     XAR3,xdb_base              ;db array address
        MOV     *AR3+,db_ptr               ;index of oldest db entry
        MOV     AR3, mmap(db_base)         ;base address for db_ptr
        MOV     T0, mmap(db_sz)            ;db_sz = nh

; Set circular/linear ARx behavior (AR1, AR4)
        BSET    AR1LC
        BSET    AR4LC

;
; Setup loop counts
;----------------------------------------------------------------
        BCLR    SXM
        MOV     T1,AC0                     ;AC0 = nx
        ||RPT   #(16-1)
                SUBC    mmap(DecFac),AC0                
        SUB     #1,AC0                     ;
        MOV     AC0, mmap(outer_cnt)       ;outer_cnt = (nx/D)-1
        BSET    SXM
        
        SUB     #3, T0                     ;setup reload for FIR taps inner_cnt = nh-3
        SUB     #2, DecFac                 ;setup reload for sample-to-db inner_cnt = D-2
        
        BCC     DecimateLoop, DecFac >= #0        
        
;
; Start of outer loop  D=1
;----------------------------------------------------------------
        MOV     T0,inner_cnt                     ;inner_cnt = nh-3 (2 iter outside loop)
        RPTBLOCAL NoDecimLoopEnd-1               ;start the outer loop
        
                ;move next input value into delay buffer
                MOV     *x_ptr+, *db_ptr                

                ;Sum h*x nh-iterations for next r value
                MPYM    *db_ptr+, *h_ptr+,AC0      
              ||RPT     inner_cnt
                        MACM    *db_ptr+, *h_ptr+, AC0, AC0
                MACMR   *db_ptr, *h_ptr+, AC0, AC0

                ;store result to memory
                MOV     HI(AC0), *r_ptr+         ;store Q15 value to memory
NoDecimLoopEnd:                                  ;end of outer loop
        B       FirDecDone                       ;goto exit procedure
;
;
; Start of outer loop  D>=2
;----------------------------------------------------------------

DecimateLoop:
        RPTBLOCAL DecimLoopEnd-1            ;outer loop (nx/D) iterations
        
                MOV     T0, inner_cnt       ;inner_cnt = nh-3 (2 iter outside loop)
                ;move next input value into delay buffer
                MOV     *x_ptr+, *db_ptr

                ;Sum h*x nh-iterations for next r value
                MPYM    *db_ptr+, *h_ptr+, AC0      
             || RPT     inner_cnt           ; Pipe 1 of 3 from MOV inner_cnt
                        MACM    *db_ptr+, *h_ptr+, AC0, AC0
                MOV     DecFac, inner_cnt   ;inner_cnt = D-2
                MACMR   *db_ptr, *h_ptr+, AC0, AC0

                ;store result to memory
                MOV     HI(AC0), *r_ptr+    ;store Q15 value to memory
        
                ;Move next D-1 input samples into delay buffer
             || RPT     inner_cnt           ; Pipe 1 of 3 from MOV inner_cnt
                        MOV     *x_ptr+, *db_ptr-
DecimLoopEnd:                               ;end of outer loop

; Update the db entry point
;----------------------------------------------------------------
FirDecDone:
        BCLR    AR1LC
        BCLR    AR4LC
        MOV     db_ptr, *-AR3               ;update 1st element of db array
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
      ||MOV     #0, oflag                   ;clear oflag
        XCCPART overflow(AC0)               ;clears ACOV0
              ||MOV     #1, oflag           ;overflow occurred

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
; - nothing to restore for this function
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)
;
; Return to calling function
;----------------------------------------------------------------

        BSET    SMUL
        POP     T2
      ||BSET    ARMS
        RET                                 ;return to calling function
      ||BCLR    FRCT

;----------------------------------------------------------------
;End of file
        .end
