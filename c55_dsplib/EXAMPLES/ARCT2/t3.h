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

/* Test for atan2: rand */
#define NX 300
#define FNAME "t3"
#define MAXERROR 20

DATA x1[NX] ={
-14029,
-6938,
198,
14548,
-12700,
-25417,
-3717,
-2178,
-31806,
10751,
14684,
-14311,
-15609,
13662,
18603,
31861,
-1747,
26399,
-3207,
19957,
21552,
-21871,
-6953,
1360,
14295,
4534,
-2569,
-3584,
-27017,
-3704,
-8762,
-12941,
23058,
17005,
29475,
3797,
-31835,
6303,
20723,
31266,
-18225,
13348,
1446,
28370,
13982,
-17823,
-3300,
-21483,
30724,
-9456,
-29553,
16734,
25874,
-14015,
-16305,
28360,
-24184,
28889,
13229,
22785,
-19053,
-2943,
-27454,
23011,
4066,
-11842,
-8199,
24104,
-8377,
-27938,
-19671,
-29524,
4372,
-24777,
1449,
-25096,
17689,
-8188,
21193,
-29711,
6417,
29435,
-13841,
25482,
-26110,
-28487,
-17413,
28383,
-28631,
-15452,
32737,
-18875,
-104,
-13730,
11322,
30015,
17469,
10887,
-24186,
-26515,
-31794,
-13881,
20757,
31816,
-31630,
20932,
7939,
3947,
-16775,
21103,
-15518,
16622,
10462,
-18739,
6692,
6877,
10453,
-20751,
8949,
-21606,
2595,
8087,
12182,
11622,
24696,
-31923,
-12425,
18290,
-12629,
27963,
11712,
-27897,
-28136,
-31986,
-17881,
1065,
-2739,
13317,
5406,
603,
-27899,
-20104,
-7890,
-14651,
17752,
-12194,
9057,
31887,
188,
29340,
21497,
27365,
-25357,
20455,
26756,
-22520,
-24765,
17214,
14536,
9938,
16647,
10693,
25132,
-14932,
-5280,
-18809,
-30435,
-27449,
22975,
-10472,
-2218,
27116,
-17788,
23727,
10264,
25636,
-777,
32286,
-8302,
2056,
-20885,
127,
-5099,
10514,
11380,
29971,
-20194,
-25479,
4263,
30747,
-31212,
24262,
-31006,
1280,
-20166,
14135,
-16340,
28433,
-23777,
1417,
25900,
28992,
-10808,
-4105,
-1890,
-22983,
-23864,
2130,
14797,
-6639,
-9279,
-14072,
24159,
8284,
-16962,
31331,
9208,
-17704,
11884,
10867,
-23939,
-31294,
-15584,
-25132,
-28225,
23129,
-20950,
-30643,
15330,
2393,
-14678,
-8621,
-31923,
25507,
23987,
-16106,
4553,
-22330,
6184,
-11069,
10395,
23831,
4432,
31489,
19125,
-22767,
21825,
-20194,
9109,
11075,
17831,
-7876,
-3828,
-1110,
7085,
-21234,
-32635,
19020,
892,
-18794,
-25988,
-22457,
-6061,
-6045,
-29314,
28955,
-22939,
-7578,
-12382,
-21723,
25994,
-11618,
15335,
-5839,
-6567,
362,
-21672,
1622,
9254,
-31706,
22076,
19887,
12962,
-2498,
-27354,
21018,
-20118,
-3581,
-31918,
-12534,
24599,
21971,
-10938,
24950,
-1331,
3986,
7596,
10610,
7644,
12133,
};

