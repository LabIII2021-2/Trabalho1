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
; Processor:   C55xx
; Descripac1on: 32-bit radix-2 DIT complex FFT using normal input data
;    and bit-reversed twiddle table (length N/2, cosine/sine format)
;    First two stages are in radix-4.
;
; Usage:    void cfft32_NOSCALE (LDATA *x, ushort nx);
;
; Limitations:
;   nx must be a power of 2 between 8 and 1024
;
; Benchmarks:
;   Cycles:
;     nx =  8:    190
;     nx = 16:    454
;     nx = 32:   1086
;     nx = 64:   2563
;     nx =128:   5992
;     nx =256:  13786
;     nx =512:  31280
;   Code Size (in bytes):  
;     .text              301
;     .const:twiddle32  4096 (shared by cfft32, cifft32, unpack32, unpacki32)
;
; History:
;	- 07/17/2003	C. Iovescu changed the way the twiddle table is included
;       - 06/19/2012    Craig Leeds: optimized, removed .bss usage
;***********************************************************************

;-----------------------------------------------------------------------
; Arguments passed to _fft
; 	AR0       ->    fftdata pointer
; 	T0        ->    fft size
;-----------------------------------------------------------------------

;-----------------------------------------------------------------------
; Array declaraac1ons
;-----------------------------------------------------------------------

        .ref twiddle32

        .def _cfft32_NOSCALE     	; make funcac1on visible to other fnct
        .cpl_on
        .arms_off     				; enable assembler for arms mode
        .mmregs
        .noremark    5579, 5573, 5684
        
;-----------------------------------------------------------------------  
; Stack frame
;-----------------------------------------------------------------------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 5            ;save-on-entry registers saved (T3, T2, AR5, AR6, AR7)
FRAME_SZ          .set 4            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ

;-----------------------------------------------------------------------
; Local variables
;-----------------------------------------------------------------------            
       .asg    0, tempmem           ; (long) must be aligned on even
       .asg    2, data_pac0
       .asg    3, data_sz

;-----------------------------------------------------------------------
; Temp data
;-----------------------------------------------------------------------
      
        .text           
_cfft32_NOSCALE:

;-----------------------------------------------------------------------
; Save any save-on-entry registers that are used
;-----------------------------------------------------------------------
        PSH     T3, T2
     || BSET    #FRCT, ST1_55          
        PSHBOTH XAR5
     || BCLR    #ARMS, ST2_55          
        PSHBOTH XAR6
     || BSET    M40
        PSHBOTH XAR7

;-----------------------------------------------------------------------
; Allocate the local frame and argument block
;-----------------------------------------------------------------------
        AADD    #-(ARG_BLK_SZ + FRAME_SZ), SP

;-----------------------------------------------------------------------
; Save entry values for later
;-----------------------------------------------------------------------
        AMAR    *AR0(T0), XAR1                       ; b: AR1 = #(fftdata+4*FFT_SIZE/4)
        AMAR    *AR1(T0) ,XAR2                       ; c: AR2 = #(fftdata+4*FFT_SIZE/2)
        AMAR    *AR2(T0) ,XAR3                       ; d: AR3 = #(fftdata+4*3*FFT_SIZE/4)
                
        MOV     T0, *SP(data_sz)   ;

        SFTS    T0, #-1                              ;T0 = FFT_SIZE/4
        SFTS    T0, #-1        
        SUB     #1, T0
        MOV     T0,BRC0
                
        MOV     XSP, XAR6
 .if tempmem != 0
        ADD     #tempmem, AR6                        ; AR6 = &tempmem (on stack)
 .endif
                
        MOV     AR0, *SP(data_pac0) ; 

;-----------------------------------------------------------------------
; FFT implementaac1on
;
; The FFT is implemented in three different steps:
;
;  1) - a radix-4 stage with twiddle factors only equal to -1, 0 and 1
;  2) - a group of log2(FFT_SIZE)-3 radix-2 stages
;  3) - on out-of-place bit-reversal
;
;  No need to implement the last stage in a different way
;  to the other stages.        
;-----------------------------------------------------------------------
; Modificaac1on of status registers          
                                           
;-----------------------------------------------------------------------
; First two stages computed as one radix-4 stage
;-----------------------------------------------------------------------      
        ; First in-place radix-4 stage
        ;
        ;        ----------
        ; a -----|   R    |----- a'
        ;            A
        ; b -----|   D    |----- b'
        ;            I
        ; c -----|   X    |----- c'
        ;  
        ; d -----|   4    |----- d'
        ;        ---------
        ;
        ; ar' =  (ar + cr) + (br + dr)
        ; ai' =  (ai + ci) + (bi + di) 
        ;
        ; br' =  (ar + cr) - (br + dr)
        ; bi' =  (ai + ci) - (bi + di)
        ;
        ; cr' =  (ar - cr) + (bi - di)
        ; ci' =  (ai - ci) - (br - dr)
        ;
        ; dr' =  (ar - cr) - (bi - di)
        ; di' =  (ai - ci) + (br - dr)
        ;        
        ; AR6  -> tempmem
        ;
        ; AR0-> a
        ; AR1-> b
        ; AR2-> c
        ; AR3-> d
        ;
        ; --------------------------------------------------------------        
       
     || RPTBLOCAL stage12-1
