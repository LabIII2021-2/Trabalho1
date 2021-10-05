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
; Description: 32-bit radix-2 DIT complex iFFT using normal input data
;    and bit-reversed twiddle table (length N/2, cosine/sine format)
;    First two stages are separately implmented for MIPS optimization.
; Usage:    void cifft32_SCALE (LDATA *x, ushort nx);
;
; Limitations:
;   nx must be a power of 2 between 8 and 1024
;
; Benchmarks:
;   Cycles:
;     nx =   8:    245
;     nx =  16:    561
;     nx =  32:   1315
;     nx =  64:   3056
;     nx = 128:   7031
;     nx = 256:  15973
;     nx = 512:  35907
;     nx =1024:  81587
;   Code Size (in bytes):  
;     .text              482
;     .const:twiddle32  4096 (shared by cfft32, cifft32, unpack32, unpacki32)
;
; History:
;    08/19/2002 Li Yuan
;        - Changed || to :: in several dual MAC instructions
;    06/19/2012 Craig Leeds
;        - optimized
;****************************************************************

;-----------------------------------------------------------------------
; Arguments passed to _ifft
;
; AR0       ->    ifftdata pointer
; T0        ->    ifft size
;
;-----------------------------------------------------------------------

;//-----------------------------------------------------------------------------
;// Array declarations
;//-----------------------------------------------------------------------------

;        .include "twiddle32.inc"
        .ref twiddle32
        .def _cifft32_SCALE     	; make function visible to other fnct
        .cpl_on
        .arms_off     				; disable assembler for arms mode
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
_cifft32_SCALE:

;----------------------------------------------------------------
; Save any save-on-entry registers that are used
;----------------------------------------------------------------

        PSH     T3, T2
        PSHBOTH XAR5
     || BCLR    #ARMS, ST2_55          
        PSHBOTH XAR6
     || BSET    #FRCT, ST1_55          
        PSHBOTH XAR7
     || BSET    M40             

;----------------------------------------------------------------
; Allocate the local frame and argument block
;----------------------------------------------------------------
        AADD    #-(ARG_BLK_SZ + FRAME_SZ), SP

;----------------------------------------------------------------
; Save entry values for later
;----------------------------------------------------------------

;-----------------------------------------------------------------------
; iFFT implementation
;
; The iFFT is implemented in 5 different steps:
;
;  1) - a radix-2 stage without any multiplications.
;  2) - a radix-2 stage with two groups, only the 2nd group has
;       multiplications with 0x7FFFFFFH and 0x00000000
;  3) - a group of log2(iFFT_SIZE)-3 radix-2 stages
;  4) - a radix-2 stage without scaling.
;  5) - on out-of-place bit-reversal
;-----------------------------------------------------------------------
        
;-----------------------------------------------------------------------
; Modification of status registers
;-----------------------------------------------------------------------          
                     
        ; Define CSR for scaling loop
        SUB     #1, T0, T1                          
        MOV     T1, BRC0                            ; BRC0 = ifftsize - 1

        MOV AR0, *SP(data_ptr) ; 
        MOV T0, *SP(data_sz)   ;
        
        AMAR    *AR0,XAR1
        AMAR    *AR0,XAR2

;-----------------------------------------------------------------------
; Scaling loop: Data scaled by 2 before first stage 
;-----------------------------------------------------------------------       
        MOV     dbl(*AR2+), AC0                     ; (Prime the Pump)
     || RPTBLOCAL scaling-1
                MOV     dbl(*AR2+), AC1
             || SFTS    AC0, #-1 
                SFTS    AC1, #-1     
             || MOV     AC0, dbl(*AR1+)
                MOV     AC1, dbl(*AR1+)
             || MOV     dbl(*AR2+), AC0             ; (for next iteration)
scaling:

;-----------------------------------------------------------------------
; Radix-2 stage 1
;-----------------------------------------------------------------------                
        AMAR   *AR0(T0),XAR1                        ; AR1->ifft_data+n2  (b)
        AMAR   *AR1(T0),XAR2                        ; AR2->ifft_data+2*n2(c)
        AMAR   *AR2(T0),XAR3                        ; AR3->ifft_data+3*n2(d)
        MOV    XAR2,XAR7
        SFTS   T0,#-1                               ; T0=ifft-size/2
        SUB    #1,T0,T1                             ; T1=ifft_size/2-1
        MOV    T1,BRC0

