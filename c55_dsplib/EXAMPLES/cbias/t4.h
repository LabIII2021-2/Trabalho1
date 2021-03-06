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

#define NA 100
#define NB 100  // NB <= NA 
#define FNAME "t4"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
-1403,
-694,
19,
1454,
-1271,
-2542,
-372,
-218,
-3181,
1075,
1468,
-1432,
-1561,
1366,
1860,
3186,
-175,
2639,
-321,
1995,
2155,
-2188,
-696,
136,
1429,
453,
-257,
-359,
-2702,
-371,
-877,
-1295,
2305,
1700,
2947,
379,
-3184,
630,
2072,
3126,
-1823,
1334,
144,
2837,
1398,
-1783,
-331,
-2149,
3072,
-946,
-2956,
1673,
2587,
-1402,
-1631,
2835,
-2419,
2888,
1322,
2278,
-1906,
-295,
-2746,
2301,
406,
-1185,
-820,
2410,
-838,
-2794,
-1968,
-2953,
437,
-2478,
144,
-2510,
1768,
-819,
2119,
-2972,
641,
2943,
-1385,
2548,
-2612,
-2849,
-1742,
2838,
-2864,
-1546,
3273,
-1888,
-11,
-1374,
1132,
3001,
1746,
1088,
-2419,
-2652,
};

DATA b[NB] ={
-3180,
-1389,
2075,
3181,
-3164,
2093,
793,
394,
-1678,
2110,
-1552,
1662,
1046,
-1874,
669,
687,
1045,
-2076,
894,
-2161,
259,
808,
1218,
1162,
2469,
-3193,
-1243,
1828,
-1263,
2796,
1171,
-2790,
-2814,
-3199,
-1789,
106,
-274,
1331,
540,
60,
-2790,
-2011,
-790,
-1466,
1775,
-1220,
905,
3188,
18,
2934,
2149,
2736,
-2536,
2045,
2675,
-2252,
-2477,
1721,
1453,
993,
1664,
1069,
2513,
-1494,
-529,
-1881,
-3044,
-2745,
2297,
-1048,
-222,
2711,
-1779,
2372,
1026,
2563,
-78,
3228,
-831,
205,
-2089,
12,
-510,
1051,
1138,
2997,
-2020,
-2548,
426,
3074,
-3122,
2426,
-3101,
127,
-2017,
1413,
-1634,
2843,
-2378,
141,
};

DATA rtest[NA+NB-1] ={
0,
1,
-1,
0,
-1,
3,
0,
1,
-1,
3,
-4,
3,
2,
4,
-1,
-2,
-6,
10,
-4,
2,
-3,
2,
-11,
1,
-1,
4,
-8,
0,
0,
0,
-3,
2,
-5,
-1,
5,
3,
-6,
6,
0,
1,
6,
12,
-4,
5,
-5,
1,
-11,
-4,
8,
-4,
-14,
-4,
-3,
-10,
6,
6,
-1,
-1,
-4,
13,
-9,
6,
3,
20,
-14,
26,
-1,
5,
-5,
15,
-5,
0,
7,
-2,
8,
-4,
-12,
-5,
-2,
9,
10,
-11,
2,
4,
-6,
2,
2,
3,
-5,
17,
-8,
-5,
4,
-7,
20,
-11,
5,
-4,
2,
-27,
1,
-10,
-12,
19,
13,
9,
-11,
12,
-15,
11,
-12,
3,
1,
-1,
-14,
-9,
-1,
-7,
14,
-8,
7,
-1,
-3,
-17,
-10,
-16,
-1,
13,
5,
11,
-11,
8,
2,
6,
-10,
17,
18,
-19,
0,
-3,
3,
-12,
20,
-9,
4,
16,
-9,
-3,
0,
-3,
-9,
12,
0,
9,
-15,
6,
-4,
9,
-10,
12,
-1,
-10,
-6,
-14,
8,
5,
8,
-7,
7,
-11,
6,
4,
2,
3,
4,
-2,
-13,
7,
-2,
1,
4,
-5,
-8,
7,
8,
-6,
-1,
3,
1,
-3,
2,
2,
1,
0,
-3,
-6,
-2,
3,
3,
};

