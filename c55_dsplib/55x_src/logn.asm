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
; Function: log_n
; Description: Calculate natural log of 16-bit Q15 number
;
; Usage:  ushort logn(DATA *x, LDATA *r, ushort nx);
;
; Benchmarks:
;   Cycles:       (16 * nx) + 24
;   Code Size (in bytes):  117
;
; History
; 3.00.00 - Craig Leeds 05/17/2012
;   Fix bug where overflow flag is not cleared at startup.
;   Optimized by about 40%.
;********************************************************************************

        .mmregs                ; assign Memory-Mapped Register names as global symbols
        .ARMS_off
        .def                _logn

        .asg    #0x8000,  CST_8000
        .asg    #0xDC56,  LB6
        .asg    #0x54ad,  LB5
        .asg    #0x9e8a,  LB4
        .asg    #0x50d5,  LB3
        .asg    #0xc056,  LB2
        .asg    #0x3ffd,  LB1
        .asg    #0x062d,  LB0
        .asg    #0x58B9,  CST_ln2

        .text
        
_logn:            
        PSH     T3
     || BCLR    ARMS
        AADD    #-8, SP
     || BCLR    ACOV0
        MOV     XSP, XAR2
;initialization for Logarithm calculation  

        SUB     #1, T0
        MOV     T0, BRC0
        MOV     #(1-8), T1

        MOV     LB5, *AR2+           ; SP[0] = LB5
        MOV     CST_8000, *AR2+      ; SP[1] = CST_8000
        MOV     LB4, *AR2+           ; SP[2] = LB4
        MOV     LB6, *AR2+           ; SP[3] = LB6
        MOV     LB3, *AR2+           ; SP[4] = LB3
        MOV     LB2, *AR2+           ; SP[5] = LB2
        MOV     LB1, *AR2+           ; SP[6] = LB1
        MOV     CST_ln2, *(AR2+T1)   ; SP[7] = CST_ln2; AR2 = &SP[0]
        MOV     LB0, AC3             ; AC3 = LB0

     || RPTBLOCAL EndLoop - 1                
**************
* Normalize x
**************
                MOV     *AR0+ << #16, AC0    ;A = x << 16
                MANT    AC0, AC0
              ::NEXP    AC0, T0              ;T0 = negative number of leading bits
             || MOV     *AR2+ << #16, AC1    ;B5 load    *SP[0] = LB5

***************************
* Polynomial approximation 
***************************
   
                SFTS    AC0, #-15, AC0       ;A <- 2*M
                SUB     uns(*AR2+), AC0      ;A <- (2*M-1) Q15    *SP[1] = CST_8000
             || SUB     #1, T0               ;T0 <- P-1    
                MOV     AC0, T3              ;U <- (2*M-1) Q15 (between 0.0 and 1.0)
             || MOV     *AR2+ << #16, AC2    ;B4 load    *SP[2] = LB4
                MACMR   *AR2+, T3, AC1, AC0  ;A(32-16) <- B6*U + B5  *SP[3] = LB6
                                             ;Q34 + Q18 << 16 = Q34
                MOV     *AR2+ << #16, AC1    ;B3 load    *SP[4] = LB3
             || MACR    AC0, T3, AC2, AC0    ;A <- (B6*U + B5)*U + B4
                                             ;Q33 + Q17 << 16 = Q33
                MOV     *AR2+ << #16, AC1    ;B2 load    *SP[5] = LB2
             || MACR    AC0, T3, AC1, AC0    ;A <- ((B6*U+B5)*U+B4)*U+B3
                                             ;Q32 + Q16 << 16 = Q32
                MOV     *AR2+ << #16, AC1    ;B1 load    *SP[6] = LB1
             || MACR    AC0, T3, AC1, AC0    ;A <- (((B6*U+B5)*U+B4)*U+B3)*U+B2
                                             ;Q31 + Q15 << 16 = Q31
                MAC     AC0, T3, AC1, AC0    ;A <- ((((B6*U+B5)*U+B4)*U+B3)*U+B2)*U+B1
                                             ;Q30 + Q14 << 16 = Q30
                SFTS    AC0, #1                                
*******************
* Process exponent
*******************
             || MPYM    *(AR2+T1), T0, AC1   ;AC1 <- ln2 * (P-1); AR2 = &SP[0]     *SP[8] = CST_ln2,  AR2 = &SP[0]
                MAC     AC0, T3, AC3, AC0    ; A <- (((((B6*U + B5)*U + B4)*U + B3)*U + B2)*U + B1)*U + B0   *SP[7] = LB0
                                             ;Q30 + Q30 = Q30
*************************
* Add both contributions
*************************
                ADD     AC0 << #-15, AC1     ; AC0 = <- f(2*M(x)-1) + (P(x)-1)*ln(2)
                MOV     AC1, dbl(*AR1+)
EndLoop:

************************
* Return overflow flag
************************

        AADD    #+8, SP

     || MOV     #0, T0
        XCCPART overflow(AC0)
              ||MOV     #1, T0

        POP     T3
     || BSET    ARMS
        RET

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
 
        
        


