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
//  Filename:    iir4_t.c
//  Version:     0.01
//  Description: test for iircas4 routine
//*****************************************************************************

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <tms320.h>
#include <Dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t4.h"
//#include "t6.h"
//#include "t7.h"
//#include "t8.h"
//#include "test.h"

short test(DATA *r, DATA *rtest, short n, DATA maxerror);

short eflag = PASS;     // error flag or index into r vector where error



#define NX 16
#define NBIQ 1
#define FNAME "t2"
#define MAXERROR 20

/* Função seno
DATA x[NX] ={
             0,
             16383,
             28377,
             32767,
             28377,
             16383,
             0,
             -16383,
             -28377,
             -32768,
              -28377,
              -16384,
};*/



DATA x[NX] ={
             1841,
             -1101,
             437,
             -58,
             1601,
             1072,
             -179,
             -1971,
             1315,
             -227,
             472,
             1194,
             1726,
             974,
             -1325,
             -386,
};


//#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ+2];  // index + (2*NBIQ+1)
DATA *dp = dbuffer;

DATA r[NX];



//#pragma DATA_SECTION (h,".coeffs")

/* Teste
DATA h[4*NBIQ] ={
                  32765,
                  12288,
                  16384,
                  2212,
};*/


DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2 ... */
                  16393,
                  -5786,
                  15478,
                  -19274,
};


/*
 * Função seno
 * DATA rtest[NX] ={
0,
16383,
28377,
32767,
28377,
16383,
0,
-16383,
-28377,
-32768,
 -28377,
 -16384,
};*/

DATA rtest[NX] ={
0,
16383,
28377,
32767,
28377,
16383,
0,
-16383,
-28377,
-32768,
 -28377,
 -16384,
};

void main()
{
    short i;

    // clear
    for (i = 0; i < NX; i++) r[i] =0;                     // clear output buffer (optional)
    for (i = 0; i < (2 * NBIQ) + 2; i++) dbuffer[i] = 0;  // clear delay buffer (a must)

    // compute
    iircas4(x, h, r, dp, NBIQ, NX);

    printf("hello world!");
    printf("222");
    return;
}
