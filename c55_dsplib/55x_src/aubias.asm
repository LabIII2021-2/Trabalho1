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
; Function:    acorr_unbias
; Processor:   C55xx
; Description: calculates positive unbiased auto-correlation
;
; Usage:    short acorr_unbias(DATA *x, DATA *r, ushort nx, ushort nr)
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
;     nx =  128:  nr = 128:    11397
;     nx =   81:  nr =  81:    5335
;     nx =   64:  nr =  64:    3653
;     nx =   32:  nr =  32:    1317
;   Code Size (in bytes):  214
;
; History:
;       Li Yuan - 08/14/2001
; - Changed save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
; - Fixed XARx init bug (added Xx_ptr,Xx_save,Xx2_save,Xxb_ptr).
;
;       Zhengting He - 10/25/2006
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;
;       Craig Leeds - 05/31/2012
;   Bug fixed where AR4 was used before being set.
;   Fixed bug where AR5 was modified but not correctly restored.
;   Fixed bug where AC0 and AC3 were checked for overflow, but overflow was not first cleared.
;   Fixed bug where T2 and T3 were modified but not restored.
;   Fixed bug where the incorrect number of elements were saved when nr was odd
;   Fixed bug where SXMD was clear instead of set on exit.
;   Fixed bug where compiler was told ARMS was clear, but it was set.
;   Optimized main loop some.
;
;****************************************************************

	.ARMS_off                     ;enable assembler for ARMS=0
	.CPL_on                       ;enable assembler for CPL=1
	.mmregs                       ;enable mem mapped register names
	.global _acorr_unbias

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 2            ;save-on-entry registers saved (T2, T3)
FRAME_SZ          .set 5            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ
	.asg    0, temp
	.asg    1, tempb
        .asg    2, rSUBnr           ; original r[nr] value
        .asg    3, r_save           ; original r
        .asg    4, restoreFlag      ; 
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
        
	.asg	T0,  nx
	.asg	T1,  nr
	.asg    T2,   loop_count
	
    
;
; CSR = counter = nx - 3
; BRC0 = loop_count = MIN(((nr+1)/2), ((nx-1)/2)) - 1;  // number of passes thru RPTBLOCAL block minus 1
; mac2flag = ((nx & 1) == 0) &&((nx - nr) <= 1)         // do 2 macs at the end
; mac1flag = (nx == nr)                                 // do 1 mac  at the end  (note: independent of mac2flag)
; restoreFlag = (nr & 1) && (!(mac2flag | mac1flag))    // restore original r[nr] at end
;

        .text
_acorr_unbias:
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

; Generic pointer and loop setup 
;      Generic will be used by both normal dual mac 

        MOV     Xx_ptr, XCDP          ; Setup CDP         
        MOV     Xx_ptr, Xx_save
        MOV     Xx_ptr, Xx2_save
        AMAR    *x_ptr(#1), Xxb_ptr   ; Setup the secondary pointer

;--------Divisor value setup----------
        MOV     nx, *SP(#temp)        ; This value is used for division
        SUB     #1, nx, AC0
            
        SUB     #3, nx, T3
        MOV     T3, CSR                ; CSR = nx - 3
        MOV     #16-1, BRC1

     || BCC      OuterLoopEnd, loop_count < #0

        MOV     AC0, *SP(#tempb)      ; This value is used for division for the second thing
        
; Perform correlation:                                       
;----------------------------------------------------------------        
     || RPTBLOCAL OuterLoopEnd-1

; ---- Preload ----
                MPY     *x_ptr+, *CDP+, AC0
                ::MPY   *xb_ptr+, *CDP+, AC3

; ---- Main Dual MAC loop  ----
              ||RPTSUB  CSR, #2
                        MAC     *x_ptr+, *CDP+, AC0
                        ::MAC   *xb_ptr+, *CDP+, AC3

; ---- Do one MAC for A, Load T4 with B  ----
                MACM    *x_ptr+, *CDP+, AC0
              ||MOV     HI(AC3), T3

; ---- Scale results ----
; Divide result by number of MACs performed, result is in 
; lower half of accumulator
;
; A and B are only used to give C and D the correct sign

                MOV     HI(AC0), T2

; ---- Get ABS of C and D, update CDP and x2_save ----
              ||ABS     T3, AC3             ; C
                MOV     x_save, CDP
              ||ABS     T2, AC0

                BCLR    SXMD                ; Set SXMD
                ADD     #2, x2_save

; ---- Scale values ----

             || RPTBLOCAL DivideLoopEnd-1
                        NOP_16              ; Remark 5682: CPU_116
                      ||SUBC    *SP(#temp), AC0
                        SUBC    *SP(#tempb), AC3     ; C
DivideLoopEnd:

                BSET    SXMD                ; Set SXMD

; ---- Negate if necessary ----
                XCCPART T2 < #0                ; for the second variable
                    ||NEG   AC0                ; C
                XCCPART T3 < #0
                    ||NEG   AC3

; ---- Store the values, update A pointer ----
                MOV     AC0, *r_ptr+
              ||AMOV    x2_save, x_ptr
                MOV     AC3, *r_ptr+
                AMAR    *x2_save(#1), Xxb_ptr        ; Setup the secondary pointer        
        
; ---- Update scaling values ----
                ADD     #-2, *SP(#temp)
                ADD     #-2, *SP(#tempb)

; ---- B pointer update ----

OuterLoopEnd:

; ---- 2 -----
; Do 2 macs at the end
; ((nx - nr) <= 1)                     
        XCC     TC1
              ||MPYM    *x_ptr+, *CDP+, AC0
        XCC     TC1
              ||MACMR   *x_ptr, *CDP-, AC0 
        XCC     TC1
              ||MOV     HI(AC0 <<#-1), *r_ptr+     ; divide by 2

; ---- 1 -----
        MPYMR   *x_ptr, *CDP, AC0
        XCCPART TC2
              ||MOV     HI(AC0), *r_ptr+           ; divide by 1

        MOV     *SP(r_save), r_ptr     ; r_ptr = r_save
        MOV     *SP(restoreFlag), T2

; Check if overflow occurred, and setup return value
; Do 1 macs at the end
; ((nx - nr) == 0)                     
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
        RET                        
     || BCLR    FRCT                 ; Clear FRCT for C
;----------------------------------------------------------------
;End of file
