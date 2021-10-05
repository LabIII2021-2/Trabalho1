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

/* Test for latfor: rand */
#define NX 400
#define NK 15
#define FNAME "t8"
#define MAXERROR 10

DATA x[NX] ={
4757,
-1634,
-1640,
-4068,
-6686,
1675,
5447,
-3384,
-565,
-7446,
-6788,
215,
3530,
-7611,
7857,
-42,
3289,
4966,
273,
44,
4174,
-4291,
7259,
-6740,
705,
6610,
5920,
2154,
-3893,
-1982,
-2665,
-3038,
7325,
576,
3309,
6145,
7967,
6313,
-1559,
2083,
-1877,
5699,
440,
5037,
-1745,
7565,
-7699,
7434,
3512,
2401,
-874,
-5331,
5493,
7702,
-5981,
-4080,
6718,
2891,
2018,
200,
-8135,
-4475,
7839,
5919,
-7956,
-233,
-1370,
4471,
-194,
370,
4621,
1495,
-6121,
-6394,
2669,
8144,
-2520,
-5308,
-7080,
-3123,
-2707,
-2029,
7409,
3593,
4577,
1928,
2445,
4199,
-5770,
1629,
6531,
-5375,
5225,
-7057,
7466,
-2993,
-8107,
4259,
-3135,
3527,
-6866,
5667,
3578,
6069,
6097,
4285,
2776,
6587,
5267,
5450,
2292,
-5633,
4639,
3791,
1061,
3659,
-4264,
-166,
-1252,
4844,
4316,
-4278,
2214,
-4398,
1900,
-3793,
8048,
4265,
-292,
7294,
-2282,
-6809,
7348,
3127,
1892,
6471,
-7987,
-3262,
7620,
-6519,
1573,
-508,
3561,
5880,
-5151,
-616,
6608,
-7830,
4266,
4847,
-3050,
-4328,
-91,
3035,
7285,
-994,
-42,
-6576,
892,
-1054,
-5222,
-5672,
7106,
-5959,
8168,
3123,
7554,
4514,
-8180,
-2859,
723,
-3170,
2830,
-2528,
7874,
-2393,
-7872,
5124,
7910,
-3083,
-1984,
4064,
-937,
-6555,
8071,
594,
-5988,
-6041,
5964,
3412,
8163,
5173,
4624,
4319,
6635,
-6502,
-4723,
5752,
3981,
-1555,
-3194,
-423,
-5821,
-93,
494,
168,
-4465,
7127,
290,
-667,
4534,
3831,
1677,
-7259,
-7012,
2223,
6166,
-1188,
3414,
-7042,
-7880,
136,
6052,
4891,
4903,
-4979,
3512,
-4669,
4694,
-5372,
-4814,
-582,
-6971,
1582,
-5063,
7124,
-3154,
-624,
5403,
-3275,
3434,
-6970,
4100,
-509,
7289,
-7963,
-7304,
3907,
2221,
7061,
-640,
211,
-1237,
-1378,
-1831,
5825,
5292,
6782,
5506,
6031,
4515,
-1115,
-1047,
-4517,
-7976,
-2032,
5547,
-3502,
-3537,
-2833,
-390,
-4489,
7570,
-3171,
4570,
6477,
-4035,
-5804,
-2597,
3820,
-7637,
725,
958,
2780,
1375,
3046,
4358,
6515,
7648,
6649,
-5266,
7840,
6521,
-7711,
-3571,
-5113,
1782,
-4762,
8155,
-7917,
-989,
-5761,
1990,
4168,
-3595,
445,
-3073,
-5214,
4575,
5071,
3659,
-7450,
1856,
-2700,
1374,
6770,
21,
-1352,
4906,
6400,
219,
-1807,
7056,
-3560,
4423,
3729,
6793,
-6453,
6372,
1557,
-7994,
-4287,
-6167,
6239,
5132,
4315,
5085,
2986,
2045,
-2161,
-4870,
-3686,
-302,
-1635,
3314,
-2927,
-7398,
4546,
875,
-7082,
-63,
5507,
-640,
4588,
-135,
3207,
7947,
-2406,
1999,
260,
5161,
-179,
3792,
3450,
5479,
-8013,
-7399,
21,
-3413,
-7966,
4820,
-7090,
-3110,
-2621,
5190,
-8120,
-101,
1859,
-2063,
-4943,
6473,
7977,
6910,
-1730,
2659,
657,
-4734,
-3189,
-7972,
-8117,
7992,
5108,
4430,
6607,
-6164,
-6618,
843,
-8085,
-6133,
-7278,
};

