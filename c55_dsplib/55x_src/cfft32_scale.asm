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
; Description: 32-bit radix-2 DIT complex FFT using normal input data
;    and bit-reversed twiddle table (length N/2, cosine/sine format)
;    First two stages are separately implmented for MIPS optimization.
;
; Usage:    void cfft32_SCALE (LDATA *x, ushort nx);
;
; Limitations:
;   nx must be a power of 2 between 8 and 1024
;
; Benchmarks:
;   Cycles:
;     nx =  8:    250
;     nx = 16:    575
;     nx = 32:   1349
;     nx = 64:   3111
;     nx =128:   7159
;     nx =256:  16236
;     nx =512:  36396
;   Code Size (in bytes):  
;     .text              496
;     .const:twiddle32  4096 (shared by cfft32, cifft32, unpack32, unpacki32)
;
; History:
;    Original: 08/16/2002 ZhengTing He
;    08/19/2002 Li Yuan
;        - Changed || to :: in several dual MAC instructions
;    06/19/2012 Craig Leeds 
;       - optimized
;****************************************************************

;-----------------------------------------------------------------------
; Arguments passed to _fft
;
; AR0       ->    fftdata pointer
; T0        ->    fft size
;
;-----------------------------------------------------------------------

;//-----------------------------------------------------------------------------
;// Array declarations
;//-----------------------------------------------------------------------------


        
        .ref twiddle32
        .def _cfft32_SCALE     		; make function visible to other fnct
        .cpl_on
        .arms_off     			; enable assembler for arms mode
        .mmregs
        .noremark    5579, 5573, 5684
  
; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 5            ;save-on-entry registers saved (T3, T2, AR5, AR6, AR7)
FRAME_SZ          .set 2            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Local variables
; --------------             
       .asg    0, data_ptr
       .asg    1, data_sz
      
;----------------------------------------------------------------
; Conditional compile
;----------------------------------------------------------------
SCALED        .set        1                ; SCALED = 0 - not scaled version
                                           ; SCALED = 1 - scaled version
                                                
        .text           
_cfft32_SCALE:

;----------------------------------------------------------------
; Save any save-on-entry registers that are used
;----------------------------------------------------------------

        PSH     T3, T2
     || BSET    #FRCT, ST1_55          
        PSHBOTH XAR5
     || BCLR    #ARMS, ST2_55          
        PSHBOTH XAR6
     || BSET    M40             
        PSHBOTH XAR7

;----------------------------------------------------------------
; Allocate the local frame and argument block
;----------------------------------------------------------------
        AADD    #-(ARG_BLK_SZ + FRAME_SZ), SP

;----------------------------------------------------------------
; Save entry values for later
;----------------------------------------------------------------

        MOV     AR0, *SP(data_ptr) ; 
        MOV     T0, *SP(data_sz)   ;

;-----------------------------------------------------------------------
; FFT implementation
;
; The FFT is implemented in 5 different steps:
;
;  1) - a radix-2 stage without any multiplications.
;  2) - a radix-2 stage with two groups, only the 2nd group has
;       multiplications with 0x7FFFFFFH and 0x00000000
;  3) - a group of log2(FFT_SIZE)-3 radix-2 stages
;  4) - a radix-2 stage without scaling.
;  5) - on out-of-place bit-reversal
;-----------------------------------------------------------------------
        
;-----------------------------------------------------------------------
; Modification of status registers
;-----------------------------------------------------------------------          
                     
              ; Define CSR for scaling loop
        SUB     #1, T0, T1                          
        MOV     T1, BRC0                               ; BRC0 = fftsize - 1
        AMAR    *AR0,XAR1
        AMAR    *AR0,XAR2

;-----------------------------------------------------------------------
; Scaling loop: Data scaled by 2 before first stage 
;-----------------------------------------------------------------------       
        MOV     dbl(*AR2+), AC0                         ; (Prime the Pump)
     || RPTBLOCAL scaling-1
                MOV     dbl(*AR2+), AC1
             || SFTS    AC0,#-1 
                SFTS    AC1,#-1     
             || MOV     AC0, dbl(*AR1+)
                MOV     AC1, dbl(*AR1+)
             || MOV     dbl(*AR2+), AC0                 ; (for next iteration)
scaling:

