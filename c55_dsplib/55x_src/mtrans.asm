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
; Function:	mtrans
; Description: matrix multiply implementation
; Usage: short mtrans(	DATA *x1,	AR0
;			short row1,	T0
;			short col1,	T1
;			DATA *r);	AR1
;
;          Always returns 0 in T0
;
; Benchmarks:
;   Cycles:       (row1 * (col1 + 1)) + 19
;   Code Size (in bytes):  56
;
; History:
;   05/26/12  Craig Leeds:   
;          - Fixed bug where T2 was modified but not restored
;          - Optimized 
;****************************************************************
	.mmregs
	.def _mtrans
				;XAR0 = x1
				;T0 = row1
				;T1 = col1
				;XAR1 = r
	
	.text
_mtrans:
        MOV     T0, HI(AC0)
     || BSET    AR0LC
        MPY     T1, AC0, AC1                ;AC1 = row1*col1
     || MOV     XAR1, XAR2                  ;XAR2 = r to ensure MDP

        MOV     AR0, mmap(@BSA01)           ;BSA01 = x1
        MOV     AR1, mmap(@BSA23)           ;BSA23 = r
        MOV     AC1, mmap(@BK03)            ;init block size
        BSET    AR2LC
        SUB     #1, T0, AR3
        MOV     AR3, BRC0                   ;outer loop BRC0 = row-1 (Note; for CPU_117, this must be > 2 cycles prior to RPTBLOCAL)
        SUB     #1, T1, AR3
        MOV     AR3, CSR                    ;inner loop CSR = col-1
        AMOV    #0, AR2                     ;AR2 = 0
        AMOV    #0, AR0                     ;AR0 = 0
        AMAR    *AR2-                       ;  next col of r        
	
     || RPTBLOCAL  EndLoop-1                ;for every row of x1
                AMAR    *AR2+               ;  next col of r        
             || RPT     CSR                 ;  for every col of x1
                        MOV     *AR0+, *(AR2+T0)
EndLoop:

        BCLR    AR0LC                       ; restore AR0 to linear for C
     || MOV     #0, T0                      ; return value is OK
        BCLR    AR2LC                       ; restore AR2 to linear for C
     || RET

