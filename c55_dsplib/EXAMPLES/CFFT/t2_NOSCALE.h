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

/* Test for cfft: rand */
#define NX 16
#define FNAME "t2"
#define MAXERROR 64

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
921,	891,	/* 0 */ 
-551,	853,	/* 1 */ 
218,	-184,	/* 2 */ 
-29,	806,	/* 3 */ 
801,	-906,	/* 4 */ 
536,	-302,	/* 5 */ 
-90,	641,	/* 6 */ 
-987,	-1004,	/* 7 */ 
658,	-740,	/* 8 */ 
-114,	-609,	/* 9 */ 
236,	-617,	/* 10 */ 
597,	212,	/* 11 */ 
863,	-467,	/* 12 */ 
487,	-617,	/* 13 */ 
-663,	-993,	/* 14 */ 
-194,	505,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
2698,	-2525,	 /* 0 */ 
1760,	4307,	 /* 1 */ 
-1070,	24,	 /* 2 */ 
2951,	3820,	 /* 3 */ 
2348,	-1039,	 /* 4 */ 
-2370,	2971,	 /* 5 */ 
4689,	2939,	 /* 6 */ 
-426,	-735,	 /* 7 */ 
3197,	-2219,	 /* 8 */ 
-24,	-3405,	 /* 9 */ 
0,	609,	 /* 10 */ 
2213,	228,	 /* 11 */ 
4735,	903,	 /* 12 */ 
-68,	2900,	 /* 13 */ 
-3961,	2523,	 /* 14 */ 
-1930,	2960,	 /* 15 */ 
};

DATA error;

