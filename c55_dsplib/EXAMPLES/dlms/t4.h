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

/* Test for dlms: nois */
#define NX 64
#define NH 32
#define STEP 327
#define FNAME "t4"
#define MAXERROR 20

DATA x[NX] ={
22158,
-31481,
11880,
-7899,
21744,
184,
13727,
-4661,
-12805,
-20339,
-20092,
11942,
-12927,
2731,
-22881,
12969,
-7971,
23593,
23177,
6131,
-226,
26199,
21078,
9496,
20838,
10500,
-10357,
-13781,
-10408,
2233,
14884,
-12499,
22183,
4461,
-8493,
13286,
3052,
-3613,
12751,
7950,
19321,
29939,
1480,
24912,
-21434,
31440,
-14979,
-16232,
24624,
15552,
-23822,
-31998,
25814,
-19718,
-13191,
10580,
-14129,
-2017,
-28523,
32003,
5425,
-5014,
1016,
-10883,
};

DATA des[NX] ={
-206,
-549,
1328,
73,
-815,
-185,
-1635,
1405,
1304,
981,
-477,
208,
-790,
-2430,
3582,
-1508,
3299,
-4350,
1485,
-7020,
5136,
-2488,
955,
-1463,
-73,
3255,
1555,
7734,
-3018,
7491,
-8688,
-2529,
-4112,
3887,
-3058,
1099,
-3404,
-4485,
-93,
-1267,
3646,
551,
3272,
1263,
5355,
1379,
2986,
1270,
436,
-6044,
2969,
2435,
3012,
3380,
-281,
-1885,
-5000,
5358,
-6417,
3270,
-1250,
3213,
1179,
5985,
};

DATA htest[NH] ={ /* C54x: hn-1 ... h0 (backward order) */
-8,
-71,
325,
-125,
262,
-195,
126,
-53,
194,
230,
169,
142,
-211,
205,
-312,
214,
-388,
189,
-425,
223,
-27,
75,
114,
5,
68,
-219,
401,
-10,
284,
76,
-47,
-121,
};

DATA rtest[NX] ={
0,
0,
-1,
-2,
13,
-13,
1,
-1,
-12,
39,
0,
6,
-32,
-2,
0,
-27,
114,
-165,
120,
-225,
185,
-238,
206,
-224,
-14,
-19,
-61,
416,
-149,
510,
-510,
572,
-637,
433,
-447,
166,
-316,
-199,
24,
-245,
337,
-383,
375,
-280,
892,
-242,
1054,
-280,
534,
-523,
507,
-2,
-100,
179,
-526,
167,
-938,
729,
-791,
380,
-471,
180,
80,
249,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NH+2];

#pragma DATA_SECTION (h,".coeffs")
DATA h[NH];

DATA r[NX];

DATA error;