;-----------------------------------------------------------------------
; Benchmark: 10 cycles for this loop                
;-----------------------------------------------------------------------
        RPTBLOCAL stage1-1
                MOV     dbl(*AR0+),AC0
                ADD     dbl(*AR7),AC0,AC1           ; AC1=AR+CR
                SUB     dbl(*AR7+),AC0              ; AC0=AR-CR
             || SFTS    AC1,#-1
                MOV     dbl(*AR0-),AC2
             || SFTS    AC0,#-1
                ADD     dbl(*AR7),AC2,AC3           ; AC3=AI+CI        
                SUB     dbl(*AR7-),AC2              ; AC2=AI-CI        
             || MOV     AC1,dbl(*AR0+)              ;(AR+CR)>>1->AR
                SFTS    AC2,#-1
             || MOV     AC0,dbl(*AR7+)              ;(AR-CR)>>1->CR
                SFTS    AC3,#-1
             || MOV     AC2,dbl(*AR7+)              ;(AI-CI)>>1->CI
                MOV     AC3,dbl(*AR0+)              ;(AI+CI)>>1->AI
stage1:

;-----------------------------------------------------------------------
; Radix-2 stage2
;-----------------------------------------------------------------------
        MOV     *SP(data_ptr), AR0
     || SFTS    T0,#-1
        SUB     #1,T0,T1                            ;T0=ifft_size/4
        MOV     T1,BRC0                             ;T1=ifft_size/4-1

;-----------------------------------------------------------------------
; Benchmark: 10 cycles for group1
;-----------------------------------------------------------------------
        RPTBLOCAL group1-1
                MOV     dbl(*AR0+),AC0
                ADD     dbl(*AR1),AC0,AC1           ; AC1=AR+BR
                SUB     dbl(*AR1+),AC0              ; AC0=AR-BR
             || SFTS    AC1,#-1
                MOV     dbl(*AR0-),AC2
             || SFTS    AC0,#-1
                ADD     dbl(*AR1),AC2,AC3           ; AC3=AI+BI
                SUB     dbl(*AR1-),AC2              ; AC2=AI-BI
             || MOV     AC1,dbl(*AR0+)              ; AR+BR->AR
                SFTS    AC2,#-1
             || MOV     AC0,dbl(*AR1+)              ; AR-BR->BR
                SFTS    AC3,#-1
             || MOV     AC2,dbl(*AR1+)              ; AI-BI->BI
                MOV     AC3,dbl(*AR0+)              ; AI+BI->AI
group1:


