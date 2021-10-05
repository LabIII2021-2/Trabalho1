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
; Function:    recip16
; Processor:   C55xx
; Description: Calculates reciprocal of Q15 number. C-callable.
;
; Usage: void recip16 (DATA *x, DATA *z, DATA *zexp, ushort nx)
;                                                              
; Benchmarks:
;   Cycles:       (18 * nx) + 14
;   Code Size (in bytes):  83
;
; History:
;   1.01  A. Jaffe  1/25/99 - Updated register usage using previous work 
;   by Alex Tessarolo and Jeff Axelrod.
;         07/07/2003 - fixed bug in range test 
;  05/22/2012 - Craig Leeds:
;      - Fixed bugs in ending of repeat blocks
;      - Optimized by 40%
;
;****************************************************************
;  Description:
;
;     This routine returns the fractional and exponential portion
;  of the reciprocal of a Q15 number. Since the reciprocal is always
;  greater than 1, it returns an exponent such that:
;          
;               z[i] * zexp[i] = reciprocal
;
;----------------------------------------------------------------
;  Algorithm:
;
;	     +--------------------------+
;	     |	Ym = 2*Ym - Ym^2*Xnorm 	| 		 
;	     +--------------------------+
;
;	If we start with an initial estimate of Ym, then equation
;	will converge to a solution very rapidly (typically
;	3 iterations for 16-bit resolution).
;
;	The initial estimate can either be obtained from a look up 
;	table, or from choosing a mid-point, or simply from linear 
;	interpolation. The method chosen for this problem is the
;	latter. This is simply accomplished by taking the complement
;	of the least significant bits of the Xnorm value.
;
;****************************************************************

      .ARMS_on                      ;enable assembler for ARMS=1
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 0            ;save-on-entry registers saved
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
      .asg     AR0, x_ptr           ;linear pointer
      .asg     AR1, z_ptr           ;linear pointer
      .asg     AR2, zexp_ptr        ;linear pointer
      .asg     T2, ye_ptr           ;table linear pointer
      .asg     T0, norm_ptr         ;temp linear pointer
                   
      
      .global _recip16
      
      .text
_recip16:

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

        BSET    FRCT
     || AADD    #-1,SP
        BCLR    SMUL
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

        SUB     #1, T0                        ;T0=n-1
        MOV     T0, BRC0                ;outer loop executes n times
;
        MOV     XSP, XAR3
        ;;;MOV     #1FFFh << #16, AC3        ;estimate the first Ym value
        MOV     #1, AC2
        
        MOV     *x_ptr+ <<#16, AC0        ;load first input value (prime the pump)
; Start of outer loop
;----------------------------------------------------------------

     || RPTBLOCAL OuterLoopEnd-1                   ;start the outer loop        
                MANT    AC0, AC0                   ;calculate normalization for 1st vlaue
              ::NEXP    AC0, T1
                MOV     HI(AC0), T0                ;store xnorm
             || SFTS    AC0 ,#-1                   ;shift right by 1 for 1st approximation
                XOR     #0x1fff << #16, AC0        ;estimate the first Ym value
                MOV     HI(AC0), *AR3              ;store first Ym
             || NEG     T1                         ;exponent value for offset pointer

; First iteration:  Calculate Ym = 2*Ym - Ym^2*X

                SFTS    AC0, #-1
             || ADD     #1, T1                     ;offset pointer to exponent
                MPYM    *AR3, T0, AC1
             || SFTL    AC2, T1, AC3               ;calculate exponent value
                MASM    *AR3, AC1, AC0
                MOV     HI(AC0 << #2), *AR3
                
; Second iteration:  Calculate Ym = 2*Ym - Ym^2*X
                
                SFTS    AC0, #1
             || MOV     AC3, *zexp_ptr+           ;store exponent
                MPYM    *AR3, T0, AC1
                MASM    *AR3, AC1, AC0
                MOV     HI(AC0 << #2), *AR3

; final iteration - same as previous two without final command
; Calculate Ym = 2*Ym - Ym^2*X

                SFTS    AC0, #1
             || MPYM    *AR3, T0, AC1
                MASM    *AR3, AC1, AC0
        
;-------------------------------------------------------------------------
; Check if value is in range 8000h <= Ym <= 7fffh, Adjust sign of result
;-------------------------------------------------------------------------
                MOV     HI(saturate(AC0 << #3)), *z_ptr+
             || MOV     *x_ptr+ << #16, AC0       ;load first input value (for next iteration)
OuterLoopEnd:                                     ;end of outer loop

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
; - nothing to restore for this function
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)
;
; Return to calling function
;----------------------------------------------------------------
        AADD    #+1,SP
     || BCLR    FRCT

        RET                                ;return to calling function
     || BSET    SMUL
        ;End of file
