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
; Function:    maxval
; Processor:   C55xx
; Description: Description: Returns the value of the maximum element of a vector x
; Usage:    short r = maxval (DATA *x, ushort nx)
;	Arguments:
;         *x     Pointer to input vector of size nx 
;         nx     number of elements in the x[nx] array  
;         r      maximum value
;
;	State of the registers after the call:
;
;	XAR0 contains *x
;	T0   contains nx
;
; Benchmarks:
;   Cycles:       (nx / 2) + 15
;   Code Size (in bytes):  28
;
; History:
;  2.10 Cesar I. optimized code for benchmark purpose. 08/03/01
;  3.0.0 Craig Leeds  - 05/17/2012
;     Fixed bug where DP is used to access memory-mapped registers, but DPH is never set.
;     Optimized.
;****************************************************************
      .ARMS_on                      ;enable assembler for ARMS=1
      .mmregs                       ;enable mem mapped register names 
      .noremark   5555, 5584, 5573, 5572       
      

      
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

        .global _maxval   
	
        .text                                                           
_maxval:   

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
;      AADD	#-(ARG_BLK_SZ + FRAME_SZ), SP
; - not necessary for this function (the above is zero)
;
; Configure the status registers as needed.
;----------------------------------------------------------------

;-----------------------------------------------------------------------
; Copy arguments to local locations and set registers
;
;-----------------------------------------------------------------------
; x pointer - passed in its destination register, need do nothing
	

; Setup loop counts
;----------------------------------------------------------------  

     SFTL  T0, #-1  			;divide by 2 
     SUB  #2, T0
     MOV T0, CSR			;CSR = NX/2 - 2

     MOV dbl(*AR0+), AC1 		;AC1_H = Aaddr[0],  AC1_L = Aaddr[1]
     MOV dbl(*AR0+), AC0		;AC0_H = Aaddr[2],  AC0_L = Aaddr[3]

  || RPT CSR  
          MOV dbl(*AR0+), AC0
       || MAXDIFF AC0, AC1, AC1, AC2	;AC1_H/L contain max's
    
     MOV AC1, T0			;T0 = odd max value
     MOV HI(AC1), T1 		        ;T1 = even max value
      
  ;test max(odd max value, even max value), Carry bit affected
     MAX T1, T0                         ;AC3 = max(odd max value, even max value) 
; return value in T0
;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      AADD	#+(ARG_BLK_SZ + FRAME_SZ), SP
; - not necessary for this function (the above is zero)

    RET        
        
        
        
        
        
        
        
        
        
        