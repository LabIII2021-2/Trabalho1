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
; Function:    bexp
; Version:     3.0
; Processor:   C55xx
; Description: block exponent
; Usage: short r_maxexp = bexp (DATA *x, ushort nx)
;  
; Benchmarks:
;   Cycles:       (3 * nx) + 9
;   Code Size (in bytes):  21
;
; History:
;        Craig Leeds  - 05/17/2012
;   Optimized loop from 5 cycles to 3 cycles, and optimized housekeeping.
;-----------------------------------------------------------------------------
; Register usage
; --------------
      .asg     AR0, in_ptr  

      .global _bexp
      .text

_bexp:
      SUB #1,T0                        ;setup loop counter=nx-1
      MOV T0,BRC0
      ||MOV #0x20,T0                   ;init T0 to the max exp
      MOV *in_ptr+ << #16,AC0          ;read in the vector with 16 bits left shift (Prime the Pump)

* Note: there is a 1-cycle pipeline delay in the loop.  So it requires 3 cycles per iteration instead of 2

      ||RPTBLOCAL end_block-1          ;start main loop
              EXP AC0,T1                       ;calculate exp and store the result into T1
              MIN T1,T0                        ;update T0 with min value
              ||MOV *in_ptr+ << #16,AC0        ;read in the vector with 16 bits left shift (for next iteration)
end_block:
      
      RET

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
