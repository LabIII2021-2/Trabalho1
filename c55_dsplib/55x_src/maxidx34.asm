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
; Function:    maxidx34
; Processor:   C55xx
; Description: Description: Returns the index of the maximum element of a vector x. In case
;        of multiple maximum elements, r contains the index of the last maximum
;        element found
;
; Usage:    short r = maxidx34 (DATA *x, ushort nx)
;     Arguments:
;        *x  Pointer to input vector of size nx 
;        nx  Number of elements in the x[NX] array  
;        r   Index for vector element with maximum value
;
;     State of the registers on entry:
;        XAR0 contains *x
;        T0   contains nx
;     State of the registers on exit:
;        T0   contains r
;
; Limitations:
;     x[] is aligned on an even word boundary
;     nx is a multiple of 2 
;     6 <= nx <= 34
;
; Benchmarks:
;   Cycles:       (nx / 2) + 26
;   Code Size (in bytes):  87
;
; History:
;  2.10 Cesar I. original code. 08/03/01
;  3.00 Craig Leeds 06/15/2012:
;   - Fixed bug where DP is used, but DPH is never set
;   - Optimized overhead by 16 cycles
;
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .mmregs                       ;enable mem mapped register names 
      .noremark   5555, 5584, 5573, 5572       
      
      
; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 4            ;save-on-entry registers saved
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ         


;----------------------------------------------------------------
; Assign auxiliary registers for temporaries and address
; calculations.
;----------------------------------------------------------------
        .asg    AR0, x_ptr           ;linear pointer                    
               
        .global _maxidx34    
        
        .text                                                           
_maxidx34:   

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
;       AADD        #-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
; - not necessary for this function (the above is zero)
;
; Save any save-on-entry registers that are used
;----------------------------------------------------------------

;
; Configure the status registers as needed.
;----------------------------------------------------------------

        PSHBOTH XDP
     || BCLR    #ARMS, ST2_55
        PSH     T2, T3   
     || BCLR    #CPL, ST1_55               ;DP relative addressing
        AMOV    #0, XDP                    ;set DP=0 for mmreg accesses
        .dp 0    
;
;-----------------------------------------------------------------------
; Copy arguments to local locations and set registers
;
;-----------------------------------------------------------------------
; x pointer - passed in its destination register, need do nothing

; Setup loop counts
;----------------------------------------------------------------
        SFTL    T0, #-1                    ;restore original value 
     || MOV     #0, AC3

        SUB     #2, T0  
        MOV     T0, CSR                    ;CSR = NG_SIZE/2 - 2
   
        XOR     T1,T1 
     || MOV     @AC3_L,TRN0                ; TRN0 = #0
        MOV     T0, AR3
     || MOV     @AC3_L,TRN1                ; TRN1 = #0  

; start benchmark
           
        MOV     dbl(*AR0+), AC1            ;AC1_H = Aaddr[0],  AC1_L = Aaddr[1]
    
       ; 1 stall
        MOV     dbl(*AR0+), AC0            ;AC0_H = Aaddr[2],  AC0_L = Aaddr[3]
     || RPT     CSR                        ;repeat( #( (NX/2 - 1) - 1) )
                MAXDIFF AC0, AC1, AC1, AC2   ;AC1_H/L contain max's
             || MOV     dbl(*AR0+), AC0

        ; 1 stall
        MOV     AC1, T2                    ; T0 = odd max value
     || MOV     @AC1_H, AC1                ; AC1_L = even max value
        ;assume even max value > odd max value
        MOV     T1, T0                     ;T0 setup for even max index computation
     || MOV     @TRN0_L << #16, AC0        ;AC0_H = TRN0 (setup for even max index)

        ;test max(odd max value, even max value), Carry bit affected
        MAX     T2, AC1                    ;AC1 = max(odd max value, even max value) 
     
        MOV     AR3, T3                    ; AR3  = #(NX/2 - 2)  ;index seed value
    || XCCPART  !CARRY                  ;if Carry=0 then odd max value > even max value
                MOV     @TRN1_L << #16, AC0  ;AC0_H = TRN1 (setup for odd max index)
             || ADD     #1, T0               ;T0 modified for odd max index computation
 
        MOV     #0ffh, @AC0_G              ;AC0_G = 0xff, to isolate leading zero
        ; 1 stall
        EXP     AC0, T2                    ;T2 = position of leading zero in AC0 
  
        SUB     T2, T3                     ;subtract lead zero position from index seed
        SFTL    T3, #1                     ;mult by 2 since 2 values tested per iteration
;   
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
;    
        POP     T2, T3
     || ADD     T3, T0                     ;T0 = index of max value (return value)
        POPBOTH XDP
     || BSET    #CPL, ST1_55               ;SP relative addressing
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      AADD        #+(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
; - not necessary for this function (the above is zero)

        RET        
     || BSET    #ARMS, ST2_55
    .end

        
        
        
        
        
        
        
        
        
        