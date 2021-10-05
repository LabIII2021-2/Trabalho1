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
; Function UNPACK32
; Processor:   C55xx
; Decription: Unpacks the output of a Radix-2 DIF complex FFT using bit-reversed input 
;    data and bit-reversed twiddle table (length N/2, cosine/sine format).
;
; Usage:  void unpack32(LDATA *x, ushort nx);
;
; Limitations:
;   nx must be a power of 2 between 16 and 1024
;
; Benchmarks:
;   Cycles:
;     nx =  16:    196
;     nx =  32:    403
;     nx =  64:    819
;     nx = 128:   1651
;     nx = 256:   3316
;     nx = 512:   6644
;     nx =1024:  13300
;   Code Size (in bytes):  
;     .text              262
;     .const:twiddle32  4096 (shared by cfft32, cifft32, unpack32, unpacki32)
;
; History;
;	- 11/20/2003	C. Iovescu initial implementation
;	- 06/16/2012	Craig Leeds: Optimized
;
;************************************************************************************
;
;  DFT of N-point real-valued sequence
;
; Implementation of the rfft based on the equations:
;
;   
;
;  g(n) n=0:N-1 is a real valued sequence. Purpose of the code
;  is to compute the RFFT of this signal: G(k) k=0:N-1 complex sequence. 
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
;  Compute the CFFT of x(n):
;
;        X(k) k=0:N/2-1
;
;  Derive from X(k) the CFFT of xe(n) and xo(n) using the equations
;
;       Xe(k) =  0.5  (X(k) + X*(N/2-k))   k=0:N/2-1  (1)
;       Xo(k) = -0.5j (X(k) - X*(N/2-k))   k=0:N/2-1  (2)
;
;  Separate in Real and Imag parts: 
;
;   Define: 
;            Xe(k) =  Xer(k)+jXei(k)
;            Xo(k) =  Xor(k)+jXoi(k)
;
;   Equations (1) and (2) yield:
;
;       Xer(k) =  0.5  (Xr(k) + Xr(N/2-k))   k=0:N/2-1  (3)
;       Xei(k) =  0.5  (Xi(k) - Xi(N/2-k))   k=0:N/2-1  (4)
;       Xor(k) =  0.5  (Xi(k) + Xi(N/2-k))   k=0:N/2-1  (5)
;       Xoi(k) = -0.5  (Xr(k) - Xr(N/2-k))   k=0:N/2-1  (6)
;
;   The previous equations have special values for:
;
;   DC Offset: 
;             k=0     Xer(0)= Xr(0)
;                     Xei(0)= 0
;                     Xor(0)= Xi(0)
;                     Xoi(0)= 0
;
;
;   Nyquist Frequency:
;             k=N/4   Xer(N/4)= Xr(N/4)
;                     Xei(N/4)= 0
;                     Xor(N/4)= Xi(N/4)
;                     Xoi(N/4)= 0
;
;
;    Computing G(k)
;
;    G(k)   = Xe(k) + W(k,N)Xo(k)     k = 0:N/2-1   (7)
;    G(N/2-k) = Xe*(k) - W(-k,N)Xo*(k)  k = 0:N/2-1   (8)
;
;  Separate in Real and Imag parts: 
;
;   Define: 
;            G(k) =  Gr(k)+jGi(k)
;            G(N-k) =  Gr(N-k)+jGi(N-k)
;            W(k,N) = cos(2Pik/N)-jsin(2Pik/N) = Wr(k)-jWi(k)
;
;   Equations (7) and (8) yield:
;
;          Gr(k)     = Xer(k) + Wr(k)Xor(k)+Wi(k)Xoi(k)   (9)
;          Gi(k)     = Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)   (10)
;          Gr(N/2-k) = Xer(k) - Wr(k)Xor(k)-Wi(k)Xoi(k)   (11)
;          Gi(N/2-k) =-Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)   (12)
;
;
;  Equations (9) through (12) will be DIVIDED BY TWO in order to avoid
;  overflow.
;
;          Gr(k)     = 0.5[Xer(k) + Wr(k)Xor(k)+Wi(k)Xoi(k)]   (13)
;          Gi(k)     = 0.5[Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]   (14)
;          Gr(N/2-k) = 0.5[Xer(k) - Wr(k)Xor(k)-Wi(k)Xoi(k)]   (15)
;          Gi(N/2-k) =0.5[-Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]   (16)
;
;  Special values:
;        
;     * DC Offset  k = 0                                    (17)
;
;           Gr(0) = 0.5 (Xr(0)+Xi(0)) 
;           Gi(0) = 0
;
;     * k = N/4                                             (18)
;
;           Gr(N/4) = 0.5 Xr(N/4) 
;           Gi(N/4) =-0.5 Xi(N/4)
;
;     * Nyquist Frequency  k = N/2                          (19)
;
;           Gr(N/2) = 0.5 (Xr(0)-Xi(0)) 
;           Gi(N/2) = 0
;
;
;  Practical computation of G(k) k=0:N-1
;      
;      1) Compute G(k) k=0:N/2
;             - G(0),G(N/4), G(N/2) based on special values formulae
;             - G(k) for   (0<k<N/2)
;      2) Deduct G(k) k=N/2+1:N-1 from the values computed in 1) using
;      the complex conjugate symmetry formulae (since g(n) is a real
;      sequence) 
;                   
;              G(k) = G*(N-k)  k=0:N-1
;
;  Algorithm implementation:
;    
;
;     The algorithm computes only G(k) k=0:N/2. In order to store the
;     result in the input array, G(0) and G(N/2) which have zero imag parts are
;     packed together and Gr(N/2) is stored at the location of Gi(0).
;
;        1) Compute Xer(k), Xei(k), Xor(k), Xoi(k) for k=1:N/4-1
;               ( k=0 and k=N/4 are special values)
;
;  
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

                .global _unpack32
                .text
