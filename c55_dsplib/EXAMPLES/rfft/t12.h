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

/* Test for rfft: both */
#define NX 64
#define FNAME "t12"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
32764,	/* 0 */ 
32031,	/* 1 */ 
29882,	/* 2 */ 
26460,	/* 3 */ 
21992,	/* 4 */ 
16770,	/* 5 */ 
11129,	/* 6 */ 
5424,	/* 7 */ 
0,	/* 8 */ 
-4835,	/* 9 */ 
-8824,	/* 10 */ 
-11789,	/* 11 */ 
-13634,	/* 12 */ 
-14354,	/* 13 */ 
-14028,	/* 14 */ 
-12812,	/* 15 */ 
-10922,	/* 16 */ 
-8612,	/* 17 */ 
-6154,	/* 18 */ 
-3809,	/* 19 */ 
-1813,	/* 20 */ 
-348,	/* 21 */ 
464,	/* 22 */ 
572,	/* 23 */ 
0,	/* 24 */ 
-1164,	/* 25 */ 
-2771,	/* 26 */ 
-4635,	/* 27 */ 
-6548,	/* 28 */ 
-8299,	/* 29 */ 
-9703,	/* 30 */ 
-10609,	/* 31 */ 
-10922,	/* 32 */ 
-10609,	/* 33 */ 
-9703,	/* 34 */ 
-8299,	/* 35 */ 
-6548,	/* 36 */ 
-4635,	/* 37 */ 
-2771,	/* 38 */ 
-1164,	/* 39 */ 
-1,	/* 40 */ 
572,	/* 41 */ 
464,	/* 42 */ 
-348,	/* 43 */ 
-1813,	/* 44 */ 
-3809,	/* 45 */ 
-6154,	/* 46 */ 
-8612,	/* 47 */ 
-10922,	/* 48 */ 
-12812,	/* 49 */ 
-14028,	/* 50 */ 
-14354,	/* 51 */ 
-13634,	/* 52 */ 
-11789,	/* 53 */ 
-8824,	/* 54 */ 
-4835,	/* 55 */ 
-1,	/* 56 */ 
5424,	/* 57 */ 
11129,	/* 58 */ 
16770,	/* 59 */ 
21992,	/* 60 */ 
26460,	/* 61 */ 
29882,	/* 62 */ 
32031,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
-1, 
-1, 
5460, 
0, 
5460, 
0, 
5460, 
0, 
0, 
0, 
0, 
-1, 
0, 
-1, 
0, 
0, 
-1, 
-1, 
-1, 
-1, 
0, 
-1, 
0, 
-1, 
0, 
0, 
0, 
-1, 
0, 
-1, 
0, 
-1, 
0, 
0, 
0, 
-1, 
0, 
-1, 
-1, 
-1, 
-1, 
0, 
-1, 
-1, 
0, 
-1, 
0, 
0, 
0, 
0, 
-1, 
-1, 
0, 
0, 
0, 
0, 
0, 
0, 
-1, 
0, 
-1, 
0, 
0, 
0, 
};

DATA error;

