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

#define NA 32
#define NB 32  // NB <= NA 
#define FNAME "t5"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
4578,
5125,
-1911,
-726,
-335,
-4063,
-4219,
376,
2615,
-1174,
-1641,
-2488,
4270,
1464,
-2999,
5538,
1627,
-3130,
2100,
1921,
-4232,
-5533,
-2755,
-4443,
-4990,
4088,
-3704,
-5418,
2710,
423,
-2595,
-1524,
};

DATA b[NB] ={
-5644,
4509,
4240,
-2848,
804,
-3948,
1093,
-1957,
1837,
4212,
783,
5566,
3380,
-4025,
3858,
-3570,
1610,
1957,
3152,
-1393,
-677,
-197,
1252,
-3754,
-5770,
3362,
157,
-3323,
-4595,
-3970,
-1072,
-1069,
};

DATA rtest[NA+NB-1] ={
-5,
-10,
-21,
-37,
-29,
0,
34,
14,
-19,
24,
19,
-19,
1,
62,
45,
-31,
-34,
0,
11,
-61,
-1,
83,
12,
17,
50,
25,
-25,
4,
33,
66,
81,
30,
7,
4,
38,
24,
-50,
34,
57,
-24,
-54,
-56,
39,
-115,
-64,
61,
-89,
-17,
64,
-30,
-34,
-17,
9,
-27,
17,
45,
-59,
10,
48,
-19,
-20,
7,
8,
};

