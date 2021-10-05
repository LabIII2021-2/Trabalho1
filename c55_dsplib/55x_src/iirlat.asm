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
; Function:    iirlat
; Processor:   C55xx
; Description: Computes a real lattice IIR filter implementation using 
;		coefficient stored in vector h. The real data input is 
;		stored in vector x. The filter output result is stored 
;		in vector r .  This function retains the address of the 
;		delay filter memory d containing the previous delayed 
;		values to allow consecutive processing of blocks. This 
;		function can be used for both block-by-block and  
;		sample-by-sample filtering (nx=1).    
;		C-callable.
;
; Usage: short oflag = iirlat (DATA *x,            // XAR0
;                              DATA *h,            // XAR1
;                              DATA *r,            // XAR2
;                              DATA *pbuffer,      // XAR3
;                              int nx,             // T0
;                              int nh)             // T1
;
; Benchmarks:
;   Cycles:       (nx * (4 *nh - 1)) + 33
;   Code Size (in bytes):  99
;
; History:
;   05/27/2012 Craig Leeds: include AC1 in overflow checking
;****************************************************************
*;Algorithm:
*; 	e(nh)[n] = x[n]
*;	
*; 	e(i-1)[n]  = e(i)[n] + k(i)*e'(i-1)[n-1]   i=nh,nh-1,.. 1
*;       e'(i)[n] = k(i)*e(i-1)[n] + e'(i-1)[n-1]   i=nh,nh-1,.. 1
*;	r[n] = e(0)[n]=e'(0)[0]
*;
*;
*;pbuffer: procession buffer of nh length
*;      e'0[n-1]
*;      e'1[n-1]
*;      e'2[n-1]
*;      e'3[n-1]
*;	.
*;	.
*;      e'nh-2[n-1]
*;      e'nh-1[n-1]
*;
*;x: input of length nx
*;	x[0]
*;	x[1]
*;	.
*;	.
*;	.
*;	x[nx-2]
*;	x[nx-1]
*;
*;h: input of length nh-1 (zero pad 1st value)
*;	0
;	h[1]
;	.
;	.
;	.
;	h[nh-1]
;	h[nh]
;
;r: output of length nx
;	r[0]
;	r[1]
;	.
;	.
;	.
;	r[nx-2]
;	r[nx-1]  
;
;
;****************************************************************


      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names
      .noremark 5684                ;BRC1 is not modified indirectly

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
      .asg     AR4, p_ptr           ;circular pointer
      .asg     AR3, temp	    ;temp buffer
	
       
      .asg     BSA45, p_base        ;base addr for p_ptr
      .asg     XAR4, xdb_base       ;extended base addr for p_ptr
      .asg     BK47, p_sz           ;circ buffer size for p_ptr
      .asg     BK47_L, p_sz_L       ;for memory mapped access
      .asg     BSA01, h_base        ;base addr for h_ptr
      .asg     BK03, h_sz           ;circ buffer size for h_sz

      .asg     T0, oflag           ;returned value

ST2mask  .set  0000000000010010b    ;circular/linear pointers, AR4, AR1 circular


      .global _iirlat

      .text
_iirlat:
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
; h pointer 
                
        MOV     AR1, mmap(h_base)        ;base address of coefficients passed in AR1
        MOV     T1, mmap(h_sz)           ;h_sz = nh

; r pointer - passed in its destination register, need do nothing
; p pointer

        MOV     XAR3, XAR4
        MOV     AR3, mmap(p_base)        ;base address for p_ptr
        MOV     T1, mmap(p_sz)           ;p_sz = nh
; Set circular/linear ARx behavior
        OR      #ST2mask, mmap(ST2_55)   ;config circ/linear pointers
;
; Setup loop counts
;----------------------------------------------------------------
        SUB     #1, T0                   ;T0 = nx-1
        MOV     T0, BRC0                 ;outer loop executes nx times
        SUB     #2, T1, T0               ;T0 = nh-2
        SUB     #1, T1                   ; T1 = nh-1   
        MOV     T1, p_ptr                ;point to last coefficient
        MOV     T1, h_ptr                ;point to last coefficient
        MOV     T0, BRC1                 ;inner loop executes nh-1 times
        AMOV     #-1, T0                  ; setup offset register 
      
;
; Start of outer loop
;----------------------------------------------------------------
     || RPTBLOCAL  loop1-1               ;start the outer loop
                ;1st iteration
                MOV     *x_ptr+ << #16, AC0                ; setup for e(0): input value
                
              ||RPTBLOCAL  loop2-1                         ;inner loop
                        NOP_16                             ; for CPU_116 Remark 5682
                      ||MOV     *p_ptr(T0) <<#16, AC1      ; setup for e'(0): input value
                        MASM    *h_ptr, *p_ptr(T0), AC0    ; calculate e(0)
                        MACM    *h_ptr-, AC0, AC1          ; calculate e'(0)
                        MOV     HI(AC1), *p_ptr-           ; store e'(i)
loop2:                   

                ;last iteration has rounding
                MACMR   *h_ptr-, *p_ptr(T0), AC0
                MOV     HI(AC0), *p_ptr-                   ; store previously cacluclated e'(i)
              ||MOV     HI(AC0), *r_ptr+                   ;store Q15 value to memory
loop1:                                                     ;end of outer loop

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
        MOV     #0, oflag                ;clear oflag
        XCCPART overflow(AC0)            ;clears ACOV0
             ||MOV        #1, oflag      ;overflow occurred
        XCCPART overflow(AC1)            ; 
             ||MOV  #1, oflag            ; 

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------

        AND     #0FE00h, mmap(ST2_55)    ;clear CDPLC and AR[7-0]LC
      
        BCLR    FRCT                     ;clear FRCT
        BSET    ARMS                     ;set ARMS

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
        BSET    SMUL                     ;restore SMUL for C
     || RET                              ;return to calling function

;----------------------------------------------------------------
;End of file
