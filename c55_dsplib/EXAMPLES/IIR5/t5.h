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

/* Test for iircas5: rand */
#define NX 32
#define NBIQ 8
#define FNAME "t5"
#define MAXERROR 20

DATA x[NX] ={
-617,
-413,
330,
-442,
-64,
-892,
1000,
169,
-157,
31,
-341,
-138,
-562,
163,
533,
61,
287,
-596,
-247,
580,
370,
-80,
138,
602,
-903,
210,
-922,
-174,
-400,
766,
-994,
548,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: a1 a2 b2 b0 b1 ... */
18514,
18091,
-16011,
-11303,
2954,
19270,
8911,
-18272,
13339,
-1911,
11358,
-3463,
4419,
5064,
-17935,
-2413,
9616,
4267,
-14401,
-18592,
-67,
-9125,
-19042,
-11517,
-7366,
-11248,
-2363,
-19018,
4215,
-19156,
5642,
17041,
-12187,
5107,
-4563,
-7077,
7208,
3417,
-5094,
7200,
};

DATA rtest[NX] ={
-1,
0,
-1,
-1,
0,
0,
-1,
0,
-2,
0,
1,
-3,
1,
-1,
-2,
2,
1,
-1,
-7,
0,
7,
-2,
-3,
2,
2,
-6,
-4,
8,
1,
-6,
2,
0,
};

