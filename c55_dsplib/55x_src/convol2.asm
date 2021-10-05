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
; Function:    convol2
; Processor:   C55xx
; Description: Implements real convolution algorithm using
;              dual-MAC approach.  C-callable.
;
; Usage: ushort oflag = convol2(DATA *x,
;                               DATA *h,
;                               DATA *r,
;                               ushort nr,
;                               ushort nh)
;
; Limitations:
;   nr is even
;   nh >= 3
;   r[] must be aligned on a 32-bit boundary
;
; Notes:
;   The algorithm will take twice as many cycles if x[] and h[]
;   are in the same block of on-chip memory.
;
; Benchmarks:
;   Cycles:       ((nr / 2) * (nh + 1)) + 28
;   Code Size (in bytes):  81
;
; History:
;   Craig Leeds 05/24/2012:  Set SMUL on exit
;                            Test ACOV1 on exit 
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

; Stack frame
; -----------
RET_ADDR_SZ    .set 1               ;return address
REG_SAVE_SZ    .set 0               ;save-on-entry registers saved
FRAME_SZ       .set 0               ;local variables
ARG_BLK_SZ     .set 0               ;argument block

PARAM_OFFSET   .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
      .asg     AR0, x_ptr           ;linear pointer
      .asg     AR2, r_ptr           ;linear pointer
      .asg     CDP, h_ptr           ;circular pointer

      .asg     BSAC, h_base         ;base addr for h_ptr
      .asg     BKC, h_sz            ;circ buffer size for h_sz
      .asg     XCDP, xh_base        ;extended base address for h_ptr

      .asg     CSR, inner_cnt       ;inner loop count
      .asg     BRC0, outer_cnt      ;outer loop count

      .asg     T0, oflag            ;returned value

      .global _convol2

      .text
_convol2:

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
        BCLR    ACOV1

;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; Setup outer loop count
        SFTS    T0, #-1              ;T0 = nr/2
        SUB     #1, T0               ;T0 = (nr/2 - 1)
        MOV     T0, outer_cnt        ;outer loop executes nr/2 times
; h pointer - setup

        MOV     XAR1, xh_base        ;extended base address for h_ptr
        SUB     #1, T1, T0           ;T0 = nh - 1
        MOV     T0, h_ptr            ;h_ptr = nh-1(end of h[])
        MOV     AR1, mmap(h_base)    ;base address of coefficients
        MOV     T1, mmap(h_sz)       ;coefficient array size

; r pointer - passed in its destination register, need do nothing

; Set circular/linear ARx behavior
      BSET        CDPLC

;
; Setup inner loop count
;----------------------------------------------------------------
        SUB     #3, T1, T0           ;T0 = nh - 3

        MOV     T0, inner_cnt        ;inner loop executes nh-2 times
      ||MOV     #1, T0               ;x_ptr offset for parallel computation

;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
        SUB     #3, T1               ;T1 = nh-3, adjustment for x_ptr

;
; Start of outer loop
;----------------------------------------------------------------
     || RPTBLOCAL LoopEnd-1          ;start the outer loop

;1st iteration
                MPY     *x_ptr+, *h_ptr-, AC0              ;part 1 of dual-MPY
              ::MPY     *x_ptr(T0), *h_ptr-, AC1           ;part 2 of dual-MPY

;inner loop
              ||RPT     inner_cnt
                        MAC     *x_ptr+, *h_ptr-, AC0      ;part 1 pf dual-MAC
                      ::MAC     *x_ptr(T0), *h_ptr-, AC1   ;part 2 of dual-MAC

;last iteration has different pointer adjustment and rounding
                MACR    *(x_ptr-T1), *h_ptr-, AC0          ;part 1 pf dual-MAC
              ::MACR    *x_ptr(T0), *h_ptr-, AC1           ;part 2 of dual-MAC

;store result to memory
                MOV     pair(HI(AC0)), dbl(*r_ptr+)        ;store both Q15 results to memory
LoopEnd:

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
        MOV     #0, oflag            ;clear oflag T0
     || BCLR    CDPLC     ; restore CDP to linear for C
        XCCPART overflow(AC0)        ;clears ACOV0
              ||MOV     #1, oflag    ;T0=1 overflow occurred
        XCCPART overflow(AC1)        ;clears ACOV1
              ||MOV     #1, oflag    ;T0=1 overflow occurred

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
        BSET    ARMS      ;set ARMS
        BCLR    FRCT      ;clear FRCT
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
