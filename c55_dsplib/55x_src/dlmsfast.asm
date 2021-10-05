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
; Usage: short oflag = dlmsfast(DATA *h, DATA *x, DATA *r, DATA *des,
;			        DATA *dbuffer, DATA step, ushort nh, ushort nx)
;
; ...where
;	h[2nh]		Pointer to coefficient vector of size nh
;			- h is stored in reverse order: h(n-1), ... h(0)
;	x[nx]		Pointer to input vector of size nx
;	r[xn]		Pointer to output data vector.
;			- r can be equal to x
;	des[nx]		Pointer to expected-output array
;	dbuffer[nh+3]	Pointer to delay buffer structure
;			- first element of structure is index into array
;			  of OLDEST data (to be overwritten with new)
;			- remaining elements are modulo-addressed for
;			  sample 0 to nh+1. NOTE that this delay buffer
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
;     nh =  12:  nx = 100:    3766
;     nh =  32:  nx =  64:    4354
;     nh =  10:  nx =  50:    1766
;     nh =  12:  nx =  20:     806
;   Code Size (in bytes):  304
;
; History:
;  2.10	Rishi  08/03/2001 - optimized the code for benchmark.
;  3.00  Craig Leeds 06/15/2012 
;    - fix bug where AR6H and AR7H not set
;    - fix bug where DP was modified and not restored
;    - move .bss usage to stack
;
;****************************************************************

        .cpl_on
        .ARMS_off

	.asg    0, err
	.asg    1, index_filt
	.asg	2, filler              ; for alignment of stack
	.asg	3, save_AR7
	.asg	4, save_AR6		
	.asg	5, save_AR5
	.asg	6, save_T3		; 2*mu*error(i) variable
	.asg	7, ret_addr
	.asg    8, arg_nx               ; argument on stack
	
;//-----------------------------------------------------------------------------
;// Temp data
;//-----------------------------------------------------------------------------

; register usage
;	XAR0-XAR4, T0 & T1 as well as accumulators are all available to callee
;	XAR0 through XAR5 are already loaded with *x, *h, *r, *des and *dbuffer
;	 respectively upon entry.
;	While T0 and T1 are loaded with the values of STEP and NH, respectively

	.asg	 AR0, ar_input
	.asg	 AR1, ar_coef
	.asg	 AR2, ar_scratch
	.asg	 AR3, ar_des
	.asg	 AR4, ar_dbuffer
	.asg     AR5, ar_output
	.asg	 AR6, ar_data1
	.asg	 AR7, ar_data2
	.asg	XAR4, Xar_dbuffer
	.asg	XAR6, Xar_data1
	.asg	XAR7, Xar_data2
	.asg	  T3, T_step
	.asg	  T1, T_nh

;*****************************************************************************
	.def	_dlmsfast
	
	
	; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 4            ;save-on-entry registers saved (T3, AR5, AR6, AR7)
FRAME_SZ          .set 3            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ
	

        .text
_dlmsfast:


; Preserve registers
;-------------------
    PSH T3                                      ;T3 is needed for LMS instruction
  ||BCLR ARMS                                   ;disable ARMS bit in ST2
    PSHBOTH XAR5				;AR5 will be used for the index into dbuffer
  ||BSET FRCT                                   ;
    PSHBOTH XAR6				;AR6 and AR7 are used in this function
  ||BCLR SST                                    ;make sure Saturate-on-STore bit in ST3 is disabled
    PSHBOTH XAR7				;AR6 and AR7 are used in this function
  ||BCLR ACOV0                                  ;clear AC0 overflow bit so that it can be tested at end
    BCLR ACOV1                                  ;clear AC1 overflow bit so that it can be tested at end
;
; Allocate the local frame and argument block
;----------------------------------------------------------------
  ||AADD	#-(FRAME_SZ + ARG_BLK_SZ), SP
; - one local variable


; Set math and overflow modes
;---------------------------
; Status registers
    OR  #0x00C6, mmap(ST2_55)                           ;AR1, AR2, AR6, & AR7 pointers put in circular mode