;-----------------------------------------------------------------------
; Radix-2 stage 1
;-----------------------------------------------------------------------                
                                                        ; AR0->fft_data       (a)
        AMAR    *AR0(T0),XAR1                           ; AR1->fft_data+1*n2  (b)
        AMAR    *AR1(T0),XAR2                           ; AR2->fft_data+2*n2  (c)
        AMAR    *AR2(T0),XAR3                           ; AR3->fft_data+3*n2  (d)
        MOV     XAR2,XAR7

        SFTS    T0, #-1                                 ; T0=fft-size/2
        SUB     #1, T0, T1                              ; T1=fft_size/2-1
        MOV     T1, BRC0
        AMAR    *AR0, XAR4

;-----------------------------------------------------------------------
; Benchmark: 9 cycles for this loop                
;-----------------------------------------------------------------------
        MOV     dbl(*AR4+),AC0                          ; (Prime the Pump)
     || RPTBLOCAL stage1-1
                ADD     dbl(*AR7),AC0,AC1               ; AC1=AR+CR
                SUB     dbl(*AR7+),AC0                  ; AC0=AR-CR
                MOV     dbl(*AR4+),AC2
            || SFTS     AC1,#-1
                ADD     dbl(*AR7),AC2,AC3               ; AC3=AI+CI        
                SUB     dbl(*AR7-),AC2                  ; AC2=AI-CI        
                SFTS    AC0,#-1
             || MOV     AC1,dbl(*AR0+)                  ;(AR+CR)>>1->AR
                SFTS    AC2,#-1
             || MOV     AC0,dbl(*AR7+)                  ;(AR-CR)>>1->CR
                SFTS    AC3,#-1
             || MOV     AC2,dbl(*AR7+)                  ;(AI-CI)>>1->CI
                MOV     AC3,dbl(*AR0+)                  ;(AI+CI)>>1->AI
             || MOV     dbl(*AR4+),AC0                  ; (for next iteration)
stage1:        
        

;-----------------------------------------------------------------------
; Radix-2 stage2
;-----------------------------------------------------------------------
        MOV     *SP(data_ptr), AR0
     || SFTS    T0, #-1
        SUB     #1, T0, T1                              ;T0=fft_size/4
        MOV     T1, BRC0                                ;T1=fft_size/4-1
        AMAR    *AR0, XAR4

;-----------------------------------------------------------------------
; Benchmark: 10 cycles for group1
;-----------------------------------------------------------------------
        MOV     dbl(*AR4+),AC0                          ; (Prime the Pump)
     || RPTBLOCAL group1-1
                ADD     dbl(*AR1),AC0,AC1               ; AC1=AR+BR
                SUB     dbl(*AR1+),AC0                  ; AC0=AR-BR
             || SFTS    AC1,#-1
                MOV     dbl(*AR4+),AC2
                ADD     dbl(*AR1),AC2,AC3               ; AC3=AI+BI
                SUB     dbl(*AR1-),AC2                  ; AC2=AI-BI
             || SFTS    AC0,#-1
                MOV     AC1,dbl(*AR0+)                  ; AR+BR->AR
             || SFTS    AC2,#-1
                MOV     AC0,dbl(*AR1+)                  ; AR-BR->BR
             || SFTS    AC3,#-1
                MOV     AC2,dbl(*AR1+)                  ; AI-BI->BI
                MOV     AC3,dbl(*AR0+)                  ; AI+BI->AI
             || MOV     dbl(*AR4+),AC0                  ; (for next iteration)
group1: 


