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
; Function:    corr_raw
; Processor:   C55xx
; Description: raw full length correlation of two vectors
;
; Usage:  ushort corr_raw (DATA *x, DATA *y, DATA *r, ushort nx, ushort ny);
;
; Notes:
;   If y[] is in SARAM instead of DARAM, the function will take twice as many cycles.
;
; Limitations:
;   ny >= nx
;   x[] must be on-chip (i.e. DARAM or SARAM)
;
; Benchmarks:
;   Cycles:
;      Cycle computations are very complicated.
;        For nx and ny = 128:     9032
;        For nx and ny = 100:     5672
;        For nx and ny =  50:     1622
;        For nx and ny =  16:      309
;        For nx and ny =   8:      152
;   Code Size (in bytes):  309
;
; History:
; - Modified save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
;   Li Yuan - 08/14/01
;
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;       Zhengting He - 10/25/2006
;
; - Bug fixed where T3 was modified but not restored.
; - Bug fixed where AC0 and AC1 checked for overflow, but bit not cleared on entry
; - Some optimizations of RPTBLOCAL blocks
;       Craig Leeds - 06/10/2012
;
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names
      
        .global _corr_raw

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 5            ;save-on-entry registers saved (T2, T3, AR5, AR6, AR7)
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ        
        .asg    0 + REG_SAVE_SZ + FRAME_SZ, RETURN_ADDR

        .asg    AR0, x_ptr
        .asg    XAR0, Xx_ptr
        .asg    AR1, y_ptr
        .asg    XAR1, Xy_ptr
        .asg    AR2, r_ptr
        .asg    AR3, mac_cnt
        .asg    AR4, x_save
        .asg    XAR4, Xx_save
        .asg    AR6, x2_save
        .asg    XAR6, Xx2_save
        .asg    AR5, y_save
        .asg    XAR5, Xy_save
        .asg    AR7, y_orig
        .asg    XAR7, Xy_orig

        .asg    T0, nx                      ; input arg
        .asg    T1, ny                      ; input arg
        .asg    T2, region1_and_3_loop_cnt
        
        .asg    T0, oflag                   ; for C55, return value in T0
        
        .text
_corr_raw:
;
; Allocate the local frame and argument block( +1 is for dbl alignment)
;----------------------------------------------------------------
; Save any save-on-entry registers that are used
; Configure the status registers as needed.
;----------------------------------------------------------------
        PSH     T2, T3
     || BCLR    ARMS                        ; clear ARMS
        PSHBOTH XAR5
     || BSET    #ST1_FRCT, ST1_55
        PSHBOTH XAR6
     || BCLR    ACOV0                        ; clear overflow bit 
        PSHBOTH XAR7
     || BCLR    ACOV1                        ; clear overflow bit 
        
;---------- X pointer setup    
; x_ptr                -        X pointer as passed
; x_save        -        X+nx
; x2_save        -        X
        MOV     Xx_ptr, Xx2_save ;
        MOV     Xx_ptr, Xx_save ;
        MOV     x_ptr, AC0
        ADD     nx, AC0
        MOV     AC0, x_save
        
;---------- Y pointer setup    
; y_ptr                -        Y pointer as passed
; y_orig        -        Unchainged original Y pointer
        MOV     Xy_ptr, Xy_save
        MOV     Xy_ptr, Xy_orig
        
; Initialize MAC cnt for regions 1 & 3, these will be          
; calculated in one loop, since the number of elements is the  
; same in each region.                                         
;----------------------------------------------------------------
        MOV     nx, AC1
        SUB     #4, AC1
;    region1_and_3_loop_cnt = AC1
        MOV     AC1, region1_and_3_loop_cnt
        SUB     #1, x_save

; ---- ODD detection ----
; Due to the Dual MAC, we need to know if the region 1 and region 3
; are odd or even in length. If the number is odd, then we will need
; to do an extra MAC outside of the loop.
;
; Test to see if the LSB 
; of NR is set. If it is, 
; then we have an odd number

        BTST    @#0, region1_and_3_loop_cnt, TC1       ; TC1 set if there is an odd count
        
; Begin Region 1:                                      
;----------------------------------------------------------------
REGION1:
        MOV     Xy_save, Xy_ptr
        MOV     Xx_save, Xx_ptr
                
; For the dual MAC, we need to divide by two followed
; by a subsequent subtraction by 1 only if we have and odd number
; of MAC's to do. 
; region1_and_3_loop_cnt = region1_and_3_loop_cnt >> #1;
        SFTL    region1_and_3_loop_cnt, #-1
