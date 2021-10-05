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

#define NX 128
#define NH 64
#define FNAME "t4"
#define MAXERROR 10

DATA x[NX] ={
16850,
-2900,
6051,
15305,
22115,
12488,
-16973,
-4944,
22831,
21857,
-4705,
20638,
-23180,
-7714,
16418,
-25698,
-18933,
-15584,
-15796,
5441,
-11944,
-15791,
-25414,
12938,
-2879,
22639,
-1783,
-4266,
18151,
1318,
-15590,
9024,
17727,
-25185,
9504,
-6319,
17395,
147,
10982,
-3729,
-10244,
-16272,
-16074,
9553,
-10341,
2184,
-18305,
10375,
-6377,
18874,
18541,
4905,
-181,
20959,
16862,
7597,
16671,
8400,
-8286,
-11025,
-8327,
1786,
11907,
-9999,
17746,
3568,
-6795,
10629,
2441,
-2890,
10200,
6360,
15457,
23951,
1184,
19930,
-17147,
25152,
-11983,
-12986,
19699,
12441,
-19057,
-25599,
20651,
-15774,
-10553,
8464,
-11304,
-1614,
-22819,
25602,
4340,
-4011,
813,
-8706,
-3518,
-14369,
4184,
13650,
1563,
7367,
-15254,
-6301,
14854,
9481,
-2040,
3556,
15425,
-23112,
5393,
-23579,
-4437,
-10224,
19627,
-25428,
14048,
24685,
25694,
15144,
-3217,
-89,
-14997,
7523,
-9436,
24122,
11882,
-4617,
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
0,
0,
-1,
0,
-1,
0,
504,
0,
0,
0,
964,
0,
0,
0,
1179,
0,
-1,
0,
936,
0,
-1,
0,
0,
0,
-1,
0,
-2187,
0,
-1,
0,
-10613,
0,
0,
0,
10612,
0,
0,
0,
2186,
0,
0,
0,
-1,
0,
0,
0,
-937,
0,
0,
0,
-1180,
0,
0,
0,
-965,
0,
-1,
0,
-505,
0,
0,
0,
0,
0,
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[NH] ;

DATA rtest[NX] ={
0,
0,
0,
0,
0,
0,
259,
-45,
93,
236,
837,
107,
-83,
375,
1609,
600,
-354,
723,
1593,
891,
-323,
472,
480,
677,
-414,
-71,
-2047,
-161,
-804,
-996,
-8673,
-792,
-1702,
-4851,
-4005,
-6769,
6112,
5816,
2801,
-2699,
-5769,
-5165,
19000,
11406,
-7083,
14273,
1974,
4029,
11614,
-9941,
-4184,
-3371,
4509,
-4141,
-7629,
-14789,
-7618,
5088,
-10716,
7135,
1935,
-2209,
-1126,
11460,
-8205,
5698,
3529,
-4559,
1514,
-1066,
12873,
4999,
12225,
-5834,
2582,
-7009,
1868,
-1676,
-2136,
-7177,
-12983,
2275,
-4648,
515,
-271,
1610,
-6038,
8100,
8300,
7056,
7502,
5922,
-5450,
-1489,
-6254,
712,
3565,
-9227,
5107,
-801,
-6736,
-1268,
-1753,
-12565,
1598,
-1964,
8903,
-3173,
4657,
13899,
-12703,
5762,
2518,
5225,
-788,
10474,
-2708,
-13801,
11415,
-4488,
2214,
-8773,
-2799,
-1350,
-7423,
8806,
1893,
530,
};

DATA r[NX];
