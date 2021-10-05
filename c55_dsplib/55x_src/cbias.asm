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
; Function:    corr_bias
; Processor:   C55xx
; Description: biased full length correlation of two vectors
;
; Usage: ushort corr_bias  (DATA *x, DATA *y, DATA *r, ushort nx, ushort ny);
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
;        For nx and ny = 128:     9068
;        For nx and ny = 100:     5708
;        For nx and ny =  64:     2540
;        For nx and ny =  50:     1622x
;        For nx and ny =  32:      812
;        For nx and ny =  24:      540
;        For nx and ny =  16:      332
;        For nx and ny =   8:      188
;   Code Size (in bytes):  338
;
; History:
; - Changed save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
;   Li Yuan - 08/14/01
;
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;       Zhengting He - 10/25/2006
;
; - Fixed bug where CDPH never set
; - Fixed bug where AR5 was modified but not correctly restored
; - Fixed bug where T3 was modified but not correctly restored
; - Bug fixed where AC0 and AC1 checked for overflow, but bit not cleared on entry
; - Some optimizations of RPTBLOCAL blocks
;       Craig Leeds - 06/10/2012
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names
      .global _corr_bias

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 5            ;save-on-entry registers saved (T2, T3, AR5, AR6, AR7)
FRAME_SZ          .set 2            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------
        

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ        
        .asg    0, temp
        .asg    1, n_inverse
        .asg    "0 + REG_SAVE_SZ + FRAME_SZ", RETURN_ADDR
        
        .asg    XAR0, Xx_ptr
        .asg     AR0,  x_ptr
        .asg    XAR1, Xy_ptr
        .asg     AR1,  y_ptr
        .asg    XAR2, Xr_ptr
        .asg     AR2,  r_ptr
        .asg     AR3,  region1_and_3_loop_cnt
        .asg    XAR4, Xx_save
        .asg     AR4,  x_save
        .asg    XAR5, Xy_save
        .asg     AR5,  y_save    
        .asg    XAR6, Xx2_save
        .asg     AR6,  x2_save
        .asg    XAR7, Xy_orig
        .asg     AR7,  y_orig    
        
        .asg    T0, nx             ; argument
        .asg    T1, ny             ; argument
        .asg    T2, mac_cnt
    
; bug: original return value in AC0
; fix: put in T0
        .asg    T0, oflag           ;returned value
        
        .text
_corr_bias:
;
; Allocate the local frame and argument block( +1 is for dbl alignment)
;----------------------------------------------------------------
        PSH     T2, T3
     || BCLR    ARMS
        PSHBOTH XAR5
     || BSET    #ST1_FRCT, ST1_55
        PSHBOTH XAR6
        PSHBOTH XAR7
     || BCLR    ACOV1                        ; clear overflow bit
        
        AADD    #-(ARG_BLK_SZ + FRAME_SZ), SP
;
; Save any save-on-entry registers that are used
; Configure the status registers as needed.
;----------------------------------------------------------------

        

;---------- X pointer setup    
; x_ptr                -        X pointer as passed
; x_save        -        X+nx
; x2_save        -        Unchanged original X pointer
        MOV     Xx_ptr, Xx2_save
        MOV     Xx_ptr, AC0
        ADD     nx, AC0
        MOV     AC0, Xx_save