;-----------------------------------------------------------------------
; Benchmark: 13 cycles for group2        
;-----------------------------------------------------------------------        
        AMOV    #twiddle32, XCDP
        MOV     T1,BRC0
        AMAR    *AR3(#3), XAR4                       ; AR4->DI_LOW
        AMAR   *AR3+                                 ; AR3->DR_LOW

     || RPTBLOCAL group2-1
                MPY     uns(*AR3-),*CDP+,AC0    ;DR_LOW * 7FFF             AR3->DR_HI        CDP->FFFF
             :: MPY     uns(*AR4-),*CDP+,AC1    ;DI_LOW * 7FFF             AR4->DI_HI  
                MAC     *AR3,uns(*CDP-),AC0     ;DR_HI*FFFF+DR_LOW*7FFF,   AR3->DR_HI        CDP->7FFF
             :: MAC     *AR4,uns(*CDP-),AC1     ;DI_HI*FFFF+DI_LOW*7FFF,   AR4->DI_HI        
                MAC     *AR3,*CDP,AC0>>#16      ;DR_HI*7FFF+AC0>>16        AR3->DR_HI        CDP_>7FFF
             :: MAC     *AR4,*CDP,AC1>>#16      ;DI_HI*7FFF+AC1>>16        AR4->DI_HI        CDP_>7FFF                                
                SUB     AC1,dbl(*AR2),AC2       ;AC2=CR-AC1
                ADD     dbl(*AR2+),AC1          ;AC1=CR+AC1                AR2->CI
             || ADD     #5, AR4                 ;                          AR4->DI(next)
                SUB     AC0,dbl(*AR2),AC3       ;AC3=CI-AC0                        
             || SFTS    AC1,#-1
                ADD     dbl(*AR2-),AC0          ;AC0=CI+AC0                AR2->CR
             || SFTS    AC3,#-1
                MOV     AC1,dbl(*AR3+)          ;AC1->DR                   AR3->DI
             || SFTS    AC2,#-1        
                MOV     AC3,dbl(*AR3+)          ;AC3->DI                   AR3->DR(next)
             || SFTS    AC0,#-1
                MOV     AC2,dbl(*AR2+)          ;AC2->CR                   AR2->CI
                MOV     AC0,dbl(*AR2+)          ;AC0->CI                   AR2->CR(next)
             || AMAR   *AR3+                    ;                          AR3->DR_LOW
group2:        

;-----------------------------------------------------------------------
; End of stage 1 and 2
;-----------------------------------------------------------------------                 
        SFTS    T0, #-1
        BCC     end_benchmark, T0==#0
                                                                                                                                                                                                                                                             
;-----------------------------------------------------------------------
; radix-2 stages (stages 3->log2(iFFT_SIZE) )  
;         register usage
;         ar0->Pr, ar1->Qr, ar3->twiddle32
;         ar4=Re distance of butterfly
;         ar6=group count, t1=butterfly count, ar5= stage count  
;-----------------------------------------------------------------------
        ; main initialization                
                
        ; modify ST2 to select linear or circular addressing modes
        OR      #0x3, mmap(ST2_55)             ; circular AR0LC,AR1LC
        MOV     *SP(data_ptr), AR1             ; AR1 = #ifftdata  

        ; circular buffer starting addresses                            
        MOV     AR1, mmap(BSA01)               ; circular buffer start address
               
        ; circular buffer sizes 
        MOV     *SP(data_sz) << #2,AC0 
        MOV     AC0, mmap(BK03)                ; BK03 = (4*iFFT_SIZE-4), AR0-AR3
        
        MOV     *SP(data_sz), AR4
        SFTS    AR4,#-1                        ; AR4 = iFFT_SIZE/2(Re distance between p q)
     || MOV     #4, AR6                        ; AR6 = group    
        MOV     T0, AR5        
     || MOV     #-2, T2
        SFTS    AR5, #-1                        ; AR5=size/16;  AR5 is stage count
        MOV     T0, T1                         ; T1 = iFFT_SIZE/8, nbfly
        AMOV    #twiddle32, XAR3
        MOV     #2, T0
     || BCC     last_stage, AR5 == #0                                                                                

;-----------------------------------------------------------------------
; Beginning of the stage loop
;         stage iniac1alizaac1on
;-----------------------------------------------------------------------
stage:  ; stage loop counter updates     
        SFTS    AR5, #-1                       ; shift right stage count  
        MOV     #0,AR0                
     || MOV     AR3, CDP
        ADD     #1,AR4,AR1                     ;AR1->QR_LOW
                                   
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

                        MAS     uns(*AR1(T0)), *CDP+, AC0       ; AC0 -= yil*cih (3,2)
                     :: MAC     uns(*AR1+), *CDP+, AC1          ; AC1 += yrl*cih (1,2)
                     || SWAP    T0, T2                          ; T0=-2

                        MAS     *AR1, uns(*(CDP+T0)), AC0       ; AC0 -= yih*cil (2,3)
                     :: MAC     *AR1(T0), uns(*(CDP+T0)), AC1   ; AC1 += yrh*cil (0,3)

                        MAC     *AR1(T0), uns(*CDP-), AC0       ; AC0 += yrh*crl (0,1)
                     :: MAC     *(AR1+T0), uns(*CDP-), AC1      ; AC1 += yih*crl (2,1)
                     || SWAP    T0, T2                          ; T0=2

                        MAC     *AR1, *(CDP+T0), AC0>>#16       ; AC0 += yrh*crh (0,0)
                     :: MAC     *AR1(T0), *(CDP+T0), AC1>>#16   ; AC1 += yih*crh (2,0)

                        MAS     *AR1(T0), *(CDP+T0), AC0        ; AC0 -= yih*cih (2,2)
                     :: MAC     *AR1, *(CDP+T0), AC1            ; AC1 += yrh*cih (0,2)        
                
                        ADD     dbl(*AR0), AC0,AC2        
                        SFTS    AC2, #-1
                     || MAR     *CDP-    
                        MOV     AC2,dbl(*AR0)                   ; new xr=ac0+xr  (0,4)
                     || SUB     AC0,dbl(*AR0+),AC3              ;                (0,4)
                        SFTS    AC3, #-1
                     || MAR     *CDP-
                        MOV     AC3, dbl(*AR1+)                 ; new yr=xr-ac0  (2,4)
                     || SUB     AC1,dbl(*AR0), AC2
                        SFTS    AC2, #-1
                     || MAR     *CDP-   
                        MOV     AC2, dbl(*AR1+)                 ; new yi=xi-ac1  (2,4) 
                     || ADD     dbl(*AR0),AC1,AC3               ;                (4,4)
                        SFTS    AC3, #-1
                     || MAR     *CDP-   
                        MOV     AC3, dbl(*AR0+)                 ; new xi=xi+ac1
                     || AADD    #1, AR1                         ;                (4,4) 
BFly:
                                                                                                                                                                                                                                                                                                                                                                                                                                                              
                AADD    AR4, AR0                                ;jump to next group
                AADD    AR4, AR1 
                AMAR    *+CDP(4)                                ;CDP+4
group:
                
        SFTS    AR6, #1                                         ;group<<1
        SFTS    T1, #-1                                         ;butterfly>>1
        SFTS    AR4, #-1                                        ;P Q distance>>1
     || BCC     stage, AR5 != #0               
;-----------------------------------------------------------------------
; END radix-2 stages (stages 3->log2(iFFT_SIZE) )  
;-----------------------------------------------------------------------

;-----------------------------------------------------------------------
; Last stage
;-----------------------------------------------------------------------                
last_stage:
        ; stage initialization
        MOV     AR3, CDP                                  
        MOV     #5, AR1                                  ;AR1->QR_LOW
        MOV     #0, AR0                 
        
        ; group counter update
     || SUB     #1, AR6
        MOV     AR6, BRC0              
        MOV     #6, T1
             
     || RPTBLOCAL lgroup-1
                MPY     uns(*AR1), *(CDP+T0), AC0       ; AC0  = yrl*crh (1,0)
             :: MPY     uns(*AR1(T0)), *(CDP+T0), AC1   ; AC1  = yil*crh (3,0)

                MAS     uns(*AR1(T0)), *CDP+, AC0       ; AC0 -= yil*cih (3,2)
             :: MAC     uns(*AR1+), *CDP+, AC1          ; AC1 += yrl*cih (1,2)
             || SWAP    T0, T2                          ; T0=-2

                MAS     *AR1, uns(*(CDP+T0)), AC0       ; AC0 -= yih*cil (2,3)
             :: MAC     *AR1(T0), uns(*(CDP+T0)), AC1   ; AC1 += yrh*cil (0,3)

                MAC     *AR1(T0), uns(*CDP-), AC0       ; AC0 += yrh*crl (0,1)
             :: MAC     *(AR1+T0), uns(*CDP-), AC1      ; AC1 += yih*crl (2,1)
             || SWAP    T0, T2                          ; T0=2

                MAC     *AR1, *(CDP+T0), AC0>>#16       ; AC0 += yrh*crh (0,0)
             :: MAC     *AR1(T0), *(CDP+T0), AC1>>#16   ; AC1 += yih*crh (2,0)

                MAS     *AR1(T0), *(CDP+T0), AC0        ; AC0 -= yih*cih (2,2)
             :: MAC     *AR1, *(CDP+T0), AC1            ; AC1 += yrh*cih (0,2)

                ADD     dbl(*AR0), AC0,AC2
                MOV     AC2,dbl(*AR0)                   ; new xr=ac0+xr  (0,4)
             || SUB     AC0,dbl(*AR0+),AC3              ;                (0,4)

                MOV     AC3, dbl(*AR1+)                 ; new yr=xr-ac0  (2,4)
             || SUB     AC1,dbl(*AR0), AC2

                MOV     AC2, dbl(*(AR1+T1))             ; new yi=xi-ac1  (2,4)
             || ADD     dbl(*AR0),AC1,AC3               ;                (4,4)

                MOV     AC3, dbl(*(AR0+T1))             ; new xi=xi+ac1:  jump to next group                                                         
             || AADD    #1, AR1                         ;                (4,4) 
lgroup:
;-----------------------------------------------------------------------
; END last stage
;-----------------------------------------------------------------------
                                                
end_benchmark:
;-----------------------------------------------------------------------
; Deallocate the local frame and argument block
;----------------------------------------------------------------
        AADD    #+(ARG_BLK_SZ + FRAME_SZ), SP

;Context restore 
        POPBOTH XAR7
     || BCLR    #AR0LC, ST2_55          
        POPBOTH XAR6
     || BCLR    #AR1LC, ST2_55          
        POPBOTH XAR5
     || BSET    #ARMS, ST2_55          
        POP     T3, T2
     || BCLR    #FRCT, ST1_55          
        RET 
     || BCLR    M40             
                .end         
        
