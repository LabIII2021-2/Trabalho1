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
; Function:	 iircas51
; Processor:   C55xx
; Description:  cascaded IIR direct form II using 5-coefs per biquad
;
; Usage:  short oflag = iircas51(DATA *x, DATA *h, DATA *r, DATA *dbuffer, 
;                                ushort nbiq, ushort nx)
;
; Benchmarks:
;   Cycles:       (nx * ((7 * nbiq) + 3)) + 37
;   Code Size (in bytes):  128
;
; History
; 2.40 Cleared XDP instead of DP register
;      Zhengting He - 10/25/2006
; 3.00 Clear AC0V0 on entry for overflow testing.  Optimize.
;      Craig Leeds - 05/29/2012
;*****************************************************************************
;
;
;	IIR Biquad Structure
;
;                          
;  x(n) ------.-----x-->+ -------> + -----.---------> y(n)
;             |    b0   |\        /|      |       
;           [z-1]       | |      | |    [z-1]     
;             |         | |      | |      |       
;             v         | |      | |      v       
;           x(n-1)--x---| |      | |--x-d(n-1)           
;             |    b1     |      |  -a1   |       
;             |           |      |        |       
;           [z-1]         |      |      [z-1]     
;             |           |      |        |       
;             v           |      |        v       
;           x(n-2)--x-----|      |---x--d(n-2)    
;                  b2              -a2            
;            
;                 "FF"             "FB"
;
;
;        "FB" = Feedback Terms
;        "FF" = Feedforward Terms
;
;
; Algorithm (for single biquad)
; -----------------------------
;  y(n)= b0*x(n) + b1*x(n-1) + b2*x(n-2) - a1*y(n-1) - a2*y(n-2)
; 
;
; Function Call
; -------------
;
;  short oflag = iircas51(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nbiq,
;                        ushort nx)
;
;   where:
; x[nx]: PASSED in XAR0.
;        Pointer to input vector of nx real elements.  
;        x(0) is the first input, 
;        while x(nx-1) is the last input.
;        
; h[5*nbiq]: PASSED in XAR1.
;        Pointer to filter coefficient vector with the following format:
;        H = b01 b11 b21 a11 a21 ....b0i b1i b2i a1i a2i
;         where i is the biquad index.
;         (i.e. a21: is the a2 coefficient of biquad 1). 
;         Pole (recursive) coefficients = a. 
;         Zero (non-recursive) coefficients = b
;
;        This array must be located in internal memory if it is 
;        accessed by the C55xx coefficient bus.
;
; r[nx]: PASSED in XAR2.
;        Pointer to output vector of nx real elements.  
;        In-place computation (r = x) is allowed.  r(0) is the first 
;        output, while r(nx-1) is the last output.
;
; dbuffer[1+4*nbiq]: PASSED in XAR3.
;        Pointer to delay buffer of length 4*nbiq.  See figure below for  
;        organization. In the case of multiple-buffering schemes, this 
;        array should be initialized to 0 for the first filter block only. 
;        Between consecutive blocks, the delay buffer preserves the 
;        previous elements needed.
;
;
; nbiq:  PASSED in T0.
;        The number of biquads making up the filter.  
;
; nx:    PASSED in T1.
;        Number of elements in the input and output vectors
;
; oflag: RETURNED in T0.
;        Overflow error flag  (returned value)
;         = 1 if a 32-bit data overflow occurred in an intermediate 
;             or final result.
;         = 0 if no such overflow occurred.
;
;
; Memory and Pointer Use Definition
; ---------------------------------
;
;              "x[nx]"                  "r[nx]"
;      AR0(x)--> x(0)            AR2(r)-->r(0)     first
;                x(1)                     r(1)
;                x(2)                     r(2)
;                 :                        :
;                 :                        :
;                x(nx-1)                  r(nx-1)  last
;
;
;      "dbuffer[4*nbiq]"            "h[5*nbiq]"
;                                 AR1(h)->b01
;      AR3(xn)-->x11                      b11 
;                x12                      b21
;                 :                       a11
;                x1n                      a21
;                x21                      b02
;                x22                      b12
;                 :                       b22
;                x2n                      a12
;      AR4(yn)-->y11                      a22
;                y12                       :
;                 :                       b0i
;                y1n                      b1i
;                y21                      b2i
;                y22                      a1i
;                 :                       a2i
;                y2n
;               
;
;      Def: xij/yij/aij/bij  where i = delay #
;                                  j = biquad #


	.arms_off
	.cpl_on
	.mmregs
        .noremark 5684   ; BRC1 not modified indirectly

