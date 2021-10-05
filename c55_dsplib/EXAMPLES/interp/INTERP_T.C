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

/*****************************************************************************
//  Filename:	 interp_t.c
//  Version:	 0.01
//  Description: test for interp routine
// *****************************************************************************/

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

short eflag = PASS;
DATA  *dbptr = &db[0];

main()
{
    short i;
    
    /* clear */
    for (i = 0; i < NX * I; i++) r[i] = 0;	       /* clear output buffer (optional) */
    for (i = 0; i < (NH / I) + 1; i++) db[i] = 0;  /* clear delay buffer (a must)  */

    /* compute */
    firinterp(x, h, r, dbptr, NH, NX, I);
    eflag = test(r, rtest, NX*I, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    /* 
    ** Try the same data again, but with multiple calls to the filter function.
    ** This proves that the index in dbuffer[0] is stored correctly.
    */
    
    // clear output and delay buffer
    for (i = 0; i < NX * I; i++) r[i] = 0;	       /* clear output buffer (optional) */
    for (i = 0; i < (NH / I) + 1; i++) db[i] = 0;  /* clear delay buffer (a must)  */

    firinterp(x, h, r, dbptr, NH, NX/3, I);
    firinterp(&x[NX/3], h, &r[I*(NX/3)], dbptr, NH, NX/3, I);
    firinterp(&x[2*(NX/3)], h, &r[I*(2*(NX/3))], dbptr, NH, (NX - (2*(NX/3))), I);
    
    /* test    */
    eflag = test(r, rtest, NX*I, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return 1;
}
