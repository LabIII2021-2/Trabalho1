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
; Function:    NEG
; Processor:   C55xx
; Description: Implements 2's complement of an input vector.
;              This routine is C-callable.
;
; Algorithm:   for(i=0, i<nx, i++)
;	             x(i) = - x(i); 
;
; Usage: ushort oflag =  neg (DATA *x,
;                              DATA *r,
;                               ushort nx)
;
;
; Benchmarks:
;   Cycles:       (1 * nx) + 12
;   Code Size (in bytes):  26
;
;        Craig Leeds  - 05/17/2012
;   AR1 no longer set to a circular buffer.
;   Optimized both loop and housekeeping.
;****************************************************************

	.ARMS_off		;enable assembler for ARMS=0
	.CPL_on			;enable assembler for CPL=1
	.mmregs			;enable mem mapped register names

; ---------------------------------------------------------------
; Stack Frame Setup
; ---------------------------------------------------------------

RET_ADDR_SZ	.set 1		;return address
REG_SAVE_SZ	.set 0		;save-on-entry registers saved
FRAME_SZ	.set 0		;local variables
ARG_BLK_SZ	.set 0		;argument block

PARAM_OFFSET	.set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ

; ---------------------------------------------------------------
; Register usage and definitions
; ---------------------------------------------------------------
	.asg	AR0, x_ptr	;linear pointer for first input vector
	.asg	AR1, r_ptr	;linear pointer for result vector

	.asg	BRC0, outer_cnt	;outer loop count
	.asg	T0, oflag	;returned value

	.def _neg
	.text
_neg:
	SUB	#1, T0			;T0=nx-1
	MOV	T0, CSR
 	MOV	#0, AC1
	||BCLR	ACOV0
	MOV	#0, oflag		;clear oflag
	SUB	*x_ptr+ << #16, AC1, AC0	; (Prime the Pump)
 	||RPT	CSR
 		MOV	HI(AC0), *r_ptr+
		||SUB	*x_ptr+ << #16, AC1, AC0
		
	XCCPART	overflow(AC0)	;clears AC0V0
		||MOV 	#1, oflag		;overflow occured

	RET				;return to calling function

;----------------------------------------------------------------
;End of file

