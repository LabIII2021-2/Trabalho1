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
;  Function:	 iircas4
;  Description:  cascaded IIR direct form II using 4-coefs per biquad
;
;  Usage: short oflag = iircas4(DATA *x, DATA *h, DATA *r, DATA *dbuffer, 
;                               ushort nbiq, ushort nx)
;
; Notes:
;   If h[] is in SARAM instead of DARAM, the function will take twice 
;   as many cycles.
;
; Limitations:
;   nbiq must be even.
;   dbuffer[] must be on-chip (i.e. in DARAM or SARAM).
;
; Benchmarks:
;   Cycles:       (nx * ((3 * nbiq) + 2)) + 56
;   Code Size (in bytes):  145
;-----------------------------------------------------------------------------
; Revision History:
; 1.00  T. Horner, 2/15/00. Original version. Started from code by Rosemarie 
;   Piedra, Greg Peake, and Karim Djafarian.
; 1.01  Li Yuan, 6/13/00. Fixed pop up order error.
; 2.00  C. Iovescu, 5/20/02 Modified implementation to use Dual Mac
; 2.10 Cesar I. optimized code for benchmark purpose. 08/03/01
;
; 2.40 Cleared XDP instead of DP register
;      Zhengting He - 10/25/2006
;
; 3.00 Fixed overflow checking.
;      Fixed dbuffer index.
;      Craig Leeds - 06/28/2012
;*****************************************************************************
;*****************************************************************************
;
;
;	IIR Biquad Structure
;
;                  d(n)         
;  x(n) ---> + -----.----- + --> y(n)
;           /|      |      |\
;          | |    [z-1]    | |
;          |        |        |
;          | |      v      | | 
;          | |--x-d(n-1)-x-| |         
;          |  -a1   |   b1   | 
;          |        |        |
;          |      [z-1]      |
;          |        |        |
;          |        v        |
;          |---x--d(n-2)--x--|
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
;  y(n) = d(n) + b1*d(n-1) + b2*d(n-2)
;
;
; Function Call
; -------------
;
;  short oflag = iircas4(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nbiq,
;                        ushort nx)
;
;   where:
; x[nx]: PASSED in XAR0.
;        Pointer to input vector of nx real elements.  
;        x(0) is the first input, 
;        while x(nx-1) is the last input.
;        
; h[4*nbiq]: PASSED in XAR1.
;        Pointer to filter coefficient vector with the following format:
;        H = a11 a21 b21 b11 ....a1i a2i b2i b1i
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
; dbuffer[2*nbiq + 2]: PASSED in XAR3.
;        Pointer to delay buffer of length 2*nbiq.  See figure below for  
;        organization. In the case of multiple-buffering schemes, this 
;        array should be initialized to 0 for the first filter block only. 
;        Between consecutive blocks, the delay buffer preserves the 
;        previous elements needed.
;
;        The first element in this array is special in that it 
;        contains the array index of the first buffer element in the 
;        delay buffer.  This is needed for multiple-buffering schemes, 
;        and should be initialized to zero (like all the other array 
;        entries) for the first  block only.
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
;      AR0(x)--> x(0)            AR2(r)-->r(0)     newest
;                x(1)                     r(1)
;                x(2)                     r(2)
;                 :                        :
;                 :                        :
;                x(nx-1)                  r(nx-1)  oldest
;
;
;      "dbuffer[2*nbiq+1]"            "h[4*nbiq]"
;                index            AR1(h)->a11
;      AR3(dn)-->d11                      b11 
;                d21                      a21
;                 :                       b21
;                dn1                      
; 				 dn2                      a12
;                                         b12
;                                         a22
;                                         b22
;                                          :
;                                         a1i
;                                         b1i
;                                         a2i
;                                         b2i
;
;      Def: dij / aij / bij  where i = delay #
;                                  j = biquad #

	.arms_off
	.cpl_on
	.mmregs    
	.noremark  5684    ; CPU_116: BRC1 not written indirectly
;******************************************
;*       Assigns
;******************************************
	.def	_iircas4

;******************************************
;*       Constant Defines
;******************************************
SCALE	.set	0

;******************************************
;*       Variable Declarations
;******************************************

;----------------------------------------------------------------
; Assign auxiliary registers for temporaries and address
; calculations.
;----------------------------------------------------------------
	.asg     CDP, db_ptr        ;circular pointer
 	.asg     AR0, in_ptr        ;linear pointer
 	.asg     AR1, h_ptr         ;circular pointer
 	.asg     AR2, out_ptr       ;linear pointer
        .asg     AR3, index         ;
	.asg     AR4, tap_updt      ;circular pointer

;**********************************************************************
; Program section
;**********************************************************************
	.text
_iircas4:
;Context save

; Configure the status registers as needed.
;----------------------------------------------------------------
        PSH     mmap(ST2_L)            ; save ARMS, AR1LC, AR4LC, CDPLC
        PSH     T2, T3
     || BSET    #CDPLC, ST2_55         ;init CDP = circular (dbuffer)    
        PSHBOTH XAR5
     || BSET    #AR1LC, ST2_55         ;init AR1 = circular (dbuffer)

