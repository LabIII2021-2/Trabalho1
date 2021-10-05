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

DATA rtest[NLAGS] ={// lag0, lag1,...  
151,
10,
14,
13,
17,
14,
20,
-16,
-36,
2,
-49,
8,
-32,
-32,
-20,
4,
-40,
-2,
10,
-8,
11,
-1,
-3,
12,
33,
32,
17,
8,
21,
10,
2,
-15,
-33,
-41,
-13,
-51,
-9,
-58,
-39,
-7,
-17,
-20,
16,
20,
-10,
63,
39,
36,
45,
17,
11,
45,
25,
86,
27,
-55,
-26,
35,
1,
-28,
-42,
-16,
86,
-126,
};

