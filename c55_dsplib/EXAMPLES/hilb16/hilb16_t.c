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
//  Filename:	 hilb16_t.c
//  Version:	 0.02
//  Description: test for hilbert routine
//*****************************************************************************

#include <stdlib.h>
#include <math.h>
#include <tms320.h>
#include <stdio.h>
#include <dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
#include "t4.h"	
//#include "test.h"

short test(DATA *r, DATA *rtest, short n, DATA maxerror);

short eflag1= PASS;
short eflag2= PASS;
DATA  *dbptr = &db[0];
                                                                                                                                                                                                   

void main()
{
    short i;
    
    // 1. Test for single-buffer

    // clear
    for (i = 0; i < NX; i++) r[i] = 0;       // clear output buffer (optional)
    for (i = 0; i < NH + 2; i++) db[i] = 0;  // clear delay buffer (a must)

    // compute
    hilb16(x, h, r, dbptr, NX, NH);

    // test
    eflag1 = test (r, rtest, NX, MAXERROR);

    // 2. Test for dual-buffer

    // clear again
    for (i = 0; i < NX; i++) r[i] = 0;       // clear output buffer (optional)
    for (i = 0; i < NH + 2; i++) db[i] = 0;  // clear delay buffer (a must)

    dbptr = &db[0];

    // compute
    if (NX >= 4)
    {
        hilb16(x, h, r, dbptr, NX/4, NH);
        hilb16(&x[NX/4], h, &r[NX/4], dbptr, NX/4, NH);
        hilb16(&x[2*(NX/4)], h, &r[2*(NX/4)], dbptr, NX/4, NH);
        hilb16(&x[3*(NX/4)], h, &r[3*(NX/4)], dbptr, (NX - (3 * (NX/4))), NH);
    }

    // test
    eflag2 = test (r, rtest, NX, MAXERROR);

    if( (eflag1 != PASS) || (eflag2 != PASS) )
    {
        exit(-1);
    }

    return;
}
