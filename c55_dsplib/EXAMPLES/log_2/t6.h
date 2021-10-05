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

/* Test for logn: rand */
#define NX 500
#define FNAME "t6"
#define MAXERROR 100

DATA x[NX] ={
21878,
26179,
15928,
21195,
2445,
8462,
27275,
23346,
21092,
6337,
15875,
9421,
13758,
23653,
10983,
10081,
31163,
9574,
12713,
14801,
13919,
12561,
2472,
9897,
22904,
21196,
20691,
24789,
1300,
10874,
10168,
17777,
27978,
15464,
6612,
25639,
15205,
14202,
16232,
9094,
10272,
10063,
24900,
10290,
24163,
16478,
7601,
27299,
19488,
11949,
2834,
18420,
23531,
25630,
11206,
8361,
25827,
23896,
24133,
9065,
13240,
16820,
9809,
18371,
23008,
16041,
30127,
17008,
14360,
23995,
13645,
13363,
18471,
15670,
13924,
14029,
18122,
5595,
6835,
19214,
6113,
16703,
6058,
24602,
15220,
15554,
6011,
15840,
20419,
9986,
13622,
23773,
12488,
14358,
24701,
28833,
15817,
31780,
29956,
18632,
25256,
30283,
5694,
8976,
4079,
15424,
8220,
22939,
833,
11912,
6029,
19452,
26613,
8774,
18332,
13681,
5093,
12828,
18599,
17760,
17027,
25446,
12604,
24891,
23099,
24120,
22529,
24904,
25205,
22541,
6891,
21240,
6169,
18096,
12040,
28344,
2148,
21512,
10302,
11284,
9277,
11200,
21389,
15782,
13560,
23375,
21482,
13129,
12713,
14890,
11547,
11344,
16238,
25221,
19817,
15302,
28512,
21674,
7138,
9245,
15481,
22899,
21151,
11517,
18296,
29727,
8120,
15459,
21851,
18158,
9322,
27191,
14373,
20006,
8141,
14077,
14858,
17803,
543,
28683,
15108,
21240,
9677,
21285,
5390,
9030,
14816,
17204,
18847,
15323,
29627,
18764,
22839,
15118,
12621,
12060,
14187,
13752,
4800,
20322,
17235,
21656,
18326,
12930,
6634,
16730,
8393,
13337,
4073,
16976,
16345,
15612,
4397,
16846,
18123,
11335,
12259,
12672,
9530,
23736,
14706,
8545,
11449,
11241,
4365,
9250,
8162,
4913,
29847,
14290,
16988,
26979,
11443,
14075,
21710,
11093,
18244,
11896,
25511,
20092,
18599,
15544,
13730,
6278,
16036,
15025,
7763,
8746,
13613,
13290,
15644,
17084,
19343,
20533,
18055,
16622,
21667,
31915,
20715,
15966,
20303,
19820,
20262,
17761,
14219,
25441,
25618,
16261,
19958,
7824,
18042,
11194,
14338,
11602,
24611,
8563,
12245,
15477,
27492,
22296,
12461,
19280,
14150,
24155,
15783,
28757,
21157,
29732,
11964,
22662,
6303,
30813,
7876,
10036,
21178,
18413,
25831,
23959,
14282,
14656,
19566,
18536,
20046,
25349,
10252,
18950,
4801,
20930,
21542,
28783,
14977,
20709,
7815,
5494,
24590,
25256,
20783,
15155,
12898,
12364,
8892,
17460,
1925,
17044,
20602,
21765,
21847,
24671,
13199,
15325,
13226,
23093,
7878,
9345,
20395,
30105,
19797,
16923,
16471,
17535,
7600,
22309,
9897,
25985,
27965,
21321,
29216,
18970,
12773,
18035,
27678,
21466,
29574,
16048,
21666,
6619,
31797,
26238,
13633,
11317,
6905,
16531,
21369,
8866,
14331,
29620,
22208,
12364,
16138,
15906,
11888,
22535,
30299,
12823,
24064,
10741,
20305,
8576,
20637,
26732,
18150,
4423,
14526,
18190,
19045,
9875,
14832,
2117,
6924,
18830,
13723,
30488,
26468,
16158,
24438,
14523,
23600,
18151,
16809,
17575,
9327,
24407,
9082,
21924,
14431,
8111,
14991,
15724,
23627,
1386,
28751,
22612,
15072,
21697,
15164,
18678,
28268,
27382,
29437,
23797,
6890,
16211,
27254,
15695,
12872,
4645,
8126,
20326,
28028,
24656,
7253,
14242,
18513,
22996,
7396,
24524,
13455,
10115,
15849,
20160,
11443,
21095,
22550,
13645,
18453,
7450,
10399,
20176,
14041,
16584,
23254,
25457,
28747,
7223,
16112,
20315,
11112,
18926,
14687,
12709,
12978,
13053,
21559,
24065,
12257,
15736,
3788,
21551,
9348,
10033,
16597,
22947,
6921,
17428,
22077,
26069,
24689,
15656,
11382,
10051,
19233,
15848,
14729,
28878,
6948,
10696,
13988,
16498,
16932,
20719,
27608,
22404,
14027,
22444,
22451,
13453,
11246,
15566,
20692,
27484,
};

