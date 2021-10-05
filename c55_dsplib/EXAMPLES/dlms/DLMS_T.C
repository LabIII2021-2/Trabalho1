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

//*****************************************************************************
//  Filename:	 dlms_t.c
//  Version:	 0.01
//  Description: test for dlms routine
//*****************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <tms320.h>
#include <stdio.h>
#include <dsplib.h>

//#include "t1.h" //3,3
//#include "t2.h" //21,40
//#include "t3.h" //12,20
//#include "t4.h" //32,64
//#include "t5.h" //21,128
//#include "t6.h" //12,100
//#include "t7.h"
//#include "t8.h" //3,32
#include "test.h" //12,100

short test(DATA *r, DATA *rtest, short n, DATA maxerror);

short eflagr = PASS;
short eflagh = PASS;

void main()
{
    short i;

    // clear
    for (i = 0; i< NH; i++) h[i] = 0;	// clear coeff buffer (optional)
    for (i = 0; i< NX; i++) r[i] = 0;	// clear output buffer (optional)
    dbuffer[0] = 0;             // clear index
    for (i = 1; i < NH+2; i++) dbuffer[i] = 0; // clear delay buffer (a must)

    // compute
    dlms(x, h, r, des, dbuffer, STEP, NH, NX);

    // test
    eflagr = test(r, rtest, NX, MAXERROR);	// for r
    eflagh = test(h, htest, NH, MAXERROR);	// for h

    if( (eflagr != PASS) || (eflagh != PASS) )
    {
        exit(-1);
    }

    return;
}
