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

/*=============================================================================
  Filename:  iir32_t.c
  Version:     0.001
  Description: test for cascaded infinite impulse response filter (raw)
=============================================================================*/

#include <dsplib.h>
#include <stdlib.h>
#include <math.h>
#include <tms320.h>
#include <stdio.h>
#include "t5.h"
//#include "test.h"

short test(DATA *r, DATA *rtest, short n, DATA maxerror);

/* #define NR   NX*/

short eflag=PASS;          /* error flag (-1: no error; else error)  */
DATA elevel=0;             /* error level detected                   */
DATA emax=0;

/* FILE *fp; */


void main()
{
    short i;

    /* clear   */
    for (i = 0; i < NX; i++) r[i] = 0;                      /* output buffer (optional) */
    for (i = 0; i < ((2 * NBIQ) + 1); i++) dbuffer[i] = 0;  /* delay buffer (mandatory) */

    /* compute */

    iir32(x, h, r, dp, NBIQ, NX);

    /* test    */
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    /*
    ** Try the same data again, but with multiple calls to the filter function.
    ** This proves that the index in dbuffer[0] is stored correctly.
    */

    /* clear again  */
    for (i = 0; i < NX; i++) r[i] = 0;                      /* output buffer (optional) */
    for (i = 0; i < ((2 * NBIQ) + 1); i++) dbuffer[i] = 0;  /* delay buffer (mandatory) */

    /* compute */

    iir32(x, h, r, dp, NBIQ, NX/3);
    iir32(&x[NX/3], h, &r[NX/3], dp, NBIQ, NX/3);
    iir32(&x[2*(NX/3)], h, &r[2*(NX/3)], dp, NBIQ, (NX - (2 * (NX/3))));

    /* test    */
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}