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
; Function:    fir
; Processor:   C55xx
; Description: Implements finite impulse response filter using
;              single-MAC approach.  C-callable.
;
; Usage: ushort oflag = fir(DATA *x,           // XAR0
;                           DATA *h,           // XAR1
;                           DATA *r,           // XAR2
;                           DATA *dbuffer,     // XAR3
;                           ushort nx,         // T0
;                           ushort nh)         // T1
;
;
; Limitations:
;   nh >= 3
;
; Benchmarks:
;   Cycles:       (nx * (nh + 2)) + 37
;   Code Size (in bytes):  88
;
; History:
;   05/26/2012 Craig Leeds:  Bug fixed: SMUL must be set on exit
;****************************************************************

      .ARMS_on                      ;enable assembler for ARMS=1
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 1            ;save-on-entry registers saved (T3)
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
      .asg     AR0, x_ptr           ;linear pointer
      .asg     AR1, h_ptr           ;circular pointer
      .asg     AR2, r_ptr           ;linear pointer
      .asg     AR4, db_ptr          ;circular pointer

      .asg     BSA45, db_base       ;base addr for db_ptr
      .asg     XAR4, xdb_base       ;extended base addr for db_ptr
      .asg     BK47, db_sz          ;circ buffer size for db_ptr
      .asg     BK47_L, db_sz_L      ;for memory mapped access
      .asg     BSA01, h_base        ;base addr for h_ptr
      .asg     BK03, h_sz           ;circ buffer size for h_sz

      .asg     T0, oflag            ;returned value

      .global _fir

      .text
_fir:

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
	PSH     T3
	|| BCLR    ACOV0
	BSET    FRCT
	BCLR    SMUL
;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; h pointer

	MOV	AR1, mmap(h_base)	;base address of coefficients
	MOV	T1, mmap(h_sz)		;coefficient array size
	MOV	#0, h_ptr		;point to first coefficient

; r pointer - passed in its destination register, need do nothing

; db pointer

     || MOV	XAR3, xdb_base		;db array address
	MOV	*AR3+, db_ptr		;index of oldest db entry
	ADD     #1, T1, T3
	MOV	T3, mmap(db_sz)		;db_sz = nh+1
	MOV	AR3, mmap(db_base)	;base address for db_ptr

; Set circular/linear ARx behavior

	BSET    AR1LC
	BSET    AR4LC
;
; Setup loop counts
;----------------------------------------------------------------

	SUB	#1, T0			;T0 = nx-1
     || MAR     *AR3-
	MOV	T0, BRC0		;outer loop executes nx times
	MOV     T1, T0
	SUB	#3, T1 		;T1 = nh-3
	MOV	T1, CSR		;inner loop executes nh-2 times
;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
; - computation not needed since T0 contains nh
;
; Start of outer loop
;----------------------------------------------------------------

      ||RPTBLOCAL	loop1-1		;start the outer loop
		MPYM	T3 = *x_ptr+, *h_ptr+, AC0
		MOV     T3, *db_ptr+
		||RPT	CSR
			MACM	*h_ptr+, *db_ptr+, AC0
		MACMR	*h_ptr+, *(db_ptr-T0), AC0   ;last iteration has different pointer adjustment and rounding
		;store result to memory 
		MOV	HI(AC0), *r_ptr+	;store Q15 value to memory
loop1:					;end of outer loop

;
; Update the db entry point
;----------------------------------------------------------------
	MOV	db_ptr, *AR3		;update 1st element of db array
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------

	||MOV	#0, oflag		;clear oflag
	XCCPART	overflow(AC0)	;clears ACOV0
	    ||MOV	#1, oflag		;overflow occurred
;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
	BCLR    AR1LC
	BCLR    AR4LC
	POP     T3
     || BCLR	FRCT			;clear FRCT
	BSET	SMUL			;set SMUL
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
	||RET

;----------------------------------------------------------------
;End of file