DATA x2[NX] ={
665,
14022,
997,
6938,
30586,
21110,
-11944,
5747,
-24235,
-16098,
19859,
11000,
-31875,
4036,
-2978,
26538,
-14276,
-28506,
-1534,
31700,
27679,
4011,
9983,
17870,
-25809,
-32697,
2737,
-32318,
-3189,
-19945,
18818,
7770,
-31751,
25615,
17151,
26675,
16945,
-7816,
-11068,
267,
4232,
17511,
18341,
-1042,
19806,
-1900,
-19480,
5218,
10912,
11584,
29000,
17704,
15558,
24003,
32174,
257,
8460,
19176,
-3365,
1596,
-21530,
-24204,
-18430,
-25855,
-23499,
-2820,
18883,
-14348,
-18036,
26796,
-32287,
5816,
2760,
10061,
-12227,
-17619,
-5501,
-13186,
11301,
28721,
-10279,
4126,
-24976,
-21691,
-14490,
3723,
-944,
29637,
-17569,
-1399,
1738,
19184,
-20119,
26843,
27669,
-31898,
17534,
29317,
20533,
27776,
-19726,
11421,
27990,
-10236,
6193,
7568,
-32547,
31589,
26182,
12632,
-3955,
13174,
7190,
-13115,
23333,
-25423,
-13660,
-26381,
-6721,
-10924,
29113,
22187,
-15832,
-29956,
-32382,
4877,
15984,
20108,
9016,
-16301,
-23310,
9932,
29234,
20702,
28196,
-12456,
-15151,
2389,
-22067,
-18940,
-18559,
9948,
-29309,
-17741,
10973,
-12391,
-12672,
14462,
29780,
-24173,
-28293,
-24561,
-21879,
26962,
-23838,
7667,
-15140,
-18306,
13953,
3211,
28924,
-11150,
13401,
29060,
5347,
24914,
16358,
-7889,
14782,
-22099,
29898,
-19908,
18100,
7425,
-22133,
-30733,
-13852,
30871,
29524,
-17822,
30050,
11787,
-29165,
6543,
-7003,
-18654,
-20814,
-27738,
-32281,
18925,
-31602,
24769,
-9664,
14558,
30700,
-22566,
-22088,
-12229,
-30842,
-9331,
-30986,
19246,
32717,
-25543,
8035,
-24080,
-12450,
-23934,
-18132,
-6780,
-23911,
-16970,
28017,
-7137,
738,
-26680,
-31346,
-22313,
22578,
24848,
-20513,
32198,
13895,
24338,
-1335,
-262,
-13924,
-28774,
-15567,
-20561,
27334,
-24689,
-31887,
-8540,
13018,
25516,
6145,
-22499,
-12013,
-17472,
-32216,
-6756,
9822,
-27197,
17617,
30782,
14077,
18478,
-17199,
-19940,
-15518,
14010,
31300,
8986,
3010,
22810,
19798,
11030,
11205,
21013,
30833,
-857,
20805,
9278,
-12691,
10547,
-9305,
28718,
-808,
-26805,
11392,
975,
-18246,
14746,
-28295,
30417,
-19159,
-22209,
9058,
-32753,
-10772,
-14739,
-29850,
-26614,
-5898,
20768,
24282,
-31290,
14888,
22807,
14981,
29825,
10247,
15880,
-10160,
25167,
-10011,
-28870,
14314,
30029,
};

DATA rtest[] ={
-15890,
-4793,
2041,
11742,
-4105,
-9155,
-29621,
-3779,
-23175,
26626,
6641,
-9549,
-28018,
13388,
18040,
9140,
-31498,
24976,
-21037,
5860,
6901,
-14492,
-6346,
792,
27492,
31331,
-7861,
-31616,
-17610,
-30853,
-4545,
-10744,
26217,
6113,
10887,
1475,
-11282,
25690,
21501,
16295,
-14004,
6794,
820,
16767,
6412,
-17492,
-31018,
-13899,
12825,
-7140,
-8291,
7898,
10737,
-5512,
-4892,
16289,
-12874,
10272,
18982,
15654,
-25212,
-31506,
-22550,
25182,
30981,
-18822,
-4272,
21984,
-28233,
-8410,
-27061,
-14355,
10510,
-12361,
31538,
-22768,
19529,
-26972,
11274,
-8369,
26947,
14931,
-27490,
23739,
-21668,
-15028,
-16949,
7967,
-22125,
-17326,
15831,
-8107,
-32714,
-4932,
4051,
24893,
8173,
3709,
-9042,
-7950,
-22176,
-9203,
6656,
19630,
-14367,
12765,
30273,
1296,
-5943,
10758,
-18987,
9394,
10104,
-22753,
2913,
30012,
25955,
-25816,
23103,
-21267,
927,
3646,
25927,
28908,
25972,
-14803,
-6892,
7698,
-9917,
21889,
27911,
-12816,
-7992,
-10393,
-5895,
31878,
-30902,
14533,
30262,
32436,
-22507,
-11591,
-30025,
-25568,
10610,
-24659,
26296,
11943,
66,
23572,
25991,
24013,
-23809,
6770,
23975,
-12961,
-22107,
24897,
8406,
13124,
5447,
24794,
11274,
-4951,
-8126,
-6745,
-11240,
-19303,
10421,
-28152,
-772,
22989,
-8101,
13221,
28239,
25516,
-32184,
8426,
-2859,
31570,
-6335,
113,
-30963,
10578,
22138,
22191,
-24734,
-25018,
31398,
10629,
-24641,
8084,
-19535,
915,
-6062,
26931,
-26125,
20621,
-25918,
31196,
25506,
10271,
-3328,
-31106,
-2410,
-24819,
-21400,
31842,
25629,
-24686,
-28907,
-25547,
7422,
23801,
-15930,
23741,
29788,
-25772,
5054,
4300,
-23774,
-8043,
-8789,
-8359,
-16877,
16502,
-22503,
-24248,
24656,
31559,
-5140,
-29264,
-24570,
19754,
11198,
-5873,
6651,
-24615,
27809,
-26878,
29513,
19266,
4421,
23815,
8620,
-6642,
10409,
-8654,
27688,
27480,
23854,
-5342,
-1269,
-1282,
12194,
-7819,
-10696,
10903,
828,
-7611,
-7305,
-16782,
-2957,
-6023,
-20645,
12741,
-20403,
-2691,
-17064,
-25664,
12076,
-15511,
25478,
-3932,
-30389,
124,
-23935,
32008,
8303,
-24745,
21119,
23036,
28495,
-31792,
-18599,
8255,
-7217,
-31579,
-11832,
-5241,
10678,
6622,
-8532,
10472,
-31409,
1638,
25998,
29094,
5116,
4005,
};

DATA r[NX];

