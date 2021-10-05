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
; Function:    acorr_bias
; Processor:   C55xx
; Description: calculates positive biased auto-correlation
;
; Usage:    short acorr_bias(DATA *x, DATA *r, ushort nx, ushort nr)
;
; Notes:
;   This function uses the dual-mac, but since it is doing an autocorrelation, all 3
;   operands are taken from the same page of memory, thus causing 1 cycle of delay for
;   arrays in DARAM, and 2 cycles of delay for arrays in SARAM.  So intuition would say
;   that it would be simpler and faster to skip the dual-mac and just use single macs.
;   That logic would be true for arrays in DARAM.  But for arrays in SARAM, each single-mac
;   instruction would cause a one-cycle delay.  Hence, the use of the dual-mac for arrays
;   in SARAM will cause a performance improvement of 25%.
;   For better performance, it would be much faster to perform the autocorrelation by
;   first temporarily copying the array to a different block of memory.  Copying to SARAM 
;   would be okay.  Then do the dual-mac autocorrelation between the original and its clone.  
;   This should speed up the autocorrelation by up to 50% from its current speed.
;
; Benchmarks:
;   Cycles:
;     nx =  152:  nr = 152:   12148
;     nx =  128:  nr = 128:    8704
;     nx =   64:  nr =  64:    2336
;     nx =   61:  nr =  61:    2252
;     nx =   61:  nr =  58:    2130
;   Code Size (in bytes):  187
;
; History:
;       Li Yuan - 08/14/2001
; - Modified save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
; 
;       Zhengting He - 10/25/2006
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;
;       Craig Leeds - 05/29/2012
;  Fixed bug where T2 & T3 were modified but not restored.
;  Fixed bug where XAR5 was modified but not properly restored.
;  Fixed bug where SXMD not 1 on exit.
;  Fixed bug where overflow bits are not cleared on entry.
;  Fixed bug where compiler told that ARMS is 0 but it is actually 1.
;  Fixed bug when nx or nr is odd.
;  A little optimization.
;
;****************************************************************

	.ARMS_off                      ;enable assembler for ARMS=0
	.CPL_on                       ;enable assembler for CPL=1
	.mmregs                       ;enable mem mapped register names
	.global _acorr_bias

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 2            ;save-on-entry registers saved (T2, T3)
FRAME_SZ          .set (4+1)        ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ
	.asg    0, temp
        .asg    1, rSUBnr           ; original r[nr] value
        .asg    2, r_save           ; original r
        .asg    3, restoreFlag      ; 
	.asg    0 + FRAME_SZ + REG_SAVE_SZ, RETURN_ADDR
	
	.asg	 AR0,  x_ptr
	.asg	XAR0, Xx_ptr
	.asg	 AR1,  r_ptr
	.asg	XAR1, Xr_ptr
	.asg	 AR2,  x_save
	.asg	XAR2, Xx_save
	.asg     AR3,  x2_save
	.asg    XAR3, Xx2_save
	.asg     AR4,  xb_ptr
	.asg    XAR4, Xxb_ptr

	.asg	T0,   nx  
	.asg	T1,   nr 
	.asg    T2,   loop_count
	.asg	T3,   n_inverse

;
; CSR = counter = nx - 3
; BRC0 = loop_count = MIN(((nr+1)/2), ((nx-1)/2)) - 1;  // number of passes thru RPTBLOCAL block minus 1
; mac2flag = ((nx & 1) == 0) &&((nx - nr) <= 1)         // do 2 macs at the end
; mac1flag = (nx == nr)                                 // do 1 mac  at the end  (note: independent of mac2flag)
; restoreFlag = (nr & 1) && (!(mac2flag | mac1flag))    // restore original r[nr] at end
;
	
        .text
_acorr_bias:

;
; Save any save-on-entry registers that are used
; Configure the status registers as needed.
;----------------------------------------------------------------
        PSH     T2, T3
      ||BCLR    ARMS                 ; clear ARMS
        BSET    FRCT                 ; Set FRCT
        ROR     CARRY, nx, TC2, AC3  ; TC2 = 1 if nx is odd (AC3 is irrelevant)
     || BCLR    ACOV0                ; clear overflow bit
        BCLR    ACOV3                ; clear overflow bit
;
; Allocate the local frame and argument block( +1 is for dbl alignment)
;----------------------------------------------------------------
     || AADD    #-(ARG_BLK_SZ + FRAME_SZ), SP 
;
; Initialize some of the variables
;----------------------------------------------------------------

        SUB     #1, nr, loop_count
        SUB     #3, nx, T3
        MIN     T3, loop_count
        SFTS    loop_count, #-1
        MOV     loop_count, BRC0       ; loop_count = MIN(((nr+1)/2), ((nx-1)/2)) - 1;  

