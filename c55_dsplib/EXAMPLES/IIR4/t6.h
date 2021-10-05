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

/* Test for iircas4 : rand */
#define NX 64
#define NBIQ 2
#define FNAME "t6"
#define MAXERROR 20

DATA x[NX] ={
-63,
-2,
-293,
146,
-185,
470,
231,
-91,
250,
-238,
-62,
443,
187,
-295,
347,
131,
-375,
-300,
109,
132,
-133,
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
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2  ... */
-17705,
13521,
5537,
-12945,

-16579,
-12823,
-12155,
19436,
};

DATA rtest[NX] ={
-63,
-69,
-362,
-252,
-411,
-19,
378,
252,
701,
418,
234,
705,
758,
499,
941,
1005,
454,
231,
214,
162,
-2,
170,
147,
-397,
-879,
-1155,
-1785,
-1929,
-1610,
-1985,
-2260,
-1966,
-1883,
-2275,
-2506,
-2694,
-2656,
-2985,
-2934,
-2495,
-2205,
-1720,
-1867,
-1725,
-1661,
-1877,
-2043,
-1767,
-1442,
-1129,
-858,
-658,
-930,
-1018,
-744,
-403,
-455,
-566,
-92,
-490,
-196,
428,
61,
-43,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ+2];  // index + (2*NBIQ+1)
DATA *dp = dbuffer;

DATA r[NX];

