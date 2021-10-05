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
#define NX 64
#define NBIQ 2
#define FNAME "t6"
#define MAXERROR 20

DATA x[NX] ={
76,
-50,
-467,
-484,
-192,
-499,
-119,
187,
-417,
-476,
114,
111,
-496,
-495,
-318,
88,
-453,
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
-388,
-51,
220,
401,
-233,
-251,
374,
-274,
311,
417,
-275,
-267,
-461,
-432,
144,
-317,
351,
-334,
-337,
505,
-62,
-164,
-191,
-139,
-110,
93,
-389,
-473,
-43,
378,
444,
-241,
-348,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: b0 b1 b2 a1 a2 ... */
6485,
-19271,
12533,
14661,
5734,
14563,
-14274,
-2746,
-10307,
18358,
};

DATA rtest[NX] ={
6,
-32,
7,
106,
-50,
-175,
187,
-31,
-154,
228,
35,
-290,
21,
315,
-78,
-184,
-121,
344,
-58,
-188,
29,
59,
211,
-245,
-76,
123,
141,
-224,
-2,
84,
97,
-138,
92,
-86,
-45,
0,
232,
-44,
-372,
342,
-59,
-141,
238,
-90,
-65,
42,
-165,
283,
-226,
152,
68,
-375,
265,
125,
-131,
-91,
56,
-30,
150,
-11,
-191,
-37,
105,
238,
};

