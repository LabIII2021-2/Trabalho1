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
;  Function:	mmul
;  Description: matrix multiply implementation
;  Usage:   short mmul(	DATA *x1,	XAR0
;			short row1,	T0
;			short col1,	T1
;			DATA *x2,	XAR1
;			short row2,	AR2
;			short col2,	AR3
;			DATA *r);	XAR4
;
; Benchmarks:
;   Cycles:       
;   Code Size (in bytes):  202
;
; History
;  2.10.1 - clear C54CM bit at the begining. Li Yuan 08/08/01
;  3.00.00 - Craig Leeds 05/17/2012
;    Fix bug where T2 and T3 were used but not restored.
;    Optimize.
;                
;****************************************************************
        .mmregs
        .noremark 5684
        .ARMS_off

        .def _mmul
        .text
_mmul:
        PSH     T3,T2
     || BSET    FRCT                    ;fractional mode set
        PSHBOTH XAR5        
     || MOV     T0, T2                  ;T2 = row1
        PSHBOTH XAR6                                
     || MOV     T1, T0                  ;T0 = col1
                                        ;XAR0 = x1
                                        ;T0 = row1
                                        ;T1 = col1
                                        ;XAR1 = x2
                                        ;AR2 = row2
                                        ;AR3 = col2
                                        ;XAR4 = r                                          

;---------------------------------------------------                                        
; Verify that the dimensions of the input matrices are legal, i.e. input1 
; row size = input2 column size; else return input1 as output
;---------------------------------------------------                                        
        SUB     AR2, T0                 ;T0 = col1 - row2
        SUB     #3, T1, T3
        SUB     #4, T2, AR5
        OR      AR5, T3                 ; if col1 < 3 or row1 < 4 then T3 < 0
     || BCC     mmulend, T0 != #0       ;return value FALSE (i.e. T0 != 0)

; Setup temps
	BCLR    ARMS
        MOV     AR3, T0                 ;T0 = col2
                                        ;T1 = col1
                                        ;T2 = row1
        BCLR    ACOV0

; test if usage of Dual-MAC or Single-MAC

        BCLR    ACOV1                   ; Not really necessary since result is Success/Failure and not overflow
     || BCC     mmul_single_mac, T3<#0

;---------------------------------------------------                                        
; Dual-MAC implementation for large matrices
; col1>=3 && row1>=4
;---------------------------------------------------
mmul_dual_mac:
                                        ;---- pointers ----
        MOV     XAR0, XAR3              ;XAR0 = &x1(1,1) (reload reg for XAR2, XAR3)
        MOV     XAR0, XAR2              ;XAR2 = &x1(1,1)
        AADD    T1, AR3                 ;XAR3 = &x1(2,1)
        MOV     XAR1, XCDP              ;XCDP = &x2(1,1)
        MOV     XAR4, XAR5              ;XAR5 = &r(1,1)
        MOV     XAR1, XAR4              ;XAR4 = &x2(1,1) (reload reg for XCDP)
        MOV     XAR5, XAR6              ;XAR6 = &r(1,1) (reload reg for XAR5)

                                        ;---- loop counters ----
        SUB     #1, T0, T3              ;
        MOV     T3, BRC0                ;outer loop count: BRC0 = col2-1
        BTST    #0, mmap(T2), TC1        ;if(row1==even) TC0=0 else TC0=1
        SUB     #3, T1, T3              ;
        MOV     T3, CSR                 ;inner loop count: CSR = col1-3
        SFTL    T2, #-1
        SUB     #1, T2                  ;
        MOV     T2, BRC1                ;mid loop count: BRS1 = (row1>>1)-1
        
        MOV	AR0, T2
        ADD	T1, T2                  ; T2 = &x1[2,1]
        
        ADD	#1, T1

; Perform Matrix Multiply
     || BCC     DualOddOuterLoop, TC1
        

        RPTBLOCAL DualEvenOuterLoopEnd-1
                AMOV    AR0, AR2           ; AR2 points to x1(1,1)
             || RPTBLOCAL DualEvenInnerLoopEnd-1
                        MPY     *AR2+, *(CDP+T0), AC0         ;first iteration
                        ::MPY   *AR3+, *(CDP+T0), AC1         ;
                      ||RPT     CSR                      
                                MAC     *AR2+, *(CDP+T0), AC0
                                ::MAC   *AR3+, *(CDP+T0), AC1
                        MACR    *(AR2+T1), *CDP, AC0          ; last iteration ; AR2 points to next row of x1
                        ::MACR  *(AR3+T1), *CDP, AC1                           ; AR3 points to next row of x1
                        MOV     HI(AC0), *(AR5+T0)            ;store to r
                      ||AMAR    *AR4, XCDP                    ;CDP points to same column of x2 
                        MOV     HI(AC1), *(AR5+T0)            ;store to r
