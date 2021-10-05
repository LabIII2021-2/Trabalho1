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
//; Version 2.30.00                                           
//;***********************************************************
//; Function:    acorr_unbias
//; Processor:   C55xx
//; Description: calculates positive unbiased auto-correlation
//; Usage:    short acorr_c_unbias(DATA *x, DATA *r, ushort nx, ushort nr)
//;****************************************************************

#include <tms320.h>

void acorr_c_unbias(DATA *x, DATA *r, ushort nx, ushort nr){

	DATA *x_ptr,*xb_ptr,*r_ptr,*x2_save,*x_save,*cdp;
	
	short counter,loop_count,i,j,k,csr,t2,t3;
	short temp,temp1;
	long ac0,ac3,ac1,ac2,c;
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
	
	//initialize some of the variables
	x_save=x;
	x2_save=x;
	r_ptr=r;
		
	ac0=nx-nr;
	
	//divisor value setup
	temp=nx;
	temp1=nx-1;
	
	if(nr!=1){
		
		//generic pointer and loop setup
		cdp=x_save;
		x_ptr=x2_save;
		xb_ptr=x_ptr+1;
		counter=nx-3;
		csr=counter;
		for(i=0;i<=loop_count;i++){
			//ac1=(long)((*x_ptr++)*(long)(*cdp));
			ac1=(long)(*x_ptr)*(*cdp);
			x_ptr++;
			ac0=ac1<<1;
			//ac2=(long)((long)(*xb_ptr++)*(long)(*cdp++));
			ac2=(long)(*xb_ptr)*(*cdp);
			xb_ptr++;cdp++;
			ac3=ac2<<1;
			for(j=0;j<=csr;j++){
				//ac1=(long)((*x_ptr++)*(long)(*cdp));
				ac1=(long)(*x_ptr)*(*cdp);
				x_ptr++;
				ac0+=ac1<<1;
				//ac2=(long)((long)(*xb_ptr++)*(long)(*cdp++));
				ac2=(long)(*xb_ptr)*(*cdp);
				xb_ptr++;cdp++;
				ac3+=ac2<<1;
			}
			csr-=2;
			//ac1=(long)((*x_ptr)*(long)(*cdp));
			ac1=(long)(*x_ptr)*(*cdp);
			ac0+=ac1<<1;
			x_ptr++;cdp++;
			
			t2=(short)(ac3>>16);
			t3=(short)(ac0>>16);
			//c=t2;
			//ac3=t3;
			//ac0=t3;
			cdp=x_save;
			ac3=ABSVAL(t3);
			c=ABSVAL(t2);
			x2_save+=2;
			for(k=0;k<=15;k++){
				if (ac3>=((long)temp<<15)){
					ac3-=(long)temp<<15;
					ac3=(ac3<<1)+1;
				}
				else
					ac3<<=1;
				if (c>=((long)temp1<<15)){
					c-=(long)temp1<<15;
					c=(c<<1)+1;
				}
				else
					c<<=1;
			}
			if(t3<0)
				ac3=-ac3;
			if(t2<0)
				c=-c;

			*r_ptr++=(short)ac3;
			*r_ptr++=(short)c;
			x_ptr=x2_save;
			xb_ptr=x_ptr+1;
			temp-=2;
			temp1-=2;
		}
		//regular
		//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			
        if (mac2flag) {
		    ac1=(long)(*x_ptr)*(*cdp);
		    x_ptr++;cdp++;
		    ac0=ac1<<1;
		    //ac1=(long)((*x_ptr)*(long)(*cdp--));
		    ac1=(long)(*x_ptr)*(*cdp);
		    cdp--;
		    ac0+=ac1<<1;
		    ac0+=0x8000;
		    ac0>>=17;
		    *r_ptr++=(short)ac0;
        }
        if (mac1flag) {
			//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			ac1=(long)(*x_ptr)*(*cdp);
			//x_ptr++;cdp++;
			ac0=ac1<<1;
			ac0+=0x8000;
			ac0>>=16;
			*r_ptr++=(short)ac0;
		}
	    if(restoreFlag) {
            r[nr] = rSUBnr;    /* restore the overwritten value */
        }
		//finish
		return;
	}
	else{
	//single mac
		temp=nx;
		cdp=x_save;
		x_ptr=x2_save;
		csr=nx-2;
		//ac1=(long)((*x_ptr++)*(long)(*cdp++));
		ac1=(long)(*x_ptr)*(*x_ptr);
		x_ptr++;
		ac0=ac1<<1;
		for(j=0;j<=csr;j++){
			//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			ac1=(long)(*x_ptr)*(*x_ptr);
			x_ptr++;
			ac0+=ac1<<1;
		}
		
		t3=(short)(ac0>>16);
		ac3=ABSVAL(t3);
		for(k=0;k<=15;k++){
			if (ac3>=((long)temp<<15)){
				ac3-=(long)temp<<15;
				ac3=(ac3<<1)+1;
			}
			else
				ac3<<=1;
		}
		if(t3<0)
			ac3=-ac3;
		*r_ptr++=(short)ac3;
		return;		
	}
}
