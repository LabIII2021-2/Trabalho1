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
//  Filename:	 rfft32_t.c
//  Version:	 0.01
//  Description: test for cfft routine
//*****************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <tms320.h>
#include <stdio.h>
#include <dsplib.h>

/*
** Note: only values of NX that are supported are powers of 2
** from 16 thru 2048.
*/
//#include "t2.h" // ok
//#include "t3.h" // ok
//#include "t4.h" // ok
//#include "t5.h" // ok
//#include "t6.h" // ok
//#include "t7.h" // ok
#include "t8.h" // ok
//#include "t10.h" // ok
//#include "t11.h" // ok
//#include "t12.h" // ok

short ltest(LDATA *r, LDATA *rtest, short n, LDATA maxerror);

short eflagf = PASS;

void main()
{
	// compute
    rfft32(x, NX, SCALE);
    
	eflagf = ltest(x, rtest, NX, MAXERROR);

    if(eflagf != PASS)
    {
        exit(-1);
    }

	return;
}