DualEvenInnerLoopEnd:

                AMAR    *AR4+,*AR6+,*CDP+  ; AR4 points to next column of x2
                                           ; AR6 points to next column of r
                                           ; CDP points to next column of x2
                AMOV    T2, AR3            ; AR3 points to x1(2,2)                                        
             || MOV     AR6, AR5           ; AR5 points to next column of r
DualEvenOuterLoopEnd:

        B       mmulret

DualOddOuterLoop:
        ADD     T1, T2
        SUB     #1, T2
     || RPTBLOCAL DualOddOuterLoopEnd-1

                ;----- if(row1==odd) do first row of x using single MAC, then go to Dual MAC
                MPYM    *AR2+, *(CDP+T0), AC0
              ||RPT     CSR                        
                        MACM    *AR2+, *(CDP+T0), AC0
                MACMR   *AR2+, *CDP, AC0
              ||MOV     AR4, CDP                       ;CDP points to same column of x2
                MOV     HI(AC0), *(AR5+T0)             ;store to r
              ||AMOV    T2, AR3                        ;|| AR3 points to next row of x1

                RPTBLOCAL DualOddInnerLoopEnd-1
                        MPY     *AR2+, *(CDP+T0), AC0         ;first iteration
                        ::MPY   *AR3+, *(CDP+T0), AC1         ;
                      ||RPT     CSR                      
                                MAC     *AR2+, *(CDP+T0), AC0
                                ::MAC   *AR3+, *(CDP+T0), AC1
                        MACR    *(AR2+T1), *CDP, AC0          ; last iteration ; AR2 points to next row of x1
                        ::MACR  *(AR3+T1), *CDP, AC1                           ; AR3 points to next row of x1
                        MOV     HI(AC0), *(AR5+T0)            ;store to r
                      ||AMAR    *AR4, XCDP                    ;CDP points to same column of x2 
                        MOV     HI(AC1), *(AR5+T0)            ;store to r
DualOddInnerLoopEnd:

                AMAR    *AR4+,*AR6+,*CDP+  ; AR4 points to next column of x2
                                           ; AR6 points to next column of r
                                           ; CDP points to next column of x2
                AMOV    AR0, AR2           ; AR2 points to x1(1,1)
              ||MOV     AR6, AR5           ; AR5 points to next column of r
DualOddOuterLoopEnd:

        B       mmulret
;---------------------------------------------------                                        
; Single-MAC implementation for small matrices
; col1<3 || row1<4
;---------------------------------------------------
mmul_single_mac:
                                 ;---- pointers ----
        MOV     XAR0, XAR2       ;XAR2 = &x1(1,1)  XAR0 = &x1(1,1) for reload
        MOV     XAR1, XAR3       ;XAR3 = &x2(1,1)  XAR1 = &x2(1,1) for reload
        MOV     XAR4, XAR5       ;XAR5 = &r(1,1)   XAR4 = &r(1,1) for reload

                                 ;---- loop counters ----
        SUB     #1, T0, T3       ;
        MOV     T3, BRC0         ;outer loop count: BRC0 = col2-1
        SUB     #1, T2
        MOV     T2, BRC1         ;mid loop count: BRC1 = row1-1
        SUB     #1, T1
        MOV     T1, CSR          ;inner loop count: CSR = col1-1

; Perform Matrix Multiply

        RPTBLOCAL        SingleOuterLoopEnd-1
                AMAR    *AR4+                   ;AR4 points to next column of r
            ||  RPTBLOCAL SingleInnerLoopEnd-1
                        MOV     #0, AC0                        ;clear AC0
                      ||RPT     CSR                            ;
                                MACM    *AR2+, *(AR3+T0), AC0
                        MOV     RND(HI(AC0)), *(AR5+T0)        ;store rounded result to r        
                      ||AMOV    AR1, AR3                       ;AR3 points back to beginning of same column of x2
SingleInnerLoopEnd:

                AMAR    *AR1+          ;AR1 points to next column of x2
              ||MOV     AR0, AR2       ;AR2 points to x1(1,1)
                AMOV    AR1, AR3       ;AR3 points to next column of x2
              ||MOV     AR4, AR5       ;AR5 points to next column of r                                        
SingleOuterLoopEnd:

mmulret:        
        MOV     #0, T0              ;return value TRUE
      ||BSET    ARMS

mmulend:
        POPBOTH XAR6
      ||BCLR    FRCT
        POPBOTH XAR5
        POP     T3,T2
        RET

