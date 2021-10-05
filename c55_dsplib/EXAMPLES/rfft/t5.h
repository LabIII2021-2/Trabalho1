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

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
-1985, 
393, 
1724, 
1175, 
1477, 
-951, 
-1397, 
-2818, 
321, 
507, 
-25, 
413, 
-46, 
-376, 
-517, 
-1064, 
689, 
-481, 
-814, 
114, 
493, 
-276, 
-273, 
1256, 
-2929, 
345, 
-1082, 
2076, 
-1686, 
-1423, 
-1684, 
-850, 
155, 
1045, 
-128, 
2236, 
-1402, 
2579, 
-138, 
-2918, 
582, 
-780, 
481, 
-1256, 
154, 
215, 
943, 
-3132, 
1127, 
494, 
-414, 
-619, 
1380, 
-241, 
675, 
170, 
-1222, 
-417, 
2593, 
-588, 
-382, 
-708, 
-2722, 
247, 
180, 
-147, 
655, 
-1163, 
-844, 
967, 
507, 
-728, 
-1218, 
-2421, 
37, 
621, 
-1555, 
1900, 
2574, 
515, 
-301, 
-200, 
-938, 
-640, 
-809, 
-231, 
-286, 
133, 
-879, 
820, 
-550, 
1547, 
-1225, 
635, 
2596, 
-1045, 
-573, 
1719, 
-1049, 
-962, 
338, 
-209, 
37, 
-1095, 
1550, 
2455, 
-1454, 
1158, 
-403, 
918, 
41, 
1307, 
-178, 
505, 
288, 
610, 
836, 
-146, 
469, 
-2313, 
883, 
8, 
1115, 
-1506, 
1162, 
138, 
1050, 
160, 
};

DATA error;