;-----------------------------------------------------------------------
; Benchmark: 20 stages for stage1_2 loop
;-----------------------------------------------------------------------           
                ;Instruction                         AC0        AC1        AC2        AC3        AR0        AR1        AR2        AR3            
                MOV     dbl(*AR0), AC0              ;AR                                ar        br        cr        dr
                SUB     dbl(*AR2),AC0,AC3           ;                        ar-cr                                
                ADD     dbl(*AR2+),AC0,AC1          ;        ar+cr                                ci        
                MOV     dbl(*AR1),AC0               ;br                                                        
                SUB     AC0,dbl(*AR3+),AC2          ;                dr-br                                di
                MOV     AC2,dbl(*AR6)               ;AR6->dr-br                                                                
             || ADD     AC0<<#1,AC2                 ;                dr+br                                        
                ADD     AC2,AC1                     ;ar+cr+dr+br                                                
             || MOV     dbl(*AR3-),AC0              ;di                                                        dr 
                MOV     AC1,dbl(*AR0+)              ;                                ai                        
             || SUB     AC2<<#1,AC1                 ;ar+cr-(dr+br)                                                
                MOV     AC1, dbl(*AR1+)             ;                                        bi                 
                ADD     dbl(*AR1),AC0,AC1           ;        bi+di                                                 
                SUB     AC0, dbl(*AR1), AC2         ;                bi-di                                        
                ADD     AC2, AC3                    ;                        ar-cr+bi-di                                
             || MOV     dbl(*AR2-),AC0              ;ci                                                cr        
                MOV     AC3,dbl(*AR2+)              ;                                                ci        
             || SUB     AC2<<#1,AC3                 ;                        ar-cr-(bi-di)                                
                MOV     AC3, dbl(*AR3+)             ;                                                        di 
             || SUB     AC0, dbl(*AR0), AC3         ;                        ai-ci 
                ADD     dbl(*AR0),AC0               ;ai+ci
                ADD     AC1, AC0                    ;ai+ci+di+bi                                                        
                MOV     dbl(*AR6),AC2               ;                dr-br                                        
                MOV     AC0, dbl(*AR0+)             ;                                arn                        
             || SUB     AC1<<#1,AC0                 ;ai+ci-(di+bi)                                                        
                MOV     AC0, dbl(*AR1+)             ;                                        brn                
             || ADD     AC2,AC3                     ;                        ai-ci+dr-br                                
                MOV     AC3,dbl(*AR2+)              ;                                                crn        
             || SUB     AC2<<#1,AC3                 ;                        ai-ci-(dr-br)                                
                MOV     AC3,dbl(*AR3+)              ;                                                        drn
stage12:
;-----------------------------------------------------------------------
; End of stage 1 and 2
;-----------------------------------------------------------------------            
                
;-----------------------------------------------------------------------
; radix-2 stages (stages 3->log2(FFT_SIZE) )  
; register usage
; ar0->Pr, ar1->Qr, ar3->twiddle
; ar4=Re distance of butterfly
; ar6=group count, t1=butterfly count, ar5= stage count  
;-----------------------------------------------------------------------
        ; main iniac1alizaac1on                 

        ; modify ST2 to select linear or circular addressing modes
        OR      #0x3, mmap(ST2_55)              ; circular AR0LC,AR1LC        
        MOV     *SP(data_pac0), AR1             ; AR1 = #fftdata  

        ; circular buffer starac1ng addresses                            
        MOV     AR1, mmap(BSA01)                ; circular buffer start address
               
        ; circular buffer sizes 
        MPYMK   *SP(data_sz),#2,AC0             ; because FRCT==1, it actually x4
        MOV     AC0, mmap(BK03)                 ; BK03 = (4*FFT_SIZE-4), ar0-ar3
        MOV     *SP(data_sz), T2
        SFTS    T2,#-1                          ; T2 = FFT_SIZE/2
        MOV     T2,AR4                          ; AR4 = FFT_SIZE/2(Re distance between p q)
        SFTS    T2,#-1
     || MOV     #4, AR6                         ; AR6 = group    
        SFTS    T2,#-1                          ; T2 = FFT_SIZE/8
        BCC     end_benchmark, T2==#0

        MOV     T2, T1                          ; T1 = number of butterfly,
        MOV     T2, AR5                         ; AR5 = stage                                                                               
        AMOV    #twiddle32, XAR3                ; AR3->twiddle          

        MOV     #2, T0                  ; moving from real->imag
        MOV     #-2, T2                 ; restoring cdp, and imag->real               
                        
