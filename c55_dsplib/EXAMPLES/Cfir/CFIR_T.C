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
//  Filename:	 cfir_t.c
//  Version:     1.0				       
//  Description: test for complex block finite impulse response filter (raw)
//=============================================================================

#include <stdlib.h>
#include <math.h>
#include <tms320.h>
#include <stdio.h>
#include <dsplib.h>

#pragma DATA_SECTION(x,".input")
#pragma DATA_ALIGN(x, 2)
#pragma DATA_ALIGN(db, 2)

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
//#include "t4.h"
//#include "t5.h"
//#include "t6.h"
//#include "t7.h"
//#include "t8.h"	
#include "test.h"

short test(DATA *r, DATA *rtest, short n, DATA maxerror);

short nx = NX;
short eflag1=-1; 	       // error flag (-1: no error; else error)
short eflag2=-1;	       //

#pragma DATA_ALIGN(r, 2)
DATA r[2*NX];

DATA *dbptr = &db[0];


void main()
{
    short i;
    
    // clear
    for (i = 0; i < (2 * NX); i++) r[i] =0;
    for (i = 0; i < ((2 * NH) + 2); i++) db[i]=0;

    // compute
    cfir(x, h, r, dbptr, NX, NH);

    // test  
    eflag1 = test(r, rtest, 2*NX, MAXERROR);

    // If NX > = 4 try to use db to point to correct location in buffer
    dbptr = &db[0];

    // clear again
    for (i = 0; i < (2 * NX); i++) r[i] =0;
    for (i = 0; i < ((2 * NH) + 2); i++) db[i]=0;

    // Compute again in parts. This proves that the delay history works
    if (NX >= 4)
    {
        cfir(x, h, r, dbptr, NX/4, NH);
        cfir(&x[(2*(NX/4))], h, &r[2*(NX/4)], dbptr, NX/4, NH);
        cfir(&x[2*(2*(NX/4))], h, &r[2*(2*(NX/4))], dbptr, NX/4, NH);
        cfir(&x[3*(2*(NX/4))], h, &r[3*(2*(NX/4))], dbptr, (NX - (3 * (NX/4))), NH);
    }

    // test  
    eflag2 = test(r, rtest, 2*NX, MAXERROR);

    if( (eflag1 != PASS) || (eflag2 != PASS))
    {
        exit(-1);
    }

    return;
}