; if (odd<#0) execute(d_unit)                                                                
        XCCPART !TC1
                ||SUB     #1, region1_and_3_loop_cnt

        MOV     region1_and_3_loop_cnt, BRC0
        MOV     #0, mac_cnt             ; 2 cycles 

; Calculate first couple of elements outside of the loop     
; ---- 1 -----
        MPYMR   *x_ptr, *y_ptr+, AC0
        MOV     HI(AC0), *r_ptr+
        
; ---- 2 and Pointer stuff ----

        MPYM    *x_ptr-, *y_ptr-, AC0 
     || ADD     #2, y_save

        MACMR   *x_ptr, *y_ptr, AC0, AC0
            
        MOV     Xx_save, XCDP
        MOV     Xy_save, Xx_ptr
        MOV     Xx_ptr, Xy_ptr
        ADD     #1, x_ptr, y_ptr    ; Setup the secondary point in case
                                ; we enter the Dual MAC        
        
        MOV     HI(AC0), *r_ptr+
        
;If there is an even number, skip the extra MAC
        BCC     REGION1_LOOP, TC1
        
; ---- 3 -----
REGION1_extra_mac:
        MPYM    *x_ptr-, *CDP-, AC0 
     || ADD     #1, y_save 

        MACM    *x_ptr-, *CDP-, AC0
        
        MACMR   *x_ptr-, *CDP-, AC0 
     || MOV     x_save, CDP
        
        MOV     Xy_save, Xx_ptr
        MOV     Xx_ptr, Xy_ptr
        ADD     #1, x_ptr, y_ptr
        ADD     #1, mac_cnt
        MOV     mac_cnt, CSR
        MOV     HI(AC0), *r_ptr+

REGION1_LOOP:
        
        RPTBLOCAL endlocal1-1
                ADD     #2, y_save

; ---- Preload AC0 ----
                MPY     *x_ptr-, *CDP-, AC0 
             :: MPY     *y_ptr-, *CDP-, AC1
        
; ---- Main Dual MAC loop  ----        
             || RPTADD  CSR, #2
                        MAC     *x_ptr-, *CDP-, AC0 
                     :: MAC     *y_ptr-, *CDP-, AC1

; ---- Cleanup MAC ----
                MACMR   *x_ptr, *CDP, AC0
            ||  AMOV    y_save, x_ptr
                MACM    *y_ptr-, *CDP-, AC1
                MACMR   *y_ptr, *CDP, AC1

; ---- Reload Pointers ----        
; ---- Store ----    
             || MOV     x_save, CDP
                MOV     HI(AC0), *r_ptr+
             || AMOV    y_save, y_ptr
                MOV     HI(AC1), *r_ptr+
             || AADD    #1, y_ptr   
endlocal1:        

; ---- Reload Pointers ----        
        MOV     Xy_orig, Xy_save
        MOV     Xx2_save, Xx_save

;
; Begin Loop for Region 2:                                      
;----------------------------------------------------------------
REGION2:
        
        MOV     Xx_save, Xx_ptr
        MOV     Xy_save, Xy_ptr

        SUB     #3, nx, mac_cnt
        MOV     mac_cnt, CSR

        MOV     ny, T3
        SUB     nx, T3
        MOV     T3, BRC0

        RPTBLOCAL localend2-1
; ---- Setup pointers ----
                ADD     #1, y_save
        
; ---- Preload A ----
                MPYM    *x_ptr+, *y_ptr+, AC0
    
; ---- Main MAC loop  ---- 
             || RPT     CSR
                        MACM     *x_ptr+, *y_ptr+, AC0, AC0

; ---- Cleanup ----
                MACMR   *x_ptr+, *y_ptr+, AC0, AC0
             || MOV     x_save, x_ptr
        
; ---- Setup for subsequent passes through Region 2 ----     
                AMOV    y_save, y_ptr
        
; ---- Store ----      
             || MOV     HI(AC0), *r_ptr+
localend2:        

;
; Begin REGION3 loop:                                           
;----------------------------------------------------------------
REGION3:

        MOV     Xx_save, XCDP
        MOV     Xy_save, Xx_ptr
        MOV     Xx_ptr, Xy_ptr
        ADD     #1, x_ptr, y_ptr

    ; We are re-loading mac_cnt to remove the dependency 
    ; from the region 2 setup code
        SUB     #5, nx, mac_cnt
        MOV     mac_cnt, CSR
        MOV     region1_and_3_loop_cnt, BRC0
        
        RPTBLOCAL localend3-1
                ADD     #2, y_save
; ---- Preload A ----
                MPY     *x_ptr+, *CDP+, AC0 
             :: MPY     *y_ptr+, *CDP+, AC1
; ---- Main Dual MAC loop  ----        
             || RPTSUB  CSR, #2
                        MAC     *x_ptr+, *CDP+, AC0 
                     :: MAC     *y_ptr+, *CDP+, AC1
; ---- Cleanup MAC ----
                MACMR   *y_ptr, *CDP, AC1
                MACM    *x_ptr+, *CDP+, AC0
             || AMOV    y_save, y_ptr
                MACMR   *x_ptr, *CDP, AC0
; ---- Reload Pointers ----        
             || MOV     x_save, CDP
; ---- Store ----    
                MOV     HI(AC0), *r_ptr+
             || AMOV    y_save, x_ptr
                MOV     HI(AC1), *r_ptr+
             || AADD    #1, y_ptr
localend3:        

;
; Calculate last correlation elements outside of loop       
;----------------------------------------------------------------
        BCC     REGION3_FINAL, TC1

; ---- 3 -----
        MPYM    *x_ptr+, *CDP+, AC0 
     || ADD     #1, y_save
        
        MACM    *x_ptr+, *CDP+, AC0
        MACMR   *x_ptr, *CDP, AC0
    
        MOV     Xx_save, XCDP
        MOV     Xy_save, Xx_ptr
        MOV     HI(AC0), *r_ptr+

; ---- 2 -----
REGION3_FINAL:
        MPYM    *x_ptr+, *CDP+, AC0
        MACMR   *x_ptr, *CDP-, AC0
        MOV     HI(AC0), *r_ptr+

; ---- 1 -----
        MPYM    *x_ptr, *CDP, AC0
        MOV     HI(AC0), *r_ptr+
        
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
        MOV     #0, oflag
        XCCPART overflow(AC0)
                || MOV #1, oflag                 ; 
        
        XCCPART overflow(AC1)
                || MOV #1, oflag 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;        
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
      
        POPBOTH XAR7
     || BSET    ARMS                        ; set ARMS for C
        POPBOTH XAR6
     || BCLR    #ST1_FRCT, ST1_55           ; clear FRCT for C
        POPBOTH XAR5
        POP     T2, T3
; Return to calling function
;----------------------------------------------------------------
        RET
;----------------------------------------------------------------
;End of file
