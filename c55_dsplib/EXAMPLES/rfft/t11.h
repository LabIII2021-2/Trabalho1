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
#define NX 32
#define FNAME "t11"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
32764,	/* 0 */ 
29882,	/* 1 */ 
21992,	/* 2 */ 
11129,	/* 3 */ 
0,	/* 4 */ 
-8824,	/* 5 */ 
-13634,	/* 6 */ 
-14028,	/* 7 */ 
-10922,	/* 8 */ 
-6154,	/* 9 */ 
-1813,	/* 10 */ 
464,	/* 11 */ 
0,	/* 12 */ 
-2771,	/* 13 */ 
-6548,	/* 14 */ 
-9703,	/* 15 */ 
-10922,	/* 16 */ 
-9703,	/* 17 */ 
-6548,	/* 18 */ 
-2771,	/* 19 */ 
-1,	/* 20 */ 
464,	/* 21 */ 
-1813,	/* 22 */ 
-6154,	/* 23 */ 
-10922,	/* 24 */ 
-14028,	/* 25 */ 
-13634,	/* 26 */ 
-8824,	/* 27 */ 
-1,	/* 28 */ 
11129,	/* 29 */ 
21992,	/* 30 */ 
29882,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
-1, 
0, 
5460, 
0, 
5460, 
0, 
5460, 
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
-1, 
0, 
-1, 
0, 
0, 
-1, 
0, 
0, 
0, 
0, 
0, 
};

DATA error;

