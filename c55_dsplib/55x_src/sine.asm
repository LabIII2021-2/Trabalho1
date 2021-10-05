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
; Function:    sine
; Processor:   C55x
; Description: Sine vector generation using polynomial evaluation.
;              C-callable
;
; Usage:  ushort sine(DATA *x, DATA *r, ushort nx);
;
; Benchmarks:
;   Cycles:       (11 * nx) + 20
;   Code Size (in bytes):     96
;
; History
;  07/07/2003 - d. elam fixed bug in q4.12 -> q1.15 conversion
;  3.00.00 - Craig Leeds 05/17/2012
;    Fix bug where overflow flag is not cleared at startup.
;    Optimized.
;****************************************************************

        .def        _sine
        
         .CPL_on
         .mmregs
        .asg        AR0, ar_x                    ;input vector
        .asg        AR1, ar_r                    ;output vector        

;****************************************************************
        
        .word        0x1CCE                        ;1.800293        (coeff for x^5 = c5)
        
        .text
_sine:

; Set status registers and get arguments 
; --------------------------------------
        
        PSH     T3, T2
     || BSET    FRCT                ;set FRCT
        BSET    SATD
        BCLR    ACOV0               ; clear overflow bit

        SUB     #1, T0              ;no: of inputs(AR2) - 1
        MOV     T0, BRC0            ;block repeat counter set to inputs -1
        MOV     #0xAACC << #16,AC2  ;AC2.Hi = -5.325196   (coeff for x^3 = c3)
        MOV     #0x0053, T0         ;T0 = 0.02026367      (coeff for x^2 = c2)
        MOV     #0x3240, T1         ;T1 = 3.140625        (coeff for x^1 = c1)
        
        MOV     #0x08B7 << #16, AC3 ; AC3.Hi = 0.5446778  (coeff for x^4 = c4)
        MOV     #0x1CCE, AR2        ; AR2 = 1.800293        (coeff for x^5 = c5)
        MOV     #0x7fff, AR3        ; AR3 = 0x7fff
        
        MOV     *ar_x+, T3          ; T3 = x[0] (Prime the Pump)
        MOV     #3, T2              ; T2 = 3
        ROL     TC2, T3, TC2, AR4   ; TC2 contains sign bit (Prime the Pump)
        
     || RPTBLOCAL LoopEnd-1

; If angle in 2nd and 4th quadrant then negate the result before removing
; sign bit
; -----------------------------------------------------------------------

                ROL     CARRY, AR4, CARRY, AR4  ; CARRY contains bit-14

                XCCPART CARRY                   ;if bit 14 is 1, negate and it in T3 
                      ||NEG     T3              ;T3 = -x
                      
                AND    AR3, T3                  ;T3 = x, remove sign bit from -x

; Start polynomial evaluation
; ---------------------------

             || MOV     AR2, HI(AC0)            ; AC0.Hi = c5
                MACR    AC0, T3, AC3, AC0
                MACR    AC0, T3, AC2, AC0       ; Note: AC2.Hi = c3
             || MOV     T0, HI(AC1)             ; AC1.Hi = c2
                MACR    AC0, T3, AC1, AC0
             || MOV     T1, HI(AC1)             ; AC1.Hi = c1
                MACR    AC0, T3, AC1, AC0
                MPYR    T3, AC0, AC0
             || MOV     *ar_x+, T3              ; T3 = x[i+1] (for next iteration) 
;changing the result from q4.12 to q1.15 format
; ---------------------------------------------                

; If angle in 3rd and 4th quadrant (negative angle), negate the result
; ---------------------------------------------------------------------

                XCCPART TC2
                      ||NEG     AC0
                MOV     HI(saturate(AC0 << T2)), *ar_r+
             || ROL     TC2, T3, TC2, AR4       ; TC2 contains sign bit (for next iteration)
LoopEnd:

; Return overflow flag
; --------------------

        MOV     #0, T0        
        XCCPART overflow(AC0)        ;clears ACOV0
             || MOV     #1, T0       ;overflow occured

; POP registers off stack and restore c environment
;--------------------------------------------------
        POP     T3, T2
     || BCLR    FRCT

        RET
     || BCLR    SATD

