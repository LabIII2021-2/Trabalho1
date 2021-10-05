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
#define MAXERROR 64

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
-113,	651,	/* 0 */ 
884,	328,	/* 1 */ 
-70,	-324,	/* 2 */ 
-167,	-431,	/* 3 */ 
708,	-326,	/* 4 */ 
51,	69,	/* 5 */ 
-609,	465,	/* 6 */ 
352,	-391,	/* 7 */ 
692,	693,	/* 8 */ 
-984,	139,	/* 9 */ 
371,	-266,	/* 10 */ 
-247,	415,	/* 11 */ 
679,	95,	/* 12 */ 
5,	-113,	/* 13 */ 
428,	398,	/* 14 */ 
-146,	248,	/* 15 */ 
-401,	603,	/* 16 */ 
-636,	935,	/* 17 */ 
-628,	46,	/* 18 */ 
373,	778,	/* 19 */ 
-404,	-670,	/* 20 */ 
85,	982,	/* 21 */ 
-715,	-469,	/* 22 */ 
405,	-508,	/* 23 */ 
-250,	769,	/* 24 */ 
737,	485,	/* 25 */ 
724,	-745,	/* 26 */ 
191,	-1000,	/* 27 */ 
-8,	806,	/* 28 */ 
818,	-617,	/* 29 */ 
658,	-413,	/* 30 */ 
296,	330,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
3093,	2977,	 /* 0 */ 
4997,	-2703,	 /* 1 */ 
556,	5243,	 /* 2 */ 
-985,	-1032,	 /* 3 */ 
-1295,	4439,	 /* 4 */ 
1115,	1314,	 /* 5 */ 
-1704,	2300,	 /* 6 */ 
660,	221,	 /* 7 */ 
3514,	4025,	 /* 8 */ 
-821,	-1330,	 /* 9 */ 
-4710,	-6098,	 /* 10 */ 
-3561,	-1190,	 /* 11 */ 
1531,	3609,	 /* 12 */ 
-861,	-3420,	 /* 13 */ 
2778,	-4696,	 /* 14 */ 
-2682,	7803,	 /* 15 */ 
-954,	-336,	 /* 16 */ 
263,	-1767,	 /* 17 */ 
-4337,	2041,	 /* 18 */ 
78,	-3568,	 /* 19 */ 
-3340,	-87,	 /* 20 */ 
-799,	-1104,	 /* 21 */ 
3761,	1475,	 /* 22 */ 
2328,	7832,	 /* 23 */ 
-2022,	3831,	 /* 24 */ 
-3427,	118,	 /* 25 */ 
-2923,	-550,	 /* 26 */ 
3678,	1667,	 /* 27 */ 
-1084,	3280,	 /* 28 */ 
1220,	1735,	 /* 29 */ 
-1073,	-1381,	 /* 30 */ 
3391,	-3827,	 /* 31 */ 
};

DATA error;

