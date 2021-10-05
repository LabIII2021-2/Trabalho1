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

/* Test for rfft: rand */
#define NX 128
#define FNAME "t5"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
-5546,	/* 0 */ 
-12779,	/* 1 */ 
24532,	/* 2 */ 
-31782,	/* 3 */ 
17558,	/* 4 */ 
30854,	/* 5 */ 
32114,	/* 6 */ 
18928,	/* 7 */ 
-4020,	/* 8 */ 
-111,	/* 9 */ 
-18744,	/* 10 */ 
9402,	/* 11 */ 
-11793,	/* 12 */ 
30150,	/* 13 */ 
14851,	/* 14 */ 
-5770,	/* 15 */ 
16026,	/* 16 */ 
-15207,	/* 17 */ 
-3937,	/* 18 */ 
28399,	/* 19 */ 
12013,	/* 20 */ 
-18836,	/* 21 */ 
22230,	/* 22 */ 
8439,	/* 23 */ 
-23999,	/* 24 */ 
-19192,	/* 25 */ 
7024,	/* 26 */ 
8511,	/* 27 */ 
-8488,	/* 28 */ 
4924,	/* 29 */ 
-3184,	/* 30 */ 
-29889,	/* 31 */ 
-30984,	/* 32 */ 
-12275,	/* 33 */ 
-31922,	/* 34 */ 
-7604,	/* 35 */ 
11999,	/* 36 */ 
-26681,	/* 37 */ 
-30450,	/* 38 */ 
7365,	/* 39 */ 
7112,	/* 40 */ 
-31732,	/* 41 */ 
-31693,	/* 42 */ 
-20310,	/* 43 */ 
5695,	/* 44 */ 
-28992,	/* 45 */ 
-8679,	/* 46 */ 
8613,	/* 47 */ 
14261,	/* 48 */ 
12625,	/* 49 */ 
-27256,	/* 50 */ 
-2992,	/* 51 */ 
-3812,	/* 52 */ 
-9617,	/* 53 */ 
-22699,	/* 54 */ 
11509,	/* 55 */ 
13054,	/* 56 */ 
14908,	/* 57 */ 
-1417,	/* 58 */ 
3593,	/* 59 */ 
-24833,	/* 60 */ 
-3228,	/* 61 */ 
14146,	/* 62 */ 
25742,	/* 63 */ 
-14869,	/* 64 */ 
-16070,	/* 65 */ 
23957,	/* 66 */ 
-17539,	/* 67 */ 
19978,	/* 68 */ 
26762,	/* 69 */ 
-17569,	/* 70 */ 
-17083,	/* 71 */ 
-29505,	/* 72 */ 
-27629,	/* 73 */ 
9227,	/* 74 */ 
-20257,	/* 75 */ 
22533,	/* 76 */ 
-21370,	/* 77 */ 
-21573,	/* 78 */ 
32390,	/* 79 */ 
-3946,	/* 80 */ 
-10482,	/* 81 */ 
-12175,	/* 82 */ 
-8842,	/* 83 */ 
-6996,	/* 84 */ 
5997,	/* 85 */ 
-24918,	/* 86 */ 
-30267,	/* 87 */ 
-2714,	/* 88 */ 
24237,	/* 89 */ 
28455,	/* 90 */ 
-15436,	/* 91 */ 
-22261,	/* 92 */ 
24432,	/* 93 */ 
-17177,	/* 94 */ 
9556,	/* 95 */ 
30594,	/* 96 */ 
10807,	/* 97 */ 
24270,	/* 98 */ 
-32115,	/* 99 */ 
-23787,	/* 100 */ 
20887,	/* 101 */ 
-4577,	/* 102 */ 
25577,	/* 103 */ 
15393,	/* 104 */ 
12275,	/* 105 */ 
-10085,	/* 106 */ 
-21885,	/* 107 */ 
-22568,	/* 108 */ 
-20241,	/* 109 */ 
-5082,	/* 110 */ 
23326,	/* 111 */ 
-639,	/* 112 */ 
20703,	/* 113 */ 
-2571,	/* 114 */ 
-2795,	/* 115 */ 
-3232,	/* 116 */ 
-5753,	/* 117 */ 
26317,	/* 118 */ 
-32399,	/* 119 */ 
-13276,	/* 120 */ 
-29544,	/* 121 */ 
12659,	/* 122 */ 
9836,	/* 123 */ 
31649,	/* 124 */ 
3451,	/* 125 */ 
-6549,	/* 126 */ 
-19739,	/* 127 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

DATA rtest[NX] ={
-824,	804,	 /* 0 */ 
2042,	816,	 /* 1 */ 
903,	-532,	 /* 2 */ 
-2492,	-302,	 /* 3 */ 
773,	-238,	 /* 4 */ 
-787,	1206,	 /* 5 */ 
-10,	1138,	 /* 6 */ 
-492,	566,	 /* 7 */ 
405,	-466,	 /* 8 */ 
45,	263,	 /* 9 */ 
512,	-1074,	 /* 10 */ 
447,	-1367,	 /* 11 */ 
-797,	-320,	 /* 12 */ 
-489,	2106,	 /* 13 */ 
-1974,	575,	 /* 14 */ 
-2279,	-330,	 /* 15 */ 
998,	-1086,	 /* 16 */ 
597,	1926,	 /* 17 */ 
-390,	4918,	 /* 18 */ 
-615,	662,	 /* 19 */ 
442,	767,	 /* 20 */ 
109,	-92,	 /* 21 */ 
65,	2016,	 /* 22 */ 
18,	-2139,	 /* 23 */ 
1101,	-260,	 /* 24 */ 
-372,	151,	 /* 25 */ 
1529,	-535,	 /* 26 */ 
733,	200,	 /* 27 */ 
-1527,	151,	 /* 28 */ 
2457,	-263,	 /* 29 */ 
-398,	-909,	 /* 30 */ 
-2770,	67,	 /* 31 */ 
151,	281,	 /* 32 */ 
647,	-1279,	 /* 33 */ 
-884,	930,	 /* 34 */ 
587,	431,	 /* 35 */ 
-969,	-2646,	 /* 36 */ 
-78,	-1557,	 /* 37 */ 
-1761,	-90,	 /* 38 */ 
2476,	926,	 /* 39 */ 
-332,	155,	 /* 40 */ 
-70,	-718,	 /* 41 */ 
-777,	-1063,	 /* 42 */ 
28,	-1125,	 /* 43 */ 
-795,	-1265,	 /* 44 */ 
-130,	397,	 /* 45 */ 
-2293,	130,	 /* 46 */ 
1815,	-995,	 /* 47 */ 
-1473,	433,	 /* 48 */ 
-510,	-1038,	 /* 49 */ 
570,	157,	 /* 50 */ 
-612,	-2928,	 /* 51 */ 
-638,	1922,	 /* 52 */ 
-2231,	175,	 /* 53 */ 
-478,	-315,	 /* 54 */ 
-875,	885,	 /* 55 */ 
50,	-149,	 /* 56 */ 
206,	964,	 /* 57 */ 
744,	1469,	 /* 58 */ 
1175,	-792,	 /* 59 */ 
376,	-944,	 /* 60 */ 
2154,	951,	 /* 61 */ 
1680,	951,	 /* 62 */ 
675,	-894,	 /* 63 */ 
};

DATA error;

