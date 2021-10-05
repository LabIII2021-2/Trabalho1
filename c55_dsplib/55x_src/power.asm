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
; Function:    POWER
; Processor:   C55xx
; Description: Implements a vector power using a single-MAC 
;              approach.  This routine is C-callable.
;
; Algorithm:   for(i=0, i<nx, i++)
;                r(i) += x(i) * x(i); 
;
; Usage: ushort oflag = power (DATA *x,
;                             LDATA *r,
;                             ushort nx,
;
; Limitations:
;    nx >= 2
;
; Benchmarks:
;   Cycles:       (1 * nx) + 13
;   Code Size (in bytes):  29
;
; History:
; - Corrected return register from AR2 to AR1.
;               ---- Li Yuan    01/17/01
;
; - Return overflow value is in T0 instead of AC0. 
;   Output vector is pointed by AR3 and returned.
;      Zhengting He - 10/25/2006
;
;  - Fixed bug where corruption occured if AR1H != AR3H
;    Optimized overhead
;      Craig Leeds - 05/26/12  
;****************************************************************

      .ARMS_on                      ;enable assembler for ARMS=1
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

ST2mask	.set  0000000000010010b 	;circular/linear pointers


        .def _power
	.text

_power:


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
; Configure the status registers as needed.
; ---------------------------------------------------------------

; ---------------------------------------------------------------
; Setup loop counts
; ---------------------------------------------------------------

	SUB	#(1+1), T0	;T0 = nx - 1 
	MOV	T0, CSR		;outer loop executes nx times 

        BSET    FRCT
        BCLR    ACOV0

; ---------------------------------------------------------------
; Setup passed parameters in their destination registers
; Setup linear CDP/ARx behavior
; ---------------------------------------------------------------
; x pointer - passed in its destination register
; y pointer - passed in its destination register
; r pointer - passed in its destination register
; Set circular/linear ARx behavior                               
; ---------------------------------------------------------------


; ---------------------------------------------------------------
; Start of outer loop 
; for (i=0; iP<nx; i++)
;    R(i) = X(i) * X(i);
; ---------------------------------------------------------------
; ----------------------------------------------------
; AC0 = m40(rnd(AC1 + uns(*x_ptr+)) * uns(*y_ptr+))))
; ----------------------------------------------------

	SQRM	*x_ptr+, AC0			;zero out the ACC and the first mpy
	||RPT	CSR
	       SQAM	*x_ptr+, AC0		;vector MAC of two inputs

	MOV AC0, dbl(*AR1)  

; ADDED CODE TO CHECK THE OVERFLOW
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	||MOV #0, T0
	XCCPART overflow(AC0)
               ||MOV #1, T0 		; 


; ---------------------------------------------------------------
; Restore status regs to expected C-convention values as needed
; ---------------------------------------------------------------
; ----------------------------------------------------------------
; Restore any save-on-entry registers that are used
; ----------------------------------------------------------------
; - nothing to restore for this function
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
; ---------------------------------------------------------------
; Return to calling function
; ---------------------------------------------------------------
      RET					;return to calling function
    ||BCLR	FRCT				;clear FRCT

;----------------------------------------------------------------
;End of file

