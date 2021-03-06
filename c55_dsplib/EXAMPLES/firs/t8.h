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

#define NX 256
#define NH 32
#define FNAME "t8"
#define MAXERROR 10

DATA x[NX] ={
-4188,
-18068,
-31904,
-8129,
22187,
-14009,
-14148,
-11333,
-1560,
-17958,
30278,
-12684,
18279,
25909,
-16140,
-23216,
-10388,
15278,
-30549,
2899,
3830,
11120,
5500,
12183,
17431,
26061,
30591,
26594,
-21065,
31358,
26082,
-30844,
-14286,
-20454,
7127,
-19048,
32619,
-31670,
-3957,
-23043,
7959,
16670,
-14379,
1781,
-12292,
-20858,
18301,
20283,
14635,
-29799,
7425,
-10800,
5496,
27077,
83,
-5407,
19625,
25598,
875,
-7227,
28222,
-14239,
17690,
14914,
27171,
-25814,
25489,
6228,
-31977,
-17150,
-24667,
24955,
20527,
17258,
20341,
11944,
8179,
-8646,
-19479,
-14743,
-1210,
-6542,
13257,
-11708,
-29593,
18185,
3499,
-28328,
-251,
22026,
-2561,
18351,
-542,
12826,
31788,
-9623,
7994,
1041,
20645,
-717,
15168,
13800,
21915,
-32053,
-29598,
83,
-13652,
-31865,
19279,
-28359,
-12441,
-10486,
20760,
-32482,
-406,
7434,
-8253,
-19772,
25891,
31906,
27641,
-6920,
10635,
2628,
-18935,
-12758,
-31890,
-32469,
31967,
20433,
17721,
26429,
-24657,
-26472,
3372,
-32341,
-24531,
-29113,
17214,
-28089,
14302,
-23567,
7582,
-1868,
678,
-10156,
-27214,
-16004,
1675,
-23558,
-24873,
179,
-14031,
-25431,
3,
-8002,
-15037,
29929,
-2749,
-16711,
21656,
-12900,
-30591,
31952,
-1326,
6785,
1064,
31277,
-16568,
11022,
-23152,
-6218,
-23459,
-10208,
3272,
-29988,
-17567,
-6633,
-24859,
-3760,
-29396,
32548,
12738,
7538,
7677,
21609,
31410,
-4101,
22689,
-6745,
-5219,
25689,
-10115,
20212,
32392,
18419,
23056,
10525,
-14935,
-16985,
-4855,
6393,
-5241,
17532,
-31085,
12634,
16609,
29724,
-7385,
-29088,
-8170,
10322,
13222,
-26822,
29359,
2283,
26885,
-12497,
14738,
-7638,
26140,
-28283,
-15401,
8163,
11814,
15525,
28375,
7515,
15617,
8947,
-21619,
-14921,
20476,
-6340,
10491,
-14021,
30237,
5017,
30580,
912,
23869,
-18001,
-16813,
26137,
13709,
31138,
-2650,
15844,
11073,
-30828,
-9808,
-27390,
-28781,
17045,
8377,
1996,
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
923,
-373,
-603,
130,
-64,
-204,
-893,
-300,
899,
145,
511,
238,
440,
-663,
-162,
-814,
725,
626,
-349,
751,
477,
-657,
406,
645,
535,
940,
162,
-263,
-239,
920,
731,
-594,
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[2*NH + 2] ;

DATA r[NX] ;

DATA rtest[NX] ={
-118,
-462,
-617,
449,
1241,
-564,
-393,
932,
1216,
-449,
-396,
-766,
505,
556,
-1144,
-238,
314,
-247,
-1625,
-2170,
2678,
1212,
193,
-522,
555,
-2752,
-2321,
-1133,
-2871,
3031,
-359,
-5265,
-1512,
2705,
622,
-1502,
22,
2073,
385,
-1081,
-2939,
-838,
-869,
94,
167,
-2216,
5287,
-834,
-619,
-903,
4695,
2481,
-179,
-210,
-1425,
-115,
351,
-604,
-1242,
2703,
2046,
-5478,
-3384,
5729,
4279,
410,
1653,
1195,
-1429,
-2257,
2674,
-1453,
1241,
1127,
188,
-390,
5616,
-2221,
-6466,
-94,
4184,
1356,
2783,
1559,
-2580,
2679,
-302,
-305,
-2571,
2431,
2460,
1441,
85,
3508,
1887,
-3790,
2970,
2449,
-1695,
2813,
1564,
4259,
1,
-3459,
-1484,
2887,
-55,
-2528,
-96,
-43,
5291,
2573,
-883,
268,
-2388,
2481,
808,
-1680,
4762,
4327,
334,
-5304,
-6,
-1234,
-1869,
-2388,
1299,
2723,
2171,
1056,
-460,
1889,
-1132,
-7589,
-314,
295,
-1822,
736,
4261,
1724,
2959,
1597,
-254,
-4238,
-1531,
3328,
-3094,
-3468,
4456,
-1585,
-6581,
-2550,
2700,
971,
1660,
-2360,
-2082,
337,
-1578,
-919,
-2084,
-1560,
-3428,
1787,
-1281,
-443,
-3405,
1885,
681,
-3378,
-6261,
-339,
-3480,
-3061,
2800,
-1154,
-4838,
1905,
-5567,
-5484,
-5069,
727,
1217,
2747,
-1005,
269,
-593,
-4913,
-5491,
-835,
-4528,
631,
-4075,
2803,
1141,
-2527,
-1824,
-246,
-309,
-6005,
-3643,
942,
-3176,
3047,
1784,
59,
1678,
3586,
-2538,
-5040,
4280,
3970,
-710,
-1857,
707,
2448,
-920,
-2238,
672,
1852,
3738,
-3012,
622,
2381,
1520,
705,
3239,
-182,
2964,
-1199,
1649,
-396,
4175,
-3048,
3520,
2229,
6014,
5012,
-4714,
-612,
5098,
814,
-4262,
-2041,
2027,
2054,
1346,
-2033,
5468,
1543,
-181,
-1891,
303,
656,
3397,
11,
};

