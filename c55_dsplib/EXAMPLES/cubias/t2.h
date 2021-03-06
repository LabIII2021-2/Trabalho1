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

#define NA 64
#define NB 64  // NB <= NA 
#define FNAME "t2"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
3567,
3415,
-736,
3224,
-3622,
-1206,
2565,
-4016,
-2959,
-2435,
-2469,
850,
-1867,
-2468,
-3971,
2021,
-450,
3537,
-279,
-667,
2836,
206,
-2436,
1410,
2769,
-3936,
1485,
-988,
2718,
23,
1715,
-583,
-1601,
-2543,
-2512,
1492,
-1616,
341,
-2861,
1621,
-997,
2949,
2897,
766,
-29,
3274,
2634,
1187,
2604,
1312,
-1295,
-1723,
-1301,
279,
1860,
-1563,
2772,
557,
-1062,
1660,
381,
-452,
1593,
993,
};

DATA b[NB] ={
2415,
3742,
185,
3114,
-2680,
3930,
-1873,
-2029,
3078,
1944,
-2978,
-4000,
3226,
-2465,
-1649,
1322,
-1767,
-253,
-3566,
4000,
678,
-627,
127,
-1361,
-550,
-2246,
653,
2132,
244,
1151,
-2384,
-985,
2321,
1481,
-319,
555,
2410,
-3612,
842,
-3685,
-694,
-1598,
3066,
-3974,
2195,
3857,
4014,
2366,
-503,
-14,
-2344,
1175,
-1475,
3769,
1856,
-722,
2003,
-1901,
-493,
3550,
1501,
-2355,
2779,
1055,
};

DATA rtest[NA+NB-1] ={
115,
206,
3,
-10,
151,
-49,
7,
49,
-105,
-10,
97,
-54,
-19,
-11,
-95,
17,
8,
-26,
45,
10,
8,
13,
-14,
-68,
18,
-45,
-90,
47,
1,
-22,
2,
6,
-15,
36,
21,
-23,
37,
-10,
25,
-26,
8,
-45,
26,
-40,
-9,
36,
6,
33,
-26,
28,
-40,
24,
-13,
-14,
15,
0,
-3,
29,
23,
6,
39,
14,
-7,
35,
30,
-16,
33,
-25,
-28,
-35,
-20,
1,
6,
-12,
-5,
27,
-33,
11,
26,
16,
-26,
20,
-12,
11,
16,
-4,
17,
-31,
-6,
-3,
44,
-15,
-6,
8,
-53,
-31,
-18,
19,
-48,
0,
15,
-21,
0,
42,
27,
14,
-10,
41,
33,
-10,
23,
32,
-33,
-50,
40,
-55,
14,
53,
4,
23,
20,
10,
47,
20,
51,
115,
73,
};

