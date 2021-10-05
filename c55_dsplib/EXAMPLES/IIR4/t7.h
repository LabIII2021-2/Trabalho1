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

/* Test for iircas4 : rand */
#define NX 35
#define NBIQ 4
#define FNAME "t7"
#define MAXERROR 20

DATA x[NX] ={
-113,
-300,
-348,
-253,
-200,
171,
-712,
-864,
-78,
691,
812,
-441,
-636,
697,
-491,
272,
873,
308,
692,
-917,
-680,
596,
-131,
730,
439,
350,
-288,
-625,
-645,
-578,
-146,
665,
-19,
590,
-74,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2  ... */
-1677,
5902,
-19442,
-11845,

-1939,
18991,
-7967,
4923,

-3452,
2071,
-17728,
9176,

15791,
-3930,
7596,
-4881,
};

DATA rtest[NX] ={
-113,
-348,
-601,
-802,
-981,
-751,
-1591,
-1825,
-1920,
-1270,
-684,
-1002,
-991,
-257,
-1167,
-11,
122,
644,
1336,
224,
387,
498,
79,
1112,
852,
1570,
883,
723,
-114,
-520,
-815,
-242,
-677,
410,
-270,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ+2];  // index + (2*NBIQ+1)
DATA *dp = dbuffer;

DATA r[NX];

