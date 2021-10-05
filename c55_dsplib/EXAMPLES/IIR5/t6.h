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
#define NX 64
#define NBIQ 2
#define FNAME "t6"
#define MAXERROR 20

DATA x[NX] ={
-454,
-136,
134,
222,
197,
-426,
-47,
-60,
-151,
-355,
179,
203,
232,
-23,
56,
-389,
-51,
221,
402,
-233,
-252,
374,
-275,
312,
418,
-275,
-267,
-462,
-432,
144,
-317,
352,
-334,
-338,
506,
-62,
-164,
-191,
-139,
-110,
93,
-390,
-473,
-43,
378,
444,
-242,
-348,
381,
-269,
149,
478,
168,
379,
-502,
-372,
326,
-72,
399,
240,
191,
-158,
-342,
-353,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: a1 a2 b2 b0 b1 ... */
-12146,
13997,
-3452,
12423,
-1677,
-3050,
-384,
15791,
-1543,
-1939,
};

DATA rtest[NX] ={
8,
15,
-83,
-70,
48,
101,
58,
-112,
-82,
35,
28,
-76,
-7,
81,
69,
-19,
-29,
-80,
-41,
74,
134,
-38,
-143,
43,
23,
28,
101,
-27,
-108,
-97,
-55,
73,
12,
48,
-38,
-124,
85,
96,
-48,
-89,
-30,
21,
63,
-43,
-141,
-40,
136,
166,
-60,
-186,
41,
49,
-2,
69,
52,
54,
-106,
-158,
65,
84,
56,
30,
13,
-38,
};

