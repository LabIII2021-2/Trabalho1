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

/* Test for rfft32: both */
#define NX 64
#define FNAME "t12"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

LDATA x[NX] ={
2147268899,	/* 0 */ 
2099249054,	/* 1 */ 
1958405452,	/* 2 */ 
1734136676,	/* 3 */ 
1441296806,	/* 4 */ 
1099049980,	/* 5 */ 
729400563,	/* 6 */ 
355519044,	/* 7 */ 
0,	/* 8 */ 
-316806839,	/* 9 */ 
-578258427,	/* 10 */ 
-772557448,	/* 11 */ 
-893480652,	/* 12 */ 
-940643629,	/* 13 */ 
-919288364,	/* 14 */ 
-839619945,	/* 15 */ 
-715756300,	/* 16 */ 
-564386543,	/* 17 */ 
-403256829,	/* 18 */ 
-249615598,	/* 19 */ 
-118751616,	/* 20 */ 
-22748341,	/* 21 */ 
30442271,	/* 22 */ 
37532584,	/* 23 */ 
0,	/* 24 */ 
-76244791,	/* 25 */ 
-181584409,	/* 26 */ 
-303744193,	/* 27 */ 
-429064540,	/* 28 */ 
-543877451,	/* 29 */ 
-635860261,	/* 30 */ 
-695242569,	/* 31 */ 
-715756300,	/* 32 */ 
-695242569,	/* 33 */ 
-635860261,	/* 34 */ 
-543877451,	/* 35 */ 
-429064540,	/* 36 */ 
-303744193,	/* 37 */ 
-181584409,	/* 38 */ 
-76244791,	/* 39 */ 
-1,	/* 40 */ 
37532584,	/* 41 */ 
30442271,	/* 42 */ 
-22748341,	/* 43 */ 
-118751616,	/* 44 */ 
-249615598,	/* 45 */ 
-403256829,	/* 46 */ 
-564386543,	/* 47 */ 
-715756300,	/* 48 */ 
-839619945,	/* 49 */ 
-919288364,	/* 50 */ 
-940643629,	/* 51 */ 
-893480652,	/* 52 */ 
-772557448,	/* 53 */ 
-578258427,	/* 54 */ 
-316806839,	/* 55 */ 
-1,	/* 56 */ 
355519044,	/* 57 */ 
729400563,	/* 58 */ 
1099049980,	/* 59 */ 
1441296806,	/* 60 */ 
1734136676,	/* 61 */ 
1958405452,	/* 62 */ 
2099249054,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

LDATA rtest[NX] ={
-1, 
-1, 
357878149, 
0, 
357878149, 
0, 
357878149, 
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
-1, 
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
0, 
0, 
0, 
0, 
0, 
0, 
-1, 
-1, 
0, 
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
-1, 
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

LDATA error;

