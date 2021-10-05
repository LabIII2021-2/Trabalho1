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
; Function:    fir2
; Processor:   C55xx
; Description: Implements finite impulse response filter using
;              dual-MAC approach.  C-callable.
;
; Usage: ushort oflag = fir2(DATA *x,           // XAR0
;                            DATA *h,           // XAR1
;                            DATA *r,           // XAR2
;                            DATA *dbuffer,     // XAR3
;                            ushort nx,         // T0
;                            ushort nh)         // T1
;
; Limitations:
;   nh >= 3
;   h[] is addressible by bbus (i.e. on-chip)
;
; Notes:
;   if dbuffer is in saram instead of daram, the function takes twice as many cycles.
;
; Benchmarks:
;   Cycles:       ((nx / 2) * (nh + 5)) + 38
;   Code Size (in bytes):  120???
;
; History:
;   2.10  Rishi       08/03/2001 - optimized the code for benchmark.
;   3.00  Craig Leeds 05/27/2012 - clear SMUL on exit
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
      .asg     AR1, db_ptr1         ;circular pointer
      .asg     AR2, r_ptr           ;linear pointer
      .asg     AR3, db_ptr2         ;circular pointer
      .asg     CDP, h_ptr           ;circular pointer

      .asg     BSA01, db_base1      ;base addr for db_ptr1
      .asg     XAR1, xdb_base1      ;extended base addr for db_ptr1
      .asg     BSA23, db_base2      ;base addr for db_ptr2
      .asg     BK03, db_sz          ;circ buffer size for db_ptr1 and db_ptr2
      .asg     BK03_L, db_sz_L      ;for memory mapped access
      .asg     BSAC, h_base         ;base addr for h_ptr
      .asg     XCDP, xh_base        ;extended base addr for h_ptr
      .asg     BKC, h_sz            ;circ buffer size for h_sz

      .asg     T0, oflag            ;returned value

ST2mask  .set  0000000100001010b    ;circular/linear pointers (AR1, AR3, CDP)


      .global _fir2

      .text
_fir2:

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
        BCLR    SMUL
        BSET    FRCT
        BCLR    ACOV0
        BCLR    ACOV1
;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; h pointer
        MOV     XAR1, xh_base            ;extended base address for h_ptr
        MOV     #0, h_ptr                ;point to first coefficient
        MOV     AR1, mmap(h_base)        ;base address of coefficients
        MOV     T1, mmap(h_sz)           ;coefficient array size

; r pointer - passed in its destination register, need do nothing

; db pointers, part 1 - must come before circ/linear ARx setup
        MOV     XAR3, XAR4               ;save db array address
        MOV     XAR4, xdb_base1          ;extended base address for db_ptr1
                                         ;xdb_base2 already setup via argument pass
        MOV     *AR4, db_ptr1            ;index of oldest db entry
        MOV     *AR4+, db_ptr2           ;index of oldest db entry

        MOV     AR4, mmap(db_base1)      ;base address for db_ptr1
        MOV     AR4, mmap(db_base2)      ;base address for db_ptr2

; Set circular/linear ARx behavior
        OR      #ST2mask, mmap(ST2_55)   ;config circ/linear pointers
        MOV     T1, mmap(db_sz)          ;db_sz = nh
        ADD     #1, mmap(db_sz)          ;db_sz = nh+1

; db pointers, part 2 - must come after circ/linear ARx setup
        AMAR    *db_ptr2-                ;index of 2nd oldest db entry
;
; Setup loop counts
;----------------------------------------------------------------
      ||SFTS    T0, #-1                  ;T0 = nx/2

        SUB     #1, T0                   ;T0 = (nx/2 - 1)
        MOV     T0, BRC0                 ;outer loop executes nx/2 times
        SUB     #3, T1, T0               ;T0 = nh-3
        MOV     T0, CSR                  ;inner loop executes nh-2 times
;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
        ADD     #1, T1, T0               ;T0 = nh+1, adjustment for db_ptr1, db_ptr2
        MOV     *x_ptr+, *db_ptr1        ;get 1st new input value
        MOV     *x_ptr+, *db_ptr2        ;get 2nd new input value (newest)
;
; Start of outer loop
;----------------------------------------------------------------
      ||RPTBLOCAL  LoopEnd-1             ;start the outer loop

;1st iteration
                MPY     *db_ptr1+, *h_ptr+, AC0           ;part 1 of dual-MPY
                ::MPY   *db_ptr2+, *h_ptr+, AC1           ;part 2 of dual-MPY
;inner loop
              ||RPT     CSR
                        MAC     *db_ptr1+, *h_ptr+, AC0   ;part 1 of dual-MAC
                        ::MAC   *db_ptr2+, *h_ptr+, AC1   ;part 2 of dual-MAC
;last iteration has different pointer adjustment and rounding
                MACR    *(db_ptr1-T0), *h_ptr+, AC0       ;part 1 of dual-MAC
                ::MACR  *(db_ptr2-T0), *h_ptr+, AC1       ;part 2 of dual-MAC
        
                MOV     *x_ptr+, *db_ptr1                 ;get 1st new input value
                MOV     *x_ptr+, *db_ptr2                 ;get 2nd new input value (newest)
;store results to memory        
                MOV     pair(HI(AC0)), dbl(*r_ptr+)       ;store 1st Q15 result to memory
                                                          ;store 2nd Q15 result to memory
LoopEnd:                                 ;end of outer loop

;
; Update the db entry point
;----------------------------------------------------------------
        MOV     db_ptr1, *-AR4           ;update 1st element of db array
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
      ||MOV     #0, oflag                ;clear oflag

        XCCPART overflow(AC0)            ;clears ACOV0
            ||MOV    #1, oflag           ;overflow occurred

        XCCPART overflow(AC1)            ;clears ACOV1
            ||MOV    #1, oflag           ;overflow occurred
;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
        AND     #0FE00h, mmap(ST2_55)    ;clear CDPLC and AR[7-0]LC (specifically AR1LC, AR3LC, CDPLC) for C
        BCLR    FRCT                     ;clear FRCT for C
        BSET    ARMS                     ;set ARMS for C
        BSET    SMUL                     ;set SMUL for C
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
      ||RET                              ;return to calling function

;----------------------------------------------------------------
;End of file

