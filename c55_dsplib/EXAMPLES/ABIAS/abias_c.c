/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

//;***********************************************************
//; Version 3.00.00                                           
//;***********************************************************
//; Function:    acorr_bias
//; Processor:   C55xx
//; Description: calculates positive biased auto-correlation
//;
//; Usage:    short acorr_bias(DATA *x, DATA *r, ushort nx, ushort nr)
//;
//;  05/31/2012:  Fixed for odd values of nr
//;****************************************************************


#include <tms320.h>

#define BIAS 1

void 
#if BIAS
acorr_c_bias
#else
acorr_c_raw
#endif
    (DATA *x, DATA *r, ushort nx, ushort nr)
{

	DATA *x_ptr,*xb_ptr,*r_ptr,*x2_save,*x_save,*cdp;
	
	short counter,loop_count,i,j,csr;
#if BIAS    
    short n_inverse, t2, t3;
	long nxs;
#endif    
	long ac0,ac3,ac1,ac2;
    DATA rSUBnr;
    short loop_count2;
    short mac2flag;     // do 2 macs at the end
    short mac1flag;     // do 1 mac  at the end (note: this can only be true if if mac2flag is set)
    short restoreFlag;  // restore original r[nr] at end
	
	//initialize some of the variables
    //loop_count = MIN(((nr+1)>>1, ((nx-1)>>1) - 1;   // number of passes thru RPTBLOCAL block minus 1
    loop_count = (nr+1)>>1;
    loop_count2 = ((nx-1)>>1);
    if (loop_count > loop_count2)
        loop_count = loop_count2;
    loop_count--;    
    mac2flag = (((nx & 1) == 0) && ((nx - nr) <= 1));   // do 2 macs at the end
    mac1flag = (nx == nr);                              // do 1 mac  at the end 
    restoreFlag = (nr & 1) && (!(mac2flag | mac1flag)); // restore original r[nr] at end
    if (restoreFlag) {
        rSUBnr = r[nr];   // save original value if it needs to be restored
	}
    
	x_save=x;
	x2_save=x;
	r_ptr=r;
    
#if BIAS    
	//prepare for scaling
	ac0=32767;
	nxs=((long)(nx))<<15;
	for(i=0;i<16;i++){
		if(ac0<nxs)
			ac0<<=1;
		else
			ac0=((ac0-nxs)<<1)+1;
	}
	n_inverse=(short)(ac0+1);
#endif    
	
	//generic pointer and loop setup
	cdp=x_save;
	x_ptr=x2_save;
	xb_ptr=x_ptr+1;
	counter=nx-3;
	csr = counter;
	for(i=0;i<=loop_count;i++) {
		ac1 = (long)(*x_ptr) * (*cdp);
		x_ptr++;
		ac0 = ac1<<1;
		ac2 = (long)(*xb_ptr) * (*cdp);
		xb_ptr++;cdp++;
		ac3=ac2<<1;
		for(j=0;j<=csr;j++){
			ac1 = (long)(*x_ptr) * (*cdp);
			x_ptr++;
			ac0 += ac1<<1;
			ac2 = (long)(*xb_ptr) * (*cdp);
			xb_ptr++;cdp++;
			ac3 += ac2<<1;
		}
		csr-=2;
		ac1 = (long)(*x_ptr) * (*cdp);
		ac0 += ac1<<1;
#if BIAS            
		t2=(short)(ac3>>16);
		ac3 = (long)(n_inverse)*t2;
		ac3<<=1;
#endif
		ac3 += (long)0x8000;
		ac3>>=16;
#if BIAS            
		t3=(short)(ac0>>16);
		ac0 = (long)(n_inverse)*t3;
		ac0<<=1;
#endif
		ac0 += (long)0x8000;
		ac0>>=16;
		x2_save+=2;
		*r_ptr++ = (short)ac0;
		cdp=x_save;
		*r_ptr++ = (short)ac3;
		x_ptr=x2_save;
		xb_ptr=x_ptr+1;
	}
        
    if (mac2flag) {
	    ac1 = (long)(*x_ptr) * (*cdp);
	    x_ptr++;cdp++;
	    ac0 = ac1<<1;
	    ac1 = (long)(*x_ptr) * (*cdp);
	    cdp--;
	    ac0 += ac1<<1;
#if BIAS            
	    t3=(short)(ac0>>16);
	    ac0 = (long)(n_inverse) * t3;
	    ac0<<=1;
#endif
	    ac0 += (long)0x8000;
	    ac0>>=16;
	    *r_ptr++=(short)ac0;
    }
    
	if(mac1flag){
		ac1 = (long)(*x_ptr) * (*cdp);
		ac0=ac1<<1;
#if BIAS            
		t3=(short)(ac0>>16);
		ac0 = (long)(n_inverse) * t3;
		ac0<<=1;
#endif            
	    ac0 += (long)0x8000;
		ac0>>=16;
		*r_ptr++=(short)ac0;
	}
	if(restoreFlag) {
        r[nr] = rSUBnr;    /* restore the overwritten value */
    }
	//finish
	return;
}
