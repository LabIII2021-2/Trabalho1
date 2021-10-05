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
;****************************************************************
; Function:    corr_unbias
; Description: unbiased full length correlation of two vectors
; Processor:   C55xx
;
; Usage:  ushort corr_unbias  (DATA *x, DATA *y, DATA *r, ushort nx, ushort ny);
;
; Notes:
;   If x[] and y[] are in the same memory block, the function will take twice as many cycles.
;   If x[] is in SARAM instead of DARAM, the function will take significantly more cycles.
;   If y[] is in SARAM instead of DARAM, the function will take significantly more cycles.
;
; Limitations:
;   ny >= nx
;   x[] must be on-chip (i.e. DARAM or SARAM)
;   y[] must be on-chip (i.e. DARAM or SARAM)
;
; Benchmarks:
;   Cycles:
;        Cycle computations are very complicated.
;        For nx and ny = 256:     0.60 * (nx * ny) 
;        For nx and ny = 100:     0.75 * (nx * ny) 
;        For nx and ny = 50:      1.00 * (nx * ny) 
;        For nx and ny = 16:      596
;   Code Size (in bytes):  424
;
; History:
; - Modified save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
;   Li Yuan - 08/14/01
;
; - Fixed bug where T3 was modified but not correctly restored
; - Bug fixed where AC0 and AC1 checked for overflow, but bit not cleared on entry
; - Bug fixed where returned overflow flag was always set to 32 
; - Some optimizations of RPTBLOCAL blocks
;       Craig Leeds - 06/10/2012
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names
        .global _corr_unbias

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 5            ;save-on-entry registers saved (T2, T3, AR5, AR6, AR7)
FRAME_SZ          .set (7+1)        ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------
PARAM_OFFSET    .set   REG_SAVE_SZ + FRAME_SZ

        .asg    0, x_orig
        .asg    2, y_orig
        .asg    4, r_orig
        .asg    6, temp
        
        .asg    "0 + REG_SAVE_SZ + FRAME_SZ", RETURN_ADDR

        .asg    XAR0, Xx_ptr        
        .asg     AR0,  x_ptr
        .asg    XAR1, Xy_ptr
        .asg     AR1,  y_ptr
        .asg    XAR2, Xr_ptr
        .asg     AR2,  r_ptr
        .asg    XAR4, Xx_save
        .asg     AR4,  x_save
        .asg    XAR5, Xy_save        
        .asg     AR5,  y_save
        .asg     AR6,  r1_r3_count
        .asg    XAR7, Xr2_ptr
        .asg     AR7,  r2_ptr
        
        .asg     T0, nx              ;input argument
        .asg     T1, ny              ;input argument
        .asg     T2, mac_cnt
        
        .asg     T0, oflag           ;returned value

        .text
_corr_unbias:

;
; Allocate the local frame and argument block
;
; Save any save-on-entry registers that are used
; Configure the status registers as needed.
;----------------------------------------------------------------
        PSH     T2, T3
     || BCLR    ARMS
        PSHBOTH XAR5
     || BSET    #ST1_FRCT, ST1_55
        PSHBOTH XAR6
        PSHBOTH XAR7
        
        AADD    #-(ARG_BLK_SZ + FRAME_SZ), SP

