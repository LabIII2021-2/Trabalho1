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

//=============================================================================
//  Filename:	 cfft32_t.c
//  Version:     1.0				       
//  Description: test for 32-bit complex fft
//=============================================================================

#include <stdlib.h>
#include <tms320.h>
#include <math.h>
#include <stdio.h>
#include <dsplib.h>

//#include "t1_SCALE.h"
//#include "t2_SCALE.h"
//#include "t3_SCALE.h"
//#include "t4_SCALE.h"
//#include "t5_SCALE.h"
//#include "t6_SCALE.h"
//#include "t7_SCALE.h"

//#include "t2_NOSCALE.h" // 16
//#include "t3_NOSCALE.h" // 32
//#include "t4_NOSCALE.h" // 64
//#include "t5_NOSCALE.h" // 128
#include "t6_NOSCALE.h" // 256

#ifndef SCALING
#define SCALING 0
#endif

short ltest(LDATA *r, LDATA *rtest, short n, LDATA maxerror);

short eflagi = PASS;


void main()
{
		
#if SCALING
	cfft32_SCALE(x,NX);
#else    
    cfft32_NOSCALE(x, NX);
#endif    

	cbrev32(x, x, NX);
	
	eflagi = ltest(x, rtest, NX, (LDATA)(MAXERROR));	// for r
    
	if(eflagi != PASS){
        exit(-1);
	}
}
