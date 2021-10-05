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

/* This is a test for sub: rand */
#define NX 32
#define FNAME "t4"
#define MAXERROR 2

#define SUB_SCALE 1

DATA x[NX] ={
-1800,
14149,
-1115,
-2666,
11344,
824,
-9744,
5640,
11079,
-15741,
5940,
-3950,
10872,
92,
6863,
-2331,
-6403,
-10170,
-10046,
5971,
-6464,
1365,
-11441,
6484,
-3986,
11796,
11588,
3065,
-113,
13099,
10539,
4748,
};

DATA y[NX] ={
10419,
5250,
-5178,
-6890,
-5204,
1117,
7442,
-6249,
11092,
2231,
-4246,
6643,
1526,
-1806,
6376,
3975,
9661,
14970,
740,
12456,
-10717,
15720,
-7489,
-8116,
12312,
7776,
-11911,
-15999,
12907,
-9859,
-6595,
5290,
};

DATA rtest[NX] ={
-6109,
4450,
2032,
2112,
8274,
-146,
-8593,
5945,
-6,
-8986,
5093,
-5296,
4673,
949,
244,
-3153,
-8031,
-12570,
-5393,
-3243,
2127,
-7177,
-1975,
7300,
-8149,
2010,
11750,
9532,
-6510,
11479,
8567,
-271,
};

DATA r[NX]; 