_unpack32:

;//-----------------------------------------------------------------------------
;// Context save / get arguments
;//-----------------------------------------------------------------------------
  
; upon entry stack aligned on 32-bit boundary
  
        AADD    #-21,SP             ; create local frame
          
;//-----------------------------------------------------------------------------
;// Initialization code
;//-----------------------------------------------------------------------------

     || BSET    FRCT,ST1_55              ; set FRCT
        BCLR    ARMS,ST2_55              ; reset ARMS

;//-----------------------------------------------------------------------------
;// Unpack for RFFT
;//
;//  T0 = N (Rfft size) 
;//
;//
;//
;//-----------------------------------------------------------------------------
        MOV     XAR0,XAR1               ; AR0 = start ptr input data = Xr[0]
        ADD     T0,AR1                  ; AR1 = end ptr input data 
        ADD     T0,AR1                  ; 32-bit data 
        MOV     T0,T1                   ; T1 = T0 = RFFT size/2
        SFTS    T1,#-1                  ; T1 = RFFT size/2 
        SFTS    T1,#-1                  ; T1 = RFFT size/4 (req. for loop)
        SUB     #4,AR1                  ; AR1 = Xr[N/2-1] - last 32-bit elt
        SUB     #2,T1                   ; loop = N/4 - 2
        MOV     T1,BRC0                 ; and store in repeat counter
        AMOV    #twiddle32,XAR2         ; pointer to sin and cos tables
        AMOV    #(twiddle32+2),XAR3     ; 32-bit values (add 2)
        AMAR    *(AR2+T0B)              ; set to 2nd entry of bit reversed
        AMAR    *(AR3+T0B)              ; sin/cos table 
                                        ; T0 = RFFT size for bitrev because 32-bit values
        MOV     XSP,XAR4                ; XAR4 local var ptr (stack)
        ADD     #4, AR4                 ; AR4 = &SP(4)