;Initialization   
        BSET    #AR4LC, ST2_55         ;init AR4 = circular (coeff)
        BCLR    #ARMS, ST2_55
        MOV     XAR3, XAR5 
        BSET    FRCT
        BCLR    ACOV0                  ; clear overflow bit 
        BCLR    ACOV1                  ; clear overflow bit 
    
;Save pointer to index at dbuffer[0]    

;Restore index of the current dbuffer location
        MOV     *AR3, AR3 

; Setup circular addressing for db_ptr (CDP) and tap_updt (AR4)
     || MOV     T0, T3                 ;compute 2*nbiq
        SFTL    T3, #1
        ADD     #1, T3 
        MOV     T3, mmap(BKC)          ;init CDP circular buf size (2*nbiq+1)
        MOV     T3, mmap(BK47)         ;init AR4 circular buf size (2*nbiq+1)
        ADD     #1, AR5 
        MOV     AR5, mmap(BSAC)        ;init CDP circular start addr: dbuffer
        MOV     AR5, mmap(BSA45)
        MOV     XAR3, XCDP             ; MOV index, db_ptr
     
        AMAR    *db_ptr+
    
        MOV     XAR3, XAR4             ;MOV index, tap_updt

 ; Setup circular addressing for h_ptr (AR1)
        MOV     T0,T3                  ;compute 4*nbiq
        SFTL    T3, #1   
        SFTL    T3, #1
        MOV     T3, mmap(BK03)         ;init AR0-3 circular buf size (4*nbiq)
        MOV     AR1, mmap(BSA01)       ;init AR0-1 circular start addr: coeff
        MOV     #0, AR1
 
 ; Store loop counters 
            
        SUB     #1, T1,T3              ;compute nx-1
        MOV     T3, BRC0               ;init outer loop counter (nx-1)                
        
        MOV     T0, T3                 ;init inner loop counter (#bi-quads/2-1)
        SFTL    T3, #-1 
     || AMOV    #1, T0
        SUB     #1, T3
     || AMOV    #2, T1 
        MOV     T3, BRC1  

; Define Address indexes 

; Define scale factor
        MOV     #SCALE, T2             ;scale factor
; Kernel
;  XAR0: x[] input
;  XAR1: h[] coefficients
;  XAR2: r[] result
;  XAR3: dbuffer[]
;  XAR7: reinit XAR1

     || RPTBLOCAL outer_loop-1                       ; Outer Loop: Process a new input

                MOV     *in_ptr+ << #16, AC0                   ; HI(AC0) = x(n)
             || RPTBLOCAL inner_loop-1                         ; Inner Loop: Process a bi-quad
       
                        MAS     *(h_ptr+T1), *db_ptr+, AC0     ; AC0 = x(n) - a1*d(n-1)
                        ::MPY   *h_ptr(T0), *db_ptr+, AC1      ; AC1 = b1*d(n-1)
                       
                        MAS     *(h_ptr+T1), *db_ptr+, AC0     ; AC0=d(n)=x(n)-a1*d(n-1)-a2*d(n-2)
                        ::MAC   *h_ptr(T0), *db_ptr+, AC1      ; AC1=b1*d(n-1)+b2*d(n-2)
                       
                        MOV     HI(AC0<<T2), *(tap_updt+T1)    ; T1 = #2 , X2 
                     || ADD     AC1, AC0                       ; AC0 =  d(n) + b1*d(n-1) + b2*d(n-2)
         
                        ; Beginning of second Biquad
                    
                        MAS     *(h_ptr+T1), *db_ptr+, AC0     ; AC0 = x(n) - a1*d(n-1)
                        ::MPY   *h_ptr(T0), *db_ptr+, AC1      ; AC1 = b1*d(n-1)
 
                        MAS     *(h_ptr+T1), *db_ptr+, AC0     ; AC0=d(n)=x(n)-a1*d(n-1)-a2*d(n-2)
                        :: MAC  *h_ptr(T0), *db_ptr+, AC1      ; AC1=b1*d(n-1)+b2*d(n-2)
      
                        MOV     HI(AC0<<T2), *(tap_updt+T1)    ; T1 = #2 , T2 = #SCALE 
                      ||ADD     AC1, AC0
inner_loop:  
             
                MOV     rnd(HI(AC0)), *out_ptr+                ; store result to output buf
outer_loop:      
       
;Signal overflow
        MOV     #0, T0
        XCCPART overflow(AC0) 
             || MOV     #1,T0 
        XCCPART overflow(AC1) 
             || MOV     #1,T0 
;Save last index value
        MOV     tap_updt, *-AR5                                ; save index to dbuffer[0]
;Context restore
        POPBOTH XAR5
      ||BCLR    FRCT
        POP     T2, T3
        POP     mmap(@ST2_L)        ; restore ARMS, AR1LC, AR4LC, CDPLC
        RET


 