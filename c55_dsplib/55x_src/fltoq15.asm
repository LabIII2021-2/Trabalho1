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
; Function:	fltoq15
; Processor:   C55xx
; Description: convert IEEE floating point to Q15"
;
; Usage:  ushort fltoq15(float *x, DATA *r, ushort nx);
; 
; Notes:
;   The 32-bit single precision IEEE Floating Point is stored as follows:
;     Bit 31:      sign:  0 => positive, 1 => negative
;     Bits 23-30:  exponent: 2's complement from -128 to +127
;     Bits 0-22:   mantissa: 23-bits unsigned
;   The mantissa also includes an implied bit at bit 23 equal to 1 unless the exponent is 0.
;
; Benchmarks:
;   Cycles:       (23 * nx) + 16
;   Code Size (in bytes):  101
;
; History:
;   T2 registered is pushed and poped.
;    Zhengting He 10/25/2006
; 
;   Error conditions now correctly reported.
;   Optimized by 50%
;     Craig Leeds 05/25/2012
;
;****************************************************************



        .ARMS_on                      ;enable assembler for ARMS=1
        .CPL_on                       ;enable assembler for CPL=1
        .mmregs

;----------------------------------------------------------------
; local stack variables:
;----------------------------------------------------------------

;----------------------------------------------------------------
; Function definition:
;----------------------------------------------------------------

        .global        _fltoq15
        .text

_fltoq15:

;----------------------------------------------------------------
; Prolog: establish local frame, reset sign extension mode
;----------------------------------------------------------------
        MOV     #32768 << #16, AC3                ; (Note: this must be done before SXMD is cleared!)
        BCLR    SXMD
     || PSH     T2, T3

;----------------------------------------------------------------
; Process function arguments
;----------------------------------------------------------------
        SUB     #1, T0
     || NOT     AC3                               ; AC3 = 0x007fffffff
        MOV     T0, BRC0
;----------------------------------------------------------------
; Store function constants
;----------------------------------------------------------------
        MOV     #127, T3                          ; T3 = 127
        MOV     #0, T0                            ; clear error flag
     || BSET    TC2                               ; so that BCC ...,TC2 will always be True inside repeat block
        MOV     #32767, AR4                       ; AR4 = 32767
        MOV     dbl(*AR0+), AC0
        
;----------------------------------------------------------------
; Convert each element of vector A, to Q15 format
; Pre-Load first vector element
;----------------------------------------------------------------

        ||RPTBLOCAL end_loop-1

                MOV     HI(AC0), AR3
             || AND     AC3, AC0
                AND     #0x7f80 << #16, AC0, AC1
                SFTL    AC1, #-(7+16), AC1      
                SUB     T3, AC1                   ; -= 127
                MOV     AC1, T2
             || BCC     store_result, AC0 == #0   ; Branch if value is zero, then AC0 is already zero

                ABS     AC1, AC2
             || SFTS    AC0, #-7
                SUB     #15, AC2
                MOV     mmap(AC0_L) << #-1, AC0  
                BSET    #15, AC0                 ; |= 0x8000
                SFTS    AC0, T2
             || BCC     not_too_large, AC1 < #0
                
;----------------------------------------------------------------
; If unbiased exponent is >= 0, then value is too large to
; represent in Q15 format
;----------------------------------------------------------------
                MOV     AR4, AC0                 ; AC0 = 0x7fff
             || OR      #1, T0                   ; error flag
                XCCPART AR3 < #0
                     || ADD     #1, AC0
                BCC     store_result, TC2        ; branch always taken since TC2 is 1
                
not_too_large:
                
;----------------------------------------------------------------
; If exponent (abs) exp > abs(min_exp) then value is too small
; to represent in Q15 format. (min_exp = -15, since 2^-15 is
; least significant bit of Q15 number
;----------------------------------------------------------------

;----------------------------------------------------------------
; Shift floating point mantissa to keep only the most significant
; 15 bits. The implied 1 of the IEEE floating point format is ORed
; in as most significant bit.
;----------------------------------------------------------------

                XCCPART AR3 < #0
                     || NEG     AC0

		XCCPART AC2 > #0                         ; check if too small
                        OR      #2, T0                   ; error flag: too small
                     || MOV     #0, AC0                  ; error: too small
store_result:
                MOV     AC0, *AR1+
              ||MOV     dbl(*AR0+), AC0
end_loop:

;----------------------------------------------------------------
; Return to calling program. Set error conditions on return"
;----------------------------------------------------------------"

        POP     T2, T3
     || BSET    SXMD
        RET
;----------------------------------------------------------------
;End of file