;--------------------------------------------------------------------------------
; Step1: 
;  Special values G(0) and G(N/2):
;        
;     * DC Offset  k = 0                                    
;
;           Gr(0) = 0.5 (Xr(0)+Xi(0)) 
;           Gi(0) = 0
;
;
;     * Nyquist Frequency  k = N/2                          
;
;           Gr(N/2) = 0.5 (Xr(0)-Xi(0)) 
;           Gi(N/2) = 0
;
;     In order to store G(k) in the input array, Gr(0) and Gr(N/2) 
;     are packed as real&imag values.
;
;--------------------------------------------------------------------------------
        MOV     dbl(*AR0+),AC1           ; AC1 = Xr[0]
        ADD     dbl(*AR0),AC1,AC0        ; AC0 = Xr[0] + Xi[0]                                                                                                       
        SUB     dbl(*AR0-),AC1,AC1       ; AC1 = Xr[0] - Xi[0]
       
     || SFTS    AC0, #-1                 ; 0.5x
        SFTS    AC1, #-1                 ; 0.5x
                      
     || MOV     AC0, dbl(*AR0+)          ; Gr(0)
        MOV     AC1, dbl(*AR0+)          ; Gr(N/2)
        MOV     #6, T1                   ; T1 = 6 (for AR1 adjustment)
