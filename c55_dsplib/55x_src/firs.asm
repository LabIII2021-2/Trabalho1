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
; Function:    firs
; Processor:   C55xx
; Description: Implements symmetric finite impulse response
;              filter using FIRS approach.  C-callable.
;
; Usage: ushort oflag = firs(DATA *x,            // XAR0
;                            DATA *h,            // XAR1
;                            DATA *r,            // XAR2
;                            DATA *dbuffer,      // XAR3
;                            ushort nx,          // T0
;                            ushort nh)          // T1
;
; Limitations:
;   nh >= 3
;   h[] is addressible by bbus (i.e. on-chip)
;
; Notes:
;   if dbuffer is in saram instead of daram, the function takes twice as many cycles.
;
; Benchmarks:
;   Cycles:       (nx * (nh + 3)) + 46
;   Code Size (in bytes):  120
;
; History:
;   05/26/2012 Craig Leeds:  Bug fixed: AC0 cleared before first iteration of loop
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
      .asg    AR0, x_ptr            ;linear pointer
      .asg    AR1, db_ptr1          ;circular pointer
      .asg    AR2, r_ptr            ;linear pointer
      .asg    AR3, db_ptr2          ;circular pointer
      .asg    CDP, h_ptr            ;circular pointer

      .asg    BSA01, db_base1       ;base addr for db_ptr1
      .asg    XAR1, xdb_base1       ;extended base addr for db_ptr1
      .asg    BSA23, db_base2       ;base addr for db_ptr2
      .asg    BK03, db_sz           ;circ buffer size for db_ptr1 and db_ptr2
      .asg    BSAC, h_base          ;base addr for h_ptr
      .asg    XCDP, xh_base         ;extended base addr for h_ptr
      .asg    BKC, h_sz             ;circ buffer size for h_sz


      .asg    T0, oflag             ;returned value

ST2mask  .set  0000000100001010b    ;circular/linear pointers (AR1LC, AR3LC, CDPLC)


      .global _firs

      .text
_firs:

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
        BCLR    ACOV0
        BCLR    ARMS
        BSET    FRCT
        BCLR    SMUL
;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; h pointer
        MOV     XAR1, xh_base      ; set CDPH
        MOV     AR1, mmap(h_base)  ; set BSAC
        MOV     T1, mmap(h_sz)     ; set BKC to nh2
        MOV     #0, h_ptr          ; clear CDP

; r pointer - passed in its destination register, need do nothing

; db pointers, part 1 - must come before circ/linear ARx setup
        MOV     XAR3, XAR4
        MOV     XAR4, xdb_base1

        MOV     *AR4, db_ptr1
        MOV     *AR4+, db_ptr2
      ||MOV     #1, AC0

        MOV     AR4, mmap(db_base1)
        MOV     AR4, mmap(db_base2)

; Set circular/linear ARx behavior
        OR      #ST2mask, mmap(ST2_55)   ; AR1LC, AR3LC, CDPLC
        ADD     mmap(T1) << #1, AC0
        MOV     AC0, mmap(db_sz)

; db pointers, part 2 - must come after circ/linear ARx setup
        AMAR    *db_ptr2-

;
; Setup loop counts
;----------------------------------------------------------------
      ||SUB     #1, T0
        MOV     T0, BRC0
      ||AMAR    *db_ptr2-
        SUB     #3, T1, T0
        MOV     T0, CSR

;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
        MOV     T1, T0
      ||MOV     #0, AC0                                
        SUB     #2, T1
        MOV     *x_ptr+, *db_ptr1  
;
; Start of outer loop
;----------------------------------------------------------------
     || RPTBLOCAL OuterLoopEnd-1

;clear AC0 and pre-load AC1 with the sum of the 1st and last inputs
        
                ADD     *db_ptr1+, *db_ptr2-, AC1

;inner loop
             || RPT     CSR
                        FIRSADD *db_ptr1+, *db_ptr2-, *h_ptr+, AC1, AC0        

;2nd to last iteration has different pointer adjustment
                FIRSADD *(db_ptr1-T0), *(db_ptr2+T1), *h_ptr+, AC1, AC0

;last iteration is a MAC with rounding
                MACMR   *h_ptr+, AC1, AC0
                MOV     *x_ptr+, *db_ptr1
    
;store result to memory
                MOV     HI(AC0), *r_ptr+        
             || MOV     #0, AC0
OuterLoopEnd:

;
; Update the db entry point
;----------------------------------------------------------------
        MOV     db_ptr1, *-AR4
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
      ||MOV     #0, oflag         ;clear oflag
        XCCPART overflow(AC0)   ;clears ACOV0
              ||MOV     #1, oflag     ;overflow occurred
;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------

        AND     #0FE00h, mmap(ST2_55)   ; clear all 8 ARxLC and CDPLC
        BSET    ARMS
        BCLR    FRCT
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
     || RET

;----------------------------------------------------------------
;End of file
