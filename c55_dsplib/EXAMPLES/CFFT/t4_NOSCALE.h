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
#define MAXERROR 64

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
-442,	222,	/* 0 */ 
-64,	-992,	/* 1 */ 
-892,	-991,	/* 2 */ 
1000,	-635,	/* 3 */ 
169,	177,	/* 4 */ 
-157,	-906,	/* 5 */ 
31,	-272,	/* 6 */ 
-341,	269,	/* 7 */ 
-138,	445,	/* 8 */ 
-562,	394,	/* 9 */ 
163,	-852,	/* 10 */ 
533,	-94,	/* 11 */ 
61,	-120,	/* 12 */ 
287,	-301,	/* 13 */ 
-596,	-710,	/* 14 */ 
-247,	359,	/* 15 */ 
580,	407,	/* 16 */ 
370,	465,	/* 17 */ 
-80,	-45,	/* 18 */ 
138,	112,	/* 19 */ 
602,	-777,	/* 20 */ 
-903,	-101,	/* 21 */ 
210,	442,	/* 22 */ 
-921,	804,	/* 23 */ 
-174,	-465,	/* 24 */ 
-400,	-503,	/* 25 */ 
766,	748,	/* 26 */ 
-994,	-549,	/* 27 */ 
548,	624,	/* 28 */ 
964,	836,	/* 29 */ 
1003,	-550,	/* 30 */ 
591,	-534,	/* 31 */ 
-126,	-923,	/* 32 */ 
-4,	-864,	/* 33 */ 
-586,	288,	/* 34 */ 
293,	-634,	/* 35 */ 
-369,	704,	/* 36 */ 
942,	-668,	/* 37 */ 
464,	-675,	/* 38 */ 
-181,	1012,	/* 39 */ 
500,	-124,	/* 40 */ 
-476,	-328,	/* 41 */ 
-124,	-381,	/* 42 */ 
887,	-277,	/* 43 */ 
375,	-219,	/* 44 */ 
-589,	187,	/* 45 */ 
694,	-779,	/* 46 */ 
263,	-946,	/* 47 */ 
-750,	-85,	/* 48 */ 
-600,	757,	/* 49 */ 
219,	889,	/* 50 */ 
265,	-483,	/* 51 */ 
-266,	-696,	/* 52 */ 
153,	763,	/* 53 */ 
-100,	-537,	/* 54 */ 
-935,	298,	/* 55 */ 
-969,	956,	/* 56 */ 
-384,	337,	/* 57 */ 
-998,	758,	/* 58 */ 
-238,	-1004,	/* 59 */ 
374,	-744,	/* 60 */ 
-834,	652,	/* 61 */ 
-952,	-144,	/* 62 */ 
230,	799,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
-2683,	-5171,	 /* 0 */ 
-6997,	-1164,	 /* 1 */ 
-5694,	-8140,	 /* 2 */ 
-2881,	-3132,	 /* 3 */ 
3343,	-3327,	 /* 4 */ 
144,	-2923,	 /* 5 */ 
-4638,	438,	 /* 6 */ 
-659,	1533,	 /* 7 */ 
-8019,	5880,	 /* 8 */ 
-4733,	2764,	 /* 9 */ 
-4240,	-28,	 /* 10 */ 
-5387,	-834,	 /* 11 */ 
5402,	-2421,	 /* 12 */ 
-1914,	-161,	 /* 13 */ 
-9966,	-3178,	 /* 14 */ 
4800,	3425,	 /* 15 */ 
1984,	4794,	 /* 16 */ 
2447,	6170,	 /* 17 */ 
7205,	2502,	 /* 18 */ 
-51,	4434,	 /* 19 */ 
2490,	6276,	 /* 20 */ 
-2392,	-2695,	 /* 21 */ 
10,	6305,	 /* 22 */ 
586,	4530,	 /* 23 */ 
-7650,	-4955,	 /* 24 */ 
174,	-1783,	 /* 25 */ 
-7934,	-10209,	 /* 26 */ 
-382,	-2796,	 /* 27 */ 
-7568,	-2730,	 /* 28 */ 
1272,	2519,	 /* 29 */ 
-3419,	449,	 /* 30 */ 
-3459,	1367,	 /* 31 */ 
1110,	-1652,	 /* 32 */ 
-5005,	-3789,	 /* 33 */ 
-3904,	8216,	 /* 34 */ 
4868,	-4833,	 /* 35 */ 
-4368,	2567,	 /* 36 */ 
-1948,	-156,	 /* 37 */ 
4205,	-2328,	 /* 38 */ 
-464,	762,	 /* 39 */ 
9267,	1657,	 /* 40 */ 
-5115,	7258,	 /* 41 */ 
57,	-2647,	 /* 42 */ 
-4156,	5771,	 /* 43 */ 
-1363,	371,	 /* 44 */ 
8709,	-11134,	 /* 45 */ 
980,	6264,	 /* 46 */ 
-722,	5012,	 /* 47 */ 
-478,	-409,	 /* 48 */ 
4694,	-6636,	 /* 49 */ 
6026,	-2520,	 /* 50 */ 
4478,	2008,	 /* 51 */ 
-1833,	-5392,	 /* 52 */ 
9518,	1624,	 /* 53 */ 
5686,	-6871,	 /* 54 */ 
-2521,	12730,	 /* 55 */ 
-5654,	3350,	 /* 56 */ 
3021,	6058,	 /* 57 */ 
3949,	-7401,	 /* 58 */ 
326,	7031,	 /* 59 */ 
4223,	-4871,	 /* 60 */ 
946,	1066,	 /* 61 */ 
5312,	2773,	 /* 62 */ 
-7320,	2574,	 /* 63 */ 
};

DATA error;

