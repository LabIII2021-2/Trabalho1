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
#define NX 64
#define FNAME "t4"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
-7971,	/* 0 */ 
23591,	/* 1 */ 
23174,	/* 2 */ 
6131,	/* 3 */ 
-226,	/* 4 */ 
26196,	/* 5 */ 
21076,	/* 6 */ 
9495,	/* 7 */ 
20836,	/* 8 */ 
10499,	/* 9 */ 
-10356,	/* 10 */ 
-13780,	/* 11 */ 
-10407,	/* 12 */ 
2233,	/* 13 */ 
14882,	/* 14 */ 
-12498,	/* 15 */ 
22181,	/* 16 */ 
4460,	/* 17 */ 
-8492,	/* 18 */ 
13285,	/* 19 */ 
3051,	/* 20 */ 
-3612,	/* 21 */ 
12749,	/* 22 */ 
7949,	/* 23 */ 
19319,	/* 24 */ 
29936,	/* 25 */ 
1480,	/* 26 */ 
24910,	/* 27 */ 
-21432,	/* 28 */ 
31437,	/* 29 */ 
-14977,	/* 30 */ 
-16230,	/* 31 */ 
24622,	/* 32 */ 
15550,	/* 33 */ 
-23819,	/* 34 */ 
-31995,	/* 35 */ 
25811,	/* 36 */ 
-19716,	/* 37 */ 
-13190,	/* 38 */ 
10579,	/* 39 */ 
-14128,	/* 40 */ 
-2017,	/* 41 */ 
-28520,	/* 42 */ 
32000,	/* 43 */ 
5425,	/* 44 */ 
-5014,	/* 45 */ 
1016,	/* 46 */ 
-10882,	/* 47 */ 
-4397,	/* 48 */ 
-17959,	/* 49 */ 
5229,	/* 50 */ 
17061,	/* 51 */ 
1954,	/* 52 */ 
9208,	/* 53 */ 
-19065,	/* 54 */ 
-7876,	/* 55 */ 
18566,	/* 56 */ 
11850,	/* 57 */ 
-2550,	/* 58 */ 
4444,	/* 59 */ 
19279,	/* 60 */ 
-28887,	/* 61 */ 
6740,	/* 62 */ 
-29471,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
2480, 
-360, 
834, 
-2306, 
311, 
1114, 
631, 
-2566, 
-1669, 
-863, 
-1214, 
-1671, 
-1254, 
-1060, 
-1319, 
1241, 
460, 
-995, 
540, 
-2574, 
2375, 
-672, 
-1198, 
-484, 
-506, 
-859, 
-965, 
-173, 
113, 
-2011, 
-10, 
-1128, 
2142, 
-1323, 
-2856, 
598, 
367, 
-1790, 
-1687, 
3532, 
-744, 
-1376, 
-2141, 
587, 
-1169, 
-984, 
281, 
916, 
1276, 
-2654, 
-472, 
-956, 
-1058, 
1361, 
-326, 
-4019, 
2281, 
978, 
-202, 
-2445, 
170, 
170, 
1946, 
212, 
};

DATA error;