;--------------------------------------------------------------------------------
; Step 2: 
;
; General loop G(k) k=1:N/2-1  (k<>N/4)
;
;    Xer(k) =  0.5  (Xr(k) + Xr(N/2-k))  k=1:N/4-1  
;    Xei(k) =  0.5  (Xi(k) - Xi(N/2-k))  k=1:N/4-1 
;    Xor(k) =  0.5  (Xi(k) + Xi(N/2-k))  k=1:N/4-1  
;    Xoi(k) = -0.5  (Xr(k) - Xr(N/2-k))  k=1:N/4-1  
;
;--------------------------------------------------------------------------------
     || RPTB    unpack_end-1              ; setup loopcounter (RFFT-size)/4 - 2

                MOV     dbl(*AR1+),AC1          ; AC1= Xr[N/2-k]                                                                                    
             || ADD     #1, AR2
                ADD     dbl(*AR0),AC1,AC0       ; Xer = AC0 =   Xr[k] + Xr[N/2-k]  
                SUB     dbl(*AR0+),AC1,AC3      ; Xoi = AC3 = -(Xr[k] - Xr[N/2-k])
             || SFTS    AC0,#-1                 ; Xer = 0.5*AC0
                    
                MOV     dbl(*AR0-),AC2          ; AC2 = Xi[k]                 
             || SFTS    AC3,#-1                 ; Xoi = 0.5*AC3
                SUB     dbl(*AR1), AC2, AC1            ; Xei = AC1 =  Xi[k] - Xi[N/2-k]             
                ADD     dbl(*AR1-),AC2,AC2      ; Xor = AC2 =  Xi[k] + Xi[N/2-k]
             || SFTS    AC1,#-1                 ; Xei = 0.5*AC1 

                                               
                MOV     AC0 ,dbl(*SP(#00h))     ; save Xer
             || SFTS    AC2,#-1                 ; Xor = 0.5*AC2
                MOV     AC1 ,dbl(*SP(#02h))     ; save Xei            
                MOV     AC2 ,dbl(*SP(#04h))     ; save Xor
                MOV     AC3 ,dbl(*SP(#06h))     ; save Xoi
            
;-----------------------------------------------------------------------
;
;   Output N-point RFFT
;
;    Gr(k)     = 0.5[ Xer(k) + Wr(k)Xor(k)+Wi(k)Xoi(k)]   
;    Gi(k)     = 0.5[ Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]   
;    Gr(N/2-k) = 0.5[ Xer(k) - Wr(k)Xor(k)-Wi(k)Xoi(k)]   
;    Gi(N/2-k) = 0.5[-Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]  
;
;    Wr(k)     = cos(2Pik/N)
;    Wi(k)     = sin(2Pik/N)
;
;--------------------------------------------------------------------------------


             ; Wr(k)Xor(k)
                        
                         ;  AR2 -> cos_H
                         ;                   cos_L
                         ; 
                         ;  AR4 -> Xor_H
                         ;               Xor_L
                         ;
                         
                MPYM    uns(*AR2-), *AR4+, AC0        ; AC0 = cos_L*Xor_H

                MACM    *AR2, uns(*AR4-), AC0         ; AC0 = AC0 + cos_H*Xor_L
                MACM    *AR2+, *AR4, AC0 >> #16, AC0  ; AC0 = AC0>>16 + cos_H*Xor_H 
                MOV     AC0 ,dbl(*SP(#08h))           ; save cos*Xor

             ; Wi(k)Xor(k)
                        
                         ;  AR3 -> sin_H
                         ;               sin_L
                         ; 
                         ;  AR4 -> Xor_H
                         ;               Xor_L
                         ;
                         
             || AADD    #1, AR3
                MPYM    uns(*AR3-), *AR4+, AC0        ; AC0 = sin_L*Xor_H
                MACM    *AR3, uns(*AR4-), AC0         ; AC0 = AC0 + sin_H*Xor_L
                MACM    *AR3+, *AR4+, AC0 >> #16, AC0 ; AC0 = AC0>>16 + sin_H*Xor_H 
                MOV     AC0 ,dbl(*SP(#0Ah))           ; save sin*Xor
             || AADD    #1, AR4
                         
             ; Wr(k)Xoi(k)
                        
                         ;         cos_H
                         ;        AR2 -> cos_L
                         ; 
                         ;  AR4 -> Xoi_H
                         ;               Xoi_L
                         ;
                         
                MPYM    uns(*AR2-), *AR4+, AC0        ; AC0 = cos_L*Xoi_H
                MACM    *AR2, uns(*AR4-), AC0         ; AC0 = AC0 + cos_H*Xoi_L
                MACM    *AR2, *AR4, AC0 >> #16, AC0   ; AC0 = AC0>>16 + cos_H*Xoi_H 
                MOV     AC0 ,dbl(*SP(#0Ch))           ; save cos*Xoi
             
              ; Wi(k)Xoi(k)
                        
                         ;         sin_H
                         ;        AR3 -> sin_L
                         ; 
                         ;  AR4 -> Xoi_H
                         ;               Xoi_L
                         ;
            
                MPYM    uns(*AR3-), *AR4+, AC0        ; AC0 = sin_L*Xoi_H
                MACM    *AR3, uns(*AR4-), AC0         ; AC0 = AC0 + sin_H*Xoi_L
                MACM    *AR3, *AR4, AC0 >> #16, AC0   ; AC0 = AC0>>16 + sin_H*Xoi_H 
                MOV     AC0 ,dbl(*SP(#0Eh))           ; save sin*Xoi
          
                  ; update AR4, local var pointer for next loop iteration 
             || SUB     #2, AR4
            
            ; update the sin/cos pointers
            ; bit-reversed addressing used because twiddle table 
            ; is in bit-reversed format and normal format is needed
            ; in this algorithm.
            
         ;   !!!this requires special alignement of twiddle table ??

                  ;  AR2 -> cos_H
                         ;               cos_L         
                  ;  AR3 -> sin_H
                         ;               sin_L
         
            
;    Gr(k)     = 0.5[ Xer(k) + Wr(k)Xor(k)+Wi(k)Xoi(k)]            
                                                                                                  
                MOV     dbl(*SP(#00h)),AC0       ; AC0 = Xer(k)                                                                                     
                ADD     dbl(*SP(#08h)),AC0,AC1   ; AC1 = Xer(k)+Wr(k)Xor(k)                                                                                                       
                ADD     dbl(*SP(#0Eh)),AC1,AC1   ; AC1 = Xer(k)+Wr(k)Xor(k)+Wi(k)Xoi(k)
                SFTS    AC1, #-1                 ; 0.5x
             || AMAR    *(AR2+T0B)      ; cos
                MOV     AC1, dbl(*AR0+)          ; Gr(k)
                                                                                                                   
;    Gi(k)     = 0.5[ Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]                                                                                                                                                            
            
                MOV     dbl(*SP(#02h)),AC1       ; AC1 = Xei(k) 
                ADD     dbl(*SP(#0Ch)),AC1,AC2   ; AC2 = Xei(k)+ Wr(k)Xoi(k)  
                SUB     dbl(*SP(#0Ah)),AC2,AC2   ; AC2 = Xei(k)+ Wr(k)Xoi(k)-Wi(k)Xor(k)  
                SFTS    AC2, #-1                 ; 0.5x    
             || AMAR    *(AR3+T0B)      ; sin
                MOV     AC2, dbl(*AR0+)          ; Gi(k)
                 
;    Gr(N/2-k) = 0.5[ Xer(k) - Wr(k)Xor(k)-Wi(k)Xoi(k)]                
             
                MOV     dbl(*SP(#00h)),AC1       ; AC1 = Xer(k) 
                SUB     dbl(*SP(#08h)),AC1,AC2   ; AC2 = Xer(k)- Wr(k)Xor(k)  
                SUB     dbl(*SP(#0Eh)),AC2,AC2   ; AC2 = Xer(k)- Wr(k)Xor(k)-Wi(k)Xoi(k)  
             
;    Gi(N/2-k) = 0.5[-Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]                
             
                MOV     dbl(*SP(#0Ch)),AC1       ; AC1 = Wr(k)Xoi(k) 
             || SFTS    AC2, #-1                 ; 0.5x    
                MOV     AC2, dbl(*AR1+)          ; Gr(N/2-k)            
                SUB     dbl(*SP(#02h)),AC1,AC2   ; AC2 = -Xei(k)+ Wr(k)Xoi(k)  
                SUB     dbl(*SP(#0Ah)),AC2,AC2   ; AC2 = -Xei(k)+ Wr(k)Xoi(k)-Wi(k)Xor(k)  
                SFTS    AC2, #-1                 ; 0.5x    
                MOV     AC2, dbl(*(AR1-T1))      ; Gi(N/2-k)   ; adjust to Gr(N/2-k-1)          
unpack_end:

;--------------------------------------------------------------------------------
; Step3: 
;  Special values G(N/4):
;
;           Gr(N/4) = 0.5 Xr(N/4) 
;           Gi(N/4) =-0.5 Xi(N/4)
;
;//-----------------------------------------------------------------------------
        MOV     dbl(*AR0+),AC0              ; Xr(N/4)
        MOV     dbl(*AR0-) ,AC1             ; Xi(N/4)          
     || SFTS    AC0,#-1                     ; 0.5*Xr(N/4)           
        NEG     AC1,AC1                     ;-Xi(N/4)
        SFTS    AC1,#-1                      ;-0.5*Xi(N/4)          
     || MOV     AC0 ,dbl(*AR0+)             ;Gr(N/4) = 0.5 Xr(N/4)
        MOV     AC1 ,dbl(*AR0+)             ;Gi(N/4) =-0.5 Xi(N/4)        
                     
;//-----------------------------------------------------------------------------
;// Context restore
;//-----------------------------------------------------------------------------
        AADD    #+21,SP                     ; destroy local frame
;//-----------------------------------------------------------------------------
;// Return
;//-----------------------------------------------------------------------------
     || BCLR    FRCT,ST1_55                 ; set FRCT
        BSET    ARMS,ST2_55                 ; reset ARMS
     || RET

        .end