stage:  ; begining of a new stage
        ; stage initialization
        
        ; 1 - loop counter updates     
        SFTS    AR5, #-1                 ; shift right stage count
     || MOV     #0, AR0                
        MOV     XAR3, XCDP
        ADD     #1, AR4, AR1             ;AR1->QR_LOW
        ADD     #2, AR1, AR2             ;AR2->QI_LOW
                   
        ; butterfly counter update                                      
        SUB     #1, T1, T3        
        MOV     T3, BRC1                 ;butterflies loop count

        ; group counter update
        SUB     #1, AR6, T3     
        MOV     T3, BRC0              
               
        RPTBLOCAL group-1
;-----------------------------------------------------------------------
; Benchmark: 12 cycles for the butterfly loop
;-----------------------------------------------------------------------
               RPTBLOCAL BFly-1                                                                 ;             (AR1,CDP)
                        MPY     uns(*AR1), *(CDP+T0), AC0       ; AC0  = yrl*crh (1,0)
                     :: MPY     uns(*AR1(T0)), *(CDP+T0), AC1   ; AC1  = yil*crh (3,0)

                        MAC     uns(*AR1(T0)), *CDP+, AC0       ; AC0 += yil*cih (3,2)
                     :: MAS     uns(*AR1+), *CDP+, AC1          ; AC1 -= yrl*cih (1,2)
                     || SWAP    T0, T2                          ; T0=-2

                        MAC     *AR1, uns(*(CDP+T0)), AC0       ; AC0 += yih*cil (2,3)
                     :: MAS     *AR1(T0), uns(*(CDP+T0)), AC1   ; AC1 -= yrh*cil (0,3)

                        MAC    *AR1(T0), uns(*CDP-), AC0        ; AC0 += yrh*crl (0,1)
                     :: MAC    *(AR1+T0), uns(*CDP-), AC1       ; AC1 += yih*crl (2,1)
                     || SWAP    T0, T2                          ; T0=2

                        MAC     *AR1, *(CDP+T0), AC0>>#16       ; AC0 += yrh*crh (0,0)
                     :: MAC     *AR1(T0), *(CDP+T0), AC1>>#16   ; AC1 += yih*crh (2,0)

                        MAC     *AR1(T0), *(CDP+T0), AC0        ; AC0 += yih*cih (2,2)
                     :: MAS     *AR1, *(CDP+T0), AC1            ; AC1 -= yrh*cih (0,2)

                        ADD     dbl(*AR0), AC0,AC2
                        MAR     *+CDP(-4)
                        MOV     AC2,dbl(*AR0)                   ; new xr=ac0+xr  (0,4)
                     || SUB     AC0,dbl(*AR0+),AC3              ;                (0,4)

                        MOV     AC3, dbl(*AR1+)                 ; new yr=xr-ac0  (2,4)
                     || SUB     AC1,dbl(*AR0), AC2

                        MOV     AC2, dbl(*AR1+)                 ; new yi=xi-ac1  (2,4)
                     || ADD     dbl(*AR0),AC1,AC3               ;                (4,4)

                        MOV     AC3, dbl(*AR0+)                 ; new xi=xi+ac1
                     || AADD    #1, AR1                         ;                (4,4)                             
BFly:
                                                                                                                                                                                                                                                                                                                                                                                                                                                              
                ADD     AR4, AR0                                ;jump to next group
                ADD     AR4, AR1
                AMAR    *+CDP(4)                                ;CDP+4
group:        
                
        SFTS    AR6,#1                                      ;group<<1
        SFTS    T1,#-1                                      ;butterfly>>1
        SFTS    AR4,#-1                                     ;P Q distance>>1
     || BCC     stage,AR5 != #0              
;-----------------------------------------------------------------------
; End of radix-2 stage 
;-----------------------------------------------------------------------
                                
end_benchmark:

;-----------------------------------------------------------------------
; De-allocate the local frame and argument block
;-----------------------------------------------------------------------
        AADD    #+(ARG_BLK_SZ + FRAME_SZ), SP

        ;Context restore 
        POPBOTH XAR7
     || BCLR    AR0LC
        POPBOTH XAR6
     || BCLR    AR1LC
        POPBOTH XAR5
     || BSET    ARMS
        POP     T3, T2
     || BCLR    FRCT
        RET 
     || BCLR    M40
        .end         
        
