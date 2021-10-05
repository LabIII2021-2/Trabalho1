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
; Function:	dlms
; Processor:   C55xx
; Description: dlms fir filter
;
; Usage: short oflag = dlms(DATA *h, DATA *x, DATA *r, DATA *des,
;                           DATA *dbuffer, DATA step, ushort nh, ushort nx)
;
; ...where
;	h[nh]		Pointer to coefficient vector of size nh
;			- h is stored in reverse order: h(n-1), ... h(0)
;	x[nx]		Pointer to input vector of size nx
;	r[xn]		Pointer to output data vector.
;			- r can be equal to x
;	des[nx]		Pointer to expected-output array
;	dbuffer[nh+2]	Pointer to delay buffer structure
;			- first element of structure is index into array
;			  of OLDEST data (to be overwritten with new)
;			- remaining elements are modulo-addressed for
;			  sample 0 to nh. NOTE that this delay buffer
;			  yields an array length of nh+1, which is used
;			  for Dual-MAC operations(not used here).
;	step		Scale factor to control adaptation rate = 2*mu
;	nh		Number of filter coefficients. Filter order = nh-1.
;	nx		Number of input samples to process (length of input
;			and output data vectors).
;	oflag	Overflow Flag
;			- If oflag = 1, a 32-bit overflow has occured
;			- If oflag = 0, a 32-bit overflow has not occured
;
; Benchmarks:
;   Cycles:       
;     nh =  21:  nx = 128:    6056
;     nh =  12:  nx = 100:    2940
;     nh =  32:  nx =  64:    4456
;     nh =  21:  nx =  40:    1920
;     nh =   3:  nx =  32:     392
;     nh =  12:  nx =  20:     620
;     nh =   3:  nx =   3:      74
;   Code Size (in bytes):  353
;
; History:
; 2.10	Rishi  08/03/2001 - optimized the code for benchmark.
; 3.00  Craig Leeds 06/15/2012 - Fixed bug where AR5H not set
;****************************************************************
        .cpl_on
        .arms_off
        .noremark 5684   ; BRC1 not modified indirectly

      .asg      0, save_T3      ; pushed on stack
      .asg      1, save_T2      ; pushed on stack
      .asg      2, save_AR5     ; pushed on stack
      .asg      3, ret_addr     ; return address on stack from CALL
      .asg      4, arg_nx       ; argument on stack

; register usage
;      XAR0-XAR4, T0 & T1 as well as accumulators are all available to callee
;      XAR0 through XAR4 are already loaded with *x, *h, *r, *des and *dbuffer
;       respectively upon entry.
;      While T0 and T1 are loaded with the values of STEP and NH, respectively

      .asg      AR0, ar_input
      .asg      AR1, ar_coef
      .asg      AR2, ar_output
      .asg      AR3, ar_des
      .asg      AR4, ar_dbuffer
      .asg      AR5, ar_data
      .asg      T0,  T_step
      .asg      T1,  T_nh

;*****************************************************************************
      .def      _dlms

        .text
_dlms:

; Preserve registers
;-------------------
      PSH  T3, T2                   
   || BCLR ARMS                       ;disable ARMS bit in ST2
      PSHBOTH XAR5                    ;AR5 will be used for the index into dbuffer
   || BSET FRCT
;
; Set math and overflow modes
;---------------------------
; Status registers
      MOV  XAR4, XAR5
      BCLR ACOV1
      BSET AR1LC                     ;AR1 pointer put in circular mode
      BSET AR5LC                     ;AR5 pointer put in circular mode
;
; Get arguments
;---------------
      MOV  *ar_dbuffer+, ar_data      ;set AR5 to index in data array
                                      ; of oldest input sample
      MOV  AR4, mmap(BSA45)           ;set BSA45 to start of data buffer
                                      ; NOTE that this is the SECOND
                                      ; element of the dbuffer structure
      MOV  AR1, mmap(BSA01)           ;copy start of coeffs to BSA01
      MOV  #0, ar_coef                ;...then set AR0 to zero (1st coeff)
      ADD  #-1, *SP(arg_nx)           ;sub 1 from # of inputs for loopcount
      MOV  *SP(arg_nx), BRC0          ;set outer loop to number of inputs-1
      MOV  T_nh, mmap(BK03)           ;load BK03 with # of coeffs for use w/ AR2
      AADD #1, T_nh
      MOV  T_nh, mmap(BK47)           ;load BK03 with # of data samples (nh+1)
                                      ; in delay-line for use w/ AR4
      ASUB #3, T_nh
      MOV  T_nh, BRC1                 ;set inner loop to number of coeffs-2

; Loop through input data stream
;-------------------------------
      MOV  #0, AC3                    ;clear AC3 for initial error term
   || RPTBLOCAL OuterLoopEnd-1        ;...while starting outer loop
             MOV  *ar_input+, *ar_data+          ;copy input -> state(0) 
             MPYM *ar_data+, AC3, AC0            ;place first update term in AC0 
          || MOV  #0, AC1                        ;...while clearing FIR value
             LMS  *ar_coef, *ar_data, AC0, AC1   ;AC0 = update coef
                                                 ;AC1 = start of FIR output
          || RPTBLOCAL InnerLoopEnd-1            ;...while starting inner loop
                    MOV  HI(AC0), *ar_coef+            ;store updated coef
                 || MPYM *ar_data+, AC3, AC0            ;...while calculating next update term
                    LMS  *ar_coef, *ar_data, AC0, AC1  ;AC0 = update coef
InnerLoopEnd:
                                                 ;AC1 = update of FIR output
             MOV  HI(AC0), *ar_coef+             ;store updated coef
          || MOV  rnd(HI(AC1)), *ar_output+      ;...and store FIR output

             SUB  AC1, *ar_des+ << #16, AC2      ;AC2 is error amount
          || AMAR *ar_data+                      ;point to oldest data sample
             MPYR T_step, AC2, AC3               ;place updated mu_error term in AC3
OuterLoopEnd:

      MOV  ar_data, *-ar_dbuffer      ;dbuffer.index = index of oldest data

; Return overflow flag
; --------------------
   || MOV  #0, T0                     ;store zero for return value
      XCCPART overflow(AC1)
            || MOV  #1, T0            ;return value 1 if overflow was encountered

;
; Restore stack to previous value
; Reset status regs to restore normal C operating environment
; Return to calling function
;----------------------------------------------------------------

;NO presumed values in ST0 by C-environment

      BCLR AR1LC                     ;AR1 pointer restored to linear mode
      POPBOTH XAR5
   || BCLR AR5LC                     ;AR5 pointer restored to linear mode
      POP  T3, T2
   || BSET ARMS                       ;set ARMS bit for C-environment

;No presumed values of ST3 were modified

      RET                             ;return to calling function
   || BCLR FRCT                       ;clear FRCT bit in ST1 for C-environment

        .end

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
