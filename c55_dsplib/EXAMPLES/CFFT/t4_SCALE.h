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
#define NX 64
#define FNAME "t4"
#define MAXERROR 16
#define SCALING 1

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
13971,	9823,	/* 0 */ 
8918,	11219,	/* 1 */ 
-1919,	-1066,	/* 2 */ 
3344,	2704,	/* 3 */ 
14508,	-18688,	/* 4 */ 
-21739,	-2429,	/* 5 */ 
5072,	10645,	/* 6 */ 
-22178,	19372,	/* 7 */ 
-4174,	-11190,	/* 8 */ 
-9617,	-12094,	/* 9 */ 
18461,	18029,	/* 10 */ 
-23917,	-13199,	/* 11 */ 
13213,	15034,	/* 12 */ 
23219,	20139,	/* 13 */ 
24167,	-13222,	/* 14 */ 
14244,	-12856,	/* 15 */ 
-3025,	-22204,	/* 16 */ 
-84,	-20792,	/* 17 */ 
-14106,	6944,	/* 18 */ 
7076,	-15244,	/* 19 */ 
-8875,	16957,	/* 20 */ 
22689,	-16082,	/* 21 */ 
11176,	-16235,	/* 22 */ 
-4342,	24375,	/* 23 */ 
12060,	-2970,	/* 24 */ 
-11444,	-7888,	/* 25 */ 
-2963,	-9162,	/* 26 */ 
21371,	-6654,	/* 27 */ 
9040,	-5265,	/* 28 */ 
-14175,	4513,	/* 29 */ 
16729,	-18752,	/* 30 */ 
6350,	-22777,	/* 31 */ 
-18060,	-2042,	/* 32 */ 
-14443,	18239,	/* 33 */ 
5286,	21413,	/* 34 */ 
6405,	-11616,	/* 35 */ 
-6388,	-16752,	/* 36 */ 
3705,	18386,	/* 37 */ 
-2396,	-12927,	/* 38 */ 
-22493,	7191,	/* 39 */ 
-23317,	23023,	/* 40 */ 
-9238,	8133,	/* 41 */ 
-24023,	18264,	/* 42 */ 
-5722,	-24168,	/* 43 */ 
9030,	-17901,	/* 44 */ 
-20079,	15718,	/* 45 */ 
-22915,	-3444,	/* 46 */ 
5542,	19248,	/* 47 */ 
5352,	11584,	/* 48 */ 
-23880,	9237,	/* 49 */ 
-23851,	-7589,	/* 50 */ 
-15284,	-16470,	/* 51 */ 
4286,	-16983,	/* 52 */ 
-21818,	-15233,	/* 53 */ 
-6531,	-3825,	/* 54 */ 
6482,	17554,	/* 55 */ 
10732,	-481,	/* 56 */ 
9501,	15579,	/* 57 */ 
-20511,	-1935,	/* 58 */ 
-2251,	-2104,	/* 59 */ 
-2869,	-2432,	/* 60 */ 
-7237,	-4329,	/* 61 */ 
-17082,	19804,	/* 62 */ 
8661,	-24382,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
-2068,	-785,	 /* 0 */ 
-987,	-3092,	 /* 1 */ 
2094,	1909,	 /* 2 */ 
-524,	1146,	 /* 3 */ 
521,	-491,	 /* 4 */ 
-710,	-905,	 /* 5 */ 
1666,	-2966,	 /* 6 */ 
3081,	-1402,	 /* 7 */ 
-711,	3381,	 /* 8 */ 
-1190,	21,	 /* 9 */ 
455,	9,	 /* 10 */ 
-177,	1146,	 /* 11 */ 
2740,	-657,	 /* 12 */ 
-600,	-30,	 /* 13 */ 
2346,	212,	 /* 14 */ 
1479,	-4191,	 /* 15 */ 
2847,	337,	 /* 16 */ 
-218,	1229,	 /* 17 */ 
-1663,	-111,	 /* 18 */ 
2344,	507,	 /* 19 */ 
1728,	2919,	 /* 20 */ 
1526,	-74,	 /* 21 */ 
142,	-1693,	 /* 22 */ 
1800,	282,	 /* 23 */ 
-2999,	-1415,	 /* 24 */ 
310,	-121,	 /* 25 */ 
3505,	2798,	 /* 26 */ 
1129,	-233,	 /* 27 */ 
-544,	815,	 /* 28 */ 
-747,	3438,	 /* 29 */ 
-212,	1371,	 /* 30 */ 
-226,	1165,	 /* 31 */ 
1132,	-264,	 /* 32 */ 
1722,	-95,	 /* 33 */ 
262,	-1499,	 /* 34 */ 
-3127,	-1644,	 /* 35 */ 
-1743,	925,	 /* 36 */ 
229,	387,	 /* 37 */ 
-2583,	2491,	 /* 38 */ 
-1533,	875,	 /* 39 */ 
2099,	475,	 /* 40 */ 
-3592,	-1913,	 /* 41 */ 
-1162,	1295,	 /* 42 */ 
625,	1462,	 /* 43 */ 
-1877,	-518,	 /* 44 */ 
3158,	2511,	 /* 45 */ 
-1412,	-3200,	 /* 46 */ 
965,	-1061,	 /* 47 */ 
-320,	-1820,	 /* 48 */ 
3218,	676,	 /* 49 */ 
-1641,	942,	 /* 50 */ 
348,	-1325,	 /* 51 */ 
-1880,	-2501,	 /* 52 */ 
-1410,	1972,	 /* 53 */ 
-1786,	680,	 /* 54 */ 
5987,	-331,	 /* 55 */ 
-791,	780,	 /* 56 */ 
-1156,	1208,	 /* 57 */ 
-745,	3239,	 /* 58 */ 
2787,	368,	 /* 59 */ 
1418,	-1898,	 /* 60 */ 
0,	-161,	 /* 61 */ 
-877,	-884,	 /* 62 */ 
1489,	4100,	 /* 63 */ 
};

DATA error;

