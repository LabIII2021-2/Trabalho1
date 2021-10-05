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
//  Filename:	 ldiv16_t.c
//  Version:     0.001				       
//  Description: test 32 bit by 16 bit divide (Q31/Q15 format assumed)
//=============================================================================
#include <stdlib.h>
#include <math.h>
#include <tms320.h>
#include <stdio.h>
#include <dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
//#include "t4.h"
//#include "t5.h"
//#include "t6.h"
//#include "t7.h"
#include "t8.h"		
//#include "test.h"

short ftest(float *r, float *rtest, short n, float maxerror);

#define NR    NX

short eflag = -1; 	       // error flag (-1: no error; else error)
float elevel;		       // error level detected

LDATA rem;
DATA exponent;
DATA explevel;

float rfloat[NR];


void main(void)
{ 
    short i;
    
    // clear
    for(i = 0; i <= (NR - 1); i++)
    {
        r[i] = 0;
        rexp[i] = 0;
        rfloat[i] = 0;
    }

    ldiv16(x, y, r, rexp, NX);

    // test 
    q15tofl(r, rfloat, NR);

    for (i = 0; i <= NR - 1; i++)
    {
        rfloat[i] = rfloat[i] * (float) rexp[i];
    }

    eflag = ftest(rfloat, rtest, NR, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }
    
    return;
}
