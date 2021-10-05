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
;  Function:	expn
;  Description: exponent vector evaluation via polynomial approximation
;
;  Usage:  ushort expn(DATA *x, DATA *r, ushort nx);
;
; Benchmarks:
;   Cycles:       (7 * nx) + 15
;   Code Size (in bytes): 
;        .text:     60
;        .const:    12
;
;  History
;        Zhengting He - 10/25/2006
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;
;        Craig Leeds  - 05/17/2012
;   Fix alignment of expn_coeffs.
;   Move expn_coeffs from .data to .const
;   Clear AC0 overflow bit on entry.
;   Optimized.
;********************************************************************************

	.mmregs

; Table containing the coefficients for the polynomial


	.sect ".const"
	.align			; 
expn_coeffs:			; hex values in q4.12
	.word	0x0039	;0.0139		(coef for x^5 = c5)
	.word	0x008f	;0.0348		(coef for x^4 = c4)
	.word	0x02ba	;0.1705		(coef for x^3 = c3)
	.word	0x07fc	;0.4990		(coef for x^2 = c2)
	.word	0x1000	;1.0001		(coef for x^1 = c1)
	.word	0x1000	;1.0000		(coef for x^0 = c0)


;****************************************************************
	.global	_expn
	.text

; Get arguments and set modes
; ---------------------------

_expn:
	SUB	#1, T0			;b = n-1
	MOV	T0, mmap(BRC0)		;BRC = n-1

	BSET	FRCT			;set FRCT on
	BSET	SATD			
;;;	BSET	SXMD	                ; (Not necessary since it's required on entry by C)
	BCLR	ACOV0			; clear overflow bit 
	AMAR	*(#expn_coeffs), XAR4	;pointer to coeff table
        MOV     #-5, T0
	MOV	*AR0+, T1		;t = x(sign-extended) (Prime the Pump)

	||RPTBLOCAL	loop-1 			;repeat n times

; Start polynomial evaluation
; ---------------------------

; this should be moved out from the loop and rewound
; back to beginning by t1 register. It is not possible yet with beta tools.


	        MOV	dbl(*AR4+), pair(HI(AC0))

	        MOV	*AR4+ << #16, AC1
	      ||MACR	AC0, T1, AC1, AC0	;a = ah*t + b
					        ;  = c5*x + c4
					        ;bh = c3  point to c2

	        MOV	*AR4+ << #16, AC1	
	      ||MACR	AC0, T1, AC1, AC0	;a = ah*t + b
					        ;  = (c5*x + c4)*x + c3
					        ;  =  c5*x^2 + c4*x + c3
					        ; bh = c2	point to c1

	        MOV	*AR4+ << #16, AC1	
	      ||MACR	AC0, T1, AC1, AC0	;a = ah*t + b
					        ;   = (c5*x^2+c4*x+c3)*x + c2
					        ;   = c5*x^3+c4*x^2+c3*x + c2
					        ; bh = c1	point to c0

	        MOV	*(AR4+T0) << #16, AC1	
	      ||MACR	AC0, T1, AC1, AC0	;a = ah*t + b
					        ;   = (c5*x^3+c4*x^2+c3*x + c2)*x + c1
					        ;   = c5*x^4+c4*x^3+c3*x^2+c2*x +c1
					        ; bh = c0	point to c(-1)
        
	        MAC	AC0, T1, AC1, AC0	; a = ah*t + b				
					        ;   = (c5*x^4+c4*x^3+c3*x^2 + c2*x+c1)*x + c0
					        ;   = c5*x^5+c4*x^4+c3*x^3+c2*x^2 +c1*x + c0
        
        
	        MOV	HI(AC0), *AR1+		;store q4.12 output
	      ||MOV	*AR0+, T1		;t = x(sign-extended) (for next iteration)
loop:

; Return overflow flag
; --------------------
; bug: original code put return value in AC0
; fix: put to T0
	MOV	#0, T0
	||BCLR	FRCT
	XCCPART	overflow(AC0)
	     ||MOV    #1, T0

	BCLR	SATD
	||RET
;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor	
