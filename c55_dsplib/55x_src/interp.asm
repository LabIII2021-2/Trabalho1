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
; Function:    firinterp
; Processor:   C55xx
; Description: Interpolation filter with user specified FIR coefficients
;
;						Passing:
; Usage:   short firinterp(	DATA *x,	XAR0
;				DATA *h,	XAR1
;				DATA *r,	XAR2
;				DATA *dbuffer,	XAR3
;				ushort nh,	T0
;				ushort nx,	T1
;				ushort I);	XAR4
;
; Requirements:	I >= 1
;		nh/I >= 3
;		x[nx]
;		h[nh]
;		r[nx*I]
;		dbuffer[(nh/I)+1]
;			dbuffer[0] is ptr to last db entry
;			dbuffer[1...(nh/I)] is db data
; Benchmarks:
;   Cycles:       (nx * (3 + I *(1 + nh/I))) + 64
;   Code Size (in bytes):  144
;
; History:
;  05/27/2012 Craig Leeds: Fixes following bugs: 
;          T2 was modified but not restored
;          T3 is tested but not set
;****************************************************************

	.ARMS_off			;enable assembler for ARMS=0
	.CPL_on				;enable assembler for CPL=1
	.mmregs				;enable mem mapped register names
        .noremark 5684                  ; CPU_116: BRC1 not written indirectly

; Stack frame
; -----------
RET_ADDR_SZ	.set	1		;return address
REG_SAVE_SZ	.set	0		;save-on-entry registers saved
FRAME_SZ	.set	0		;local variables
ARG_BLK_SZ	.set	0		;argument block

PARAM_OFFSET	.set	ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
	.asg	AR0, x_ptr		;linear pointer
	.asg	AR1, h_ptr		;circular pointer
	.asg	AR2, r_ptr		;linear pointer
	.asg	AR4, db_ptr		;circular pointer

	.asg	BSA01, h_base		;base addr for h_ptr
	.asg	BK03, h_sz		;circ buffer size for h_sz
	.asg	BSA45, db_base		;base addr for db_ptr
	.asg	XAR4, xdb_base		;extended base addr for db_ptr
	.asg	BK47, db_sz		;circ buffer size for db_ptr
                                	
	.asg	T0, oflag		;returned value

	.global	_firinterp

	.text
_firinterp:
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
        PSH     T3, T2
     || BCLR    ARMS
        BSET    FRCT
        BCLR    SMUL
        BCLR    ACOV0
;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
; Setup loop counts
;----------------------------------------------------------------

; outer loop count
        SUB     #1, T1
        MOV     T1, BRC0                  ;BRC0 = nx-1
        MOV     AR4, T1                   ;save I in T1 (interpolation factor)

; x pointer - passed in its destination register, need do nothing

; h pointer
        MOV     AR1, mmap(h_base)         ;base address of coefficients
        MOV     #0, h_ptr                 ;point to first coefficient
        MOV     T0, mmap(h_sz)            ;coefficient array size h_sz = nh

; r pointer - already passed in its destination register

; db pointer
        MOV     XAR3, xdb_base            ;db array address
        MOV     *AR3+, db_ptr             ;index of oldest db entry
        MOV     AR3, mmap(db_base)        ;base address for db_ptr
; Set circular/linear ARx behavior
        BSET    AR1LC                     ; set AR1 as a circular buffer
        BSET    AR4LC                     ; set AR4 as a circular buffer
; Setup loop counts
        BCLR    SXM
        MOV     T0, AC0                   ;AC0 = nh
      ||RPT     #(16-1)
                SUBC    mmap(T1), AC0     ;LO(AC0) = (nh/I)
        MOV     HI(AC0), T0               ;T0 = remainder of (nh/I)
        MOV     AC0, mmap(db_sz)          ;db_sz = (nh/I)
        SUB     #3, AC0                   ;
        MOV     AC0, mmap(CSR)            ;inner_cnt = (nh/I)-3 (reload for FIR taps)
        ADD     T1, T0                    ;T0 += I
        ADD     #1, T0                    ;T0 = remainder+I+1 (last tap hptr update)
        BSET    SXM

        SUB     #1, T1, T2                ;T2 = I-1
        MOV     T2, BRC1                  ;BRC1 = I-1        
        
        BCC     InterpLoop, T2 >= #0        
        
;
; Start of outer loop  I=1
;----------------------------------------------------------------
No_Interp:
        MOV     T2, CSR                   ;inner_cnt = nh-3 (2 iter outside loop)
        
        RPTBLOCAL NoInterpLoopEnd-1                     ;start the outer loop
                ;Sum h*x nh-iterations for next r value
                MPYM    T3 = *x_ptr+, *h_ptr+, AC0      
                ;move next input value into delay buffer
                MOV     T3, *db_ptr+
              ||RPT     CSR
                        MACM    *db_ptr+, *h_ptr+, AC0, AC0
                MACMR   *db_ptr, *h_ptr+, AC0, AC0
                MOV     HI(AC0), *r_ptr+                ;store Q15 value to memory
NoInterpLoopEnd:                                        ;end of outer loop
        
        B       InterpDone                ;goto exit procedure
;
; Start of outer loop  I>=2
;----------------------------------------------------------------
InterpLoop:
        RPTBLOCAL   OuterLoopEnd-1        ;outer loop (nx iterations)
        
                ;move next input value into delay buffer
                MOV     *x_ptr+, *db_ptr                

              ||RPTBLOCAL  InnerLoopEnd-1           ;  middle loop (I iterations)
                        ;Sum h*x (nh/I)-iterations (only non-zero) for next r value
                        MPYM    *db_ptr+, *(h_ptr+T1), AC0        ;    inner loop (nh/I iterations)      
                      ||RPT     CSR
                                MACM    *db_ptr+, *(h_ptr+T1), AC0, AC0
                        MACMR   *db_ptr+, *(h_ptr+T0), AC0, AC0
                        MOV     HI(AC0), *r_ptr+                ;    store Q15 value to memory
InnerLoopEnd:        
                ;reset h_ptr
                AMAR    *(h_ptr-T1)                 ;  h_ptr = &h[0]        
                ;Point db_ptr to new entry
              ||AMAR    *db_ptr-                
OuterLoopEnd:                             ;end of outer loop

;
; Update the db entry point
;----------------------------------------------------------------
InterpDone:
        MOV     db_ptr, *-AR3            ;update 1st element of db array
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
      ||MOV     #0, oflag                ;clear oflag
        XCCPART overflow(AC0)            ;clears ACOV0
            ||MOV    #1, oflag           ;overflow occurred
;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
        AND     #0xfe00, mmap(ST2_55)    ; Clear AR0LC-AR7LC, CDPLC (specifically AR1LC and AR4LC)
        POP     T3, T2
     || BSET    ARMS
        BCLR    FRCT
        BSET    SMUL
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
     || RET                              ;return to calling function

;----------------------------------------------------------------
;End of file
