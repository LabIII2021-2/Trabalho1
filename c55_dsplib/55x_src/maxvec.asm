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
; Function:  MAXVEC
; Processor:   C55xx
; Description: maxvec: Value and Index of the maximum element of a vector
;
; Usage:	void maxvec (DATA *x, ushort nx, DATA *r_val, DATA *r_idx)
;
; Benchmarks:
;   Cycles:       (3 * nx) + 11
;   Code Size (in bytes):  30
;
; History:
;   05/26/12  Craig Leeds:   Optimized 
;********************************************************************************

        .global        _maxvec
        .text
_maxvec:
        MOV     *AR0+, AC1
     || SUB     #(1+1),T0

        MOV     T0, BRC0
     || MOV     #0, AR3

        MOV     #0, T0
        
        MOV     #0, T1
     || RPTBLOCAL LoopEnd-1
                MOV     *AR0+, AC0
             || ADD     #1, AR3
                MAX     AC0, AC1
                XCCPART end_block, !CARRY
                     || MOV     AR3, T1
LoopEnd:
        MOV     AC1,*AR1
        MOV     T1, *AR2
     || RET

