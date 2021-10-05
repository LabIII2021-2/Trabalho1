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

DATA x[2*NX] ={
-11593,	17492,	/* 0 */ 
-18414,	27105,	/* 1 */ 
-18190,	1340,	/* 2 */ 
10811,	22554,	/* 3 */ 
-11703,	-19404,	/* 4 */ 
2472,	28464,	/* 5 */ 
-20715,	-13561,	/* 6 */ 
11741,	-14695,	/* 7 */ 
-7217,	22293,	/* 8 */ 
21360,	14079,	/* 9 */ 
20982,	-21566,	/* 10 */ 
5551,	-28969,	/* 11 */ 
-205,	23370,	/* 12 */ 
23718,	-17851,	/* 13 */ 
19082,	-11943,	/* 14 */ 
8597,	9578,	/* 15 */ 
18865,	-12792,	/* 16 */ 
9506,	-1826,	/* 17 */ 
-9377,	-25823,	/* 18 */ 
-12476,	28973,	/* 19 */ 
-9423,	4912,	/* 20 */ 
2021,	-4540,	/* 21 */ 
13474,	920,	/* 22 */ 
-11316,	-9852,	/* 23 */ 
20083,	-3981,	/* 24 */ 
4038,	-16260,	/* 25 */ 
-7689,	4735,	/* 26 */ 
12028,	15447,	/* 27 */ 
2763,	1769,	/* 28 */ 
-3271,	8337,	/* 29 */ 
11543,	-17262,	/* 30 */ 
7197,	-7131,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
2633,	122,	 /* 0 */ 
-2831,	2073,	 /* 1 */ 
980,	5079,	 /* 2 */ 
-794,	-446,	 /* 3 */ 
2566,	620,	 /* 4 */ 
1295,	1409,	 /* 5 */ 
30,	1861,	 /* 6 */ 
519,	3656,	 /* 7 */ 
439,	3360,	 /* 8 */ 
3840,	-397,	 /* 9 */ 
-2577,	384,	 /* 10 */ 
-2910,	1665,	 /* 11 */ 
2893,	539,	 /* 12 */ 
219,	4217,	 /* 13 */ 
4235,	-3781,	 /* 14 */ 
-1096,	-4250,	 /* 15 */ 
-1966,	-3217,	 /* 16 */ 
-1546,	1621,	 /* 17 */ 
-3546,	-2042,	 /* 18 */ 
3187,	2674,	 /* 19 */ 
-114,	2505,	 /* 20 */ 
-1856,	4088,	 /* 21 */ 
2622,	357,	 /* 22 */ 
-3046,	-6927,	 /* 23 */ 
-911,	3941,	 /* 24 */ 
-166,	305,	 /* 25 */ 
-512,	-2165,	 /* 26 */ 
-6877,	1000,	 /* 27 */ 
-508,	-2121,	 /* 28 */ 
-5,	1076,	 /* 29 */ 
-2635,	-3101,	 /* 30 */ 
-3170,	3370,	 /* 31 */ 
};

DATA error;

