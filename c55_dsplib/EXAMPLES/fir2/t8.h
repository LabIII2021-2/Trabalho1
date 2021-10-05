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
#define NH 64
#define FNAME "t8"
#define MAXERROR 10

DATA x[NX] ={
-32282,
18925,
-31603,
24768,
-9664,
14558,
30700,
-22567,
-22089,
-12230,
-30843,
-9331,
-30987,
19245,
32717,
-25544,
8034,
-24080,
-12450,
-23935,
-18133,
-6780,
-23912,
-16970,
28017,
-7137,
738,
-26680,
-31346,
-22313,
22578,
24848,
-20514,
32198,
13895,
24337,
-1335,
-262,
-13925,
-28775,
-15567,
-20562,
27334,
-24689,
-31887,
-8540,
13018,
25516,
6145,
-22500,
-12014,
-17473,
-32217,
-6757,
9821,
-27198,
17616,
30782,
14076,
18478,
-17199,
-19941,
-15518,
14010,
31299,
8986,
3009,
22810,
19798,
11030,
11205,
21013,
30832,
-857,
20805,
9277,
-12692,
10546,
-9305,
28717,
-809,
-26805,
11392,
975,
-18247,
14746,
-28296,
30416,
-19159,
-22209,
9058,
-32754,
-10772,
-14740,
-29850,
-26615,
-5899,
20767,
24282,
-31290,
14888,
22807,
14981,
29825,
10246,
15879,
-10161,
25167,
-10012,
-28871,
14314,
30029,
-22490,
-5482,
-26606,
-3281,
24192,
-7103,
-16202,
-9544,
15923,
9884,
28822,
21810,
-1968,
8510,
-28955,
2764,
-2902,
23795,
23278,
-1819,
18803,
10222,
-32766,
-24168,
-336,
-30256,
-17863,
-11280,
26179,
-12208,
-16275,
-4392,
22438,
-20678,
536,
-3131,
-11431,
-7860,
25328,
17121,
25150,
-2792,
19608,
-23982,
-28488,
-8183,
-8289,
-1048,
30766,
-10351,
-16208,
5563,
1553,
-22059,
-892,
-259,
22491,
20066,
23447,
7192,
4307,
7333,
-26020,
-22393,
-5660,
3959,
-15160,
18628,
-7349,
-30738,
5603,
3837,
-19616,
-27039,
28392,
-15770,
-19388,
-29544,
6957,
3037,
-26488,
8978,
-3739,
-28418,
-8239,
-16443,
27844,
8486,
24792,
9284,
19555,
-4259,
31531,
-26480,
1801,
2991,
-14134,
-8468,
-28529,
2936,
22044,
-23245,
-21528,
-28309,
21234,
-23989,
25217,
965,
30384,
-24872,
-29604,
-7855,
-5716,
-6463,
-5178,
-8064,
26695,
11151,
30267,
-22087,
16295,
-8254,
-3000,
-30241,
4091,
-8369,
19187,
19348,
-7674,
-16202,
-10294,
30658,
-1324,
-8630,
17338,
-8052,
26234,
-20747,
-8630,
27358,
1043,
-26850,
15421,
-32460,
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
221,
982,
-221,
498,
397,
1029,
-638,
200,
971,
-516,
31,
293,
-214,
-29,
538,
-805,
-984,
-278,
415,
937,
-49,
-798,
-35,
958,
-285,
-370,
587,
-437,
-694,
410,
-508,
-91,
739,
820,
430,
550,
1020,
-211,
-794,
483,
859,
-709,
-984,
-45,
-874,
322,
973,
-91,
79,
-933,
-14,
-178,
-447,
-453,
546,
-868,
-911,
475,
569,
339,
667,
-271,
-417,
-279,
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[NH+2] ;

DATA rtest[NX] ={
-219,
-840,
571,
-1398,
787,
-1623,
1925,
-735,
-377,
140,
-867,
68,
-2280,
-1190,
950,
-1026,
-898,
1040,
-1249,
-660,
-2678,
-399,
-1710,
-2235,
1647,
822,
-1753,
-220,
-336,
-842,
-3174,
-1098,
2293,
-2329,
508,
914,
97,
1420,
4341,
503,
-1322,
-1954,
-779,
373,
-2344,
-1847,
-2799,
-960,
-2982,
2781,
192,
-2860,
-1777,
2292,
-1541,
-3147,
69,
-633,
-3880,
3046,
2576,
731,
-3353,
-3037,
4707,
3725,
2898,
2474,
687,
1000,
4907,
4995,
731,
311,
-1472,
-1427,
2723,
522,
584,
-1055,
214,
1740,
4769,
1291,
-4731,
-3828,
-4481,
-788,
-373,
-4196,
4346,
-217,
1242,
5836,
-960,
-2871,
-1925,
-561,
-1619,
-1002,
-617,
2012,
1469,
1839,
5678,
5676,
3208,
267,
3514,
-3050,
676,
3959,
-1989,
-4691,
-942,
1292,
1330,
-2970,
-1769,
-1906,
-3860,
-260,
-1607,
-108,
1207,
123,
-1867,
-2983,
-3447,
-48,
5716,
-3709,
-1874,
6911,
1073,
-1383,
3422,
4185,
-3070,
-671,
480,
369,
-2161,
2876,
1062,
-4016,
-2191,
2250,
-874,
-3119,
708,
2783,
-1073,
-3608,
-530,
4639,
1700,
-347,
1267,
-833,
-5639,
2609,
3779,
267,
940,
1936,
-4500,
-1985,
1476,
529,
57,
-1662,
-2117,
758,
-3023,
-451,
1869,
-55,
-1733,
-33,
1859,
-2515,
-2175,
3340,
-1969,
-5322,
3227,
5241,
-5399,
-82,
4744,
377,
-3528,
-1737,
-786,
-4468,
-1170,
96,
486,
250,
1003,
-89,
309,
1527,
2623,
5545,
349,
-3218,
900,
2751,
-2345,
-634,
3275,
-3515,
-3993,
-3707,
-890,
831,
-1768,
1810,
-2490,
-3058,
-859,
942,
-3640,
-126,
2006,
-427,
-4101,
538,
4643,
1147,
-2309,
3757,
152,
-1459,
2086,
5640,
2631,
1482,
73,
-1918,
-3181,
811,
2109,
-4611,
-952,
2520,
-491,
-2440,
-890,
3993,
4793,
-2769,
-4718,
-1661,
};

DATA r[NX];
