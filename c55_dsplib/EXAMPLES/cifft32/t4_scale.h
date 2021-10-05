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

LDATA x[2*NX] ={
218,	153,	/* 0 */ 
139,	175,	/* 1 */ 
-30,	-17,	/* 2 */ 
52,	42,	/* 3 */ 
226,	-292,	/* 4 */ 
-340,	-38,	/* 5 */ 
79,	166,	/* 6 */ 
-347,	302,	/* 7 */ 
-66,	-175,	/* 8 */ 
-151,	-189,	/* 9 */ 
288,	281,	/* 10 */ 
-374,	-207,	/* 11 */ 
206,	234,	/* 12 */ 
362,	314,	/* 13 */ 
377,	-207,	/* 14 */ 
222,	-201,	/* 15 */ 
-48,	-347,	/* 16 */ 
-2,	-325,	/* 17 */ 
-221,	108,	/* 18 */ 
110,	-239,	/* 19 */ 
-139,	264,	/* 20 */ 
354,	-252,	/* 21 */ 
174,	-254,	/* 22 */ 
-68,	380,	/* 23 */ 
188,	-47,	/* 24 */ 
-179,	-124,	/* 25 */ 
-47,	-144,	/* 26 */ 
333,	-104,	/* 27 */ 
141,	-83,	/* 28 */ 
-222,	70,	/* 29 */ 
261,	-293,	/* 30 */ 
99,	-356,	/* 31 */ 
-283,	-32,	/* 32 */ 
-226,	284,	/* 33 */ 
82,	334,	/* 34 */ 
100,	-182,	/* 35 */ 
-100,	-262,	/* 36 */ 
57,	287,	/* 37 */ 
-38,	-202,	/* 38 */ 
-352,	112,	/* 39 */ 
-365,	359,	/* 40 */ 
-145,	127,	/* 41 */ 
-376,	285,	/* 42 */ 
-90,	-378,	/* 43 */ 
141,	-280,	/* 44 */ 
-314,	245,	/* 45 */ 
-359,	-54,	/* 46 */ 
86,	300,	/* 47 */ 
83,	181,	/* 48 */ 
-374,	144,	/* 49 */ 
-373,	-119,	/* 50 */ 
-239,	-258,	/* 51 */ 
66,	-266,	/* 52 */ 
-341,	-239,	/* 53 */ 
-103,	-60,	/* 54 */ 
101,	274,	/* 55 */ 
167,	-8,	/* 56 */ 
148,	243,	/* 57 */ 
-321,	-31,	/* 58 */ 
-36,	-33,	/* 59 */ 
-45,	-38,	/* 60 */ 
-114,	-68,	/* 61 */ 
-267,	309,	/* 62 */ 
135,	-381,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

LDATA rtest[2*NX] ={
-33,	-13,	 /* 0 */ 
23,	64,	 /* 1 */ 
-14,	-14,	 /* 2 */ 
0,	-3,	 /* 3 */ 
22,	-30,	 /* 4 */ 
43,	5,	 /* 5 */ 
-12,	50,	 /* 6 */ 
-19,	18,	 /* 7 */ 
-13,	12,	 /* 8 */ 
93,	-6,	 /* 9 */ 
-28,	10,	 /* 10 */ 
-23,	30,	 /* 11 */ 
-30,	-40,	 /* 12 */ 
5,	-21,	 /* 13 */ 
-26,	14,	 /* 14 */ 
50,	10,	 /* 15 */ 
-5,	-29,	 /* 16 */ 
15,	-17,	 /* 17 */ 
-23,	-50,	 /* 18 */ 
49,	39,	 /* 19 */ 
-30,	-9,	 /* 20 */ 
9,	22,	 /* 21 */ 
-19,	20,	 /* 22 */ 
-57,	-30,	 /* 23 */ 
32,	7,	 /* 24 */ 
-24,	13,	 /* 25 */ 
-41,	38,	 /* 26 */ 
3,	6,	 /* 27 */ 
-28,	14,	 /* 28 */ 
-49,	-26,	 /* 29 */ 
4,	-24,	 /* 30 */ 
26,	-2,	 /* 31 */ 
17,	-5,	 /* 32 */ 
-4,	18,	 /* 33 */ 
-4,	21,	 /* 34 */ 
-12,	53,	 /* 35 */ 
-9,	12,	 /* 36 */ 
17,	-4,	 /* 37 */ 
54,	43,	 /* 38 */ 
4,	-2,	 /* 39 */ 
-47,	-23,	 /* 40 */ 
28,	4,	 /* 41 */ 
2,	-27,	 /* 42 */ 
23,	-2,	 /* 43 */ 
27,	45,	 /* 44 */ 
36,	7,	 /* 45 */ 
-26,	-2,	 /* 46 */ 
-4,	19,	 /* 47 */ 
44,	5,	 /* 48 */ 
23,	-66,	 /* 49 */ 
36,	3,	 /* 50 */ 
-10,	-1,	 /* 51 */ 
42,	-11,	 /* 52 */ 
-3,	17,	 /* 53 */ 
7,	0,	 /* 54 */ 
-19,	0,	 /* 55 */ 
-12,	52,	 /* 56 */ 
48,	-22,	 /* 57 */ 
26,	-47,	 /* 58 */ 
-12,	-15,	 /* 59 */ 
8,	-8,	 /* 60 */ 
-9,	17,	 /* 61 */ 
32,	29,	 /* 62 */ 
-16,	-49,	 /* 63 */ 
};

DATA error;