;-----------------------------------------------------------------------
; Benchmark: 11 cycles for group2        
;-----------------------------------------------------------------------        
        MOV     T1,BRC0
        AMOV    #twiddle32, XCDP
        AMAR    *AR3(#3), XAR4                         ; AR4->DI_LOW
        MOV     #3, T1
        AMAR    *AR3+                          ;                         AR3->DR_LOW

     || RPTBLOCAL group2-1
                MPY     uns(*AR3-),*CDP+,AC0           ;DR_LOW * 7FFF            AR3->DR_HI    CDP->FFFF
             :: MPY     uns(*AR4-),*CDP+,AC1           ;DI_LOW * 7FFF            AR4->DI_HI  
                MAC     *AR3,uns(*CDP-),AC0            ;DR_HI*FFFF+DR_LOW*7FFF,  AR3->DR_HI    CDP->7FFF
             :: MAC     *AR4,uns(*CDP-),AC1            ;DI_HI*FFFF+DI_LOW*7FFF,  AR4->DI_HI        
                MAC     *AR3,*CDP,AC0>>#16             ;DR_HI*7FFF+AC0>>16       AR3->DR_HI    CDP_>7FFF
             :: MAC     *AR4,*CDP,AC1>>#16             ;DI_HI*7FFF+AC1>>16       AR4->DI_HI    CDP_>7FFF                                
                SUB     AC1,dbl(*AR2),AC2              ;AC2=CR-AC1
             || ADD     #5, AR4                        ;                         AR4->DI(next)
                ADD     dbl(*AR2+),AC1                 ;AC1=CR+AC1               AR2->CI
                SUB     AC0,dbl(*AR2),AC3              ;AC3=CI-AC0                        
             || SFTS    AC1,#-1
                ADD     dbl(*AR2-),AC0                 ;AC0=CI+AC0               AR2->CR
             || SFTS    AC3,#-1
                MOV     AC1,dbl(*AR2+)                 ;AC1->CR                  AR2->CI
             || SFTS    AC2,#-1        
                MOV     AC3,dbl(*AR2+)                 ;AC3->CI                  AR2->CR(next)
             || SFTS    AC0,#-1
                MOV     AC2,dbl(*AR3+)                 ;AC2->DR                  AR3->DI
                MOV     AC0,dbl(*(AR3+T1))             ;AC0->DI                  AR3->DR(next)
group2:        

;-----------------------------------------------------------------------
; End of stage 1 and 2
;-----------------------------------------------------------------------                 
        SFTS    T0, #-1
        BCC     end_benchmark, T0==#0
                                                                                                                                                                                                                                                             
;-----------------------------------------------------------------------
; radix-2 stages (stages 3->log2(FFT_SIZE) )  
;         register usage
;         AR0->Pr, AR1->Qr, AR3->twiddle
;         AR4=Re distance of butterfly
;         AR6=group count, t1=butterfly count, AR5= stage count  
;-----------------------------------------------------------------------
        ; main initialization                
                
        ; modify ST2 to select linear or circular addressing modes
        OR       #0x3 , mmap(ST2_55)                ; circular AR0,AR1   
        MOV      *SP(data_ptr), AR1                ; AR1 = #fftdata  

        ; circular buffer starting addresses                            
        MOV     AR1, mmap(BSA01)                ; circular buffer start address
               
        ; circular buffer sizes 
        MPYMK   *SP(data_sz),#2,AC0        ; because FRCT==1, it actually x4
        MOV     AC0, mmap(BK03)                ; bk03 = (4*FFT_SIZE-4), AR0-AR3
        
        
        MOV     *SP(data_sz), T2
        SFTS    T2, #-1                                        ; T2 = FFT_SIZE/2
     || MOV     #4, AR6                                        ; AR6 = group    
        MOV     T2, AR4                                    ; AR4 = FFT_SIZE/2(Re distance between p q)
        
        MOV     T0, T1                                        ; T1 = FFT_SIZE/8, nbfly
            
        SFTS    T0,#-1                                        ; T0=size/16
     || MOV     #-2, T2
        MOV     T0, AR5                                        ; AR5 is stage count
        MOV     #2, T0
        AMOV    #twiddle32, XAR3
        BCC     last_stage, AR5==#0                                                                                

;-----------------------------------------------------------------------
; Beginning of the stage loop
;         stage initialization
;-----------------------------------------------------------------------
stage:  ; stage loop counter updates     
        SFTS    AR5,#-1                            ; shift right stage count  

        MOV     #0,AR0                
     || MOV     AR3, CDP
        ADD     #1,AR4,AR1                                ;AR1->QR_LOW
                                   
        ; butterfly counter update                                      
        SUB     #1,T1,T3        
        MOV     T3, BRC1        

        ; group counter update
        SUB     #1,AR6,T3     
        MOV     T3, BRC0              
                     
        RPTBLOCAL group-1
;-----------------------------------------------------------------------
; Benchmark: 15 cycles for butterfly loop
;-----------------------------------------------------------------------
                RPTBLOCAL BFly-1                                                                 ;             (AR1,CDP)
                        MPY     uns(*AR1), *(CDP+T0), AC0       ; AC0  = yrl*crh (1,0)
                     :: MPY     uns(*AR1(T0)), *(CDP+T0), AC1   ; AC1  = yil*crh (3,0)

                        MAC     uns(*AR1(T0)), *CDP+, AC0       ; AC0 += yil*cih (3,2)
                     :: MAS     uns(*AR1+), *CDP+, AC1          ; AC1 -= yrl*cih (1,2)
                     || SWAP    T0, T2                          ; T0=-2

                        MAC     *AR1, uns(*(CDP+T0)), AC0       ; AC0 += yih*cil (2,3)
                     :: MAS     *AR1(T0), uns(*(CDP+T0)), AC1   ; AC1 -= yrh*cil (0,3)

                        MAC     *AR1(T0), uns(*CDP-), AC0       ; AC0 += yrh*crl (0,1)
                     :: MAC     *(AR1+T0), uns(*CDP-), AC1      ; AC1 += yih*crl (2,1)
                     || SWAP    T0, T2                          ; T0=2

                        MAC     *AR1, *(CDP+T0), AC0>>#16       ; AC0 += yrh*crh (0,0)
                     :: MAC     *AR1(T0), *(CDP+T0), AC1>>#16   ; AC1 += yih*crh (2,0)

                        MAC     *AR1(T0), *(CDP+T0), AC0        ; AC0 += yih*cih (2,2)
                     :: MAS     *AR1, *(CDP+T0), AC1            ; AC1 -= yrh*cih (0,2)        
                
                        ADD     dbl(*AR0), AC0,AC2        
                        SFTS    AC2, #-1
                     || MAR     *CDP-    
                        MOV     AC2,dbl(*AR0)                   ; new xr=AC0+xr  (0,4)
                     || SUB     AC0,dbl(*AR0+),AC3              ;                (0,4)
                        SFTS    AC3, #-1
                     || MAR     *CDP-
                        MOV     AC3, dbl(*AR1+)                 ; new yr=xr-AC0  (2,4)
                     || SUB     AC1,dbl(*AR0), AC2
                        SFTS    AC2, #-1
                     || MAR     *CDP-   
                        MOV     AC2, dbl(*AR1+)                 ; new yi=xi-AC1  (2,4)
                     || ADD     dbl(*AR0),AC1,AC3               ;                (4,4)
                        SFTS    AC3, #-1
                     || MAR     *CDP-   
                        MOV     AC3, dbl(*AR0+)                 ; new xi=xi+AC1
                     || AADD    #1, AR1                         ;                (4,4) 
BFly:
                ADD     AR4, AR0                                ;jump to next group
                ADD     AR4, AR1
                AMAR    *+CDP(4)                                ;CDP+4
group:
                
        SFTS    AR6, #1                                        ;group<<1
        SFTS    T1, #-1                                        ;butterfly>>1
        SFTS    AR4, #-1                                       ;P Q distance>>1
     || BCC     stage, AR5 != #0
;-----------------------------------------------------------------------
; END radix-2 stages (stages 3->log2(FFT_SIZE) )  
;-----------------------------------------------------------------------

;-----------------------------------------------------------------------
; Last stage
;-----------------------------------------------------------------------                
last_stage:
        ; stage initialization
        MOV     #0, AR0                 
        MOV     AR3, CDP                                  
        MOV     #5, AR1                                 ;AR1->QR_LOW
        
        ; group counter update
        SUB     #1, AR6, T3    
        MOV     T3, BRC0              
        MOV     #6, T1
             
     || RPTBLOCAL lgroup-1                                
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
                MOV     AC2,dbl(*AR0)                   ; new xr=AC0+xr  (0,4)
             || SUB     AC0,dbl(*AR0+),AC3              ;                (0,4)

                MOV     AC3, dbl(*AR1+)                 ; new yr=xr-AC0  (2,4)
             || SUB     AC1,dbl(*AR0), AC2

                MOV     AC2, dbl(*AR1+)                 ; new yi=xi-AC1  (2,4)
             || ADD     dbl(*AR0),AC1,AC3               ;                (4,4)

                MOV     AC3, dbl(*(AR0+T1))             ; new xi=xi+AC1 (and jump to next group)
             || AADD    #5, AR1                         ;                (4,4)
lgroup:        
;-----------------------------------------------------------------------
; END last stage
;-----------------------------------------------------------------------
                                                
end_benchmark:
;-----------------------------------------------------------------------
; Allocate the local frame and argument block
;----------------------------------------------------------------
        AADD    #+(ARG_BLK_SZ + FRAME_SZ), SP

;Context restore 
        POPBOTH XAR7
     || BCLR    AR0LC
        POPBOTH XAR6
     || BCLR    AR1LC
        POPBOTH XAR5
     || BSET    #ARMS, ST2_55          
        POP     T3, T2
     || BCLR    #FRCT, ST1_55          
        RET 
     || BCLR    M40             
                .end         
        
