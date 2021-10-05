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
#define FNAME "t6"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
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
3621,
-1383,
1305,
-908,
1068,
1670,
};

DATA rtest[NLAGS] ={ // lag0, lag1,... 
164,
11,
0,
-36,
-43,
5,
-9,
17,
8,
-4,
22,
9,
14,
7,
-22,
-5,
-20,
17,
0,
-8,
-1,
13,
7,
7,
-11,
-3,
-19,
-9,
17,
-11,
2,
8,
10,
-1,
-20,
-2,
-8,
7,
16,
0,
20,
0,
-10,
3,
-15,
16,
-2,
-10,
11,
-3,
11,
-12,
-2,
11,
-6,
5,
-2,
0,
2,
-3,
-2,
};

