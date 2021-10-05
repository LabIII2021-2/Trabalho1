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
; Function:	 iircas5
; Processor:   C55xx
; Description:  cascaded IIR direct form II using 5-coefs per biquad
;
;  Usage: short oflag = iircas5(DATA *x, DATA *h, DATA *r, DATA *dbuffer, 
;                              ushort nbiq, ushort nx)
;
; Benchmarks:
;   Cycles:       (nx * ((6 * nbiq) + 2)) + 28
;   Code Size (in bytes):  87
;
; History
; 2.40 Cleared XDP instead of DP register
;      Zhengting He - 10/25/2006
;
; 3.00 Clear ACOV0 on entry.  Optimize outer loop
;      Craig Leeds - 5/29/2012
;*****************************************************************************
;
;
;	IIR Biquad Structure
;
;                  d(n)         
;  x(n) ---> + -----.-----x-- + --> y(n)
;           /|      |    b0   |\
;          | |    [z-1]       | |
;          | |      |         | |
;          | |      v         | | 
;          | |--x-d(n-1)--x---| |         
;          |  -a1   |    b1     | 
;          |        |           |
;          |      [z-1]         |
;          |        |           |
;          |        v           |
;          |---x--d(n-2)--x-----|
;            -a2         b2 
;
;              "FB"   "FF"
;
;
;        "FB" = Feedback Terms
;        "FF" = Feedforward Terms
;
;
; Algorithm (for single biquad)
; -----------------------------
;  d(n) = x(n) - a1*d(n-1) - a2*d(n-2)
;  y(n) = b0*d(n) + b1*d(n-1) + b2*d(n-2)
; 
;
; Function Call
; -------------
;
;  short oflag = iircas5(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nbiq,
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
;        H = a11 a21 b21 b01 b11 ....a1i a2i b2i b0i b1i
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
; dbuffer[2*nbiq]: PASSED in XAR3.
;        Pointer to delay buffer of length 2*nbiq.  See figure below for  
;        organization. In the case of multiple-buffering schemes, this 
;        array should be initialized to 0 for the first filter block only. 
;        Between consecutive blocks, the delay buffer preserves the 
;        previous elements needed.
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
;      "dbuffer[2*nbiq]"            "h[5*nbiq]"
;                                 AR1(h)->a11
;      AR3(dn)-->d11                      a21 
;                d12                      b21
;                 :                       b01
;                d1n                      b11
;                d21                      a12
;                d22                      a22
;                 :                       b22
;                d2n                      b02
;                                         b12
;                                          :
;                                         a1i
;                                         a2i
;                                         b2i
;                                         b0i
;                                         b1i
;
;      Def: dij / aij / bij  where i = delay #
;                                  j = biquad #


	.arms_on
	.cpl_on
	.mmregs
        .noremark 5684    ; CPU_116: No indirect write to BRC1
;******************************************
;*       Assigns
;******************************************
	.def	_iircas5

;******************************************
;*       Constant Defines
;******************************************
SCALE	.set	0

;******************************************
;*       Variable Declarations
;******************************************

;**********************************************************************
; Program section
;**********************************************************************
	.text
_iircas5:
;Context save
        PSH     T2,T3
;Initialization
     || BSET    FRCT               ;fractional mode enable
        BCLR    ACOV0              ; clear overflow bit 
    
; Setup circular addressing
        AMAR    *AR3(1), XAR4      ; point AR4 to beginning of dbuffer data &dbuffer[1]
        MOV     T0, T3             ;compute 2*nbiq
        SFTS    T3, #1
        MOV     T3, mmap(BK47)     ;init AR7-7 circular buf size (2*nbiq)

        MOV     AR4, mmap(BSA45)   ;init AR4-5 circular start addr: dbuffer(0)

        BSET    AR4LC              ;init AR4 = circular (dbuffer)
        MOV     *AR3, AR4               
     || SUB     #1, T1             ;compute nx-1
        MOV     T1, BRC0           ;init outer loop counter (nx-1)                

        MOV     AR1, T2            ;save original value to reinitialize coeff buffer pntr
        
        SUB     #1, T0, T3         ;init inner loop counter (#bi-quads-1)
        MOV     T3, BRC1   

        
; Kernel
;  XAR0: x[] input
;  XAR1: h[] coefficients
;  XAR2: r[] result
;  XAR4: dbuffer[0]  (pointer to index)
;  XAR4: dbuffer[]  (circular)
;  T2:   reinit XAR1

        RPTBLOCAL OuterLoopEnd-1                  ; Outer Loop: Process a new input
                MOV     *AR0+ << #16, AC0         ; HI(AC0) = x(n)
              ||RPTBLOCAL InnerLoopEnd-1                  ; Inner Loop: Process a bi-quad
                        MASM    *(AR4+T0), *AR1+, AC0     ; AC0 -= a1*d(n-1)      (1) 
                        MASM    T3 = *AR4, *AR1+, AC0     ; AC0 -= a2*d(n-2)      (2)
                        MOV     HI(AC0), T1
                     || MOV     HI(AC0), *(AR4+T0)        ; d(n) replaces d(n-2)
                        MPYM    *AR1+, T3, AC0            ; AC0 = b2*d(n-2)       (3)
                        MACM    *AR1+, T1, AC0            ; AC0 += b0*d(n)        (4)
                        MACM    *AR4+, *AR1+, AC0         ; AC0 += b1*d(n-1)      (5)
                                                          ; input to next biquad
InnerLoopEnd:

                AMOV    T2, AR1                  ; reinitialize coeff pointer
             || MOV     rnd(HI(AC0)), *AR2+       ; store result to output buffer
OuterLoopEnd:

;Signal overflow
        MOV     AR4, *AR3                                ; save index to dbuffer[0]
     || MOV     #0, T0
        XCCPART overflow(AC0)
            ||MOV   #1, T0

;Context restore
        POP     T2,T3
     || BCLR    AR4LC                ; restore AR4LC for C
        RET
     || BCLR    FRCT                 ; restore FRCT for C

