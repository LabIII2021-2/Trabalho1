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

/* Test for maxval: rand */
#define NX 200
#define FNAME "t7"
#define MAXERROR 40

DATA x[NX] ={
21497,
27365,
-25358,
20455,
26755,
-22520,
-24765,
17214,
14535,
9937,
16647,
10692,
25132,
-14932,
-5281,
-18810,
-30435,
-27449,
22974,
-10473,
-2219,
27116,
-17788,
23726,
10264,
25636,
-778,
32286,
-8302,
2056,
-20886,
127,
-5100,
10513,
11380,
29971,
-20194,
-25480,
4263,
30747,
-31212,
24262,
-31007,
1279,
-20166,
14135,
-16340,
28433,
-23778,
1417,
25899,
28992,
-10808,
-4105,
-1891,
-22983,
-23864,
2129,
14797,
-6639,
-9279,
-14072,
24158,
8284,
-16963,
31331,
9207,
-17705,
11883,
10867,
-23940,
-31294,
-15585,
-25133,
-28226,
23129,
-20950,
-30644,
15330,
2393,
-14679,
-8621,
-31924,
25507,
23987,
-16106,
4553,
-22331,
6184,
-11070,
10394,
23831,
4431,
31488,
19125,
-22768,
21825,
-20195,
9108,
11075,
17831,
-7877,
-3829,
-1111,
7084,
-21234,
-32636,
19020,
891,
-18794,
-25989,
-22457,
-6062,
-6046,
-29315,
28954,
-22940,
-7578,
-12383,
-21723,
25994,
-11618,
15335,
-5839,
-6568,
361,
-21673,
1621,
9253,
-31707,
22075,
19887,
12962,
-2498,
-27354,
21018,
-20119,
-3582,
-31919,
-12535,
24598,
21971,
-10939,
24949,
-1332,
3985,
7596,
10610,
7643,
12133,
665,
14022,
996,
6938,
30585,
21110,
-11944,
5747,
-24236,
-16099,
19859,
10999,
-31875,
4035,
-2978,
26538,
-14277,
-28506,
-1535,
31700,
27679,
4010,
9982,
17870,
-25810,
-32698,
2737,
-32319,
-3190,
-19946,
18818,
7770,
-31751,
25615,
17150,
26675,
16945,
-7817,
-11069,
267,
4231,
17511,
18341,
-1043,
19805,
-1900,
-19480,
5217,
10911,
11584,
};

DATA rtest[NX] ={
19025,
22799,
-21581,
18286,
22437,
-19731,
-21207,
15850,
13681,
9648,
15403,
10335,
21439,
-14011,
-5236,
-17076,
-24527,
-22849,
20037,
-10137,
-2215,
22652,
-16297,
20536,
9946,
21754,
-777,
25493,
-8131,
2053,
-18594,
127,
-5059,
10173,
10953,
24276,
-18098,
-21657,
4239,
24693,
-24940,
20884,
-24832,
1279,
-18078,
13345,
-15158,
23419,
-20569,
1416,
21917,
23735,
-10440,
-4084,
-1889,
-20043,
-20626,
2126,
13899,
-6550,
-9042,
-13292,
20817,
8114,
-15653,
25001,
8976,
-16233,
11400,
10493,
-20675,
-24983,
-14547,
-21440,
-23300,
20140,
-18640,
-24639,
14339,
2388,
-13800,
-8430,
-25309,
21674,
20706,
-14970,
4524,
-19602,
6112,
-10675,
10065,
20604,
4405,
25083,
17312,
-19898,
19253,
-18098,
8884,
10680,
16330,
-7730,
-3811,
-1110,
6977,
-18841,
-25670,
17233,
891,
-17064,
-21972,
-19688,
-5994,
-5979,
-23916,
23714,
-20014,
-7447,
-11839,
-19183,
21975,
-11165,
14343,
-5779,
-6482,
361,
-19148,
1620,
9018,
-25197,
19426,
17874,
12343,
-2493,
-22794,
18688,
-18043,
-3568,
-25306,
-11972,
21100,
19354,
-10558,
21324,
-1331,
3966,
7464,
10261,
7509,
11620,
665,
13249,
996,
6837,
24607,
18753,
-11454,
5689,
-20867,
-14964,
17854,
10612,
-25284,
4015,
-2970,
22306,
-13464,
-23461,
-1533,
25193,
22983,
3990,
9690,
16360,
-21862,
-25701,
2730,
-25510,
-3180,
-17917,
17081,
7629,
-25220,
21741,
15800,
22389,
15638,
-7674,
-10675,
267,
4208,
16081,
16721,
-1042,
17814,
-1898,
-17576,
5174,
10533,
11135,
};

DATA r[NX];