; mac2flag = ((nx & 1) == 0) &&((nx - nr) <= 1)         // do 2 macs at the end
; mac1flag = (nx == nr)                                 // do 1 mac  at the end  (note: independent of mac2flag)
; restoreFlag = (nr & 1) && (!(mac2flag | mac1flag))    // restore original r[nr] at end

        MOV     nx, AC0
     || MOV     #0, AC1
        SUB     nr, AC0                  ; AC0 = (nx - nr)
        SUB     #1, AC0, AC3             ; AC3 = (nx - nr) - 1 
        CMPAND  AC3 <= AC1, !TC2, TC1    ; TC1 = mac2flag = ((nx & 1) == 0) &&((nx - nr) <= 1) 
        CMP     AC0 == AC1, TC2          ; TC2 = mac1flag = (nx == nr) 

     || AND     #1, nr, T3               ; T3 = (nx - nr)
        XCCPART TC1 | TC2
            ||MOV   #0, T3               ; T3 = restoreFlag = (nr & 1) && (!(mac2flag | mac1flag))    // restore original r[nr] at end
        MOV     T3, *SP(restoreFlag)
        XCCPART T3 != #0
            ||MOV     *r_ptr(nr), AC0
        MOV     AC0, *SP(rSUBnr)         ; save original r[nr] 
        MOV     r_ptr, *SP(r_save)       ; r_save = r_ptr

; ---- Prepare the scaling value ----
        MOV     nx, *SP(#temp)
        MOV     #32767, AC0
     || RPT     #16-1
                SUBC    *SP(#temp), AC0
        ADD     #1, AC0, T3         ; T3 = n_inverse

; Generic pointer and loop setup 
;      Generic will be used by both normal dual mac 

        MOV     Xx_ptr, XCDP          ; Setup CDP         
        MOV     Xx_ptr, Xx_save
        MOV     Xx_ptr, Xx2_save
        AMAR    *x_ptr(#1), Xxb_ptr   ; Setup the secondary pointer

        SUB     #3, nx
        MOV     nx, CSR                ; CSR = nx - 3

     || BCC      OuterLoopEnd, loop_count < #0
;
; Perform correlation:                                       
;----------------------------------------------------------------
        
        RPTBLOCAL OuterLoopEnd-1

                ; ---- Preload A ----
                MPY     *x_ptr+, *CDP+, AC0
                ::MPY   *xb_ptr+, *CDP+, AC3

                ; ---- Main Dual MAC loop  ----
              ||RPTSUB  CSR, #2
                        MAC     *x_ptr+, *CDP+, AC0
                        ::MAC   *xb_ptr+, *CDP+, AC3

                ; ---- Do one MAC for A, Load with B  ----
                MACM    *x_ptr, *CDP, AC0
              ||AADD    #2, x2_save

                ; ---- Multiply B with inverse, Load T3 with A  ----
                MPYR    T3, AC3, AC3
              ||MOV     x_save, CDP

                ; ---- Multiply A with inverse, x2 incremented by two because of DUAL MAC ----
                MPYR    T3, AC0, AC0
              ||AMOV    x2_save, x_ptr      

                ; ---- Store A, reset CDP ----
                ; ---- Reload x_pointer (used for A) with new x2_save ----
                MOV     HI(AC0), *r_ptr+
              ||AMOV    x2_save, xb_ptr               ; Setup the secondary pointer

                ; ---- Store B, 
                MOV     HI(AC3), *r_ptr+

                ; ---- Reload xb_ptr (used for B) with one more than x_ptr ----
              ||AADD    #1, xb_ptr               ; Setup the secondary pointer
OuterLoopEnd:

;;;     BCC     Skip2macs, !TC1
        
; ---- 2 -----
; Do 2 macs at the end
; ((nx - nr) <= 1)                     
        XCC    TC1
             ||MPYM    *x_ptr+, *CDP+, AC0
        XCC    TC1
             ||MACM    *x_ptr, *CDP-, AC0
        MPYR    T3, AC0, AC0
        XCC    TC1
             ||MOV     HI(AC0), *r_ptr+
;;;Skip2macs:

; ---- 1 -----
; Do 1 macs at the end
; ((nx - nr) == 0)                     
        MPYM    *x_ptr, *CDP, AC0
        MPYR    T3, AC0, AC0
        XCCPART TC2
            ||MOV    HI(AC0), *r_ptr

        MOV     *SP(r_save), r_ptr     ; r_ptr = r_save
        MOV     *SP(restoreFlag), T2

; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
        MOV     #0, T0               ;clear oflag
        XCCPART overflow(AC0)        ;clears ACOV0
            ||MOV   #1, T0           ;overflow occurred
        XCCPART overflow(AC3)        ;clears ACOV3
            ||MOV   #1, T0           ;overflow occurred
;
; If there were an odd number of output elements 
; then r[nr] may have been incorrectly overwritten.
; So restore r[nr] to its original value.
;
        MOV    *SP(rSUBnr), AC0
        XCCPART T2 != #0
            ||MOV   AC0, *r_ptr(nr)
;
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------

        AADD    #(ARG_BLK_SZ + FRAME_SZ), SP
        POP     T2, T3
     || BSET    ARMS                 ; set ARMS for C
;
; Return to calling function
;----------------------------------------------------------------
        BCLR    FRCT                 ; Clear FRCT for C
     || RET                        
;----------------------------------------------------------------
;End of file
