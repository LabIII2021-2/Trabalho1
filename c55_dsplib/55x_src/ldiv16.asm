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
; Function:    ldiv16
; Processor:   C55xx
; Description: Implements long division function.  Reciprocal of Q15, y 
; 	       is calculated then multiplied times Q31 x. C-callable.
;
; Usage: void ldiv16(LDATA *x, 
;                    DATA *y, 
;                    DATA *z, 
;                    DATA *zexp, 
;                    ushort nx)
;
; Algorithm:
;     This routine returns the fractional and exponential portion
;  of the division in the form of :
;          
;               z[i] * zexp[i] = reciprocal
;
; Benchmarks:
;   Cycles:       (29 * nx) + 27
;   Code Size (in bytes):  123
;
; History:
;         07/07/2003 - d. elam fixed bug in range test 
;         05/25/2012 - Craig Leeds: optimize by 45%
;****************************************************************
   
      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 2            ;save-on-entry registers saved
FRAME_SZ          .set 2            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
      .asg     AR0, x_ptr           ;linear pointer
      .asg     AR1, y_ptr            ;linear pointer
      .asg     AR2, z_ptr           ;linear pointer
      .asg     AR3, zexp_ptr        ;linear pointer
                   
      .global _ldiv16
      
      .text
_ldiv16:


;
; Allocate the local frame and argument block
;----------------------------------------------------------------
;      SP = SP - #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

;
; Save any save-on-entry registers that are used
;----------------------------------------------------------------
; - nothing to save for this function

;
; Configure the status registers as needed.
;----------------------------------------------------------------
        PSH     T2, T3
     || BCLR    ARMS
        AADD    #-(2+1), SP
     || BSET    FRCT
        BCLR    SMUL
        BSET    M40
;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing
; z pointer - passed in its destination register, need do nothing
; zexp  pointer - passed in its destination register, need do nothing
; Set circular/linear ARx behavior
;
; Setup loop counts
;----------------------------------------------------------------
        SUB     #1, T0                   ;T0 = n-1
        AMAR    *SP(0), XAR4
        MOV     T0, BRC0                 ;outer loop executes n times
        MOV     #3-1, BRC1               ;repeat inner loop 3x
        AMOV    #3, T0
        ADD     #1, x_ptr                ; x_ptr = &x[0].Lo
        
                MOV     *y_ptr+ << #16, AC1       ;load first input value (Prime the Pump)
                MANT    AC1, AC3                  ;calculate normalization of 1st value (Prime the Pump)
              ::NEXP    AC1, T1                   ; (Prime the Pump)
                NEG     T1                        ;exponent value for the offset pointer (Prime the Pump)
                ADD     #1, T1                    ;offset pointer to exponent (Prime the Pump)
              ||SFTS    AC3, #-1, AC2             ;shift right by one for 1st approximation (Prime the Pump)
                XOR     #0x1FFF << #16, AC2       ;estimate the first Ym value (Prime the Pump)
;
; Start of outer loop
;----------------------------------------------------------------
     || RPTBLOCAL OuterLoopEnd-1                  ;start the outer loop 
                MOV     HI(AC2), *AR4             ;store first Ym

; First two iterations      Calculate Ym = 2*Ym - Ym^2*X
                ||RPTBLOCAL InnerLoopEnd-1
                        MOV     *AR4 << #15, AC0
                     || MPYM    T3 = *AR4, AC3, AC2
                        MAS     T3, AC2, AC0
                        MOV     HI(saturate(AC0 << #2)), *AR4
InnerLoopEnd:

;-------------------------------------------------------------------------
; Check if value is in range 8000h <= Ym <= 7fffh, Adjust sign of result
;-------------------------------------------------------------------------
                MOV     HI(saturate(AC0 << #3)), *AR4                
             || MOV     *y_ptr+ << #16, AC1       ;load first input value (for next iteration)
;-------------------------------------------------------------------------
; Multiply numerator by reciprocal of denominator
;-------------------------------------------------------------------------
                MPYM    *AR4, uns(*x_ptr-), AC2             ;numerator low  * denominator high; x_ptr = &x[i].Hi
                MACMR   *AR4, *(x_ptr+T0), AC2 >> #16, AC2  ;numerator high * denominator high; x_ptr = &x[i+1].Lo
                
                MANT    AC2, AC2
                ::NEXP  AC2, T2                   ;calculate normalization of 1st value
                ADD     T1, T2                    ;offset pointer to exponent values
             || MOV     #1, AC0
        
                MANT    AC1, AC3                  ;calculate normalization of 1st value (for next iteration)
              ::NEXP    AC1, T1                   ; (for next iteration)
             || XCCPART  T2 < #0
                       SFTS    AC2, T2, AC2
                    || MOV     #0, T2

                MOV     HI(AC2), *z_ptr+
             || NEG     T1                        ;exponent value for the offset pointer (for next iteration)
                ADD     #1, T1                    ;offset pointer to exponent (for next iteration)
             || SFTS    AC3, #-1, AC2             ;shift right by one for 1st approximation (for next iteration)
                XOR     #0x1FFF << #16, AC2       ;estimate the first Ym value (for next iteration)
             || SFTS    AC0, T2, AC0              ;calculate exponent value
                MOV     AC0, *zexp_ptr+           ;store exponent
                
OuterLoopEnd:                                     ;end of outer loop

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
; - nothing to restore for this function
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)
; Return to calling function
;----------------------------------------------------------------

        AADD    #+(2+1), SP
     || BCLR    FRCT               ; restore for C
        BCLR    M40                ; restore for C
        POP     T2, T3
     || BSET    ARMS               ; set ARMS for C
        BSET    SMUL               ; restore for C
     || RET                        ; return to calling function

        
;----------------------------------------------------------------
;End of file
