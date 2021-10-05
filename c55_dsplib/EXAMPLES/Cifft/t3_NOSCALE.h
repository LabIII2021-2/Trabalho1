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
#define MAXERROR 20

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
-79,	455,	/* 0 */ 
619,	229,	/* 1 */ 
-49,	-227,	/* 2 */ 
-117,	-302,	/* 3 */ 
496,	-228,	/* 4 */ 
36,	48,	/* 5 */ 
-427,	325,	/* 6 */ 
246,	-274,	/* 7 */ 
484,	485,	/* 8 */ 
-689,	97,	/* 9 */ 
259,	-186,	/* 10 */ 
-173,	290,	/* 11 */ 
475,	66,	/* 12 */ 
4,	-80,	/* 13 */ 
300,	278,	/* 14 */ 
-102,	173,	/* 15 */ 
-281,	422,	/* 16 */ 
-445,	654,	/* 17 */ 
-440,	32,	/* 18 */ 
261,	544,	/* 19 */ 
-283,	-469,	/* 20 */ 
59,	687,	/* 21 */ 
-501,	-328,	/* 22 */ 
283,	-356,	/* 23 */ 
-175,	538,	/* 24 */ 
516,	340,	/* 25 */ 
506,	-522,	/* 26 */ 
134,	-700,	/* 27 */ 
-5,	564,	/* 28 */ 
573,	-432,	/* 29 */ 
461,	-289,	/* 30 */ 
207,	231,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
2165,	2084,	 /* 0 */ 
2374,	-2679,	 /* 1 */ 
-752,	-967,	 /* 2 */ 
854,	1215,	 /* 3 */ 
-759,	2296,	 /* 4 */ 
2575,	1167,	 /* 5 */ 
-2046,	-385,	 /* 6 */ 
-2399,	83,	 /* 7 */ 
-1415,	2682,	 /* 8 */ 
1630,	5483,	 /* 9 */ 
2633,	1032,	 /* 10 */ 
-559,	-773,	 /* 11 */ 
-2339,	-61,	 /* 12 */ 
55,	-2498,	 /* 13 */ 
-3036,	1429,	 /* 14 */ 
184,	-1237,	 /* 15 */ 
-668,	-236,	 /* 16 */ 
-1878,	5463,	 /* 17 */ 
1945,	-3287,	 /* 18 */ 
-603,	-2394,	 /* 19 */ 
1071,	2526,	 /* 20 */ 
-2493,	-833,	 /* 21 */ 
-3297,	-4269,	 /* 22 */ 
-575,	-931,	 /* 23 */ 
2460,	2817,	 /* 24 */ 
462,	154,	 /* 25 */ 
-1193,	1610,	 /* 26 */ 
780,	919,	 /* 27 */ 
-907,	3107,	 /* 28 */ 
-690,	-722,	 /* 29 */ 
389,	3670,	 /* 30 */ 
3498,	-1892,	 /* 31 */ 
};

DATA error;

