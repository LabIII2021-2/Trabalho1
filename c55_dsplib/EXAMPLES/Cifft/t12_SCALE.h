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

/* Test for cfft: both */
#define NX 64
#define FNAME "t12"
#define MAXERROR 16
#define SCALING 1

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
362,	362,	/* 0 */ 
353,	353,	/* 1 */ 
330,	330,	/* 2 */ 
292,	292,	/* 3 */ 
243,	243,	/* 4 */ 
185,	185,	/* 5 */ 
122,	122,	/* 6 */ 
59,	59,	/* 7 */ 
0,	0,	/* 8 */ 
-54,	-54,	/* 9 */ 
-98,	-98,	/* 10 */ 
-131,	-131,	/* 11 */ 
-151,	-151,	/* 12 */ 
-159,	-159,	/* 13 */ 
-155,	-155,	/* 14 */ 
-142,	-142,	/* 15 */ 
-121,	-121,	/* 16 */ 
-96,	-96,	/* 17 */ 
-68,	-68,	/* 18 */ 
-43,	-43,	/* 19 */ 
-21,	-21,	/* 20 */ 
-4,	-4,	/* 21 */ 
5,	5,	/* 22 */ 
6,	6,	/* 23 */ 
0,	0,	/* 24 */ 
-13,	-13,	/* 25 */ 
-31,	-31,	/* 26 */ 
-52,	-52,	/* 27 */ 
-73,	-73,	/* 28 */ 
-92,	-92,	/* 29 */ 
-108,	-108,	/* 30 */ 
-118,	-118,	/* 31 */ 
-121,	-121,	/* 32 */ 
-118,	-118,	/* 33 */ 
-108,	-108,	/* 34 */ 
-92,	-92,	/* 35 */ 
-73,	-73,	/* 36 */ 
-52,	-52,	/* 37 */ 
-31,	-31,	/* 38 */ 
-13,	-13,	/* 39 */ 
-1,	-1,	/* 40 */ 
6,	6,	/* 41 */ 
5,	5,	/* 42 */ 
-4,	-4,	/* 43 */ 
-21,	-21,	/* 44 */ 
-43,	-43,	/* 45 */ 
-68,	-68,	/* 46 */ 
-96,	-96,	/* 47 */ 
-121,	-121,	/* 48 */ 
-142,	-142,	/* 49 */ 
-155,	-155,	/* 50 */ 
-159,	-159,	/* 51 */ 
-151,	-151,	/* 52 */ 
-131,	-131,	/* 53 */ 
-98,	-98,	/* 54 */ 
-54,	-54,	/* 55 */ 
-1,	-1,	/* 56 */ 
59,	59,	/* 57 */ 
122,	122,	/* 58 */ 
185,	185,	/* 59 */ 
243,	243,	/* 60 */ 
292,	292,	/* 61 */ 
330,	330,	/* 62 */ 
353,	353,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
-1,	-1,	 /* 0 */ 
60,	60,	 /* 1 */ 
60,	60,	 /* 2 */ 
60,	60,	 /* 3 */ 
0,	0,	 /* 4 */ 
0,	0,	 /* 5 */ 
-1,	0,	 /* 6 */ 
0,	0,	 /* 7 */ 
-1,	-1,	 /* 8 */ 
-1,	0,	 /* 9 */ 
-1,	0,	 /* 10 */ 
0,	0,	 /* 11 */ 
0,	-1,	 /* 12 */ 
-1,	0,	 /* 13 */ 
-1,	0,	 /* 14 */ 
0,	0,	 /* 15 */ 
0,	0,	 /* 16 */ 
0,	0,	 /* 17 */ 
0,	-1,	 /* 18 */ 
-1,	-1,	 /* 19 */ 
-1,	-1,	 /* 20 */ 
-1,	-1,	 /* 21 */ 
0,	0,	 /* 22 */ 
0,	0,	 /* 23 */ 
0,	-1,	 /* 24 */ 
-1,	-1,	 /* 25 */ 
0,	0,	 /* 26 */ 
0,	-1,	 /* 27 */ 
0,	-1,	 /* 28 */ 
-1,	-1,	 /* 29 */ 
-1,	-1,	 /* 30 */ 
0,	-1,	 /* 31 */ 
-1,	-1,	 /* 32 */ 
0,	0,	 /* 33 */ 
0,	-1,	 /* 34 */ 
-1,	-1,	 /* 35 */ 
-1,	0,	 /* 36 */ 
-1,	0,	 /* 37 */ 
0,	0,	 /* 38 */ 
-1,	-1,	 /* 39 */ 
-1,	0,	 /* 40 */ 
0,	0,	 /* 41 */ 
0,	0,	 /* 42 */ 
-1,	-1,	 /* 43 */ 
-1,	-1,	 /* 44 */ 
0,	-1,	 /* 45 */ 
0,	-1,	 /* 46 */ 
0,	0,	 /* 47 */ 
0,	0,	 /* 48 */ 
0,	0,	 /* 49 */ 
0,	0,	 /* 50 */ 
0,	-1,	 /* 51 */ 
-1,	0,	 /* 52 */ 
0,	0,	 /* 53 */ 
0,	-1,	 /* 54 */ 
0,	-1,	 /* 55 */ 
-1,	-1,	 /* 56 */ 
0,	0,	 /* 57 */ 
0,	-1,	 /* 58 */ 
0,	0,	 /* 59 */ 
0,	0,	 /* 60 */ 
60,	60,	 /* 61 */ 
60,	60,	 /* 62 */ 
60,	60,	 /* 63 */ 
};

DATA error;

