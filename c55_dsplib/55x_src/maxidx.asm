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
; Function:    maxidx
; Processor:   C55xx
; Description: Description: Returns the index of the maximum element of a vector x. In case
;       of multiple maximum elements, r contains the index of the last maximum
;       element found
; Usage:    short r = maxidx (DATA *x, ushort ng, ushort ng_size)
;       Arguments:
;          *x        Pointer to input vector of size nx  (where nx = ng * ng_size)
;          ng        Number of groups forming the x[nx] array
;          ng_size   Size of the group  
;          r         Index for vector element with maximum value
;
;       State of the registers on entry:
;          XAR0 contains *x
;          T0   contains ng
;          T1   contains ng_size
;       On exit:
;          T0   index of maximum value (from 0 to nx-1)
;
; Benchmarks:
;   Cycles:       (ng * 14) + (ng * ng_size / 2) + 29
;   Code Size (in bytes):  141
;
; History:
;  2.10 Cesar I. optimized code for benchmark purpose. 08/03/01
;  2.11 Li Yuan fixed code to work when the first element is the max 07/11/02
;  3.00 Craig Leeds 06/15/2012:
;   - Fixed bug where AR5 and AR6 pointed to TRN0 and TRN1 but AR5H and AR6H not set
;   - Fixed bug where TRN0 not set to 0 before first iteration of loop
;   - Fixed bug where T2 not set to 0 before first iteration of loop
;   - Fixed bug where DP is used, but DPH is never set
;   - .bss usage removed
;
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .mmregs                       ;enable mem mapped register names 
      .noremark   5555, 5584, 5573, 5572       
      
; Local variable
;----------------

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 5            ;save-on-entry registers saved (T3, T2, AR5, AR6, DP)
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ         

;----------------------------------------------------------------
; Assign auxiliary registers for temporaries and address
; calculations.
;----------------------------------------------------------------
      .asg     AR0, x_ptr           ;linear pointer                    
      .asg     AR5, trn0_ptr        ; linear pointer
      .asg     AR6, trn1_ptr        ; linear pointer
      .asg     AC3, maxv
      .asg     BRC0, outer_cnt      ;outer loop count

        .global _maxidx    

        .text                                                           
_maxidx:   

;
; Save any save-on-entry registers that are used
; Allocate the local frame and argument block
; Copy arguments to local locations and set registers
;----------------------------------------------------------------

        PSH     T3, T2
     || BCLR    #ARMS, ST2_55
        PSHBOTH XAR5
     || BCLR    #CPL, ST1_55              ;DP relative addressing
        PSHBOTH XAR6
     || SUB  #1, T0                    ;T0 = ng-1
        PSHBOTH XDP

        AMOV #0, XDP                   ;set DP=0 for mmreg accesses
          .dp 0       
;
;-----------------------------------------------------------------------
; x pointer - passed in its destination register, need do nothing
          
;
; Setup loop counts
;----------------------------------------------------------------
      
        MOV  T0, outer_cnt             ;outer loop executes ng times
     || MOV  #0, AR1                  ; AR1 = #0 used to initialize TRN0,1

        MOV  T1, T3                    ; T3 = ng_size
     || MOV  *x_ptr, maxv              ; maxValue = x[0]    

        SFTL T1, #-1
        AMOV #TRN1_L, XAR6             ; trn1_ptr = &TRN1 
           
        SUB  #2, T1

        MOV  T1, CSR                   ;CSR = NG_SIZE/2 - 2
        AMOV #TRN0_L, XAR5             ; trn0_ptr = &TRN0

        MOV  T1, AR3                   ;init position of leading zero 
    
        XOR  T1, T1                    ; T1 = 0
     || MOV  #0ffh, AR2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        MOV  T1, *AR5                  ; TRN0 = 0
     || MOV  #0, T2                    ; T2 = 0
        MOV  T1, AR4                   ; AR4 = 0 (save base index of max value initially)

;BENCHMARK KERNEL ******************************************************
;Data values are processed via the outer loop N_GROUP values at a time.
;The outer loop is therefore executed N_INPUT/N_GROUP times.
;
;  Register usage during loop:
;    T1    ng_size * index
;    T3    ng_size
;    AR0   &x[ng_size * index] (aligned)
;    AR1   0
;    AR2   0xff
;    AR3   ng_size/2 - 2
;    AR4   base index of max value (ng_size * index) + odd
;    AR5   &TRN0
;    AR6   &TRN1
;    AC3   maximum value
;    CSR   ng_size/2 - 2
;    BRC0  ng - 1
;

      ||RPTBLOCAL outer_loop-1                  ;START OF OUTER LOOP *******************

              MOV  AR1, *AR6                    ; init TRN1 = #0 
           || MOV  dbl(*AR0+), AC1              ;AC1_H = x[ng_size * index + 0],  AC1_L = x[ng_size * index + 1]

              MOV  dbl(*AR0+), AC0              ;AC0_H = x[ng_size * index + 2],  AC0_L = x[ng_size * index + 3]
           || RPT  CSR                          ;repeat( #( (N_GROUP/2 - 1) - 1) )
                    MAXDIFF AC0, AC1, AC1, AC2  ;AC1_H/L contain max's
                 || MOV  dbl(*AR0+), AC0

              MOV  maxv, AC0                    ;AC0 = old max value   
            ||SUB  #2, AR0 
      
              MOV  AC1, T0                      ; T0    = odd max value
           || SFTS AC1, #-16                    ; AC1_L = even max value 
       
    ;test max(odd max value, even max value), Carry bit affected
              MAX  T0, AC1                      ;AC1 = max(odd max value, even max value) (affects CARRY for XCCPART!)
      
    ;test max(old max value, new max value)
              CMP  AC1 > AC0, TC1               ;TC1 set if max(odd,even) value > old max value
     
    ;assume even max value > odd max value
              MOV  T1, T0                       ;T0=ng_size * index  setup for even max index computation
           || MOV  *AR5 << #16, AC0             ;AC0_H = TRN0 (setup for even max index) 
   
              XCCPART  !CARRY                   ;if Carry=0 then odd max value > even max value
                    MOV  *AR6 << #16, AC0       ;AC0_H = TRN1 (setup for odd max index) 
                 || ADD  #1, T0                 ;T0 = (ng_size * index) + 1   modified for odd max index computation
   
    ;PERFORM IN_LOOP NECESSARY PORTION OF INDEX COMPUTATION **********

;  if TC1=1 or TC2=1, then a new max value is > old max value
              MOV AR1, *AR5                     ; TRN0 = #0 (for next iteration)
            ||XCCPART TC1
                    MOV  AR2, @AC0_G            ;AC0_G = 0xff, to isolate leading zero
                 || MOV  T0, AR4                ;save base index of max value
      
              ADD  T3, T1                       ; T1 = ng_size * index   (T3 = ng_size)
           || XCC TC1
                    EXP  AC0, T2                ; T2 = position of leading zero in AC0 
                 || MOV  AC1, maxv              ;update maxValue
outer_loop:                                     ;end outer loop
          
        SUB  T2,  AR3                           ;subtract lead zero position from index seed
        SFTL AR3, #1                            ;mult by 2 since 2 values tested per iteration
        ADD  AR4, AR3                           ;AR3 = index of max value
        MOV  AR3, T0                            ; return value
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------

        POPBOTH XDP
        POPBOTH XAR6
     || BSET    #ARMS, ST2_55
        POPBOTH XAR5
     || BSET    #CPL, ST1_55                       ;SP relative addressing
        POP     T3, T2
; - not necessary for this function (the above is zero)

        RET        
    .end
        
        
        
        
        
        
        
        
        
        