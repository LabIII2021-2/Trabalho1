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
#define NX 32
#define FNAME "t11"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

LDATA x[NX] ={
2147268899,	/* 0 */ 
1958405452,	/* 1 */ 
1441296806,	/* 2 */ 
729400563,	/* 3 */ 
0,	/* 4 */ 
-578258427,	/* 5 */ 
-893480652,	/* 6 */ 
-919288364,	/* 7 */ 
-715756300,	/* 8 */ 
-403256829,	/* 9 */ 
-118751616,	/* 10 */ 
30442271,	/* 11 */ 
0,	/* 12 */ 
-181584409,	/* 13 */ 
-429064540,	/* 14 */ 
-635860261,	/* 15 */ 
-715756300,	/* 16 */ 
-635860261,	/* 17 */ 
-429064540,	/* 18 */ 
-181584409,	/* 19 */ 
-1,	/* 20 */ 
30442271,	/* 21 */ 
-118751616,	/* 22 */ 
-403256829,	/* 23 */ 
-715756300,	/* 24 */ 
-919288364,	/* 25 */ 
-893480652,	/* 26 */ 
-578258427,	/* 27 */ 
-1,	/* 28 */ 
729400563,	/* 29 */ 
1441296806,	/* 30 */ 
1958405452,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

LDATA rtest[NX] ={
-1, 
0, 
357878149, 
0, 
357878149, 
0, 
357878149, 
0, 
0, 
-1, 
0, 
-1, 
0, 
-1, 
-1, 
0, 
0, 
-1, 
0, 
-1, 
0, 
0, 
-1, 
0, 
0, 
0, 
-1, 
0, 
0, 
0, 
0, 
0, 
};

LDATA error;

