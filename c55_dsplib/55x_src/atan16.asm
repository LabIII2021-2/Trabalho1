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
; Function:    atan16
; Processor:   C55xx
; Description: Arctangent implementation
; Usage:   short atan16( DATA *x, DATA *r, int nx)
;   nx : number of element of x and r
;   r[i]=atan(x[i]) with x and r in Q15 format
;   return 0
;
; Benchmarks:
;   Cycles:   (5 * nx) + 14
;   Code Size (in bytes):  49
;
; History:
;   05/25/2012 Craig Leeds:  .data removed; Optimized by 30%.
;   03/20/2013 Craig Leeds:  Optimized by 17%
;****************************************************************

	.mmregs
	.cpl_on
	.arms_on

	.def	_atan16

        .text
_atan16:
;* AR0   assigned to _x
;* AR1   assigned to _r
;* T0   assigned to _nx
        PSH     T3
     || BSET	FRCT			;fractional mode
	SUB	#1, T0			;nx-1
	MOV	T0, BRC0		;repeat nx times
        MOV     #2596 << #16, AC3       ; AC3.Hi = C5
        MOV	#-9464 << #16, AC1	; AC1.Hi = C3
	MOV	#32617 << #16, AC2	; AC2.Hi = C1
*
* Note: loading T3 on the instruction before a multiply that uses it will
* cause a 1-cycle delay.
*
	MPYMR	T3=*AR0+, AC3, AC0      ; (Prime the Pump)
	
     || RPTBLOCAL	loop1-1
	        MACR	AC0, T3, AC1, AC0
	        MPYR	T3, AC0
	      ||MOV	*AR0+, T1               ; (for next iteration)
	        MACR	AC0, T3, AC2, AC0
	        MPYR	T3, AC0
              ||MOV	T1, T3
	        MOV	HI(AC0), *AR1+		;save result
	      ||MPYR	T1, AC3, AC0            ; (for next iteration)
loop1:

        POP     T3
     || BCLR	FRCT			;return to standard C
	MOV	#0, T0			;return OK value (no possible error)
     || RET

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
