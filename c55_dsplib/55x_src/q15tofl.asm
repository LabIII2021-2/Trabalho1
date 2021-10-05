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
; Function:	q15tofl
; Description: converts Q15 to IEEE floating point
;
; Usage:  ushort q15tofl(DATA *x, float *r, ushort nx);
;
; Notes:
;    The 32-bit single precision IEEE Floating Point is stored as follows:
;      Bit 31:      sign:  0 => positive, 1 => negative
;      Bits 23-30:  exponent: 2's complement from -128 to +127
;      Bits 0-22:   mantissa: 23-bits unsigned
;    The mantissa also includes an implied bit at bit 23 equal to 1 unless the exponent is 0.
;
; Benchmarks:
;   Cycles:       (15 * nx) + 15
;   Code Size (in bytes):  83
;
; History:
;    Craig Leeds 05/22/2012:
;       - Fixes bug where T3 was used and not restored
;       - Fixes bug where overflow flag bit was not cleared on entry
;       - Optimized by 50%
;****************************************************************

        .ARMS_on                      ;enable assembler for ARMS=0
        .CPL_on                       ;enable assembler for CPL=1
        .mmregs

;----------------------------------------------------------------
; Function definition:
;----------------------------------------------------------------

        .global        _q15tofl

        .text
_q15tofl:

;----------------------------------------------------------------
; Prologue: establish local frame, reset sign extension mode
;----------------------------------------------------------------

        BCLR    ACOV0                   ; clear overflow bit
        SUB     #1, T0
        MOV     T0, BRC0

;----------------------------------------------------------------
; Store function constants
;----------------------------------------------------------------

        MOV     #127, AR2               ; AR2 = 127
        MOV     #0x3fff << #16, AC3
        OR      #0xffff, AC3            ; AC3 = 0x3fffffff
        MOV     #0x7fff << #16, AC2     ; AC2 = 0x7fff0000
        
        MOV     *AR0+ << #16, AC0       ; (Prime the Pump)

;----------------------------------------------------------------
; Convert each element of vector A, to Q15 format
; Pre-Load first vector element
;----------------------------------------------------------------
        
        ||RPTBLOCAL end_loop-1
                CMP     AC0 == AC2, TC2                ; TC2 set if AC0_H == 0x7fff
                AND     #32768 << #16, AC0, AC1        ; AC1 = bit-31 of AC0 (i.e. sign bit)
                SFTL    AC1, #-31, AC1                 ; Put sign in LSB
             || MOV     HI(AC0), AR3
        
                XCCPART TC2 
                      ||MOV        #0, AC0
 
                ABS     AC0
             || SFTL    AC1, #31, AC1

;----------------------------------------------------------------
; Shift right by one, since exp and norm never count shift into
; upper most bit (bit 31)
;----------------------------------------------------------------

                SFTS    AC0, #-1                       ; 
                MANT    AC0, AC0
                ::NEXP  AC0, T1
                ADD     AR2, T1                        ; T1 += 127

;----------------------------------------------------------------
; Remove upper most bit as this becomes an implicit 1
; 2^exp * (1.f) where f is mantissa
;----------------------------------------------------------------

             || AND     AC3, AC0                       ; remove sign bit from AC0
                ADD     mmap(T1) << #(16+7), AC1
                SFTS    AC0, #-7, AC0                        ; 
                OR      AC1, AC0

		XCCPART AR3 == #0                      ; check for input value being zero
                     || MOV     #0, AC0
                     
                MOV     AC0, dbl(*AR1+)
             || MOV     *AR0+ << #16, AC0

end_loop:

;----------------------------------------------------------------
; Return to calling program.
;----------------------------------------------------------------
        
        MOV    #0, T0
        XCCPART overflow(AC0)
             || MOV     #1, T0

        RET        



