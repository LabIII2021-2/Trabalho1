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
;****************************************************************
; Function:    atan2_16
; Processor:   C55xx
; Description: arctangent 2 implementation
; Usage:    short atan2( DATA *x2, DATA *x1, DATA *r, int *nx)
;   r[i]=arctangent(x1[i]/x2[i]) Q15 format
;   nx=number of elements in x1,x2,r
;   x1,x2 input
;   r result
;   return 0 if ok; 1 if error
;   
; Benchmarks:
;   Cycles:       (nx * 39) + 21
;   Code Size (in bytes):  168
;
;  History:
;    Craig Leeds 05/25/2012:  Optimized by 40%; removed .data
;****************************************************************
        .mmregs
        .cpl_on
        .arms_on

        .def    _atan2_16


********************************************************************************

;;;        .sect ".const"    
;;;atancoeffs:
;;;        .word 0xfda8 ; C5 -0.009159*2*32767.999*x^5
;;;        .word 0x118b ; C4 +0.068542*2*32767.999*x^4
;;;        .word 0xde7c ; C3 -0.130908*2*32767.999*x^3    
;;;        .word 0x00d9 ; C2 +0.003314*2*32767.999*x^2
;;;        .word 0x5179 ; C1 +0.318253*2*32767.999*x^1
;;;;;;     .word 0x0000 ; C0 0*x^0


; LOCAL VARIABLE
;* AR0   assigned to _x
;* AR1   assigned to _y
;* AR2   assigned to _r
;* T0   assigned to _nx
        
        .text
_atan2_16:
        PSH     T3, T2
     || BSET    FRCT                    ;fractional mode set
        PSH     AR5, AR6                ; Note: doesn't use AR5H and AR6H
     || BSET    SATD                    ;saturation mode on
        SUB     #1, T0                  ;nx - 1
        MOV     T0, BRC0                ;repeat nx times
        MOV     #2-1, BRC1
        MOV     #0xfda8, T3             ; T3  = C5 -0.009159*2*32767.999*x^5
        MOV     #0x118b, AR3            ; AR3 = C4 +0.068542*2*32767.999*x^4
        MOV     #0xde7c, AR4            ; AR4 = C3 -0.130908*2*32767.999*x^3    
        MOV     #0x00d9, AR5            ; AR5 = C2 +0.003314*2*32767.999*x^2
        MOV     #0x5179, AR6            ; AR6 = C1 +0.318253*2*32767.999*x^1

     || RPTBLOCAL OuterLoopEnd-1
                MOV     *AR0 << #16, AC0
             || MOV     *AR1 << #16, AC1
                ABS     AC0
             || BCLR    TC1
                MOV     HI(AC0), T2
             || ABS     AC1
                MAX     AC1, AC0

                XCCPART   CARRY
                      ||BSET    TC1

                XCCPART CARRY
                      ||MOV     HI(AC1), T2

                MANT    AC0, AC1
              ::NEXP    AC0, T1

*****************************************************************************
; INPUT VALUE IN AC1,T1,T2
; RETURN AC1
; USE: AC0,AC1
; FRCT = 1
                SFTS    AC1, #-1, AC2
                XOR     #1FFFh << #16, AC2
              ||MOV     HI(AC1), T0

; COMPUTE 2^28/X
; Calculate Ym = 2*Ym - Ym^2*X
                RPTBLOCAL InnerLoopEnd-1
; Ym: AC2_h ; X: T0
                        MPY     T0, AC2, AC3
                     || SFTS    AC2, #-1, AC0
                        MPY     AC2, AC3
                        SUB     AC3, AC0
                        SFTS    AC0, #2, AC2
InnerLoopEnd:

; LAST ITERATION
                MPY     T0, AC2, AC3
             || SFTS    AC0, #1
                MPY     AC2, AC3
             || NEG     T1
                SUB     AC3, AC0

                MPY     T2, AC0, AC2
                SFTS    AC2, #3, AC2
                SFTL    AC2, T1, AC2

                SFTS    AC2, #1
             || MOV     T3, HI(AC0)        ; C5
                MOV     HI(AC2), T0
             || MOV     AR3, HI(AC1)       ; C4
                MACR    AC0, T0, AC1, AC0
             || MOV     AR4, HI(AC1)       ; C3
                MACR    AC0, T0, AC1, AC0
             || MOV     AR5, HI(AC1)       ; C2
                MACR    AC0, T0, AC1, AC0
             || MOV     AR6, HI(AC1)       ; C1
                MACR    AC0, T0, AC1, AC0
                MPYR    T0, AC0
                SFTS    AC0, #-1

*****************************************************************************
             || BTST    #15, *AR0+, TC2
                XCCPART !TC1
                      ||SUB        #16384 << #16, AC0
                XCCPART !TC1
                      ||NEG        AC0

                BTST    #15, *AR1+, TC1
                XCCPART        TC2
                     || SUB        #32767 << #16, AC0
                XCCPART        TC1 ^ TC2
                     || NEG        AC0
                MOV     HI(AC0), *AR2+        
OuterLoopEnd:

        POP     AR5, AR6
      ||BCLR    FRCT                        ;fractional mode reset
        POP     T3, T2
      || BCLR   SATD                        ;saturation mode off
        MOV     #0, T0                      ;returned value
      ||RET

;*************************************************

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor


        

