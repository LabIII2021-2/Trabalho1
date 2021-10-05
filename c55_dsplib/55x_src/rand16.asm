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
; Filename:	rand16.asm
; Processor:   C55xx
; Description: Generates 16 bit random numbers
;
; Usage: ushort oflag= rand16(DATA *r, ushort nr)
;                                                              
; Benchmarks:
;   Cycles:       (2 * nx) + 17
;   Code Size (in bytes):  54
;
;        Craig Leeds  - 05/17/2012 3.00.00
;   Fix bug where T3 was not being restored.
;   Fix bug where abs16(#rndseed) was used without DPH being set to 0.
;   Optimize main loop. 
;**************************************************************** 		
;
; Use memory mapped register mnemonics
;-----------------------------------------------------------------------------
			.mmregs

;-----------------------------------------------------------------------------
; Define constants used in the random number generation algorithm
;-----------------------------------------------------------------------------
                                    
RNDMULT		.set	31821					; Multiplier value
RNDINC		.set	13849					; Increment value     
			
;-----------------------------------------------------------------------------
; Initialize Random Number Generator -	Load the SEED value
;-----------------------------------------------------------------------------
        	.ref	rndseed         ; Global variable initialized in randinit()
		.def	_rand16

		.text
_rand16: 
      PSH       T3
   || BCLR	SMUL,ST3_55	  	; Clear SMUL bit  
      BCLR	ACOV0,ST0_55          	; Clear AC0 overflow flag 

      SUB	#1,T0                	; Set up count to 'nr-1'	
      MOV	T0,CSR		    	; Store number of vector  elements in repeat cntr  

      MOV	#RNDMULT,T1		; Initialize register with  constant	    	     						               		      			
      AMOV	#rndseed,XAR1
      AMOV      #AC0_L, XAR2
      MOV	#RNDINC,AC1		; Initialize register with constant  

      MACM	*AR1,T1,AC1,AC0	        ; (Prime the Pump)
*
* Note: AR2 access of AC0_L causes one delay cycle in the repeat loop.
*
   || RPT       CSR
            MOV	    AC0, *AR0+		      	; Store random number in array
         || MACM    T3=*AR2,T1,AC1,AC0	  	; Generate new random number  

      MOV	T3,*AR1           	; Store final result as random seed 
	        
      MOV	#0,T0                 	; Clear flag for returning overflow status              									  		 
   || POP       T3
      XCCPART    overflow(AC0)           ; Test AC0 overflow flag
          || MOV    #1,T0                ; If overflow, set return flag		

      BSET	SMUL,ST3_55	  	; set SMUL bit on exit
   || RET                    
;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
    

