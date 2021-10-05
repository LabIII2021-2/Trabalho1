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

/* Test for iircas51: rand */
#define NX 16
#define NBIQ 8
#define FNAME "t5"
#define MAXERROR 20

DATA x[NX] ={
-1232,
-824,
660,
-883,
-126,
-1781,
1998,
338,
-314,
63,
-680,
-275,
-1122,
326,
1065,
122,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: b0 b1 b2 a1 a2 ... */
18514,
18091,
-11303,
5525,
-17334,
19270,
8911,
13339,
-11440,
4044,
11358,
-3463,
5064,
-4726,
-17685,
-2413,
9616,
-14401,
11140,
-3328,
-67,
-9125,
-11517,
7111,
-7668,
-11248,
-2363,
4215,
-1530,
14720,
5642,
17041,
5107,
2667,
-19071,
-7077,
7208,
-5094,
11568,
10536,
};

DATA rtest[NX] ={
-1,
-1,
-1,
0,
-1,
-1,
-1,
-2,
-2,
-2,
-3,
-1,
-4,
-1,
-2,
-2,
};


