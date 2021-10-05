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
; Function UNPACKI32
; Processor:   C55xx
; Decription: Unpacks the output of a Radix-2 DIF complex FFT using bit-reversed input 
;    data and bit-reversed twiddle table (length N/2, cosine/sine format).
;
; Usage:  void unpacki32(LDATA *x, ushort nx);
;
; Limitations:
;   nx must be a power of 2 between 16 and 1024
;
; Benchmarks:
;   Cycles:
;     nx =  16:    185
;     nx =  32:    381
;     nx =  64:    773
;     nx = 128:   1557
;     nx = 256:   3125
;     nx = 512:   6261
;     nx =1024:  12533
;   Code Size (in bytes):  
;     .text              259
;     .const:twiddle32  4096 (shared by cfft32, cifft32, unpack32, unpacki32)
;
; History;
;	- 11/20/2003	C. Iovescu initial implementation
;	- 05/26/2012	Craig Leeds: Optimized
;************************************************************************************
;
;  IDFT of N-point frequency domain sequence obtained from
;  a real-valued sequence.      
;
; Implementation of the rifft based on the derivation
;   
;  g(n) n=0:N-1 is a real valued sequence. The RFFT of this signal is
;  denoted G(k) k=0:N-1 complex sequence. The objective of the code is to
;  recover g(n) based on G(k).
;
;  g(n) is split in two real sequences, odd and even part
;    
;          xe(n) = g(2n)    n=0:N/2-1
;          xo(n) = g(2n+1)  n=0:N/2-1
;
;  Form the complex sequence:
;
;         x(n) = xe(n) + jxo(n)  n=0:N/2-1
;
;  The CFFT of x(n)can be expressed as:
;
;        X(k) k=0:N/2-1
;
;        X(k) = Xe(k) +j*Xo(k) k=0:N/2-1                (1)
;
;  The RFFT of g(n)can be expressed as:
;
;      G(k)     = Xe(k) + W(k,N)Xo(k)     k = 0:N/2-1   (2)
;      G(N/2+k) = Xe(k) - W(k,N)Xo(k)     k = 0:N/2-1   (3)
;
;   where W(k,n) = cos(2*PI*k/N)-j*sin(2*PI*k/N)
;         W(k,n) = Wr(k)-j*Wi(k)
;
;  (2) and (3) yield
;
;      Xe(k) = (G(k) + G(N/2+k))/2          k = 0:N/2-1       
;      Xo(k) = (G(k) - G(N/2+k))/(2*W(k,N)) k = 0:N/2-1
;
;  since g(n) is a real valued sequence the DFT has the complex
;  conjugate symmetry:
;
;     G(k) = G*(N-k)                      k = 0:N-1     (4)
;
;   And since 1/W(k,N) = W(-k, N)
;   Therefore:
;   
;     Xe(k) = (G(k) + G*(N/2-k))/2          k = 0:N/2-1  (5) 
;     Xo(k) = W(-k,N)(G(k) - G*(N/2-k))/2   k = 0:N/2-1  (6)
;
;  Separate in Real and Imag parts: 
;
;    Xr(k)+j*Xi(k) = (Xer(k)+ j*Xei(k)) +j*(Xor(k)+jXoi(k)) k=0:N/2-1 
;
;  define:
;
;     Grp(k) = (Gr(k) + Gr(N/2-k))/2   k = 0:N/2-1     (7)
;     Grm(k) = (Gr(k) - Gr(N/2-k))/2   k = 0:N/2-1     (8)
;     Gip(k) = (Gi(k) + Gi(N/2-k))/2   k = 0:N/2-1     (9)
;     Gim(k) = (Gi(k) - Gi(N/2-k))/2   k = 0:N/2-1     (10)
;
;
;    Xr(k)     = 0.5 [Grp(k)-Gip(k)*Wr(k)-Grm(k)*Wi(k)]       k = 0:N/2-1  (11)
;    Xi(k)     = 0.5 [Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]       k = 0:N/2-1  (12)
;    Xr(N/2-k) = 0.5 [Grp(k)+Gip(k)*Wr(k)+Grm(k)*Wi(k)]       k = 0:N/2-1  (13)
;    Xi(N/2-k) = 0.5 [-Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]       k = 0:N/2-1  (14)
;       
;  Special values:
;        
;     * DC Offset  k = 0                                 
;
;     Xr(0) = 0.5*0.5*(Gr(0)+Gr(N/2))
;     Xi(0) = 0.5*0.5*(Gr(0)-Gr(N/2))
;
;    This was derived based on:
;
;           Wr(0) = 1
;           Wi(0) = 0
;           Gi(0) = Gi(N/2) = 0
;
;     * Nyquist Frequency  k = N/4                          
;
;      Xr(N/4) =  0.5*Gr(N/4) 
;      Xi(N/4) = -0.5*Gi(N/4)
;
;     This was derived based on:
;
;           Wr(N/4) = 0
;           Wi(N/4) = 1
;
;
;****************************************************************

           .mmregs
           .cpl_on
           .arms_off
           .ref twiddle32

