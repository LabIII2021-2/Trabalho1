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
; Function:    acorr_raw
; Version:     2.0
; Processor:   C55xx
;
; Description: calculates raw auto-correlation
;
; Usage:    short acorr_raw(DATA *x, DATA *r, ushort nx, ushort nr)
;
; Limits:
;     nr <= nx
;     nx != 3
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
;     nx =  128:  nr = 128:    8557
;     nx =  128:  nr = 127:    8557
;     nx =  128:  nr = 126:    8554
;     nx =  128:  nr = 125:    8554
;     nx =   64:  nr =  64:    2252
;     nx =   16:  nr =  15:     212
;   Code Size (in bytes):   162
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
;   Bug fixed: AR5 was modified but not restored (if an interrupt occured).
;   Bug fixed: AC0 and AC3 checked for overflow, but their bit not cleared on entry.
;   Bug fixed: if NR is odd, one too many elements were written to r[].
;   Bug fixed: if NX is 1 or 2, output was incorrect.
;   Outer loop optimized.
;
;****************************************************************

	.ARMS_off                     ;enable assembler for ARMS=0
	.CPL_on                       ;enable assembler for CPL=1
	.mmregs                       ;enable mem mapped register names
	.global _acorr_raw

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 2            ;save-on-entry registers saved (T2, T3)
FRAME_SZ          .set 2            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ
        .asg    0, rSUBnr           ; original r[nr] value
        .asg    1, r_save           ; original r

        .asg    0 + FRAME_SZ + REG_SAVE_SZ, RETURN_ADDR
        
        .asg    T0, nx
        .asg    T1, nr
        .asg    T2, loop_count

        .asg    AR0, x_ptr
        .asg    XAR0, Xx_ptr
        .asg    AR1, r_ptr
        .asg    AR2, x_save
        .asg    XAR2, Xx_save
        .asg    AR3, x2_save
        .asg    XAR3, Xx2_save
        .asg    AR4, xb_ptr
        .asg    XAR4, Xxb_ptr

;
; CSR = counter = nx - 3;
; BRC0 = loop_count = MIN(((nr+1)/2), ((nx-1)/2)) - 1;  // number of passes thru RPTBLOCAL block minus 1
; mac2flag = ((nx & 1) == 0) &&((nx - nr) <= 1)         // do 2 macs at the end
; mac1flag = (nx == nr)                                 // do 1 mac  at the end  (note: independent of mac2flag)
; restoreFlag = (nr & 1) && (!(mac2flag | mac1flag))    // restore original r[nr] at end
;

        .text
_acorr_raw:

;
; Save any save-on-entry registers that are used
; Configure the status registers as needed.
;----------------------------------------------------------------
        PSH     T3, T2
      ||BCLR    ARMS                     ; clear ARMS
        BSET    FRCT                     ; Set FRCT
        ROR     CARRY, nx, TC2, AC3      ; TC2 = 1 if nx is odd (AC3 is irrelevant)
      ||BCLR    ACOV3                    ; clear overflow bit 

;
; Allocate the local frame and argument block( +1 is for dbl alignment)
;----------------------------------------------------------------
        AADD    #-(ARG_BLK_SZ + FRAME_SZ + 1), SP
     || BCLR    ACOV0                    ; clear overflow bit 
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
        XCCPART T3 != #0
            ||MOV     *r_ptr(nr), AC0
        MOV     AC0, *SP(rSUBnr)         ; save original r[nr] 
        MOV     r_ptr, *SP(r_save)       ; r_save = r_ptr

;----------------------------------------------------------------
    
        MOV     Xx_ptr, XCDP            ; Setup CDP         
        MOV     Xx_ptr, Xx_save
        MOV     Xx_ptr, Xx2_save
        AMAR    *x_ptr(#1), Xxb_ptr   ; Setup the secondary pointer

        SUB     #3, nx                   ; 
        MOV     nx, CSR                  ; Because of the CSR updates, we need to preload CSR

; If nx < 4, then skip the repeat block.
; If nx is 3, the function will not work!
      
        BCC      OuterLoopEnd, loop_count < #0
;
; Perform correlation:                                       
;----------------------------------------------------------------
        RPTBLOCAL OuterLoopEnd-1

                ; ---- Preload ----
                MPY     *x_ptr+, *CDP+, AC0
                ::MPY   *xb_ptr+, *CDP+, AC3

                ; ---- Main Dual MAC loop  ----
             || RPTSUB  CSR, #2
                        MAC     *x_ptr+, *CDP+, AC0
                        ::MAC   *xb_ptr+, *CDP+, AC3
    
                ; ---- Do final MAC for A  ----
                MACMR   *x_ptr, *CDP, AC0        ;Create the A result (B result already created)
              ||AADD    #2, x2_save              ; increment x2_save to next set of 2 starting points
              
                MOV     rnd(HI(AC0)), *r_ptr+    ; Store A
             || AMOV    x2_save, x_ptr           ; reset x_ptr to next set of 2 starting points
        
                ; ---- Final MAC for A  ----
                MOV     rnd(HI(AC3)), *r_ptr+    ; Store B
             || AMAR    *x_save, XCDP            ; Reset CDP
    

                ; ---- Store B, reload x_pointer (used for A) with new x2_save ----
                ; ---- Reload xb_ptr (used for B) with one more than x_ptr ----
                AMAR    *x2_save(#1), Xxb_ptr         ;xb_ptr = x_ptr + #1 ; Setup the secondary pointer
OuterLoopEnd:

;;;     BCC     Skip2macs, !TC1

; ---- 2 -----
; Do 2 macs at the end
; ((nx - nr) <= 1)                     

        XCC    TC1
             ||MPYM    *x_ptr+, *CDP+, AC0
        XCC    TC1
             ||MACMR   *x_ptr, *CDP-, AC0
        XCC    TC1
             ||MOV    HI(AC0), *r_ptr+
;;;Skip2macs:

; ---- 1 -----
; Do 1 macs at the end
; ((nx - nr) == 0)                     

        MPYMR   *x_ptr, *CDP, AC0
        XCCPART TC2
            ||MOV    HI(AC0), *r_ptr

        MOV     *SP(r_save), r_ptr     ; r_ptr = r_save
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
        MOV     #0, T0               ;clear oflag
        XCCPART overflow(AC0)        ;clears ACOV0
             ||MOV    #1, T0         ;overflow occurred
        XCCPART overflow(AC3)        ;clears ACOV3
             ||MOV    #1, T0         ;overflow occurred
;
; If there were an odd number of output elements (i.e. T3 is set)
; then r[nr] was incorrectly overwritten.
; So restore r[nr] to its original value.
;
        MOV    *SP(rSUBnr), AC0
        XCCPART T3 != #0
            ||MOV   AC0, *r_ptr(nr)
;
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
        AADD    #+(ARG_BLK_SZ + FRAME_SZ + 1), SP
        POP     T3, T2
     || BSET    ARMS                 ; set ARMS for C
;
; Return to calling function
;----------------------------------------------------------------
        RET     
     || BCLR    FRCT                 ; Clear FRCT for C
;----------------------------------------------------------------
;End of file