;
; Get arguments
;---------------

    MOV XAR2, XAR5;                                     ;XAR5 set to ar_output
    MOV Xar_dbuffer, Xar_data1                          ;set AR6H 
    MOV Xar_dbuffer, Xar_data2                          ;set AR7H 
    MOV T0, T_step

; NOTE!!!  the index value saved points to the oldest value:
; EXample: if we need to update x(-16) and X(-15) it will point to X(-16) 

    MOV *ar_dbuffer, ar_data2                           ;set AR6 to index in data array
                                                        ; of oldest input sample
    MOV *ar_dbuffer+, ar_data1							
							
	 
;***** Delay buffer ********
;       
;   |          |     
;   | x(0)     | <------ ar_data1 
;   | x(1)     | <------ ar_data2
;   | x(-N)	   |
;   | x(-(N-1))|
;   | .....    |
;   | x(-2)    |  
;   | x(-1)    |    
	
								
    MOV ar_dbuffer, mmap(BSA67)                         ;set BSA67 to start of data buffer
                                                        ; NOTE that this is the SECOND
                                                        ; element of the dbuffer structure

    ; initialize delay buffer CDP pointer	
    MOV ar_dbuffer, mmap(BSAC)
																											
    MOV T_nh, T0      
    AADD  AR1, T0 								
    MOV T0, mmap(BSA23)                                 ; BSA scratch = BSA coeff + NH
    MOV #0, ar_scratch				
								
    MOV AR1, mmap(BSA01)                                ;copy start of coeffs to BSA01
    MOV #0, ar_coef                                     ;...then set AR0 to zero (1st coeff)
	
	
    ; initialize counter for Coef update loop
    MOV  T1, T0
    SFTS T0, #-1                                        ;T0 = nh/2
    SUB	 #5, T0                                         ;T0 = (nh/2 - 2 - 3) => (-3) is for inner loop unroll
    MOV T0, BRC1                                        ; BRC1 = coef_cntr
	
    ; initialize counter for Filter loop
    MOV  T1, T0
    SUB  #2, T0                                         ;T0 = (nh - 2 - 4) => 4 is for unrolls
    MOV  T0, CSR                                        ; CSR = filt_cntr
	
    ;initialize the error 
    AMOV XSP, XCDP	                                ; CDP = &err (on stack)
    MOV  T_nh, mmap(BK03)                               ;load BK03 with # of coeffs for use w/ AR2
    ADD  #2, T_nh
    MOV  T_nh, mmap(BK47)                               ;load BK47 with # of data samples (nh+2)
                                                        ;in delay-line for use w/ AR6,7
    MOV  T_nh, mmap(BKC)

 .if (err != 0)
    AMAR *+CDP(#err)                                    ; CDP = &err (on stack)
 .endif
															
    MOV *SP(arg_nx), T0
    SFTS T0, #-1
    SUB #1, T0
    MOV T0, BRC0                                  ;BRC0 = nx/2 -1

    MOV  #0,*CDP 	                                    ;Set initial error is 0
    MOV  #5, T1		                                    ;circular buffer pointer wrap
    MOV  #2, T0

    MOV  *ar_input+, *ar_data2+                          ;update the two oldest values 
    MOV  *ar_input+, *(ar_data2+T0) 
    AMAR *(ar_data1+T0)

    MOV  ar_data2, *SP(index_filt)	
				

;  First Coefficient update stage
;  ------------------------------
;  Update Coefficients from the previous error e(n-1)
;
;   The coefficients h and h' are stored in reversed order: h(n-1)... h(0) where
;	h(n) is at the lowest memory address. 
;
;  AR6 ---> h
;  AR7 ---> h'
;  AR1 ---> x[n-(N-(2*k))]
;  AR3 ---> x[n-(N-(2*k+1))]
;  CDP ---> e(n-1)
;  T0 = #2
;  BRC1 = NH/2 -2
; 

; 21 = 15AD + 6IBQ stalls in the LOOP

;***** Filter coefficients buffer ********
;
;   | h(N-1)  | <------ ar_coef
;   |  .....  |
;   | h(0)    |
;   | h'(N-1) | <------ ar_scratch
;   |  .....  |
;   |  h'(0)  |  

;***** Delay buffer ********
;                      
;   | x(0)     | 
;   | x(1)     | 
;   | x(-N)	   | <------ ar_data1
;   | x(-(N-1))| <------ ar_data2
;   | .....    |
;   | x(-2)    |  
;   | x(-1)    | 

    RPTB #(ext_loop-1)

        MOV   dbl(*(ar_coef+T0)), PAIR(HI(AC0))

        ; Following 3 unrolls for BRC1 set up 4 cycles before rptb
        
        MACR  *(ar_data1+T0),*CDP,AC0    			
        :: MACR  *(ar_data2+T0),*CDP,AC1    		
        MOV   PAIR(HI(AC0)),dbl(*(ar_scratch+T0)) 	
     || MOV   dbl(*(ar_coef+T0)), PAIR(HI(AC0))	


        MACR  *(ar_data1+T0),*CDP,AC0    			
        :: MACR  *(ar_data2+T0),*CDP,AC1    		
        MOV   PAIR(HI(AC0)),dbl(*(ar_scratch+T0)) 	
        || MOV   dbl(*(ar_coef+T0)), PAIR(HI(AC0))	

        MACR  *(ar_data1+T0),*CDP,AC0    			
        :: MACR  *(ar_data2+T0),*CDP,AC1    		
        MOV   PAIR(HI(AC0)),dbl(*(ar_scratch+T0)) 	
     || MOV   dbl(*(ar_coef+T0)), PAIR(HI(AC0))	
        

        RPTBLOCAL   #(coef_updt1 -1)                ; 2 stalls 	; segment update loop       
            MACR  *(ar_data1+T0),*CDP,AC0    			; AC0=AC0+2^15+en*x[n-(N-(2*k))]
            :: MACR  *(ar_data2+T0),*CDP,AC1    		; AC1=AC1+2^15+en*x[n-(N-(2*k+1))]
            MOV   PAIR(HI(AC0)),dbl(*(ar_scratch+T0)) 		; h'(N-1-(2*k)) = HIGH(AC0)
         || MOV   dbl(*(ar_coef+T0)), PAIR(HI(AC0))	        ; h'(N-1-(2*k+1)) = HIGH(AC1)
                                                                ; HI(AC0) = h[N-(2*k+2)]
                                                                ; HI(AC0) = h[N-(2*k+2+1)]
        ; 1 stall in rptblocal loop after 1st iteration                                         
coef_updt1:    

        ; modify arr_data1 and ar_data2 pointing to the correct position      
        MACR  *(ar_data1+T1),*CDP,AC0      			; AC0=AC0+2^15+en*x[n-1]
        ::MACR  *(ar_data2+T1),*CDP,AC1      			; AC1=AC1+2^15+en*x[n-2]
        MOV   PAIR(HI(AC0)),dbl(*(ar_scratch+T0)) 	        ; h'[0] = HIGH(AC0)
                                                                ; h'[1] = HIGH(AC1)

;   Filtering stage
;	----------------
;	Two filters are processes in parallel using the dual MAC instruction.
;   The filter coefficients are stored in the buffers h[n](k) and h[n+1](k).
;   (n is the time index and k is the coefficient index)
;   We will use the following notations:
;								h(k)  = h[i](k) 
;								h'(k) = h[i+1](k)
;
;   Equations:
;   ----------
;   y(i)   =            h(0) x(i-1)+h(1)(1)x(i-2)+ ... +h(N-2)x(i-(N-1))+h(N-1)x(i-N)
;   y(i+1) = h'(0)x(i)+ h'(1)x(i-1)+       ...         +h'(N-1)x(i-(N-1)
;
;   Implementation:
;	---------------
;   Head and tail are computed using single MAC, all the other mpys are 
;   implemented using dual MAC.
;
;   The coefficients h and h' are stored in reversed order: h(n-1)... h(0) where
;	h(n) is at the lowest memory address.
;
;   CDP ---> db , circular
;   AR6 ---> h
;   AR7 ---> h'  
;
;
;***** Filter coefficients buffer ********
;
;   | h(N-1)  | <------ ar_coef
;   |  .....  |
;   |  h(0)   |
;   | h'(N-1) | <------ ar_scratch
;   |  .....  |
;   |  h'(0)  |  

;***** Delay buffer ********
;                      
;   | x(0)     | 
;   | x(1)     | 
;   | x(-N)	   |
;   | x(-(N-1))|
;   | x(-(N-2))| <------ CDP
;   | .....    |
;   | x(-2)    | 
;   | x(-1)    | 

; TEMP comments 
; ar_coef and ar_scratch should be in correct position since they are circular ptrs
; CDP has to be set circular ( parameters BKC, BSAC are set in initialization code)
; the index of CDP has to be set
; CSR has to be set

        BSET CDPLC					; 
        MOV  #0, AC1
        MOV  XAR4, XCDP		; initialize extended part
        
        MOV  *SP(index_filt), CDP    ; 
        MPYM *ar_coef+,*CDP+,AC0	;   4 stalls	; h(N-1)x(i-N)	    
        
     || RPT   CSR
            MAC    *ar_coef+,*CDP+,AC0
            :: MAC *ar_scratch+,*CDP+,AC1
        
        MACM   *ar_scratch+,*CDP+,AC1			; h'(0)x(i)
        AMAR *+CDP(#3)
        
        MOV  CDP, *SP(index_filt)
	
        ; store output
        MOV  rnd(HI(AC0)), *ar_output+;
        MOV  rnd(HI(AC1)), *ar_output+;
	
;   Error computation stage
;	-----------------------
;	Computing e(n) and e(n+1)		
        BCLR    CDPLC                                   ; 5 stalls; Disable CDP for circ addressing
        MOV     XSP, XCDP                               ; CDP = &err (on stack)
        SUB     AC0,*ar_des+<<#16,AC0                   ; AC0 = e(n) = y(n) - AC0
        MPYR    T_step, AC0

        SUB     AC1,*ar_des+<<#16,AC2                   ; AC1 = e(n+1) = y(n+1) - AC1
 .if (err != 0)
        AMAR *+CDP(#err)                                 ; CDP = &err (on stack)
 .endif
        MPYR    T_step, AC2
      ||MOV     HI(AC0), *CDP
         
;  Second Coefficient update stage
;  ------------------------------
;  Update Coefficients from the previous error e(n)
;
;   The coefficients h and h' are stored in reversed order: h(n-1)... h(0) where
;	h(n) is at the lowest memory address. 
;
;  AR6 ---> h
;  AR7 ---> h'
;  AR1 ---> x[n-(N-(2*k))]
;  AR3 ---> x[n-(N-(2*k+1))]
;  CDP ---> e(n)
;  T0 = #2
;  BRC1 = NH/2 -2
; 				

;***** Filter coefficients buffer ********
;
;   | h(N-1)  | <------ ar_coef
;   |  .....  |
;   |  h(0)   |
;   | h'(N-1) | <------ ar_scratch
;   |  .....  |
;   |  h'(0)  |  

;***** Delay buffer ********
;                      
;   | x(0)     | <------ ar_data1
;   | x(1)     | 
;   | x(-N)	   |
;   | x(-(N-1))| <------ ar_data1
;   | .....    | <------ ar_data2
;   | x(-2)    | 
;   | x(-1)    |  

        ; loop starts here	
        MOV   dbl(*(ar_scratch+T0)),PAIR(HI(AC0)) 		

        ; Following 3 unrolls are to allow BRC1 setup
        MACR  *(ar_data1+T0),*CDP,AC0    			
        :: MACR  *(ar_data2+T0),*CDP,AC1    		
        MOV   PAIR(HI(AC0)),dbl(*(ar_coef+T0)) 		
     || MOV   dbl(*(ar_scratch+T0)), PAIR(HI(AC0))

        MACR  *(ar_data1+T0),*CDP,AC0    			
        :: MACR  *(ar_data2+T0),*CDP,AC1    		
        MOV   PAIR(HI(AC0)),dbl(*(ar_coef+T0)) 		
     || MOV   dbl(*(ar_scratch+T0)), PAIR(HI(AC0))

        MACR  *(ar_data1+T0),*CDP,AC0    			
        :: MACR  *(ar_data2+T0),*CDP,AC1    		
        MOV   PAIR(HI(AC0)),dbl(*(ar_coef+T0)) 		
     || MOV   dbl(*(ar_scratch+T0)), PAIR(HI(AC0))
                                                    
        RPTBLOCAL   #(coef_updt2-1)                                 ; 2 stalls   ; segment update loop            
            MACR  *(ar_data1+T0),*CDP,AC0                           ; AC0=AC0+2^15+en*x[n-(N-(2*k))]
            :: MACR  *(ar_data2+T0),*CDP,AC1                        ; AC1=AC1+2^15+en*x[n-(N-(2*k+1))]
            MOV   PAIR(HI(AC0)),dbl(*(ar_coef+T0))                  ; h'(N-1-(2*k)) = HIGH(AC0)
         || MOV   dbl(*(ar_scratch+T0)), PAIR(HI(AC0))              ; h'(N-1-(2*k+1)) = HIGH(AC1)
                                                                    ; HI(AC0) = h[N-(2*k+2)]
                                                                    ; HI(AC0) = h[N-(2*k+2+1)]
        ; 1 stall in rptblocal loop after 1st iteration                                            
coef_updt2:          

	MACR  *(ar_data1+T1),*CDP,AC0                               ; AC0=AC0+2^15+en*x[n-1]
	::MACR  *(ar_data2+T0),*CDP,AC1                             ; AC1=AC1+2^15+en*x[n-2]
	MOV   PAIR(HI(AC0)),dbl(*(ar_coef+T0))                      ; h'[0] = HIGH(AC0)
	                                                            ; h'[1] = HIGH(AC1)

;   Update the delay line
;  -------------------------
;	
        MOV  *ar_input+, *ar_data2+                                  ;copy input -> state(0)
        MOV  *ar_input+, *(ar_data2+T0)                              ;copy input -> state(0)
	
;  Preserve e(n+1) for next stage
;  ------------------------------
;  
        MOV     HI(AC2), *CDP

ext_loop:     ; end of RPTB loop

;NO presumed values in ST0 by C-environment
;No presumed values of ST3 were modified

    AND  #0xF800, mmap(ST2_55)                                  ;all pointers put in linear mode, clear RDM

; Return overflow flag
; --------------------
    MOV  #0, T0                                                  ;store zero for return value
    XCCPART overflow(AC0)
        || MOV  #1, T0                                           ;return value 1 if overflow was encountered
    XCCPART overflow(AC1)
        || MOV  #1, T0                                           ;return value 1 if overflow was encountered
;
; Allocate the local frame and argument block
;----------------------------------------------------------------
    AADD   #+(FRAME_SZ + ARG_BLK_SZ), SP
	
;
; Restore stack to previous value
; Reset status regs to restore normal C operating environment
; Return to calling function
;----------------------------------------------------------------
    POPBOTH XAR7                                                ;AR6 and AR7 are used in this function
 || BSET ARMS                                                   ;set ARMS bit for C-environment
    POPBOTH XAR6                                                ;AR6 and AR7 are used in this function
 || BCLR FRCT                                                   ;clear FRCT bit in ST1 for C-environment
    POPBOTH XAR5                                                ;AR6 and AR7 are used in this function
    POP  T3
    RET                                                         ;return to calling function

    .end

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
