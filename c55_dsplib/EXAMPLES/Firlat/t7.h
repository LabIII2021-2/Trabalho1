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

/* Test for latfor: sine */
#define NX 200
#define NK 11
#define FNAME "t7"
#define MAXERROR 10

DATA x[NX] ={
0,
1163,
2302,
3395,
4419,
5354,
6180,
6881,
7442,
7853,
8104,
8191,
8113,
7869,
7467,
6912,
6218,
5398,
4469,
3448,
2358,
1220,
58,
-1106,
-2247,
-3343,
-4371,
-5311,
-6143,
-6850,
-7419,
-7837,
-8097,
-8192,
-8121,
-7886,
-7491,
-6945,
-6257,
-5443,
-4518,
-3502,
-2415,
-1279,
-117,
1047,
2190,
3289,
4321,
5265,
6103,
6817,
7393,
7819,
8086,
8190,
8128,
7901,
7514,
6974,
6294,
5485,
4566,
3554,
2470,
1336,
175,
-990,
-2135,
-3236,
-4272,
-5221,
-6065,
-6785,
-7369,
-7802,
-8078,
-8190,
-8136,
-7917,
-7538,
-7006,
-6332,
-5530,
-4615,
-3607,
-2526,
-1394,
-234,
931,
2077,
3182,
4221,
5175,
6024,
6752,
7342,
7783,
8067,
8187,
8142,
7931,
7560,
7035,
6368,
5571,
4662,
3659,
2581,
1451,
291,
-874,
-2022,
-3129,
-4172,
-5131,
-5986,
-6719,
-7317,
-7766,
-8058,
-8186,
-8149,
-7946,
-7583,
-7066,
-6405,
-5615,
-4711,
-3712,
-2637,
-1509,
-351,
815,
1964,
3074,
4121,
5084,
5945,
6685,
7289,
7746,
8046,
8183,
8154,
7959,
7604,
7094,
6440,
5656,
4758,
3763,
2691,
1565,
408,
-758,
-1909,
-3021,
-4071,
-5039,
-5905,
-6652,
-7264,
-7728,
-8036,
-8181,
-8160,
-7974,
-7626,
-7124,
-6477,
-5700,
-4806,
-3815,
-2747,
-1624,
-467,
699,
1851,
2965,
4019,
4992,
5864,
6617,
7235,
7707,
8023,
8176,
8164,
7986,
7646,
7152,
6512,
5740,
4852,
3866,
2801,
1680,
524,
-642,
};

#pragma DATA_SECTION (k,".coeffs")
DATA k[NK] ={
4593,
6767,
2363,
2070,
1968,
4518,
1764,
5452,
2530,
3848,
4144,
};

DATA rtest[] ={
0,
1163,
2598,
4351,
6235,
8203,
10206,
12276,
14270,
16250,
18067,
19689,
21060,
22003,
22501,
22543,
22128,
21265,
19971,
18272,
16202,
13805,
11127,
8224,
5155,
1981,
-1233,
-4422,
-7522,
-10469,
-13204,
-15671,
-17821,
-19610,
-21001,
-21967,
-22487,
-22552,
-22160,
-21319,
-20045,
-18366,
-16314,
-13932,
-11267,
-8374,
-5311,
-2141,
1073,
4264,
7370,
10326,
13073,
15555,
17722,
19529,
20941,
21929,
22472,
22560,
22190,
21371,
20119,
18459,
16425,
14058,
11406,
8523,
5468,
2301,
-912,
-4106,
-7218,
-10183,
-12942,
-15438,
-17622,
-19448,
-20881,
-21890,
-22456,
-22566,
-22219,
-21422,
-20191,
-18551,
-16535,
-14183,
-11545,
-8672,
-5624,
-2461,
751,
3948,
7065,
10039,
12809,
15320,
17521,
19366,
20819,
21850,
22438,
22571,
22248,
21473,
20263,
18642,
16644,
14308,
11683,
8820,
5779,
2621,
-590,
-3790,
-6912,
-9895,
-12677,
-15202,
-17419,
-19283,
-20756,
-21809,
-22419,
-22576,
-22275,
-21522,
-20333,
-18733,
-16752,
-14432,
-11820,
-8968,
-5935,
-2781,
429,
3631,
6759,
9750,
12543,
15082,
17316,
19199,
20692,
21766,
22400,
22579,
22300,
21570,
20403,
18822,
16860,
14556,
11957,
9116,
6090,
2940,
-269,
-3472,
-6605,
-9604,
-12409,
-14962,
-17212,
-19113,
-20627,
-21723,
-22379,
-22581,
-22325,
-21617,
-20471,
-18910,
-16966,
-14678,
-12093,
-9263,
-6244,
-3100,
108,
3313,
6451,
9459,
12274,
14841,
17108,
19027,
20561,
21679,
22356,
22581,
22349,
21663,
20539,
18998,
17072,
14800,
12229,
9409,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NK];
DATA *dp = dbuffer;

DATA r[NX];

