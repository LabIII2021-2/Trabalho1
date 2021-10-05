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
#define MAXERROR 34

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
-310,	155,	/* 0 */ 
-45,	-695,	/* 1 */ 
-624,	-694,	/* 2 */ 
700,	-445,	/* 3 */ 
118,	124,	/* 4 */ 
-110,	-635,	/* 5 */ 
22,	-190,	/* 6 */ 
-239,	188,	/* 7 */ 
-97,	312,	/* 8 */ 
-393,	276,	/* 9 */ 
114,	-597,	/* 10 */ 
373,	-66,	/* 11 */ 
42,	-84,	/* 12 */ 
201,	-211,	/* 13 */ 
-418,	-497,	/* 14 */ 
-173,	251,	/* 15 */ 
406,	285,	/* 16 */ 
259,	326,	/* 17 */ 
-56,	-31,	/* 18 */ 
97,	78,	/* 19 */ 
421,	-544,	/* 20 */ 
-632,	-71,	/* 21 */ 
147,	309,	/* 22 */ 
-645,	563,	/* 23 */ 
-122,	-326,	/* 24 */ 
-280,	-352,	/* 25 */ 
536,	524,	/* 26 */ 
-696,	-384,	/* 27 */ 
384,	437,	/* 28 */ 
675,	585,	/* 29 */ 
702,	-385,	/* 30 */ 
414,	-374,	/* 31 */ 
-88,	-646,	/* 32 */ 
-3,	-605,	/* 33 */ 
-411,	201,	/* 34 */ 
205,	-444,	/* 35 */ 
-258,	492,	/* 36 */ 
659,	-468,	/* 37 */ 
324,	-472,	/* 38 */ 
-127,	708,	/* 39 */ 
350,	-87,	/* 40 */ 
-333,	-230,	/* 41 */ 
-87,	-267,	/* 42 */ 
621,	-194,	/* 43 */ 
262,	-154,	/* 44 */ 
-413,	131,	/* 45 */ 
486,	-546,	/* 46 */ 
184,	-663,	/* 47 */ 
-526,	-60,	/* 48 */ 
-420,	530,	/* 49 */ 
153,	622,	/* 50 */ 
186,	-338,	/* 51 */ 
-186,	-487,	/* 52 */ 
107,	534,	/* 53 */ 
-70,	-376,	/* 54 */ 
-654,	209,	/* 55 */ 
-678,	669,	/* 56 */ 
-269,	236,	/* 57 */ 
-699,	530,	/* 58 */ 
-167,	-703,	/* 59 */ 
262,	-521,	/* 60 */ 
-584,	456,	/* 61 */ 
-667,	-101,	/* 62 */ 
161,	559,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
-1878,	-3620,	 /* 0 */ 
-5125,	1802,	 /* 1 */ 
3719,	1941,	 /* 2 */ 
662,	746,	 /* 3 */ 
2956,	-3411,	 /* 4 */ 
228,	4922,	 /* 5 */ 
2764,	-5182,	 /* 6 */ 
2115,	4241,	 /* 7 */ 
-3958,	2345,	 /* 8 */ 
-1765,	8912,	 /* 9 */ 
3981,	-4810,	 /* 10 */ 
6663,	1137,	 /* 11 */ 
-1284,	-3775,	 /* 12 */ 
3135,	1406,	 /* 13 */ 
4218,	-1764,	 /* 14 */ 
3286,	-4646,	 /* 15 */ 
-335,	-286,	 /* 16 */ 
-506,	3509,	 /* 17 */ 
686,	4385,	 /* 18 */ 
6097,	-7795,	 /* 19 */ 
-955,	259,	 /* 20 */ 
-2909,	4040,	 /* 21 */ 
40,	-1853,	 /* 22 */ 
-3581,	5081,	 /* 23 */ 
6487,	1160,	 /* 24 */ 
-325,	534,	 /* 25 */ 
2944,	-1630,	 /* 26 */ 
-1364,	-109,	 /* 27 */ 
-3058,	1797,	 /* 28 */ 
3408,	-3384,	 /* 29 */ 
-2733,	5751,	 /* 30 */ 
-3504,	-2653,	 /* 31 */ 
777,	-1157,	 /* 32 */ 
-2422,	957,	 /* 33 */ 
-2394,	314,	 /* 34 */ 
890,	1763,	 /* 35 */ 
-5298,	-1911,	 /* 36 */ 
-268,	-1958,	 /* 37 */ 
-5554,	-7147,	 /* 38 */ 
122,	-1248,	 /* 39 */ 
-5355,	-3469,	 /* 40 */ 
410,	3171,	 /* 41 */ 
7,	4413,	 /* 42 */ 
-1675,	-1887,	 /* 43 */ 
1743,	4394,	 /* 44 */ 
-36,	3104,	 /* 45 */ 
5044,	1751,	 /* 46 */ 
1713,	4319,	 /* 47 */ 
1389,	3356,	 /* 48 */ 
3360,	2397,	 /* 49 */ 
-6977,	-2225,	 /* 50 */ 
-1340,	-113,	 /* 51 */ 
3782,	-1695,	 /* 52 */ 
-3771,	-584,	 /* 53 */ 
-2968,	-20,	 /* 54 */ 
-3313,	1935,	 /* 55 */ 
-5614,	4116,	 /* 56 */ 
-462,	1073,	 /* 57 */ 
-3247,	307,	 /* 58 */ 
101,	-2046,	 /* 59 */ 
2340,	-2330,	 /* 60 */ 
-2017,	-2192,	 /* 61 */ 
-3986,	-5698,	 /* 62 */ 
-4899,	-815,	 /* 63 */ 
};

DATA error;

