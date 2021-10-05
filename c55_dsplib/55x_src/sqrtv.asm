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
;***************************************************************
; Function :	sqrtv
; Processor:	C55x
; Description:   Square root of a 16-bit number
;		C-callable
;
; Usage: ushort sqrt_16(DATA *x, DATA *r, short nx);
;
; Benchmarks:
;   Cycles:       (22 * nx) + 24
;   Code Size:
;        .text     99 bytes
;        .const    32 bytes
;
; History:
;		- Li Yuan 01/30/2002
; 		  fixed the bug where NX should be stored in register T0 instead of AR2.
; 		  fixed code to work in large block memory by correct XAR loading.
; 3.00.00 - Craig Leeds 05/17/2012
;   Fixed bug where overflow flag is not cleared at startup.
;   Fixed bug in rounding method
;   Optimized by 40%.
;       
;****************************************************************

        .noremark  5684
        .mmregs 

; assign registers and set status bits
;-------------------------------------
        .asg AR0, AR_X                ;input vector
        .asg AR1, AR_R                ;output vector
        .asg AR4, AR_TBL
        .asg XAR4, XAR_TBL


        .asg 0, SP_TEMP
        
; Square root lookup table
;-------------------------------------------------
; Ytable = 1/sqrt(2^n) values:
;
           .sect ".const"
        .def SqrtTable
        .align
SqrtTable:                        
        .word        7FFFh                ; 1/sqrt(2^0)  = 0.99997 
        .word        5A82h                ; 1/sqrt(2^1)  = 0.70711 
        .word        4000h                ; 1/sqrt(2^2)  = 0.50000 
        .word        2D41h                ; 1/sqrt(2^3)  = 0.35355 
        .word        2000h                ; 1/sqrt(2^4)  = 0.25000 
        .word        16A1h                ; 1/sqrt(2^5)  = 0.17678
        .word        1000h                ; 1/sqrt(2^6)  = 0.12500 
        .word        0B50h                ; 1/sqrt(2^7)  = 0.08839
        .word        0800h                ; 1/sqrt(2^8)  = 0.06250 
        .word        05A8h                ; 1/sqrt(2^9)  = 0.04419 
        .word        0400h                ; 1/sqrt(2^10) = 0.03125 
        .word        02D4h                ; 1/sqrt(2^11) = 0.02210 
        .word        0200h                ; 1/sqrt(2^12) = 0.01563 
        .word        016Ah                ; 1/sqrt(2^13) = 0.01105 
        .word        0100h                ; 1/sqrt(2^14) = 0.00781 
        .word        0000h        
        
        
        .def    _sqrt_16
        .text
_sqrt_16:

        AADD    #-1, SP
     || BCLR    ACOV0
        BCLR    ACOV1

; N=N-1
;------
                                
        SUB     #1, T0               ;no: of inputs-1
        MOV     T0, BRC0             ;Block repeat counter set to no: of inputs-1

; Set Number Of Iterations of Sqrt Algorithm (N=5)
;------------------------------------------------
        MOV     #5-1, BRC1           ;inner loop counter set to no: of iterations-1
        
; Initialize constants
;---------------------
                                                   
        MOV     #0, BK03
        AMOV    #SqrtTable, XAR4     ;initialize square root lookup table XAR_TBL
        MOV     AR4,mmap(BSA45)
        BSET    AR4LC                ; Set up AR4 as a circular buffer
        MOV     #0x05E00, T1
        AMAR    *SP(SP_TEMP), XAR2
        MOV     #0x1 << #15, AC2     ; value to round the input
        ADD     *AR_X+ << #16, AC2, AC3  ;load the input to AC3, shift left by 16 bits (with round) (Prime the Pump)
      
     || RPTBLOCAL OuterLoopEnd-1                 

; Get next input value in array, x
; and round input value by adding 0x8000
;----------------------------------------------------------------

                ;;;ADD     *AR_X+ << #16, AC2, AC3        ;load the input to AC3, shift left by 16 bits (with round)
         
; Normalize input value
;----------------------
        
                MANT    AC3, AC3
                ::NEXP  AC3, T0                        ;normalize the input

             || MOV     T1, *AR2                       ; Initial value for Ynorm = 0x5e00

; Use lookup table to find SQRT of exponent
; lookup table index == exponent
;------------------------------------------
                NEG     T0, AR_TBL                     ;add the exponent to AR_TBL
             || SFTS    AC3, #-16, AC3
                MOV     T1, HI(AC0)                    ; Initial value for Ynorm = 0x5e00
             || SFTS    AC3, #15, AC3

; Load normalized estimate of square root
; Ynorm(new) = Ynorm(old) - (Ynorm(old)^2 - Xnorm)/2
;---------------------------------------------------
        
                MOV     AC3, AC1   
              ||RPTBLOCAL InnerLoopEnd-1               ; do 5 iterations
                        NOP_16                         ; added to avoid Remark 5682
                     || SQS     AC0, AC1
                        ADD     *AR2 << #16, AC1, AC0
                        MOV     HI(AC0), *AR2         
                     || MOV     AC3, AC1   
InnerLoopEnd:                                          ;inner loop ends here

; Multiply sqrt(Ynorm) * sqrt(normalized_exponent)
; And round the result
;-------------------------------------------------

                MPYM    *AR_TBL, AC0  
                MOV     RND(HI(AC0<<#1)), *AR_R+       ; Store result in AR_R
             || ADD     *AR_X+ << #16, AC2, AC3        ;load the input to AC3, shift left by 16 bits (with round) (for next iteration)
OuterLoopEnd:                                          ;outer loop ends here
        
;Return overflow flag
;---------------------
        MOV     #0, T0
        XCCPART overflow(AC0)
              ||MOV     #1, T0
        XCCPART overflow(AC1)
              ||MOV     #1, T0

; Pop off registers and restore c environment
;--------------------------------------------
        AADD    #+1, SP
        
;Return to calling function
;---------------------------        
        BCLR    AR4LC
     || RET
        


