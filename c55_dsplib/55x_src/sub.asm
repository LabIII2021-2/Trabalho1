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
; Function:    SUB
; Processor:   C55xx
; Description: Implements a vector sub using a single-MAC 
;              approach.  This routine is C-callable.
;
; Algorithm:   for(i=0; i<nx; i++)
;	             r(i) = x(i) - y(i); 
;
; Usage: ushort oflag = sub (DATA *x,
;                            DATA *y,
;                            DATA *r,
;                            ushort nx,
;                            ushort scale)
;
; Benchmarks:
;   Cycles:       (2 * nx) + 13
;   Code Size (in bytes):  31
;
;        Craig Leeds  - 05/17/2012
;   AR1 no longer set to a circular buffer.
;   Optimized both loop and housekeeping.
;****************************************************************

      .ARMS_on                     ;enable assembler for ARMS=1
      .CPL_on                      ;enable assembler for CPL=1
      .mmregs                      ;enable mem mapped register names

; -----------
; Stack frame
; -----------

RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 0            ;save-on-entry registers saved
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ

; ------------------------------
; Register usage and definitions
; ------------------------------
        .asg     AR0, x_ptr                   ;linear pointer for first input vector
        .asg     AR1, y_ptr                   ;linear pointer for second input vector
        .asg     AR2, r_ptr                   ;linear pointer for result vector

        .asg     BRC0, outer_cnt              ;outer loop count
        .asg     T0, oflag                    ;returned value

        .def _sub
        .text
_sub:

; ---------------------------------------------------------------
; Allocate the local frame and argument block
; ---------------------------------------------------------------
;      SP = SP - #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

; ---------------------------------------------------------------
; Save any save-on-entry registers that are used
; ---------------------------------------------------------------
; - nothing to save for this function

; ---------------------------------------------------------------
; Configure the status registers as needed.
; ---------------------------------------------------------------

        BCLR    ACOV0

; ---------------------------------------------------------------
; Setup passed parameters in their destination registers
; Setup linear CDP/ARx behavior
; ---------------------------------------------------------------
; x pointer - passed in its destination register
; y pointer - passed in its destination register
; r pointer - passed in its destination register
; ---------------------------------------------------------------

; ---------------------------------------------------------------
; Setup loop counts
; ---------------------------------------------------------------

        SUB     #1, T0                       ;T0=nx-1
        MOV     T0, outer_cnt                ;outer loop executes nx times

; ---------------------------------------------------------------
; Setup output shift
; ---------------------------------------------------------------
        AMOV    #-1, T0
        XCC     T1 == #0                ;testing for scaling
             || AMOV    #0, T0

; ---------------------------------------------------------------
; Start of outer loop 
; for (i=0; iP<nx; i++)
;    R(i) = X(i) - Y(i);
; ---------------------------------------------------------------

        RPTBLOCAL LoopEnd-1                   ;start the outer loop
                SUB     *AR0+, *AR1+, AC0     ;vector subtract of two inputs
                MOV     HI(AC0 << T0), *AR2+  ; shift right by 0 or 1
LoopEnd:                                      ;end of outer loop

; ---------------------------------------------------------------
; Check if overflow occurred, and setup return value
; ---------------------------------------------------------------

        MOV     #0, oflag                ;clear oflag
        XCCPART overflow(AC0)
             || MOV     #1, oflag        ;overflow occured

; ---------------------------------------------------------------
; Restore status regs to expected C-convention values as needed
; ---------------------------------------------------------------

; ----------------------------------------------------------------
; Restore any save-on-entry registers that are used
; ----------------------------------------------------------------
; - nothing to restore for this function

; ---------------------------------------------------------------
; Deallocate the local frame and argument block
; ---------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

; ---------------------------------------------------------------
; Return to calling function
; ---------------------------------------------------------------

      RET                 
                
;----------------------------------------------------------------
;End of file 
