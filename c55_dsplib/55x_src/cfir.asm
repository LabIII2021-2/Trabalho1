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
; Function:     Complex block fir
; Processor:   C55xx
; Description: Implements complex finite impulse response filter using
;              dual-MAC approach.  C-callable.
;
; Usage: ushort oflag = cfir(DATA *x,
;                            DATA *h,
;                            DATA *r,
;                            DATA *dbuffer,
;                            ushort nx,
;                            ushort nh)
;
;                
;     State of the registers upon entry:
;
;        XAR0 contains *x
;        XAR1 contains *h
;        XAR2 contains *r
;        XAR3 contains *dbuffer
;        T0   contains nx
;        T1   contains nh
;
; Notes:
;   x[] array is nx*2 words
;   h[] array is nx*2 words
;   r[] array is nx*2 words
;   dbuffer[] array is (nh*2 + 2) words
;
; Limitations:
;   nh >= 3
;   x[] array must be aligned on 32-bit boundary
;   r[] array must be aligned on 32-bit boundary
;   dbuffer[] array must be aligned on 32-bit boundary
;
; Benchmarks:
;   Cycles:       (nx * ((nh * 2)  + 4)) + 46
;   Code Size (in bytes):  120
;
;----------------------------------------------------------------
; Revision History:
; 1.00  C. Iovescu  01/05/00 - Original release.
; 2.10       Rishi  08/03/2001 - optimized the code for benchmark.
; 3.00  Craig Leeds 05/27/2012 - optimized the code
;
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


;----------------------------------------------------------------
; Assign auxiliary registers for temporaries and address
; calculations.
;----------------------------------------------------------------
        .asg     AR0, x_ptr           ;linear pointer
        .asg     CDP, h_ptr           ;circular pointer
        .asg     AR2, r_ptr           ;linear pointer
        .asg     AR4, db_ptr          ;circular pointer

        .asg     BSAC, h_base         ;base addr for h_ptr
        .asg     BKC, h_sz            ;circ buffer size for h_sz

        .asg     BSA45, db_base       ;base addr for db_ptr
        .asg     XAR4, xdb_base       ;extended base addr for db_ptr
        .asg     BK47, db_sz          ;circ buffer size for db_ptr

        .asg     T0, oflag

        .def    _cfir

        .text
_cfir:
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
        BCLR    ACOV0
        BCLR    ACOV1
        BSET    FRCT
        BCLR    ARMS
        BCLR    SMUL
;-----------------------------------------------------------------------
; Copy arguments to local locations and set registers
;
;-----------------------------------------------------------------------
; x pointer - passed in its destination register, need do nothing

; h pointer
        MOV     AR1, mmap(h_base)       ;base address of coefficients
        MOV     XAR1, XCDP

        MOV     #0, h_ptr               ;point to first coefficient
      ||SFTL    T1, #1                  ;multiply by 2 because complex numbers

        MOV     T1, mmap(h_sz)          ;coefficient array size

; r pointer - passed in its destination register, need do nothing

; db pointer
        MOV     XAR3, xdb_base          ;db array address
        AMAR    *AR3+                   ;align pointer to index location
        MOV     *AR3+, db_ptr           ;index of oldest db entry
        MOV     AR3, mmap(db_base)      ;base address for db_ptr
        MOV     T1, mmap(db_sz)         ;db_sz = 2*nh

; Set circular/linear ARx behavior
        BSET    AR4LC
        BSET    CDPLC
;
; Setup loop counts
;----------------------------------------------------------------
        SUB     #1, T0                  ;T0 = nx-1
        MOV     T0, BRC0                ;outer loop executes nx times
        SFTL    T1, #-1                 ;restore original value
        SUB     #3, T1                  ;T1 = nh-3
        MOV     T1, BRC1                ;inner loop executes nh-2 times
;
; Setup index registers
;--------------------------------------------------------------------
     || AMOV    #1, T0
        AMOV    #2, T1
; copy the first value from the input buffer to the delay buffer
        MOV     dbl(*x_ptr+), dbl(*db_ptr)
        
     || RPTBLOCAL  OuterLoopEnd-1       ;start the outer loop
                ;First tap
                MPY     *db_ptr, *h_ptr+, AC0        
                ::MPY   *db_ptr(T0), *h_ptr+, AC1        

                MAS     *db_ptr(T0), *h_ptr+, AC0
                ::MAC   *(db_ptr+T1), *h_ptr+, AC1

                ;Taps 2 through N_TAP
              ||RPTBLOCAL  InnerLoopEnd-1
                        MAC     *db_ptr, *h_ptr+, AC0        ;part 1 of dual MAC, real
                        ::MAC   *db_ptr(T0), *h_ptr+, AC1    ;part 1 of dual MAC, imag
                        MAS     *db_ptr(T0), *h_ptr+, AC0                
                        ::MAC   *(db_ptr+T1), *h_ptr+, AC1
InnerLoopEnd:

                MAC     *db_ptr, *h_ptr+, AC0                ;part 1 of dual MAC, real
                ::MAC   *db_ptr(T0), *h_ptr+, AC1            ;part 1 of dual MAC, imag
                MASR    *db_ptr(T0), *h_ptr+, AC0                
                ::MACR  *db_ptr, *h_ptr+, AC1
; copy the next value from the input buffer to the delay buffer
                MOV     dbl(*x_ptr+), dbl(*db_ptr)
                MOV     pair(HI(AC0)), dbl(*r_ptr+)        ;store result real & imag part (Note: requires alignment of AR2 input array)
OuterLoopEnd:                           ;end of outer loop

;
; Update the db entry point
;----------------------------------------------------------------
        MOV        db_ptr, *-AR3        ;update 1st element of db array
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
        ||MOV   #0, oflag               ;clear oflag
        XCCPART overflow(AC0)
            ||MOV     #1, oflag         ;overflow occurred
        XCCPART overflow(AC1)
            ||MOV     #1, oflag         ;overflow occurred
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
        BCLR    AR4LC
        BCLR    CDPLC
        BSET    ARMS                    ;set ARMS for C
        BCLR    FRCT                    ;clear FRCT for C
        BSET    SMUL                    ;set SMUL for C
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
     || RET                             ;return to calling function
;----------------------------------------------------------------
;End of file