;//-----------------------------------------------------------------------------
;// Program section
;//-----------------------------------------------------------------------------

           .global _unpacki32

Gip           .set  0x0
GrmR          .set  0x2
Grp           .set  0x4
Gim           .set  0x6
cosGip        .set  0x8
sinGip        .set  0xa
cosGrm        .set  0xc
sinGrm        .set  0xe
RawFrameSize  .set  0x10
FrameSize     .set  (RawFrameSize+1)

           .text
          .align 4    ; needed for optimization due to RPTB too big for RPTBLOCAL
_unpacki32:

;//-----------------------------------------------------------------------------
;// Context save / get arguments
;//-----------------------------------------------------------------------------
  
; upon entry stack aligned on 32-bit boundary
  
        AADD    #-FrameSize, SP               ; create local frame
          
;//-----------------------------------------------------------------------------
;// Initialization code
;//-----------------------------------------------------------------------------

     || BSET    FRCT, ST1_55              ; set FRCT
        BCLR    ARMS, ST2_55              ; reset ARMS
        BSET    M40

;//-----------------------------------------------------------------------------
;// Unpack for RIFFT
;//
;//  T0 = N (Rfft size) 
;//
;//
;//
;//-----------------------------------------------------------------------------
        MOV     XAR0, XAR1               ; AR0 = start ptr input data = Xr[0]
        ADD     T0, AR1                  ; AR1 = end ptr input data 
        ADD     T0, AR1                  ; 32-bit data 
        MOV     T0, T1                   ; T1 = T0 = RFFT size/2
        SFTS    T1, #-1                  ; T1 = RFFT size/2 
        SFTS    T1, #-1                  ; T1 = RFFT size/4 (req. for loop)
        SUB     #4, AR1                  ; AR1 = Xr[N/2-1] - last 32-bit elt
        SUB     #2, T1                   ; loop = N/4 - 2
        MOV     T1, BRC0                 ; and store in repeat counter
        AMOV    #twiddle32, XAR2         ; pointer to sin and cos tables
        AMAR    *AR2(2), XAR3            ; 32-bit values (add 2)
        AMAR    *SP(#Gip), XAR4           ; XAR4 local var ptr (stack)
        AMAR    *(AR2+T0B)               ; set to 2nd entry of bit reversed
        ; T0 = RFFT size for bitrev because 32-bit values

;--------------------------------------------------------------------------------
; Step1: 
;  Special values X(0):
;        
;     * DC Offset  k = 0                                    
;
;           Xr(0) = 0.5*0.5 (Gr(0)+Gi(N/2)) 
;           Xi(0) = 0.5*0.5 (Gr(0)-Gi(N/2))
;
;     Note: Gi(N/2) is stored as the imag part of G(0).
;
;--------------------------------------------------------------------------------
        MOV     dbl(*AR0+), AC1                  ; AC1 = Gr[0]
        ADD     dbl(*AR0), AC1, AC0              ; AC0 = Gr[0] + Gi[N/2]                                                                                                       
        SUB     dbl(*AR0-), AC1, AC1             ; AC1 = Gr[0] - Gi[N/2]
       
     || SFTS    AC0, #-2                         ; 0.25x
        SFTS    AC1, #-2                         ; 0.25x
                 
     || MOV     AC0, dbl(*AR0+)                  ; Xr(0)
        MOV     AC1, dbl(*AR0+)                  ; Xi(0)
     || MOV     #6, T1                           ; for AR1
        AMAR    *(AR3+T0B)               ; sin/cos table 
;--------------------------------------------------------------------------------
; Step 2: 
;
; General loop X(k) k=1:N/2-1  k<>N/4 (X(k)&X(N/2-k) computed in same iteration)
;  
;     Grp(k) = 0.5 (Gr(k) + Gr(N/2-k))   k = 1:N/4-1     
;     Grm(k) = 0.5 (Gr(k) - Gr(N/2-k))   k = 1:N/4-1     
;     Gip(k) = 0.5 (Gi(k) + Gi(N/2-k))   k = 1:N/4-1     
;     Gim(k) = 0.5 (Gi(k) - Gi(N/2-k))   k = 1:N/4-1      
;
;--------------------------------------------------------------------------------
     || RPTB    unpackiLoopEnd-1                 ; setup loopcounter (RFFT-size)/4 - 2
                MOV     dbl(*AR0+), AC3          ; AC3 = Gr[k]                                                                                    
              ||ADD     #1, AR2
                ADD     dbl(*AR1), AC3, AC0      ; Grp = AC0 =   Gr[k] + Gr[N/2-k]  
              ||ADD     #1, AR3
                SUB     dbl(*AR1+), AC3          ; Grm = AC3 =   Gr[k] - Gr[N/2-k]
              ||SFTS    AC0, #-1                 ; Grp = 0.5*AC0
                       
                MOV     dbl(*AR0-), AC2          ; AC2 = Gi[k]                 
              ||SFTS    AC3, #-1                 ; Grm = 0.5*AC3
                ADD     dbl(*AR1), AC2, AC1      ; Gip = AC1 =  Gi[k] + Gi[N/2-k]             
                SUB     dbl(*AR1-), AC2, AC2     ; Gim = AC2 =  Gi[k] - Gi[N/2-k]
              ||SFTS    AC1, #-1                 ; Gip = 0.5*AC1 
                
                MOV     AC0, dbl(*SP(Grp))       ; save Grp
              ||SFTS    AC2, #-1                 ; Gim = 0.5*AC2
                MOV     AC1, dbl(*AR4+)          ; save Gip   *SP(0)
                MOV     AC2, dbl(*SP(Gim))       ; save Gim
                MOV     AC3, dbl(*AR4-)          ; save GrmR  *SP(2)
            
;-----------------------------------------------------------------------
;
;   Output for N/2-point CIFFT
;
;    Xr(k)     = 0.5 [Grp(k)-Gip(k)*Wr(k)-Grm(k)*Wi(k)]      
;    Xi(k)     = 0.5 [Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]       
;    Xr(N/2-k) = 0.5 [Grp(k)+Gip(k)*Wr(k)+Grm(k)*Wi(k)]       
;    Xi(N/2-k) = 0.5 [-Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]         
;
;    Wr(k)     = cos(2Pik/N)
;    Wi(k)     = sin(2Pik/N)
;
;--------------------------------------------------------------------------------

                ; Wr(k)Gip(k)
                ;  AR2 -> cos_H
                ;             cos_L
                ; 
                ;  AR4 -> Gip_H
                ;             Gip_L
                ;

                MPYM    uns(*AR2-), *AR4+, AC0         ; AC0 = cos_L*Gip_H
                MACM    *AR2, uns(*AR4-), AC0          ; AC0 = AC0 + cos_H*Gip_L
                MACM    *AR2+, *AR4, AC0 >> #16, AC0   ; AC0 = AC0>>16 + cos_H*Gip_H 
                MOV     AC0, dbl(*SP(cosGip))          ; save cos*Gip

                ; Wi(k)Gip(k)
                ;  AR3 -> sin_H
                ;             sin_L
                ; 
                ;  AR4 -> Gip_H
                ;             Gip_L
                ;
                    
                MPYM    uns(*AR3-), *AR4+, AC0         ; AC0 = sin_L*Gip_H
                MACM    *AR3, uns(*AR4-), AC0          ; AC0 = AC0 + sin_H*Gip_L
                MACM    *AR3+, *AR4+, AC0 >> #16, AC0  ; AC0 = AC0>>16 + sin_H*Gip_H 
                MOV     AC0, dbl(*SP(sinGip))          ; save sin*Gip
              ||AADD    #1, AR4
                    
                ; Wr(k)Grm(k)
                ;         cos_H
                ;  AR2 -> cos_L
                ; 
                ;  AR4 -> Grm_H
                ;             Grm_L
                ;
                    
                MPYM    uns(*AR2-), *AR4+, AC0       ; AC0 = cos_L*Grm_H
                MACM    *AR2, uns(*AR4-), AC0        ; AC0 = AC0 + cos_H*Grm_L
                MACM    *AR2, *AR4, AC0 >> #16, AC0  ; AC0 = AC0>>16 + cos_H*Grm_H 
                MOV     AC0, dbl(*SP(cosGrm))        ; save cos*Grm
   
                ; Wi(k)Grm(k)
                ;         sin_H
                ;        AR3 -> sin_L
                ; 
                ;  AR4 -> Grm_H
                ;               Grm_L
                ;
                    
                MPYM    uns(*AR3-), *AR4+, AC0       ; AC0 = sin_L*Grm_H
                MACM    *AR3, uns(*AR4-), AC0        ; AC0 = AC0 + sin_H*Grm_L
                MACM    *AR3, *AR4-, AC0 >> #16, AC0 ; AC0 = AC0>>16 + sin_H*Grm_H 
                MOV     AC0, dbl(*SP(sinGrm))        ; save sin*Grm
          
                ; update AR4, local var pointer for next loop iteration 
                SUB     #1, AR4
             || MAR     *(AR3+T0B)                   ; sin
            
                ; update the sin/cos pointers
                ; bit-reversed addressing used because twiddle table 
                ; is in bit-reversed format and normal format is needed
                ; in this algorithm.
                ;
                ;  AR2 -> cos_H
                ;               cos_L         
                ;  AR3 -> sin_H
                ;               sin_L
            
;     Xr(k)     =0.5 [Grp(k)-Gip(k)*Wr(k)-Grm(k)*Wi(k)]                       
                                                                                             
                MOV     dbl(*SP(Grp)), AC0           ; AC0 = Grp(k)                                                                                     
                SUB     dbl(*SP(cosGip)), AC0, AC1   ; AC1 = Grp(k)-Wr(k)Gip(k)                                                                                                       
                SUB     dbl(*SP(sinGrm)), AC1, AC1   ; AC1 = Grp(k)-Wr(k)Gip(k)-Wi(k)Grm(k)
                SFTS    AC1, #-1                     ; 0.5x
             || AMAR    *(AR2+T0B)                   ; cos
                MOV     AC1, dbl(*AR0+)              ; Xr(k)

;    Xi(k)     =0.5 [Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]                                                                                                                        
                                                                                                                                                       
                MOV     dbl(*SP(cosGrm)), AC1        ; AC1 = Gim(k) 
                ADD     dbl(*SP(Gim)), AC1, AC2      ; AC2 = Gim(k)+ Wr(k)Grm(k)  
                SUB     dbl(*SP(sinGip)), AC2, AC2   ; AC2 = Gim(k)+ Wr(k)Grm(k)-Wi(k)Gip(k)  
                SFTS    AC2, #-1                     ; 0.5x    

;    Xr(N/2-k) =0.5 [Grp(k)+Gip(k)*Wr(k)+Grm(k)*Wi(k)]                   
        
             || ADD     dbl(*SP(cosGip)), AC0, AC3   ; AC3 = Grp(k)+ Wr(k)Gip(k)  
                ADD     dbl(*SP(sinGrm)), AC3, AC3   ; AC3 = Grp(k)+ Wr(k)Gip(k)+Wi(k)Grm(k)  
                SFTS    AC3, #-1                     ; 0.5x    
             || MOV     AC2, dbl(*AR0+)              ; Xi(k)

;    Xi(N/2-k) =0.5 [-Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]                              
        
                SUB     dbl(*SP(Gim)), AC1, AC2      ; AC2 = -Gim(k)+ Wr(k)Grm(k)  
                SUB     dbl(*SP(sinGip)), AC2, AC2   ; AC2 = -Gim(k)+ Wr(k)Grm(k)-Wi(k)Gip(k)  
                MOV     AC3, dbl(*AR1+)              ; Xr(N/2-k)            
             || SFTS    AC2, #-1                     ; 0.5x    
                MOV     AC2, dbl(*(AR1-T1))          ; Xi(N/2-k) ; adjust to Gr(N/2-k-1)          
unpackiLoopEnd:

;--------------------------------------------------------------------------------
; Step3: 
;  Special values G(N/4):
;
;           Gr(N/4) = 0.5 Xr(N/4) 
;           Gi(N/4) =-0.5 Xi(N/4)
;
;//-----------------------------------------------------------------------------
        MOV     dbl(*AR0+), AC0          ; Xr(N/4)
        MOV     dbl(*AR0-), AC1          ; Xi(N/4)          
     || SFTS    AC0, #-1                 ; 0.5*Xr(N/4)           
        NEG     AC1, AC1                 ;-Xi(N/4)
     || MOV     AC0, dbl(*AR0+)          ;Gr(N/4) = 0.5 Xr(N/4)
        SFTS    AC1, #-1                 ;-0.5*Xi(N/4)          
        MOV     AC1, dbl(*AR0+)          ;Gi(N/4) =-0.5 Xi(N/4)        
;//-----------------------------------------------------------------------------
;// Context restore
;//-----------------------------------------------------------------------------
     || AADD    #+FrameSize, SP          ; destroy local frame
;//-----------------------------------------------------------------------------
;// Return
;//-----------------------------------------------------------------------------
        BSET    ARMS, ST2_55             ; set ARMS for C
        BCLR    FRCT, ST1_55             ; reset FRCT for C
        BCLR    M40
     || RET

        .end
