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

#define NX 81
#define NLAGS 81 // max NLAGS = N 
#define FNAME "t8"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
-286,
-399,
-3002,
-412,
-974,
-1438,
2562,
1889,
3275,
421,
-3538,
700,
2302,
3474,
-2026,
1483,
160,
3152,
1553,
-1981,
-367,
-2387,
3413,
-1051,
-3284,
1859,
2874,
-1558,
-1812,
3151,
-2688,
3209,
1469,
2531,
-2118,
-328,
-3051,
2556,
451,
-1316,
-911,
2678,
-931,
-3105,
-2186,
-3281,
485,
-2754,
161,
-2789,
1965,
-910,
2354,
-3302,
712,
3270,
-1538,
2831,
-2902,
-3166,
-1935,
3153,
-3182,
-1717,
3637,
-2098,
-12,
-1526,
1257,
3334,
1940,
1209,
-2688,
-2947,
-3533,
-1543,
2306,
3535,
-3515,
2325,
882,
};

DATA rtest[NLAGS] ={// lag0, lag1,...  
164,
-15,
-8,
-19,
6,
-6,
1,
2,
-25,
41,
-20,
0,
-24,
11,
8,
24,
9,
-22,
-13,
17,
20,
-28,
-6,
1,
15,
12,
11,
-42,
-5,
23,
-6,
-22,
-7,
-5,
-34,
36,
-48,
-18,
24,
46,
-18,
-51,
15,
-5,
48,
-34,
8,
-27,
33,
2,
-33,
27,
-24,
2,
17,
0,
-26,
22,
19,
-27,
-7,
-17,
21,
39,
56,
-28,
-82,
-72,
28,
17,
36,
60,
14,
58,
-19,
-67,
41,
-53,
-26,
-15,
-8,
};