;
; Calculate inverse of number of MACs  = nx                 
; We load Q15 equivalent of 1 into accumulator and use SUBC 
; Thus calculating Q15 equivalent of 1/N                    
;----------------------------------------------------------------
        
        MOV     nx, *SP(#(temp))
        MOV     #32767, AC0
        
        RPT     #16-1
                SUBC    *SP(#(temp)), AC0, AC0
        
        ADD     #1, AC0
     || BCLR    ACOV0                        ; clear overflow bit
        MOV     AC0, *SP(#(n_inverse))
         
;---------- Y pointer setup    
; y_ptr                -        Y pointer as passed
; y_orig                -        Unchainged original Y pointer
        MOV     Xy_ptr, Xy_save
        MOV     Xy_ptr, Xy_orig

; Initialize MAC cnt for regions 1 & 3, these will be          
; calculated in one loop, since the number of elements is the  
; same in each region.                                         
;----------------------------------------------------------------
        MOV     nx, AC1
        SUB     #4, AC1
        MOV     AC1, region1_and_3_loop_cnt
        SUB     #1, x_save

; ---- ODD detection ----
; Due to the Dual MAC, we need to know if the region 1 and region 3
; are odd or even in length. If the number is odd, then we will need
; to do an extra MAC outside of the loop.
        BTST    @#0, region1_and_3_loop_cnt, TC1

;        
; Initial lag is in region 1, load initial MAC count and      
; number of elements to calculate in region 1                 
;----------------------------------------------------------------

REGION1:
; ---- Pointer setup -----
        MOV     y_save, y_ptr
        MOV     x_save, x_ptr
        
; ---- Initialize BRC and mac_cnt -----
        SFTL     region1_and_3_loop_cnt, #-1
        XCCPART !TC1
             || SUB     #1, region1_and_3_loop_cnt
        MOV     region1_and_3_loop_cnt, BRC0
        
        MOV     #0, mac_cnt
                
        MPYM    *x_ptr, *y_ptr+, AC0
        MPYMR   *SP(#(n_inverse)), AC0, AC0
        MOV     HI(AC0), *r_ptr+

; ---- 2 -----        
        MPYM    *x_ptr-, *y_ptr-, AC0  
        MACM    *x_ptr, *y_ptr, AC0
        MPYMR   *SP(#n_inverse), AC0, AC0
        MOV     HI(AC0), *r_ptr+    

; ---- Pointer stuff ----                   
        ADD     #2, y_save
        MOV     Xx_save, XCDP
        MOV     y_save, x_ptr
        ADD     #1, x_ptr, y_ptr
                                                
        BCC REGION1_LOOP, TC1

; ---- 3 -----        
        MPYM    *x_ptr-, *CDP-, AC0
        MACM    *x_ptr-, *CDP-, AC0
        MACM    *x_ptr-, *CDP-, AC0
        
        MPYMR   *SP(#(n_inverse)), AC0, AC0
        
        MOV     HI(AC0), *r_ptr+
        
        ADD     #1, y_save
        MOV     Xx_save, XCDP

        MOV     Xy_save, Xx_ptr
        ADD     #1, x_ptr, y_ptr
        ADD     #2, mac_cnt

REGION1_LOOP:
        MOV     mac_cnt, CSR
        MOV     *SP(#n_inverse), T3

     || RPTBLOCAL endlocal1-1
                ADD     #2, y_save
    
                MPY     *x_ptr-, *CDP-, AC0 
             :: MPY     *y_ptr-, *CDP-, AC1
        
; ---- Main Dual MAC loop  ----   
             || RPTADD  CSR, #2
                        MAC     *x_ptr-, *CDP-, AC0 
                     :: MAC     *y_ptr-, *CDP-, AC1
        
; ---- Cleanup MAC ----
                MACM    *y_ptr-, *CDP, AC1
             || MOV     y_save, x_ptr
                MPYR    T3, AC0, AC0
        
; ---- Reload Pointers ----        
             || MOV     x_save, CDP
                AMAR    *y_save(#1), Xy_ptr

; ---- BIAS AC0 and AC1  ----
                MPYR    T3, AC1, AC1

; ---- Store ----    
             || MOV     HI(AC0), *r_ptr+
                MOV     HI(AC1), *r_ptr+ 
endlocal1:

; ---- Reload Pointers ----        
        MOV     Xy_orig, Xy_save
        MOV     x2_save, x_save

;
; Begin Loop for Region 2:                                      
;----------------------------------------------------------------

REGION2:
        MOV     ny, T3
        SUB     nx, T3
        MOV     T3, BRC0
    
        MOV     x_save, x_ptr
        MOV     y_save, y_ptr

        SUB     #3, nx, mac_cnt
        MOV     mac_cnt, CSR
        MOV     *SP(#n_inverse), T3

     || RPTBLOCAL localend2-1
        
; ---- Setup pointers ----
                ADD     #1, y_save

; ---- Preload AC0 ----
                MPYM    *x_ptr+, *y_ptr+, AC0
        
; ---- Main MAC loop  ---- 
;        MOV mac_cnt, CSR
             || RPT     CSR
                        MACM    *x_ptr+, *y_ptr+, AC0, AC0        
        
; ---- Cleanup ----
                MACM    *x_ptr+, *y_ptr+, AC0, AC0        
             || MOV     x_save, x_ptr
                MPYR    T3, AC0, AC0
        
; ---- Setup for subsequent passes through Region 2 ----     
             || AMOV    y_save, y_ptr

; ---- Store ----      
                MOV     HI(AC0), *r_ptr+
localend2:        

;
; Begin REGION3 loop:                                           
;----------------------------------------------------------------

REGION3:

        MOV     region1_and_3_loop_cnt, BRC0
        MOV     x_save, CDP
        MOV     y_save, x_ptr
        ADD     #1, x_ptr, y_ptr

        MOV     nx, mac_cnt
        SUB     #4, mac_cnt
        MOV     mac_cnt, CSR
        MOV     *SP(#n_inverse), T3

     || RPTBLOCAL localend3-1
                ADD     #2, y_save
; ---- Preload AC0 ----
                MPY     *x_ptr+, *CDP+, AC0 
             :: MPY     *y_ptr+, *CDP+, AC1
; ---- Main Dual MAC loop  ----   
             || RPTSUB  CSR, #2
                        MAC     *x_ptr+, *CDP+, AC0
                     :: MAC     *y_ptr+, *CDP+, AC1
; ---- Cleanup ----     
                MACM    *x_ptr, *CDP, AC0
; ---- Setup Pointers ----    
             || MOV     x_save, CDP
; ---- BIAS AC0 and AC1  ----
                MPYR    T3, AC0, AC0
             || ADD     #1, y_save, y_ptr
                MPYR    T3, AC1, AC1
; ---- Store ----    
             || MOV     HI(AC0), *r_ptr+
                MOV     HI(AC1), *r_ptr+ 
             || AMOV    y_save, x_ptr
localend3:        
;        }

;
; Calculate last correlation elements outside of loop       
;----------------------------------------------------------------
        BCC REGION3_FINAL, TC1

; ---- 3 -----
        MPYM    *x_ptr+, *CDP+, AC0
        MACM    *x_ptr+, *CDP+, AC0
        MACM    *x_ptr+, *CDP+, AC0

        MPYMR   *SP(#(n_inverse)), AC0, AC0
        
        MOV     HI(AC0), *r_ptr+
        
        ADD     #1, y_save
        MOV     x_save, CDP
        MOV     y_save, x_ptr
     
REGION3_FINAL:
; ---- 2 -----
        MPYM    *x_ptr+, *CDP+, AC0
        MACM    *x_ptr, *CDP-, AC0
        MPYMR   *SP(#(n_inverse)), AC0, AC0
        MOV     HI(AC0), *r_ptr+    

; ---- 1 -----
        MPYM    *x_ptr, *CDP, AC0
        MPYMR   *SP(#(n_inverse)), AC0, AC0
        MOV     HI(AC0), *r_ptr+    

; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
; bug: original code put return value in AC0
; fix: put in oflag
        MOV     #0, oflag
        XCCPART overflow(AC0)
             || MOV     #1, oflag
        XCCPART overflow(AC1)
             || MOV     #1, oflag
        
;                
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
        AADD    #+(ARG_BLK_SZ + FRAME_SZ), SP
        POPBOTH XAR7
     || BSET    ARMS
        POPBOTH XAR6
     || BCLR    FRCT
        POPBOTH XAR5
        POP     T2, T3
;
; Return to calling function
;----------------------------------------------------------------
        RET
;----------------------------------------------------------------
;End of file


