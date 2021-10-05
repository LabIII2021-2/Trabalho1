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
; Function:    NEG32 
; Processor:   C55xx
; Description: Implements a 32-bit 2'complement of an input
;              vector.  This routine is C-callable.
;
; Algorithm:   for(i=0, i<nx, i++)
;	              r(i) =  - x(i); 
;
; Usage: ushort oflag = neg32 (LDATA *x,
;                              LDATA *r,
;                              ushort nx)
;
; Benchmarks:
;   Cycles:       (1 * nx) + 12
;   Code Size (in bytes):  31
;
; History:
; 1. Corrected loop lable
;           ------Li Yuan 10/31/2000
; 2. Corrected SATD bit setting from clear to set.
;           ------Li Yuan 01/19/2001
; 3. SATD cleared on exit.
;    AR1 no longer set to circular buffer.
;    Loop and housekeeping optimized by 67%.
;           ------Craig Leeds 05/17/2012
;****************************************************************

      .ARMS_on                     ;enable assembler for ARMS=1
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

; -----------
; Stack frame
; -----------

RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 0            ;save-on-entry registers saved
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ

; ------------------------------
; Register usage and definitions
; ------------------------------
	.asg     AR0, x_ptr           	;linear pointer for first input vector
	.asg     AR1, r_ptr           	;linear pointer for result vector

	.asg     T0, oflag           	;returned value

	.def _neg32
	.text

_neg32:

; ---------------------------------------------------------------
; Allocate the local frame and argument block
; ---------------------------------------------------------------
;      SP = SP - #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

; ---------------------------------------------------------------
; Save any save-on-entry registers that are used
; ---------------------------------------------------------------
; - nothing to save for this function

; ---------------------------------------------------------------
; Setup loop counts
; --------------------------------------------------------------

	SUB	#1, T0			;T0 = nx - 1
	MOV	T0, CSR 		;outer loop executes nx times
        MOV     #0, AC1

; ---------------------------------------------------------------
; Configure the status registers as needed.
; ---------------------------------------------------------------

     || BSET	SATD			
	BCLR	ACOV0			; clear overflow bit 
	MOV	#0, oflag		;cler oflag

; ---------------------------------------------------------------
; Setup passed parameters in their destination registers
; Setup linear CDP/ARx behavior
; ---------------------------------------------------------------
; x pointer - passed in its destination register
; y pointer - passed in its destination register
; r pointer - passed in its destination register
; ---------------------------------------------------------------

; ---------------------------------------------------------------
; Start of outer loop 
; for (i=0; iP<nx; i++)
;    R(i) = - X(i);
; ---------------------------------------------------------------

	SUB	dbl(*AR0+), AC1, AC0	;AC0=32-bit value (input vector) (Prime the Pump)

     || RPT     CSR
	        MOV	AC0, dbl(*AR1+)		;storing 32-bit ACC to mem
	     || SUB	dbl(*AR0+), AC1, AC0	;AC0=32-bit value (input vector) (for next iteration)

; ---------------------------------------------------------------
; Check if overflow occurred, and setup return value
; ---------------------------------------------------------------

	XCCPART	overflow(AC0)	;clears AC0V0
	    ||MOV	#1, oflag		;overflow occured

; ---------------------------------------------------------------
; Restore status regs to expected C-convention values as needed
; ---------------------------------------------------------------

; ----------------------------------------------------------------
; Restore any save-on-entry registers that are used
; ----------------------------------------------------------------
; - nothing to restore for this function

; ---------------------------------------------------------------
; Deallocate the local frame and argument block
; ---------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

; ---------------------------------------------------------------
; Return to calling function
; ---------------------------------------------------------------
      BCLR	SATD
    ||RET                      ;return to calling function

;----------------------------------------------------------------
;End of file