long rtest[] ={
-19097,
-10613,
-34103,
-20597,
-122690,
-64004,
-8673,
-16028,
-20826,
-77671,
-34260,
-58928,
-41027,
-15410,
-51676,
-55728,
-2375,
-58166,
-44762,
-37572,
-40478,
-45329,
-122182,
-56597,
-16931,
-20595,
-21734,
-13193,
-152554,
-52146,
-55321,
-28911,
-7470,
-35501,
-75667,
-11599,
-36299,
-39523,
-33207,
-60598,
-54839,
-55810,
-12981,
-54757,
-14401,
-32496,
-69079,
-8633,
-24567,
-47691,
-115708,
-27231,
-15653,
-11614,
-50727,
-64570,
-11254,
-14926,
-14461,
-60748,
-42842,
-31526,
-57020,
-27356,
-16717,
-33767,
-3973,
-31001,
-39002,
-14731,
-41417,
-42404,
-27100,
-34874,
-40459,
-40105,
-28001,
-83562,
-74098,
-25235,
-79377,
-31856,
-79799,
-13549,
-36252,
-35225,
-80169,
-34365,
-22359,
-56173,
-41497,
-15171,
-45605,
-39009,
-13359,
-6048,
-34434,
-1448,
-4241,
-26690,
-12310,
-3728,
-82730,
-61214,
-98501,
-35621,
-65373,
-16859,
-173574,
-47839,
-80029,
-24654,
-9836,
-62291,
-27458,
-41290,
-88004,
-44335,
-26773,
-28956,
-30948,
-11955,
-45168,
-12998,
-16529,
-14484,
-17712,
-12973,
-12404,
-17685,
-73712,
-20496,
-78945,
-28070,
-47333,
-6857,
-128813,
-19894,
-54702,
-50398,
-59657,
-50749,
-20167,
-34539,
-41712,
-15969,
-19962,
-43237,
-44762,
-37287,
-49308,
-50145,
-33191,
-12376,
-23775,
-35998,
-6578,
-19539,
-72049,
-59821,
-35447,
-16942,
-20695,
-49431,
-27550,
-4604,
-65955,
-35516,
-19156,
-27907,
-59428,
-8820,
-38959,
-23326,
-65831,
-39944,
-37389,
-28841,
-193794,
-6295,
-36602,
-20497,
-57660,
-20395,
-85329,
-60930,
-37522,
-30459,
-26147,
-35933,
-4764,
-26355,
-17065,
-36570,
-45104,
-47253,
-39574,
-41047,
-90802,
-22584,
-30374,
-19580,
-27473,
-43960,
-75509,
-31779,
-64390,
-42497,
-98566,
-31090,
-32880,
-35050,
-94953,
-31453,
-28000,
-50185,
-46482,
-44913,
-58386,
-15245,
-37876,
-63543,
-49712,
-50576,
-95297,
-59795,
-65707,
-89705,
-4414,
-39233,
-31057,
-9189,
-49736,
-39949,
-19463,
-51205,
-27686,
-47901,
-11834,
-23124,
-26773,
-35255,
-41124,
-78114,
-33782,
-36863,
-68076,
-62441,
-41526,
-42664,
-34954,
-30790,
-24919,
-22097,
-28178,
-32086,
-19555,
-1247,
-21680,
-33989,
-22628,
-23767,
-22725,
-28953,
-39469,
-11965,
-11636,
-33125,
-23440,
-67711,
-28210,
-50777,
-39075,
-49083,
-13532,
-63441,
-46533,
-35461,
-8300,
-18202,
-45706,
-25074,
-39696,
-14417,
-34534,
-6172,
-20681,
-4597,
-47630,
-17434,
-77927,
-2908,
-67397,
-55939,
-20635,
-27249,
-11245,
-14802,
-39258,
-38038,
-24377,
-26935,
-23233,
-12137,
-54930,
-25890,
-90792,
-21192,
-19828,
-6130,
-37013,
-21693,
-67765,
-84421,
-13572,
-12310,
-21525,
-36453,
-44078,
-46078,
-61662,
-29761,
-134001,
-30900,
-21939,
-19342,
-19163,
-13418,
-42988,
-35928,
-42889,
-16542,
-67386,
-59312,
-22416,
-4006,
-23823,
-31238,
-32517,
-29558,
-69080,
-18176,
-56595,
-10965,
-7493,
-20317,
-5425,
-25840,
-44537,
-28230,
-7981,
-19996,
-4848,
-33747,
-19558,
-75616,
-1422,
-10507,
-41457,
-50261,
-73615,
-32346,
-20210,
-61798,
-39098,
-4776,
-18389,
-46077,
-33482,
-34167,
-47933,
-17700,
-3704,
-44354,
-14594,
-52727,
-22625,
-63370,
-21858,
-9625,
-27928,
-94673,
-38457,
-27824,
-25652,
-56705,
-37471,
-129516,
-73483,
-26190,
-41146,
-3410,
-10094,
-33424,
-13865,
-38466,
-15515,
-27926,
-31558,
-29452,
-59404,
-13925,
-60662,
-18998,
-38770,
-66007,
-36969,
-34711,
-15461,
-149519,
-6182,
-17538,
-36713,
-19491,
-36425,
-26573,
-6984,
-8488,
-5067,
-15123,
-73716,
-33271,
-8710,
-34798,
-44173,
-92357,
-65921,
-22576,
-7387,
-13446,
-71293,
-39393,
-26993,
-16742,
-70366,
-13701,
-42079,
-55566,
-34337,
-22965,
-49735,
-20821,
-17667,
-41417,
-27145,
-70025,
-54257,
-22925,
-40063,
-32194,
-16214,
-11936,
-6189,
-71489,
-33560,
-22601,
-51123,
-25950,
-37936,
-44776,
-43786,
-43513,
-19791,
-14594,
-46486,
-34676,
-102003,
-19810,
-59295,
-55955,
-32158,
-16842,
-73503,
-29848,
-18668,
-10811,
-13384,
-34918,
-49987,
-55869,
-25188,
-34341,
-37801,
-5974,
-73319,
-52929,
-40241,
-32441,
-31211,
-21671,
-8101,
-17975,
-40112,
-17889,
-17875,
-42086,
-50555,
-35190,
-21733,
-8313,
};

long r[NX];
