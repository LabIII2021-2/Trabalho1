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

#define NX 64
#define NLAGS 64 // max NLAGS = N 
#define FNAME "t2"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
2632,
-453,
945,
2391,
3455,
1951,
-2653,
-773,
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
};

DATA rtest[NLAGS] ={ // lag0, lag1,... 
151,
10,
13,
12,
16,
13,
19,
-15,
-31,
2,
-41,
6,
-26,
-26,
-16,
3,
-30,
-1,
7,
-5,
8,
0,
-2,
8,
20,
19,
10,
5,
12,
5,
1,
-8,
-17,
-20,
-6,
-23,
-4,
-25,
-16,
-3,
-6,
-7,
5,
7,
-3,
19,
11,
10,
11,
4,
2,
9,
5,
15,
4,
-8,
-3,
4,
0,
-2,
-3,
-1,
3,
-2,
};