#pragma DATA_SECTION (k,".coeffs")
DATA k[NK] ={
0,
12496,
1170,
11768,
2300,
10088,
7725,
8362,
5653,
1389,
4191,
8611,
2303,
1974,
8237,
};

DATA rtest[] ={
4757,
-5037,
-1214,
-4470,
-1822,
6546,
7931,
-6055,
300,
-8554,
-1331,
3356,
9076,
-9919,
14516,
-6193,
2603,
-4551,
73,
-6713,
8325,
-7076,
10863,
-12106,
8947,
-1360,
9635,
-7019,
-5998,
-2114,
470,
-1746,
11947,
-3208,
4950,
-540,
3127,
-3473,
-7710,
141,
-3920,
11373,
-3602,
5499,
-6624,
10190,
-17808,
16002,
-5408,
7161,
-11676,
531,
2469,
9872,
-14291,
-608,
9620,
5515,
-5722,
-2465,
-8033,
-31,
12326,
1664,
-9823,
4483,
-3227,
4438,
-1778,
1225,
1038,
2233,
-9866,
-5394,
9674,
10044,
-9746,
-2773,
-4295,
3397,
-743,
1544,
10330,
2838,
-1149,
-9113,
297,
793,
-10607,
5397,
10352,
-5359,
5920,
-13324,
14866,
-10576,
-2107,
3020,
3261,
5272,
-13161,
9521,
938,
4231,
-2834,
61,
-1667,
4764,
-5832,
3953,
-4038,
-4392,
3444,
5602,
1019,
321,
-6611,
1244,
-1426,
7585,
-1220,
-5127,
3287,
-7228,
5667,
-5600,
13581,
-2117,
-380,
1022,
-6705,
-8949,
11559,
-450,
4412,
2087,
-10819,
-2977,
10854,
-8692,
3551,
2434,
7225,
-2247,
-7106,
-3421,
6233,
-7631,
7294,
2070,
1404,
-9449,
2140,
3786,
8098,
-6971,
-1579,
-8243,
9050,
-5856,
-1511,
-1444,
16313,
-11242,
12713,
-6471,
8253,
-10091,
-9711,
-4110,
9725,
-1086,
5448,
-2689,
14610,
-13616,
-6715,
5536,
10088,
-7992,
-4357,
4553,
-407,
-8641,
10123,
-2283,
164,
-5499,
9170,
2143,
8393,
-8452,
-1724,
-402,
3522,
-17908,
2938,
11046,
6253,
-5616,
-2074,
583,
-4337,
2464,
-385,
4972,
-3497,
7018,
-8099,
2876,
-568,
2191,
-2479,
-5011,
-4846,
8959,
7520,
-3888,
1394,
-9041,
-4162,
2961,
11398,
1059,
3294,
-12471,
3691,
-9726,
10910,
-12782,
7512,
1515,
-707,
2589,
-3422,
8959,
-8008,
1884,
2480,
-4154,
2427,
-10699,
8586,
-395,
9589,
-15290,
-311,
7607,
4617,
1700,
-3650,
-2928,
-2294,
-2685,
-1783,
9909,
4920,
2821,
-4180,
3187,
-6159,
-6401,
-3165,
-207,
-1140,
6576,
8894,
-3858,
-2547,
-3536,
1949,
-3508,
12196,
-10339,
8927,
-1310,
-7838,
-10109,
6158,
6991,
-5250,
7705,
1293,
2523,
-3583,
-1716,
-1205,
7797,
-1063,
-576,
-11765,
12148,
-3773,
-7837,
-979,
2519,
8749,
-4289,
11755,
-14860,
5486,
-11552,
9095,
1702,
1240,
-5473,
707,
-4401,
9178,
266,
4726,
-13706,
7628,
-6700,
5204,
4032,
-1866,
-3822,
6643,
1632,
-5287,
-4373,
8269,
-8457,
8843,
-1207,
5242,
-12934,
10149,
-7195,
-3214,
-2282,
613,
11683,
7122,
-2182,
-2862,
-1556,
-4362,
-7854,
-1889,
3480,
4460,
3409,
3811,
-4263,
-6153,
6279,
-409,
-5539,
3096,
6248,
-4196,
3025,
-6163,
3215,
5545,
-5815,
-832,
1308,
6643,
-8400,
4874,
263,
3774,
-14410,
-1852,
3658,
5782,
-7350,
12067,
-7907,
4871,
-7676,
10356,
-13603,
9387,
-3554,
1585,
-6061,
12393,
-806,
5990,
-11989,
2236,
-4426,
-1148,
-4405,
-1250,
2318,
15891,
1902,
1166,
-1878,
-13545,
-8376,
4786,
-2847,
1629,
1366,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NK];
DATA *dp = dbuffer;

DATA r[NX];

