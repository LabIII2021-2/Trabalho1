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
; Function:	 iircas32
; Processor:   C55xx
; Description:  cascaded IIR direct form II using 5-coefs per biquad
;                using 32 bit coefficients and delay buffer
;
;  Usage:  short oflag iir32(DATA *x,LDATA *h,DATA *r,LDATA *d, 
;                            ushort nbiq, ushort nx);
;
; Notes;
;   dbuffer[] array size is ((4 * nbiq) + 2) words.
;   There are no alignment requirements of the arrays.
;
; Benchmarks:
;   Cycles:       (nx * ((24 * nbiq) + 8)) + 28
;   Code Size (in bytes):  181
;
; History
; 2.40 Cleared XDP instead of DP register
;      Zhengting He - 10/25/2006
;
; 3.00 Fixed overflow handling.  Optimized.
;      Craig Leeds - 05/28/2012
; 
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
;  short oflag iir32(DATA *x,LDATA *h,DATA *r,LDATA *d, ushort nbiq, ushort nx);
;
;   where:
; x[nx]: PASSED in XAR0.					16 bit
;        Pointer to input vector of nx real elements.  
;        x(0) is the first input, 
;        while x(nx-1) is the last input.
;        
; h[2(5*nbiq)]: PASSED in XAR1.				32 bit
;        Pointer to longword filter coefficient vector with the following format:
;        H = a11 a21 b21 b01 b11 ....a1i a2i b2i b0i b1i
;         where i is the biquad index.
;         (i.e. a21: is the a2 coefficient of biquad 1). 
;         Pole (recursive) coefficients = a. 
;         Zero (non-recursive) coefficients = b
;
;        This array must be located in internal memory if it is 
;        accessed by the C55xx coefficient bus.
;
; r[nx]: PASSED in XAR2.					16 bit
;        Pointer to output vector of nx real elements.  
;        In-place computation (r = x) is allowed.  r(0) is the first 
;        output, while r(nx-1) is the last output.
;
; dbuffer[(2*nbiq) + 1]: PASSED in XAR3.	32 bit
;        Pointer to longword delay buffer of length 2*nbiq + 1.  See figure 
;        below for organization. In the case of multiple-buffering schemes, 
;        this array should be initialized to 0 for the first filter block 
;        only.  Between consecutive blocks, the delay buffer preserves the 
;        previous elements needed.
;
;        The first element in this array is special in that it 
;        contains the array index of the first buffer element in the 
;        delay buffer.  This is needed for multiple-buffering schemes, 
;        and should be initialized to zero (like all the other array 
;        entries) for the first block only.
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
;      "dbuffer[2*(2*nbiq+2)]"        "h[2*(5*nbiq)]"
;               index             AR1(h)->b21H
;               dummy                     b21L 
;       R3(dn)-->d21L                     b11H
;               d21H                      b11L
;               d11L                      b01H
;               d11H                      b01L
;               d22L                      a21H
;               d22H                      a21L
;               d12L                      a11H
;               d12H                      a11L
;                :                         :
;               d1nH                       :
;               extra 
;               dummy
;
;      Def: dij / aij / bij  where i = delay #
;                                  j = biquad #


	.arms_off
	.mmregs
        .noremark 5684    ; CPU_116: BRC1 not written indirectly in outer loop

;******************************************
;*       Assigns
;******************************************
	.def	_iir32

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
_iir32:
;Context save
        psh     T3, T2
     || bset    FRCT, ST1_55            ;fractional mode enable
        pshboth XAR5
     || bset    AR3LC, ST2_55           ;init AR3 = circular (dbuffer)
        pshboth XAR7
     || bclr    ARMS
        bset    M40
        bclr    ACOV0

;Initialization
    
;Save pointer to index at dbuffer[0]    
        mov     XAR3, XAR5

; Setup loop counters
        sub     #1, T1, T3              ;compute nx-1
        mov     T3, BRC0                ;init outer loop counter (nx-1)
        
        sub     #1, T0, T3              ;init inner loop counter (#bi-quads-1)
        mov     T3, BRC1

; Setup circular addressing
        mov     #4, BK03                ;init AR0-3 circular buf size (2 delay elements)
        mov     *AR5, AR3               ;init AR3 offset to buffer start
     || add     #2, AR5                 ;adjust AR5 to buffer start address (d20L)

        mov     XAR1, XAR7              ;save coeff buffer start address to reinit pntr

; Setup offset registers
        amov    #3, T0                  ;b0 bypass index
     || mov     #5, T1                  ;b0 pick up index
        
