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
; Function:    convol
; Processor:   C55xx
; Description: Implements real convolution algorithm using
;              single-MAC approach.  C-callable.
;
; Usage: ushort oflag = convol(DATA *x,
;                              DATA *h,
;                              DATA *r,
;                              ushort nr,
;                              ushort nh)
; Limitations:
;   nh >= 3
;
; Benchmarks:
;   Cycles:       (nr * (nh + 1)) + 24
;   Code Size (in bytes):  68
;
; History:
;   Craig Leeds 05/24/2012:  Set SMUL on exit; optimized housekeeping
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
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
      .asg     AR1, h_ptr           ;circular pointer
      .asg     AR2, r_ptr           ;linear pointer

      .asg     BSA01, h_base        ;base addr for h_ptr
      .asg     BK03, h_sz           ;circ buffer size for h_sz

      .asg     CSR, inner_cnt       ;inner loop count
      .asg     BRC0, outer_cnt      ;outer loop count

      .asg     T0, oflag            ;returned value

      .global _convol

      .text
_convol:

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
        BCLR    ARMS
        BSET    FRCT
        BCLR    SMUL
        BCLR    ACOV0
;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; h pointer - setup

        MOV     AR1, mmap(h_base)        ;base address of h[]
        SUB     #1, T1, h_ptr            ;h_ptr = nh-1 (end of h[])
        MOV     T1, mmap(h_sz)           ;coefficient array size

; r pointer - passed in its destination register, need do nothing

; Set circular/linear ARx behavior

        BSET    AR1LC
;
; Setup loop counts
;----------------------------------------------------------------
        SUB     #1, T0                   ;T0 = nr - 1
        MOV     T0, outer_cnt            ;outer loop executes nr times
        SUB     #3, T1, T0               ;T0 = nh - 3
        MOV     T0, inner_cnt            ;inner loop executes nh-2 times
;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
        SUB     #2, T1                   ;T1 = nh-2, adjustment for x_ptr

; Start of outer loop
;----------------------------------------------------------------
     || RPTBLOCAL EndLoop-1              ;start the outer loop

;1st iteration
                MPYM    *x_ptr+, *h_ptr-, AC0

;inner loop
             || RPT     inner_cnt
                        MACM    *x_ptr+, *h_ptr-, AC0

;last iteration has different pointer adjustment and rounding
                MACMR   *(x_ptr-T1), *h_ptr-, AC0

;store result to memory
                MOV     HI(AC0), *r_ptr+    ;store Q15 result to memory
EndLoop:                                    ;end of outer loop

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
        MOV     #0, oflag                   ;clear oflag T0
     || BCLR    AR1LC                       ; restore AR1 to linear for C
        XCCPART overflow(AC0)               ;clears ACOV0
              ||MOV     #1, oflag           ;T0=1 overflow occurred

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
        BCLR    FRCT                        ;clear FRCT
        BSET    ARMS                        ;set ARMS
        BSET    SMUL
;
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
     || RET                                ;return to calling function

;----------------------------------------------------------------
;End of file
