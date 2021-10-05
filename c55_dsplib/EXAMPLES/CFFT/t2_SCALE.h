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
#define MAXERROR 16
#define SCALING 1

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
23773,	-2998,	/* 0 */ 
22759,	23573,	/* 1 */ 
-4899,	-1857,	/* 2 */ 
21490,	-4442,	/* 3 */ 
-24136,	18901,	/* 4 */ 
-8033,	1373,	/* 5 */ 
17096,	-16234,	/* 6 */ 
-26758,	9397,	/* 7 */ 
-19714,	18458,	/* 8 */ 
-16227,	-26225,	/* 9 */ 
-16448,	9896,	/* 10 */ 
5666,	-6580,	/* 11 */ 
-12437,	18113,	/* 12 */ 
-16443,	153,	/* 13 */ 
-26463,	11435,	/* 14 */ 
13472,	-3882,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
-4206,	3068,	 /* 0 */ 
6064,	-1581,	 /* 1 */ 
2009,	-3210,	 /* 2 */ 
7369,	-3740,	 /* 3 */ 
161,	5065,	 /* 4 */ 
8019,	953,	 /* 5 */ 
1238,	-5800,	 /* 6 */ 
-53,	-2434,	 /* 7 */ 
-3698,	3896,	 /* 8 */ 
-6844,	-3103,	 /* 9 */ 
4674,	2013,	 /* 10 */ 
-2688,	-6683,	 /* 11 */ 
-387,	1088,	 /* 12 */ 
3828,	1291,	 /* 13 */ 
2235,	1608,	 /* 14 */ 
6045,	4566,	 /* 15 */ 
};

DATA error;