; Kernel
;  XAR0: x[] input (16 bit)
;  XAR1: h[] coefficients (32 bit: H/L)
;  XAR2: r[] result (16 bit)
;  XAR3: dbuffer[] (32 bit: H/L)
;  XAR5: dbuffer d2jL pointer 
;  XAR7: reinit XAR1
;
;                                                               
; BIQUAD's are calculated as follows                            
;    tmp = b2*d[n-2] + b1*d[n-1]                                
;    d[n] = x[n] or y[n]   (depending on BIQUAD)                
;    d[n] = d[n] - a2*d[n-2] - a1*d[n-1] 
;    store new d[n]                        
;    y[n] = b0*d[n] + tmp
;    store y[n]
;
; Note: u---L * u---L not needed for 32 bit result. 
;        Saves one MAC per tap.
;----------------------------------------------------------------                                                               

;  for(i=0; i<nx; i++)
        rptblocal OuterLoopEnd-1                             ; Outer Loop: Process a new input
                 mov    AR5, mmap(BSA23)                     ; 
; HI(AC0) = x(n)
                 mov    *AR0+ << #16, AC0        
;      for(j=0; j<nbiq; j++)
              || rptblocal InnerLoopEnd-1                    ; Inner Loop: Process a bi-quad

; AC2 = b2 * d[n-2]
                        NOP_16                               ; CPU_116: Remark 5684
                     || mpym    *AR1, uns(*AR3+), AC3        ; b2jH * ud2jL
                        mpym    *AR1+, *AR3, AC2             ; b2jH * d2jH
                        macm    uns(*AR1+), *AR3+, AC3       ; ub2jL * d2jH
                        add     AC3 << #-16, AC2
                
; AC2 += b1 * d[n-1]
                     || mpym    *AR1, uns(*AR3+), AC3        ; b1jH * ud1jL        
                        macm    *AR1+, *AR3, AC2             ; b1jH * d1jH
                        macm    uns(*(AR1+T0)), *AR3+, AC3   ; ub1jL * d1jH
                        add     AC3 << #-16, AC2
;   AR3 circular addressing -> last d2jL
;   AR1+index -> a2jH 
;    (skip b0j temporarily)

; AC0 -= a2 * d[n-2]
                     || mpym    *AR1, uns(*AR3+), AC1        ; a2jH * ud2jL        
                        masm    *AR1+, *AR3, AC0             ; a2jH * d2jH
                        macm    uns(*AR1+), *AR3+, AC1       ; ua2jL * d2jH
                        sub     AC1 << #-16, AC0

; d[n] = AC0 -= a1 * d[n-1]
                     || mpym    *AR1, uns(*AR3+), AC1        ; a1jH * ud1jL        
                        masm    *AR1+, *AR3, AC0             ; a1jH * d1jH
                        macm    uns(*(AR1-T1)), *AR3+, AC1   ; ua1jL * d1jH
                        sub     AC1 << #-16, AC0
;   AR3 circular addressing -> last d2jL
;   AR1-index -> b0jH

;   Replace d[n-2] with new d[n]
                        sat     AC0                          ; probably not necessary
                        mov     AC0, *AR3+                   ; d0jL
                        mov     HI(AC0), *AR3-               ; d0jH

; AC0 = b0 * d[n]
                     || mpym    *AR1, AC0                    ; b0jH * d0jH
                        mpym    *AR1+, uns(*AR3+), AC1       ; b0jH * ud0jL
                        macm    uns(*AR1+), *AR3-, AC1       ; ub0jL * d0jH
                        add     #4, mmap(BSA23)                
                        add     AC1 << #-16, AC0
;   AR3 adjusted -> last d2jH

; y[n] = AC0 += AC2
;  or input to next biquad
                        add     AC2, AC0

;   update AR1 -> b2jH
                     || aadd    #4, AR1                        ; 
InnerLoopEnd:

                amov    AR7, AR1                        ; reinitialize coeff pointer
             || mov     rnd(HI(saturate(AC0))), *AR2+   ; store result to output buffer
                aadd    #2, AR3                         ; Adjust dbuffer offset for next sample
OuterLoopEnd:
;  end of outer loop

        asub    #2, AR5

;Signal overflow check
     || mov     #0, T0
        xccpart overflow(AC0)
            ||mov   #1, T0

;Save last index value
        mov     AR3, *AR5                ; save index to dbuffer[0]

;Context restore
     || popboth XAR7
        popboth XAR5
     || bclr    AR3LC, ST2_55            ; restore for C
        pop     T3, T2
     || bset    ARMS                     ; restore for C
        bclr    FRCT, ST1_55             ; restore for C
        ret
     || bclr    M40                      ; restore for C


 