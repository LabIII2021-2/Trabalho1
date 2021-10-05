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

/* Test for mtrans: nois */
#define row 20
#define col 32
#define FNAME "t2"
#define MAXERROR 0

DATA x[row*col] ={
14748,
-14486,
11078,
-113,
9660,
2713,
-2773,
6007,
3556,
-12416,
-1973,
-11893,
-6638,
-10030,
7095,
-4577,
7623,
5570,
10226,
-10227,
-7014,
10775,
-9112,
-9526,
3208,
-15895,
1298,
-13948,
8323,
-10442,
12949,
-11968,
-8809,
-4821,
-15739,
13098,
14968,
-2507,
-6389,
-9418,
-15866,
-1614,
-5241,
10444,
-14772,
13264,
371,
1590,
-2548,
-9801,
3608,
-307,
-3469,
-10935,
6674,
-1471,
14716,
-6940,
4043,
-10051,
5346,
64,
14495,
-15645,
3501,
10261,
5939,
10538,
740,
508,
12266,
11115,
-15846,
7073,
-6087,
-2288,
6330,
2268,
9056,
-7806,
15117,
-7435,
6602,
-2973,
99,
-3476,
723,
-13726,
-6920,
10378,
6091,
-3945,
12565,
-2549,
-5403,
-7791,
-459,
-16059,
-3949,
4748,
12455,
-5441,
-15891,
4220,
-10155,
12871,
-4421,
12789,
4918,
4318,
-349,
3189,
-14021,
4136,
-13362,
-1195,
7273,
680,
14184,
11504,
12740,
15907,
5811,
-7325,
-7465,
5256,
-2052,
-12565,
12821,
-11832,
10871,
10418,
-10716,
-2198,
8779,
-11999,
2848,
-7434,
-3498,
7697,
15825,
-8702,
-10291,
-14768,
1750,
1207,
-2461,
3635,
-6350,
7147,
6990,
2033,
-13054,
-15813,
12347,
8875,
-2640,
5690,
-945,
-14111,
8588,
-9739,
92,
5250,
15719,
-8979,
15427,
-9596,
-14496,
-8035,
2999,
6138,
1726,
1598,
6574,
2328,
-6816,
-14433,
-4077,
-14051,
-12707,
2267,
-8911,
-5921,
-14242,
10465,
-15960,
-6097,
-9404,
14984,
-11490,
11564,
-1426,
-9871,
6863,
-5178,
-7488,
2615,
16057,
3512,
-4339,
11979,
-12459,
-5042,
-3274,
14141,
15816,
6581,
11729,
-13468,
-10938,
-6085,
-1858,
-1284,
-1650,
-4099,
-8706,
3969,
-6212,
4528,
-15216,
-10096,
-11931,
-10474,
-15776,
3401,
-2330,
-6890,
-8115,
8531,
9464,
4256,
4307,
-8769,
-15133,
-10942,
-9869,
-5400,
10047,
15147,
-5381,
-7493,
10916,
3551,
-1089,
-1792,
-10740,
12051,
14190,
1973,
9144,
15942,
-13723,
-12738,
1065,
-15320,
10531,
-7464,
-6402,
-5203,
12311,
977,
-2010,
-4244,
7131,
9989,
-1357,
-11284,
4102,
5096,
6670,
8208,
5904,
-2979,
11095,
-10648,
-15902,
-13507,
15361,
-4188,
-14314,
-8387,
-6314,
94,
11486,
2131,
7398,
7665,
-1812,
-9868,
-10168,
1117,
7775,
4604,
-55,
2462,
6313,
13381,
12119,
-10120,
7646,
-3542,
-493,
7863,
-14631,
-851,
-1585,
3965,
5375,
-1852,
-4727,
-13968,
-7725,
10550,
13980,
14669,
-5236,
15372,
-3319,
1196,
3782,
-15882,
-10045,
7441,
-11909,
-9532,
-9372,
-1592,
-13628,
-8784,
14228,
-2541,
-4067,
4171,
-12627,
-2232,
-4697,
13400,
14960,
-8324,
7341,
-4381,
-14775,
-9835,
16367,
-7758,
5856,
10748,
-1109,
-15604,
-4639,
-7338,
9565,
8086,
5970,
-6249,
-15997,
-3938,
4701,
-14944,
-1496,
-8541,
-7718,
11663,
-16059,
6523,
5401,
4399,
-56,
3154,
-11561,
2862,
-7155,
-6470,
8366,
-14761,
-9437,
8310,
-13947,
13681,
13557,
12130,
-7035,
-4310,
13821,
-1799,
-6462,
11091,
12906,
9283,
-5896,
-15492,
-1906,
-14752,
-11130,
-319,
-2626,
-3369,
-4411,
9929,
-2148,
-5604,
12121,
198,
-7804,
11528,
12936,
2186,
-52,
5231,
-14067,
-12677,
-8893,
-15502,
12078,
-15960,
7805,
14148,
1365,
2230,
-9858,
5925,
15075,
-6137,
-4808,
-13814,
12216,
10352,
8311,
-2830,
-11794,
-13634,
2046,
-714,
8828,
-1154,
6831,
8502,
-7007,
-12388,
-6865,
-9369,
-15991,
10227,
11862,
640,
4142,
12752,
-10607,
-1114,
-11439,
-4246,
-6595,
-1275,
7426,
-15961,
-11349,
4614,
-8588,
-1285,
9629,
5086,
2188,
14595,
3821,
3184,
-1830,
1357,
9301,
14736,
-8152,
724,
5660,
3346,
-8940,
13377,
5132,
-10082,
-8480,
11993,
-3090,
-2665,
6484,
6643,
5290,
2222,
-2885,
-3802,
5755,
-10128,
4778,
-1397,
13760,
11061,
10583,
13628,
-12669,
-11093,
3952,
14493,
15929,
1898,
14178,
-12547,
15006,
3438,
532,
-11259,
12817,
7067,
15664,
-8052,
14268,
11344,
-3985,
1526,
-7064,
9640,
8013,
6000,
6527,
11267,
15297,
-1616,
11295,
-4207,
5699,
3342,
13049,
10795,
14799,
-5185,
-873,
-15916,
-12091,
8844,
8733,
5226,
-1369,
-12381,
-388,
-8169,
4603,
2277,
13660,
824,
11796,
-1806,
-1008,
-14443,
-7603,
-13340,
7454,
-10685,
5404,
-2876,
-4333,
-2449,
16364,
-8075,
8340,
14945,
4587,
-3217,
13198,
3151,
14443,
-4094,
5443,
-10375,
6658,
8606,
16141,
14215,
-8851,
-11164,
-2940,
-9743,
11587,
6375,
-14260,
3370,
-1968,
-15225,
-708,
-10786,
12135,
13159,
3958,
3102,
15125,
12236,
9539,
3131,
-8279,
-6301,
-1604,
10360,
6614,
10596,
-12092,
4474,
2703,
7267,
-4150,
-11887,
5941,
3092,
12898,
5640,
3066,
3975,
16000,
-14735,
14200,
3683,
1797,
16195,
-16057,
-16199,
7578,
2154,
-14454,
439,
10319,
-15440,
-4826,
-2897,
9977,
15632,
11392,
-14854,
-13256,
-10802,
302,
4968,
1028,
708,
5433,
-5534,
};

