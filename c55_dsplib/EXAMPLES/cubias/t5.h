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

#define NA 50
#define NB 50  // NB <= NA 
#define FNAME "t5"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
3662,
4100,
-1529,
-581,
-268,
-3251,
-3375,
301,
2092,
-939,
-1313,
-1991,
3416,
1171,
-2399,
4430,
1302,
-2504,
1680,
1536,
-3386,
-4426,
-2204,
-3555,
-3992,
3271,
-2963,
-4334,
2168,
338,
-2076,
-1220,
-4515,
3607,
3392,
-2278,
643,
-3158,
874,
-1566,
1470,
3370,
626,
4453,
2704,
-3220,
3086,
-2856,
1288,
1566,
};

DATA b[NB] ={
2521,
-1114,
-542,
-158,
1001,
-3003,
-4616,
2689,
126,
-2658,
-3676,
-3176,
-858,
-855,
-4146,
4094,
-3245,
-1072,
-1752,
-3073,
3676,
-1644,
2168,
-826,
-929,
51,
-3065,
229,
1308,
-4484,
3122,
2812,
1833,
-354,
-3869,
2972,
-2846,
-507,
-4514,
-1773,
3478,
3107,
-1547,
3528,
-189,
563,
1074,
1500,
1080,
1715,
};

DATA rtest[NA+NB-1] ={
192,
168,
74,
57,
19,
-34,
4,
2,
-17,
66,
5,
-115,
-60,
-19,
-25,
4,
22,
46,
62,
10,
-18,
34,
1,
-93,
-26,
-8,
-28,
-17,
-35,
-12,
-26,
-9,
-35,
3,
59,
-24,
-9,
58,
-49,
-22,
-37,
-5,
73,
11,
8,
-20,
26,
32,
-27,
35,
38,
-45,
66,
-27,
-9,
0,
-44,
53,
8,
-2,
71,
4,
75,
7,
-14,
67,
-58,
97,
9,
-42,
108,
-27,
-25,
-32,
-34,
85,
-57,
-12,
17,
-88,
30,
-119,
-4,
16,
-70,
21,
-56,
-84,
7,
-45,
32,
21,
-20,
29,
-53,
76,
-96,
23,
121,
};