;---------- X pointer setup    
; x_ptr                -        X pointer as passed
; x_save        -        Used extensively in Region 3 and Region 2
; x_orig        -        Unchanged original X pointer
        MOV     Xx_ptr, dbl(*SP(#x_orig))
        ADD     nx, x_ptr
        SUB     #1, x_ptr
        MOV     Xx_ptr, Xx_save
  
;---------- Y pointer setup    
; y_ptr                -        Y pointer as passed
; y_save        -        Y+nx-2 and Y+nx-1 in Region 3
; y_orig                -        Unchainged original Y pointer
        MOV     Xy_ptr, dbl(*SP(#y_orig))
        MOV     y_ptr, AC0
        ADD     nx, AC0
        SUB     #2, AC0
        MOV     Xy_ptr, Xy_save
        MOV     AC0, y_save

;---------- R pointer setup    
; r_ptr                -        R pointer as passed. Eventually used and initialized as r+nx-2
; r2_ptr        -        r+ny
; r_orig        -        Unchainged original Y pointer
        MOV     Xr_ptr,dbl( *SP(#r_orig))
        MOV     r_ptr, AC0
        MOV     r_ptr, AC1
        ADD     nx, AC1
        SUB     #2, AC1
        MOV     AC1, r_ptr
     || ADD     ny, AC0
        MOV     Xr_ptr, Xr2_ptr
        MOV     AC0, r2_ptr

;
; Initialize MAC cnt for regions 1 & 3, these will be          
; calculated in one loop, since the number of elements is the  
; same in each region.                                         
;----------------------------------------------------------------
        SUB     #4, nx, mac_cnt
        SUB     #1, nx, AC0
        MOV     mac_cnt, r1_r3_count


;+++++++++++ BIAS Calculator +++++++++++++++
; Upon entry:
; r_ptr        =        r+nx-2
; r2_ptr        =        r+ny
; mac_cnt        =        nx-4
; temp                =        nx-1
        MOV     mac_cnt, BRC0 
     || MOV     AC0, *SP(#temp)
                
        BCLR    #ST1_SXMD, ST1_55
                
        MOV     #32767, AC1 
     || RPTBLOCAL biasCalcLocalEnd-1
        
                ;Compute bias value
                SUBC    *SP(#temp), AC1, AC0
             || RPT     #15-1
                        SUBC    *SP(#temp), AC0, AC0
    
                ; Adjust the temp value
                ADD     #-1, *SP(#temp)
        
                ;Store bias value twice into output array
                MOV     AC0, *r_ptr-
             || MOV     AC0, *r2_ptr+
biasCalcLocalEnd:
        
        BSET    #ST1_SXMD, ST1_55
        BCLR    ACOV0                        ; clear overflow bit after division loop
        BCLR    ACOV1                        ; clear overflow bit after division loop
                        
;+++++++++++ End of BIAS calculator +++++++++++++++

; ---- ODD detection ----
; Due to the Dual MAC, we need to know if the region 1 and region 3
; are odd or even in length. If the number is odd, then we will need
; to do an extra MAC outside of the loop.
        BTST    @#0, r1_r3_count, TC1

; For the dual MAC, we need to divide by two followed
; by a subsequent subtraction by 1 only if we have and odd number
; of MAC's to do. 

        SFTL    r1_r3_count, #-1
        XCCPART !TC1
             || SUB     #1, r1_r3_count
        MOV     r1_r3_count, BRC0

        SUB     #4, nx, mac_cnt
        
    
; Initial lag is in region 1, load initial MAC count and      
; number of elements to calculate in region 1                 
;----------------------------------------------------------------

REGION1_AND_3:

; ---- Pointer Setup ----
        MOV     Xy_save, Xy_ptr
        MOV     Xy_ptr, Xx_ptr
        SUB     #1, y_ptr, x_ptr
        MOV     Xx_save, XCDP
            
        MOV     mac_cnt, CSR

        ;Reset r_ptr to initial values
        MOV     dbl(*SP(#r_orig)), AC1
        ADD     nx, AC1
        SUB     #2, AC1
        MOV     AC1, Xr_ptr
        SUB     #(2+1), y_save

;--------- Calculate sum in region 1  

     || RPTBLOCAL endlocal1-1
    
; ---- Preload AC0 ----
                MPY     *x_ptr-, *CDP-, AC0 
             :: MPY     *y_ptr-, *CDP-, AC1
        
; ---- Main Dual MAC loop  ----         
             || RPTSUB  CSR, #2
                        MAC     *x_ptr-, *CDP-, AC0
                     :: MAC     *y_ptr-, *CDP-, AC1
                
; ---- Cleanup MAC ----
                MACM    *y_ptr, *CDP, AC1
    
; ---- BIAS AC0 and AC1 and Store ----        
                MPYMR   *r_ptr, AC1, AC1
             || MOV     x_save, CDP
                AMOV    y_save, x_ptr
             || MOV     HI(AC1), *r_ptr-
                MPYMR   *r_ptr, AC0, AC0
                AMAR    *y_save(#1), Xy_ptr
                MOV     HI(AC0), *r_ptr-
             || SUB     #2, y_save
endlocal1:        
; ---- Setup for Region 1 ----       

;---------- Calculate some MAC's outside of the loop
        ADD     #(2+1), y_save
     || BCC     REGION1_FINAL, TC1
        
; ---- 3 -----        
        MPYM    *y_ptr-, *CDP-, AC0
        MACM    *y_ptr-, *CDP-, AC0
        MACM    *y_ptr, *CDP, AC0
        
        MOV     Xx_save, XCDP
        SUB     #1, y_save
        MOV     Xy_save, Xy_ptr
        ; BIAS
        MPYMR   *r_ptr, AC0, AC0        
        
        MOV     HI(AC0), *r_ptr-
        
        ; Setup pointers for next loop


; ---- 2 -----        
REGION1_FINAL:
        MPYM    *y_ptr-, *CDP-, AC0
        MACMR   *y_ptr, *CDP+, AC0
        MOV     HI(AC0 << #-1), *r_ptr-

; ---- 1 -----        
        MPYM    *y_ptr, *CDP, AC0
        MOV     HI(AC0), *r_ptr-

;--------- Calculate sum in region 3                              
        MOV     r1_r3_count, BRC0
        MOV     mac_cnt, CSR

; ---- Pointer Setup ----
        MOV     dbl(*SP(#y_orig)), AC1
        ADD     ny, AC1
        SUB     #1, AC1
        MOV     AC1, Xy_save
        MOV     Xy_save, XCDP

        ; Compute x_save=X+nx-2
        MOV     dbl(*SP(#x_orig)), Xx_save
        ADD     nx, x_save
        SUB     #3, x_save

        MOV     Xx_save, Xy_ptr
        MOV     Xx_save, Xx_ptr
        ADD     #1, y_ptr
        
        ;Reset r2_ptr to initial values
        MOV     dbl(*SP(#r_orig)), AC0
        ADD     ny, AC0
        MOV     AC0, Xr2_ptr

        SUB     #2, x_save
     || RPTBLOCAL localend3-1
        
; ---- Preload AC0 ----
                MPY     *x_ptr-, *CDP-, AC0 
             :: MPY     *y_ptr-, *CDP-, AC1
        
; ---- Main  Dual MAC loop  ----         
             || RPTSUB  CSR, #2
                        MAC     *x_ptr-, *CDP-, AC0 
                     :: MAC     *y_ptr-, *CDP-, AC1

; ---- Cleanup MAC ----
                MACM    *y_ptr, *CDP, AC1
             || MOV     y_save, CDP
        
; ---- BIAS AC0 and AC1 and Store ----        
                MPYMR   *r2_ptr+, AC1, AC1
             || MOV     x_save, x_ptr
                AMAR    *x_save(1), Xy_ptr
                MPYMR   *r2_ptr-, AC0, AC0
                MOV     HI(AC1), *r2_ptr+
                MOV     HI(AC0), *r2_ptr+
             || SUB     #2, x_save
localend3:        

; ---- Setup for Region 3 ----     

; ---- 3 -----        
        ADD     #2, x_save
     || BCC REGION3_FINAL, TC1
        
        ; no need for division since the previous one did it for me already
        
        ; MACs
        MPYM    *y_ptr-, *CDP-, AC0
        MACM    *y_ptr-, *CDP-, AC0
        MACM    *y_ptr, *CDP, AC0
        
                
        ; BIAS
        MPYMR   *r2_ptr, AC0, AC0        
        
        MOV     HI(AC0), *r2_ptr+
         
        ; Setup pointers for next loop
        MOV     Xx_save, XCDP
        MOV     Xy_save, Xy_ptr

; ---- 2 -----        
REGION3_FINAL:
        MPYM    *y_ptr-, *CDP-, AC0
        MACMR   *y_ptr+, *CDP, AC0
        MOV     HI(AC0 << #-1), *r2_ptr+
        
; ---- 1 -----        
        XCC     TC1
             || AMAR    *y_ptr-, *AR7, *cdp+

        MPYM    *y_ptr, *CDP, AC0
        MOV     HI(AC0), *r2_ptr

;--------- Calculate sum in region 2
; ---- BIAS calculation -----        
        BCLR    #ST1_SXMD, ST1_55
        
        ; Actual calculation
        MOV     #32767, AC0
        MOV     nx, *SP(#temp)
     || RPT     #16-1
                SUBC    *SP(#temp), AC0, AC0
        ADD     #1, AC0
        BSET    #ST1_SXMD, ST1_55
        MOV     AC0, *SP(#temp)
        

REGION2:
        ; Repeat setup
        MOV     ny, AC0
        SUB     nx, AC0
        MOV     AC0, T3
        MOV     T3, BRC0
        SUB     #2, nx, mac_cnt
         
        ; R pointer setup
        MOV     nx, AC1
        SUB     #1, AC1
        ADD     dbl(*SP(#r_orig)), AC1
        MOV     AC1, Xr_ptr

        ; Setup pointers
        MOV     dbl(*SP(#y_orig)), Xy_save
        MOV     dbl(*SP(#x_orig)), Xx_save
        MOV     Xx_save, XCDP
        MOV     Xy_save, Xy_ptr
        MOV     mac_cnt, CSR
        MOV     *SP(#temp), T3
        
        RPTBLOCAL r2localloop-1

; ---- Setup pointers ----
                ADD     #1, y_save

; ---- Preload AC0 ----
                MPYM    *y_ptr+, *CDP+, AC0 

; ---- Main MAC loop  ---- 
             || RPT     CSR
                        MACM *y_ptr+, *CDP+, AC0

; ---- Setup for subsequent passes through Region 2 ----     
                MOV     Xx_save, XCDP

; ---- BIAS ----
                MPYR    T3, AC0, AC0
             || AMOV    y_save, y_ptr
        
; ---- Store ----      
                MOV     HI(AC0), *r_ptr+
r2localloop:


; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
        MOV     #0, oflag
        XCCPART overflow(AC0)
             || MOV     #1, oflag 
        XCCPART overflow(AC1)
             || MOV     #1, oflag 
;
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
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
