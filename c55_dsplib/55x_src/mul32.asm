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
; Function:    mul32
; Processor:   C55xx
; Description: Implements a vector add using a single-MAC 
;              approach.  This routine is C-callable.
;
; Usage:   ushort mul32(LDATA *x, LDATA *y,  LDATA *r, ushort nx);
;
; Benchmarks:
;   Cycles:       (4 * nx) + 17
;   Code Size (in bytes):  47
;
; History:
;  Craig Leeds 05/28/2012: 
;    - Fixed bug where AR5 was modified but not restored.
;    - Fixed bug where T3 was modified but not restored.
;****************************************************************

        .mmregs
        .ARMS_off

                                    ; register usage
                                    ; ar0: addr. idx
      .asg      ar0, ar_x  ; used for mul32
      .asg      ar1, ar_y
      .asg      ar2, ar_z

      .asg     T0, oflag            ;returned value

;*****************************************************************************
      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

      .def      _mul32
      .text

_mul32:

;
; Configure the status registers as needed.
;----------------------------------------------------------------

      BCLR      ARMS
      BSET      FRCT
      BCLR      ACOV0

  ; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; y pointer - - passed in its destination register, need do nothing

; r/z pointer - passed in its destination register, need do nothing

      SUB   #1, T0
   || MAR   *ar_x+          ; ar_x = &X[0].Lo
      MOV   T0, BRC0              

      AMOV  #2,T0           ; for indexing
      AMOV  #3,T1           ; for indexing


      ; long data are stored in XH[0],XL[0], XH[1],XL[1], XH[2],XL[2], ... 
   || RPTBLOCAL LoopEnd-1        
            MPYM40 uns(*ar_x-), *ar_y+, AC0 
            MACM40 *ar_x, uns(*ar_y-), AC0 
            MACM40 *(ar_x+T1), *(ar_y+T0), AC0 >> #16
            MOV    saturate(AC0), dbl(*ar_z+)
LoopEnd:                                 ; Total loop cycles = 4 

; Return
;--------
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------

      MOV       #0, oflag              ;clear oflag
   || BCLR      FRCT
      XCCPART   overflow(AC0)          ;clears ACOV0
            ||MOV    #1, oflag         ;overflow occurred

      BSET      ARMS
   || RET

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
