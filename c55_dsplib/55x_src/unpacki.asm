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
; Function UNPACK
; Processor:   C55xx
; Decription: Unpacks the output of a Radix-2 DIF complex IFFT using bit-reversed input data
;    and bit-reversed twiddle table (length N/2, cosine/sine format)
;
; Usage:  void unpacki(DATA *x, ushort nx);
;
; Benchmarks:
;   Cycles:
;     (5 * nx) + 13
;        nx =  16:     93
;        nx =  32:    173
;        nx =  64:    333
;        nx = 128:    653
;        nx = 256:   1293
;        nx = 512:   2573
;        nx =1024:   5133
;   Code Size (in bytes):  
;     .text            145
;     .const:twiddle  2048 (shared by cfft, cifft, unpack, unpacki)
;
; History;
;	- 07/17/2003	C. Iovescu changed the way the twiddle table is included
;	- 05/26/2012	Craig Leeds: 
;           - Fixed stack alignment bug putting T3 at risk
;           - optimized by 40%
;****************************************************************

            .mmregs
            .cpl_on
            .arms_off
            .ref twiddle

;//-----------------------------------------------------------------------------
;// Program section
;//-----------------------------------------------------------------------------

            .global _unpacki
            .text
_unpacki:

;//-----------------------------------------------------------------------------
;// Context save / get arguments
;//-----------------------------------------------------------------------------
        PSH        T3, T2

;//-----------------------------------------------------------------------------
;// Initialization code
;//-----------------------------------------------------------------------------

     || BSET    FRCT, ST1_55            ; set FRCT
        BSET    M40, ST1_55             ; set M40
        BCLR    ARMS, ST2_55            ; reset ARMS
        
;//-----------------------------------------------------------------------------
;// Unpack for IRFFT
;//-----------------------------------------------------------------------------
        MOV     XAR0,XAR1               ; AR1 = pointer to input data = rm[0]
        ADD     T0,AR1                  ; AR1 = pointer to input data = rm[N]
        SFTS    T0,#-1                  ; T0 = RFFT size/2 (req. for loop)
        MOV     T0,T1                   ; T1 = T0 = RFFT size/2
        SFTS    T1,#-1                  ; T1 = RFFT size/4 (req. for loop)
        SUB     #2,AR1                  ; element in the data buffer
        SUB     #2,T1                   ; loop = N/4 - 2
        MOV     T1,BRC0                 ; and store in repeat counter 
        MOV     #-1,T2
        AMOV    #twiddle,XAR2           ; pointer to sin and cos tables
        AMOV    #(twiddle+1),XAR3       ; 
        AMAR    *(AR2+T0B)              ; set to 2nd entry of bit reversed
        AMAR    *(AR3+T0B)              ; sin/cos table 
            
;--------------------------------------------------------------------------------
; process yre[0] (DC) and yre[0] (Nyquist)
; yre[0] = 1/2(xre[0] + xim[0])    store in yre[0] 
; yre[N] = 1/2(xre[0] - xim[0])    store in yim[0]
;
;Scaling by 2 added to avoid overflow
;--------------------------------------------------------------------------------
        MOV     *AR0+,AC1                  ; AC1=xre[0]
        ADD     *AR0,AC1,AC0               ; AC0=xre[0]+xim[0]
        SUB     *AR0-,AC1,AC1              ; AC1=xre[0]-xim[0]
        MOV     AC0 << #-2, *AR0+          ; yre[0]=0.5*xre[0]+xim[0]
        MOV     AC1 << #-2, *AR0+          ; yim[0]=0.5*xre[0]-xim[0]
;--------------------------------------------------------------------------------
; process y1re/im
;
;Scaling by 2 added to avoid overflow
;--------------------------------------------------------------------------------
     || RPTBLOCAL   unpackiLoopEnd-1            ; setup loopcounter (RFFT-size)/4 - 2 
             ADD         *AR0,*AR1,AC0          ; AC0 = x1Re+x2Re   
             SUB         *AR0+,*AR1+,AC3        ; AC3 = x1Re-x2Re
           ||SFTS        AC0,#-1                ; rp = 0.5*AC0 = 0.5*(x1Re+x2Re)
             SUB         *AR0,*AR1,AC1          ; AC1 = x1Im-x2Im
           ||SFTS        AC3,#-1                ; rm = 0.5*AC2 = 0.5*(x1Im+x2Im)
             ADD         *AR0-,*AR1-,AC2        ;  
           ||SFTS        AC1,#-1                ; ip = 0.5*AC1 = 0.5*(x1Im-x2Im)
             NEG         AC2                    ; AC2 = -(x1Im+x2Im)
             SFTS        AC2,#-1                ; im = 0.5*AC3 = -0.5*(x1Re-x2Re)
           ||MOV         HI(AC3),T3             ; save im to T3  
             MOV         HI(AC2),T1             ; save rm to T1

;-----------------------------------------------------------------------
             MASM        *AR2,T1,AC0,AC2        ; y2re=AC2=rp-cos*rm
             MASM        *AR2,T3,AC1,AC3        ; y2im=AC3=ip-cos*im
             MACM        *AR2,T1,AC0,AC0        ; y1re=AC0=rp+cos*rm
             MACM        *(AR2+T0B),T3,AC1,AC1  ; y1im=AC1=ip+cos*im
;-----------------------------------------------------------------------
             ; y1re=rp+cos*rm-sin*im
             MASM        *AR3,T3,AC0,AC0        
             ; y1im=ip+cos*im+sin*rm                                         
             MACM        *AR3,T1,AC1,AC1 
             ::MOV       HI(AC0<<T2),*AR0+       
             ; y2re=-rp-cos*rm+sin*im
             MACM        *AR3,T3,AC2,AC2 
             ::MOV       HI(AC1<<T2),*AR0+       
             ; y2im=ip-cos*im-sin*rm
             MASM        *(AR3+T0B),T1,AC3,AC3       
             NEG         AC3
          || MOV         HI(AC2<<T2),*AR1+
             MOV         HI(AC3<<T2),*AR1
          || ASUB        #3,AR1                 ; adjust to next rm
unpackiLoopEnd: 
;//-----------------------------------------------------------------------------
;       yre(N/2) = yre(N/2)
;       yim(N/2) = - yim(N/2)
;
;Scaling by 2 added to avoid overflow
;//-----------------------------------------------------------------------------
        MOV     dbl(*AR0),pair(HI(AC0))
        NEG     AC1,AC1
        SFTS    AC0,#-1,AC0            
        SFTS    AC1,#-1,AC1            
        MOV     pair(HI(AC0)),dbl(*AR0)
;//-----------------------------------------------------------------------------
;// Context restore and return
;//-----------------------------------------------------------------------------

        BCLR    FRCT, ST1_55              ; restore FRCT for C
        BSET    ARMS, ST2_55              ; restore ARMS for C
     || POP     T3, T2
        BCLR    M40, ST1_55               ; restore M40 for C
     || RET

        .end
