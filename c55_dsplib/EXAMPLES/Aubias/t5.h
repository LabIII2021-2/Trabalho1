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

#define NX 61
#define NLAGS 61 // max NLAGS = N 
#define FNAME "t5"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
767,
-3191,
-3876,
-348,
3103,
3643,
-1977,
-2851,
3128,
-2200,
1223,
3917,
1383,
3107,
-4113,
-3046,
2674,
-586,
3275,
1971,
1571,
-1292,
-2803,
-2890,
-2592,
-651,
2986,
-82,
2651,
-330,
-358,
-414,
-737,
3369,
-4149,
-1700,
-3783,
1620,
1259,
4052,
441,
-839,
-2528,
1050,
1958,
-1042,
-4113,
-673,
2128,
2465,
3523,
2892,
-1110,
1013,
1940,
-2569,
3396,
580,
1105,
-2229,
409,
};

DATA rtest[NLAGS] ={// lag0, lag1,...  
178,
21,
-15,
-52,
-44,
2,
6,
20,
22,
-23,
-7,
1,
18,
28,
-17,
-2,
-39,
-7,
-25,
-15,
10,
43,
16,
25,
-26,
0,
-46,
-16,
23,
-12,
-13,
-1,
25,
19,
2,
2,
-26,
-18,
27,
30,
75,
-29,
-76,
10,
32,
102,
44,
-72,
-34,
-41,
-15,
-20,
25,
47,
-40,
-106,
-9,
41,
65,
-46,
10,
};

