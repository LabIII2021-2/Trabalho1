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

#define NX 128
#define NLAGS 128 // max NLAGS = N 
#define FNAME "t3"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
1960,
394,
-751,
1174,
269,
-320,
1127,
702,
1707,
2646,
130,
2202,
-1895,
2778,
-1324,
-1435,
2176,
1374,
-2106,
-2829,
2281,
-1743,
-1166,
935,
-1249,
-179,
-2522,
2828,
479,
-444,
89,
-962,
-389,
-1588,
462,
1508,
172,
814,
-1686,
-697,
1641,
1047,
-226,
392,
1704,
-2554,
595,
-2606,
-491,
-1130,
2168,
-2810,
1552,
2727,
2838,
1673,
-356,
-10,
-1657,
831,
-1043,
2665,
1312,
-511,
1416,
-1345,
-348,
2510,
1061,
-1666,
1965,
745,
-2122,
-1697,
620,
752,
-751,
435,
-282,
-2643,
-2739,
-1086,
-2822,
-673,
1060,
-2359,
-2692,
651,
628,
-2806,
-2802,
-1796,
503,
-2563,
-768,
761,
1260,
1116,
-2410,
-265,
-337,
-851,
-2007,
1017,
1153,
1317,
-126,
317,
-2196,
-286,
1250,
2275,
-1315,
-1421,
2117,
-1551,
1766,
2365,
-1554,
-1511,
-2609,
-2443,
815,
-1791,
1991,
-1889,
-1907,
2863,
};

DATA rtest[NLAGS] ={ // lag0, lag1,... 
82,
0,
-2,
9,
5,
-2,
-1,
18,
2,
2,
4,
3,
-3,
11,
4,
-13,
-5,
7,
-4,
-4,
2,
1,
-4,
-5,
-4,
-8,
-2,
8,
-4,
-6,
5,
-8,
-4,
9,
2,
1,
-5,
-1,
-13,
2,
6,
3,
-1,
9,
8,
-11,
3,
5,
-1,
-6,
7,
3,
-3,
5,
4,
3,
-3,
8,
-5,
-5,
6,
13,
-2,
1,
4,
-4,
-10,
5,
4,
-8,
2,
-3,
-2,
-8,
4,
2,
-1,
-3,
-6,
-3,
-4,
-3,
-7,
1,
0,
-11,
-4,
7,
0,
-1,
-1,
-4,
-4,
-4,
6,
-2,
0,
5,
-4,
-2,
5,
3,
-1,
0,
3,
-1,
0,
3,
0,
-4,
-3,
5,
-8,
-1,
1,
-4,
2,
-2,
0,
0,
-2,
1,
-1,
-1,
2,
-2,
-1,
1,
};

