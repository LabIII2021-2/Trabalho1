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
//  Filename:	 cubias_t.c
//  Version:     0.001				       
//  Description: test for real cross-correlation (unbiased)
//=============================================================================

#include <stdlib.h>
#include <math.h>
#include <tms320.h>
#include <stdio.h>
#include <dsplib.h>

#pragma DATA_SECTION(b, ".dbuffer")
#pragma DATA_SECTION(r, ".bss:saram")

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
//#include "t4.h" //100,100
//#include "t5.h" //50,50
#include "t6.h" //16,16
//#include "t7.h"
//#include "t8.h"
//#include "t12.h" // 77,77
//#include "test.h"

short test(DATA *r, DATA *rtest, short n, DATA maxerror);

#define NLAGS    (NA + NB - 1)

short i;
short eflag=PASS; 	       // error flag (-1: no error; else error)
DATA r[NLAGS];


void main()
{
    //clear
    for (i = 0; i < NLAGS; i++) r[i] = 0;

    // compute  
    (void)corr(b, a, r, NA, NB, unbias);

    // test  
    eflag = test(r, rtest, NLAGS, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
