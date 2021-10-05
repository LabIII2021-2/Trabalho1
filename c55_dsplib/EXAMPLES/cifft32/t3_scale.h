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
#define NX 32
#define FNAME "t3"
#define MAXERROR 16
#define SCALING 1

#pragma DATA_SECTION (x,".input")

LDATA x[2*NX] ={
-363,	546,	/* 0 */ 
-576,	847,	/* 1 */ 
-569,	41,	/* 2 */ 
337,	704,	/* 3 */ 
-366,	-607,	/* 4 */ 
77,	889,	/* 5 */ 
-648,	-424,	/* 6 */ 
366,	-460,	/* 7 */ 
-226,	696,	/* 8 */ 
667,	439,	/* 9 */ 
655,	-674,	/* 10 */ 
173,	-906,	/* 11 */ 
-7,	730,	/* 12 */ 
741,	-558,	/* 13 */ 
596,	-374,	/* 14 */ 
268,	299,	/* 15 */ 
589,	-400,	/* 16 */ 
297,	-58,	/* 17 */ 
-294,	-807,	/* 18 */ 
-390,	905,	/* 19 */ 
-295,	153,	/* 20 */ 
63,	-142,	/* 21 */ 
421,	28,	/* 22 */ 
-354,	-308,	/* 23 */ 
627,	-125,	/* 24 */ 
126,	-509,	/* 25 */ 
-241,	147,	/* 26 */ 
375,	482,	/* 27 */ 
86,	55,	/* 28 */ 
-103,	260,	/* 29 */ 
360,	-540,	/* 30 */ 
224,	-223,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

LDATA rtest[2*NX] ={
82,	3,	 /* 0 */ 
-100,	105,	 /* 1 */ 
-83,	-97,	 /* 2 */ 
-1,	33,	 /* 3 */ 
-16,	-67,	 /* 4 */ 
-215,	31,	 /* 5 */ 
-16,	-68,	 /* 6 */ 
-6,	9,	 /* 7 */ 
-29,	123,	 /* 8 */ 
-96,	-217,	 /* 9 */ 
81,	11,	 /* 10 */ 
-58,	127,	 /* 11 */ 
-4,	78,	 /* 12 */ 
99,	83,	 /* 13 */ 
-111,	-64,	 /* 14 */ 
-49,	50,	 /* 15 */ 
-62,	-101,	 /* 16 */ 
-35,	-133,	 /* 17 */ 
132,	-119,	 /* 18 */ 
6,	131,	 /* 19 */ 
90,	16,	 /* 20 */ 
-91,	52,	 /* 21 */ 
-81,	12,	 /* 22 */ 
120,	-13,	 /* 23 */ 
13,	105,	 /* 24 */ 
16,	114,	 /* 25 */ 
0,	58,	 /* 26 */ 
40,	44,	 /* 27 */ 
80,	19,	 /* 28 */ 
-25,	-14,	 /* 29 */ 
30,	158,	 /* 30 */ 
-89,	64,	 /* 31 */ 
};

DATA error;

