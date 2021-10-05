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

/* Test for sqrtv: rand */
#define NX 300
#define FNAME "t5"
#define MAXERROR 20

DATA x[NX] ={
29785,
19537,
10779,
15669,
19568,
5290,
27180,
31330,
19514,
942,
26611,
19992,
22986,
3021,
13922,
12306,
5444,
27300,
27480,
14798,
31345,
4821,
28505,
25212,
14554,
20336,
31184,
20971,
8104,
11557,
6155,
16077,
13411,
15188,
20019,
2332,
10298,
19935,
5735,
20349,
8059,
19246,
16582,
15229,
17741,
30878,
11198,
13166,
10082,
13486,
9369,
12914,
16482,
23657,
10033,
3675,
14525,
15294,
480,
21759,
23726,
9228,
8579,
23215,
25685,
32314,
15510,
29583,
14780,
26362,
27160,
5448,
12907,
17064,
23531,
18651,
15099,
14591,
2875,
14532,
12002,
9913,
27913,
24886,
31121,
18282,
466,
19535,
26745,
32017,
7271,
23058,
17106,
30569,
23375,
7472,
14733,
5642,
31746,
11656,
1607,
24750,
29321,
9376,
8231,
30563,
4292,
30828,
22998,
27776,
6857,
14912,
2656,
27889,
18417,
10462,
12284,
28435,
12195,
2414,
6548,
1621,
18569,
3995,
17108,
3835,
25228,
12289,
26980,
1528,
19592,
31101,
9463,
29125,
3328,
2140,
7677,
30575,
2068,
8657,
32752,
6946,
16331,
9518,
22044,
31391,
25118,
21827,
4290,
3126,
487,
9443,
26762,
32292,
568,
26849,
20353,
18357,
7996,
26935,
8624,
24695,
21615,
7014,
19730,
19822,
21610,
6008,
20858,
5580,
17681,
20427,
22475,
22195,
28731,
422,
10171,
25528,
10069,
30365,
22240,
2435,
2315,
390,
7443,
16916,
15014,
23042,
19086,
16685,
2434,
6331,
12438,
9058,
25260,
10286,
20912,
32327,
16478,
31054,
27132,
30066,
3705,
26611,
29761,
5124,
4001,
24991,
23651,
21352,
24707,
21730,
28950,
8918,
13743,
6979,
1166,
2659,
27871,
11147,
15274,
29942,
7490,
28247,
21516,
29202,
15995,
32527,
12233,
17412,
5941,
16447,
13834,
21640,
22074,
31369,
6287,
3644,
18515,
31757,
778,
28515,
880,
17023,
6301,
23451,
8214,
30600,
4495,
17092,
29333,
30880,
10980,
14331,
15438,
4892,
4452,
17448,
23782,
13064,
11744,
9348,
28463,
20526,
7902,
32049,
20987,
7531,
22325,
21817,
4414,
737,
8591,
3817,
2271,
27948,
5909,
1062,
24049,
17580,
9044,
12073,
422,
29137,
28377,
8331,
18660,
5218,
19476,
10849,
21581,
28299,
18599,
32128,
25946,
5000,
27296,
6286,
20938,
21921,
};

DATA rtest[NX] = {
31241,
25302,
18793,
22659,
25322,
13166,
29843,
32041,
25287,
5555,
29529,
25595,
27444,
9949,
21359,
20081,
13356,
29909,
30008,
22020,
32049,
12569,
30562,
28743,
21838,
25814,
31966,
26214,
16296,
19460,
14202,
22952,
20963,
22309,
25612,
8741,
18369,
25558,
13708,
25822,
16251,
25113,
23310,
22339,
24111,
31809,
19156,
20770,
18176,
21021,
17522,
20571,
23240,
27842,
18132,
10974,
21816,
22387,
3968,
26702,
27882,
17389,
16766,
27581,
29011,
32540,
22544,
31135,
22007,
29391,
29832,
13361,
20565,
23646,
27768,
24721,
22243,
21866,
9706,
21821,
19832,
18023,
30243,
28556,
31934,
24476,
3909,
25300,
29603,
32390,
15436,
27487,
23676,
31649,
27675,
15647,
21972,
13597,
32253,
19543,
7256,
28478,
30996,
17528,
16423,
31646,
11859,
31783,
27451,
30169,
14990,
22105,
9330,
30230,
24566,
18515,
20063,
30525,
19990,
8895,
14648,
7289,
24667,
11441,
23677,
11211,
28752,
20067,
29733,
7076,
25337,
31924,
17609,
30892,
10443,
8374,
15861,
31652,
8233,
16843,
32760,
15087,
23133,
17660,
26876,
32072,
28689,
26744,
11857,
10121,
3995,
17591,
29613,
32529,
4317,
29661,
25825,
24526,
16187,
29708,
16811,
28446,
26613,
15160,
25426,
25486,
26610,
14031,
26143,
13522,
24070,
25872,
27137,
26968,
30683,
3720,
18256,
28922,
18164,
31543,
26995,
8933,
8710,
3579,
15617,
23544,
22180,
27478,
25008,
23382,
8931,
14404,
20189,
17228,
28770,
18359,
26177,
32547,
23237,
31899,
29817,
31388,
11019,
29529,
31228,
12957,
11450,
28616,
27839,
26451,
28453,
26684,
30800,
17094,
21221,
15122,
6182,
9335,
30220,
19112,
22372,
31323,
15666,
30423,
26552,
30933,
22894,
32647,
20021,
23886,
13953,
23215,
21291,
26629,
26894,
32061,
14353,
10927,
24631,
32258,
5049,
30567,
5372,
23618,
14369,
27721,
16406,
31665,
12136,
23666,
31003,
31810,
18968,
21670,
22492,
12661,
12078,
23911,
27916,
20690,
19617,
17501,
30539,
25934,
16092,
32406,
26224,
15709,
27047,
26738,
12027,
4914,
16778,
11185,
8627,
30262,
13915,
5899,
28072,
24001,
17215,
19890,
3719,
30899,
30493,
16522,
24728,
13077,
25262,
18855,
26592,
30451,
24687,
32446,
29158,
12800,
29907,
14353,
26193,
26801,
};

DATA r[NX];