DATA rtest[] ={
14748,
-8809,
3501,
-459,
12821,
8588,
-1426,
-15776,
10531,
-1812,
3782,
9565,
13821,
7805,
-10607,
-3090,
14268,
13660,
-2940,
12898,
-14486,
-4821,
10261,
-16059,
-11832,
-9739,
-9871,
3401,
-7464,
-9868,
-15882,
8086,
-1799,
14148,
-1114,
-2665,
11344,
824,
-9743,
5640,
11078,
-15739,
5939,
-3949,
10871,
92,
6863,
-2330,
-6402,
-10168,
-10045,
5970,
-6462,
1365,
-11439,
6484,
-3985,
11796,
11587,
3066,
-113,
13098,
10538,
4748,
10418,
5250,
-5178,
-6890,
-5203,
1117,
7441,
-6249,
11091,
2230,
-4246,
6643,
1526,
-1806,
6375,
3975,
9660,
14968,
740,
12455,
-10716,
15719,
-7488,
-8115,
12311,
7775,
-11909,
-15997,
12906,
-9858,
-6595,
5290,
-7064,
-1008,
-14260,
16000,
2713,
-2507,
508,
-5441,
-2198,
-8979,
2615,
8531,
977,
4604,
-9532,
-3938,
9283,
5925,
-1275,
2222,
9640,
-14443,
3370,
-14735,
-2773,
-6389,
12266,
-15891,
8779,
15427,
16057,
9464,
-2010,
-55,
-9372,
4701,
-5896,
15075,
7426,
-2885,
8013,
-7603,
-1968,
14200,
6007,
-9418,
11115,
4220,
-11999,
-9596,
3512,
4256,
-4244,
2462,
-1592,
-14944,
-15492,
-6137,
-15961,
-3802,
6000,
-13340,
-15225,
3683,
3556,
-15866,
-15846,
-10155,
2848,
-14496,
-4339,
4307,
7131,
6313,
-13628,
-1496,
-1906,
-4808,
-11349,
5755,
6527,
7454,
-708,
1797,
-12416,
-1614,
7073,
12871,
-7434,
-8035,
11979,
-8769,
9989,
13381,
-8784,
-8541,
-14752,
-13814,
4614,
-10128,
11267,
-10685,
-10786,
16195,
-1973,
-5241,
-6087,
-4421,
-3498,
2999,
-12459,
-15133,
-1357,
12119,
14228,
-7718,
-11130,
12216,
-8588,
4778,
15297,
5404,
12135,
-16057,
-11893,
10444,
-2288,
12789,
7697,
6138,
-5042,
-10942,
-11284,
-10120,
-2541,
11663,
-319,
10352,
-1285,
-1397,
-1616,
-2876,
13159,
-16199,
-6638,
-14772,
6330,
4918,
15825,
1726,
-3274,
-9869,
4102,
7646,
-4067,
-16059,
-2626,
8311,
9629,
13760,
11295,
-4333,
3958,
7578,
-10030,
13264,
2268,
4318,
-8702,
1598,
14141,
-5400,
5096,
-3542,
4171,
6523,
-3369,
-2830,
5086,
11061,
-4207,
-2449,
3102,
2154,
7095,
371,
9056,
-349,
-10291,
6574,
15816,
10047,
6670,
-493,
-12627,
5401,
-4411,
-11794,
2188,
10583,
5699,
16364,
15125,
-14454,
-4577,
1590,
-7806,
3189,
-14768,
2328,
6581,
15147,
8208,
7863,
-2232,
4399,
9929,
-13634,
14595,
13628,
3342,
-8075,
12236,
439,
7623,
-2548,
15117,
-14021,
1750,
-6816,
11729,
-5381,
5904,
-14631,
-4697,
-56,
-2148,
2046,
3821,
-12669,
13049,
8340,
9539,
10319,
5570,
-9801,
-7435,
4136,
1207,
-14433,
-13468,
-7493,
-2979,
-851,
13400,
3154,
-5604,
-714,
3184,
-11093,
10795,
14945,
3131,
-15440,
10226,
3608,
6602,
-13362,
-2461,
-4077,
-10938,
10916,
11095,
-1585,
14960,
-11561,
12121,
8828,
-1830,
3952,
14799,
4587,
-8279,
-4826,
-10227,
-307,
-2973,
-1195,
3635,
-14051,
-6085,
3551,
-10648,
3965,
-8324,
2862,
198,
-1154,
1357,
14493,
-5185,
-3217,
-6301,
-2897,
-7014,
-3469,
99,
7273,
-6350,
-12707,
-1858,
-1089,
-15902,
5375,
7341,
-7155,
-7804,
6831,
9301,
15929,
-873,
13198,
-1604,
9977,
10775,
-10935,
-3476,
680,
7147,
2267,
-1284,
-1792,
-13507,
-1852,
-4381,
-6470,
11528,
8502,
14736,
1898,
-15916,
3151,
10360,
15632,
-9112,
6674,
723,
14184,
6990,
-8911,
-1650,
-10740,
15361,
-4727,
-14775,
8366,
12936,
-7007,
-8152,
14178,
-12091,
14443,
6614,
11392,
-9526,
-1471,
-13726,
11504,
2033,
-5921,
-4099,
12051,
-4188,
-13968,
-9835,
-14761,
2186,
-12388,
724,
-12547,
8844,
-4094,
10596,
-14854,
3208,
14716,
-6920,
12740,
-13054,
-14242,
-8706,
14190,
-14314,
-7725,
16367,
-9437,
-52,
-6865,
5660,
15006,
8733,
5443,
-12092,
-13256,
-15895,
-6940,
10378,
15907,
-15813,
10465,
3969,
1973,
-8387,
10550,
-7758,
8310,
5231,
-9369,
3346,
3438,
5226,
-10375,
4474,
-10802,
1298,
4043,
6091,
5811,
12347,
-15960,
-6212,
9144,
-6314,
13980,
5856,
-13947,
-14067,
-15991,
-8940,
532,
-1369,
6658,
2703,
302,
-13948,
-10051,
-3945,
-7325,
8875,
-6097,
4528,
15942,
94,
14669,
10748,
13681,
-12677,
10227,
13377,
-11259,
-12381,
8606,
7267,
4968,
8323,
5346,
12565,
-7465,
-2640,
-9404,
-15216,
-13723,
11486,
-5236,
-1109,
13557,
-8893,
11862,
5132,
12817,
-388,
16141,
-4150,
1028,
-10442,
64,
-2549,
5256,
5690,
14984,
-10096,
-12738,
2131,
15372,
-15604,
12130,
-15502,
640,
-10082,
7067,
-8169,
14215,
-11887,
708,
12949,
14495,
-5403,
-2052,
-945,
-11490,
-11931,
1065,
7398,
-3319,
-4639,
-7035,
12078,
4142,
-8480,
15664,
4603,
-8851,
5941,
5433,
-11968,
-15645,
-7791,
-12565,
-14111,
11564,
-10474,
-15320,
7665,
1196,
-7338,
-4310,
-15960,
12752,
11993,
-8052,
2277,
-11164,
3092,
-5534,
};

DATA r[row*col];