;******************************************
;*       Assigns
;******************************************
	.def	_iircas51

;******************************************
;*       Constant Defines
;******************************************

;******************************************
;*       Variable Declarations
;******************************************

;**********************************************************************
; Program section
;**********************************************************************
	.text
_iircas51:
;Context save
;initialization

        PSH     T3, T2
     || BCLR    ARMS
        PSHBOTH XAR6
     || BSET    FRCT                   ;fractional mode enable
        PSHBOTH XAR7
     || BCLR    ACOV0                  ; clear overflow bit 
        BCLR    ACOV1                  ; clear overflow bit 

;setup circular addressing in AR6 and AR4
        MOV     T0, T3                 ;compute 2*nbiq
        SFTS    T3, #1
        MOV     T3, mmap(BK47)         ;init AR4-7 circular buf size (2*nbiq)
        AMAR    *AR3(1), XAR6          ; set AR6H (and skip over pointer)
        MOV     XAR6, XAR4             ;adjust AR4 to buffer start
        MOV     AR6, mmap(BSA67)       ;init AR6-7 circular start addr: dbuffer(1)
        
        ADD     T3, AR4
        MOV     AR4, mmap(BSA45)       ;init AR45 circ start addr: dbuffer(2*nbiq)
        BSET    AR4LC                  ;init AR4 = circular (dbuffer)
        BSET    AR6LC                  ;init AR6 = circular (dbuffer)

        SUB     #1, T1, T3             ;compute nx-1
        MOV     *AR3, AR6              ;init AR6 offset to x(n) buffer start
        MOV     T3, BRC0               ;init outer loop counter (nx-1)
        MOV     AR6, AR4               ;init AR4 offset to y(n) buffer start

        MOV     XAR1, XAR7             ;save original value to reinitialize coeff buffer pntr

        SUB     #1, T0, T3             ;init inner loop counter (#bi-quads-1)
        MOV     T3, BRC1

        ADD     #1, T0, T1             ;index for buffer reset

; Kernel
;  XAR0: x[] input
;  XAR1: h[] coefficients
;  XAR2: r[] result
;  XAR4: dbuffer[y]
;  XAR6: dbuffer[x]
;  XAR7: reinit XAR1

     || RPTBLOCAL OuterLoopEnd-1                          ;outer loop: process a new input
                MOV     *AR0+ << #16, AC1                 ; HI(AC1) = x(n)
                ||RPTBLOCAL     InnerLoopEnd-1            ;inner loop: process a bi-quad
                        NOP_16                            ; CPU_116: Remark 5682
                     || MPYM    *AR1+, AC1, AC0           ; AC0 = b0*x(n)
                        MACM    *AR1+, *(AR6+T0), AC0     ; AC0 += b1*x(n-1)
                        MACM    *AR1+, *AR6, AC0          ; AC0 += b2*x(n-2)
                        MOV     HI(AC1), *(AR6+T1)        ; x(n) replaces x(n-2) 
                        MASM    *AR1+, *(AR4+T0), AC0     ; AC0 -= a0*y(n-1) 
                        MASM    *AR1+, *AR4, AC0, AC1     ; AC1 -= a1*y(n-2) 
                        MOV     rnd(HI(AC1)), *(AR4+T1)   ; y(n) replaces y(n-2)
InnerLoopEnd:
                AMOV    AR7, AR1                          ;reinitialize coeff pointer 
             || MOV     rnd(HI(AC1)), *AR2+               ;store result to output buffer
OuterLoopEnd:

        MOV     AR4, *AR3                                 ; Update delay pointer

; Signal overflow
     || MOV     #0, T0
        XCCPART overflow(AC0)
            ||MOV  #1, T0
        XCCPART overflow(AC1)
            ||MOV  #1, T0

;Context restore
        POPBOTH XAR7
     || BCLR    AR6LC             ; restore for C
        POPBOTH XAR6
     || BCLR    AR4LC             ; restore for C
        POP     T3, T2
     || BSET    ARMS              ; restore for C
        RET        
     || BCLR    FRCT              ; restore for C
        
