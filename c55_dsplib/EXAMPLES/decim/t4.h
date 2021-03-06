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

/* Test for decimate: sine */
#define NX 500
#define NH 31
#define D 20
#define FNAME "t4"
#define MAXERROR 100

DATA x[NX] ={
0,
2326,
4605,
6791,
8839,
10709,
12361,
13762,
14885,
15706,
16209,
16383,
16226,
15739,
14934,
13825,
12437,
10797,
8938,
6897,
4717,
2441,
116,
-2211,
-4494,
-6686,
-8742,
-10621,
-12285,
-13700,
-14837,
-15674,
-16193,
-16384,
-16242,
-15772,
-14982,
-13889,
-12514,
-10885,
-9036,
-7004,
-4830,
-2558,
-234,
2095,
4381,
6578,
8642,
10531,
12206,
13634,
14786,
15638,
16173,
16381,
16256,
15802,
15028,
13949,
12588,
10971,
9132,
7108,
4940,
2672,
350,
-1980,
-4269,
-6472,
-8544,
-10442,
-12129,
-13570,
-14737,
-15604,
-16155,
-16379,
-16271,
-15834,
-15075,
-14011,
-12663,
-11059,
-9230,
-7214,
-5052,
-2788,
-467,
1863,
4155,
6364,
8443,
10351,
12049,
13504,
14684,
15567,
16135,
16375,
16284,
15862,
15120,
14070,
12736,
11143,
9325,
7318,
5162,
2902,
583,
-1748,
-4043,
-6257,
-8344,
-10261,
-11971,
-13438,
-14633,
-15531,
-16115,
-16372,
-16297,
-15892,
-15165,
-14131,
-12810,
-11230,
-9422,
-7423,
-5274,
-3018,
-701,
1631,
3929,
6148,
8242,
10169,
11890,
13370,
14579,
15493,
16092,
16366,
16308,
15919,
15208,
14188,
12881,
11313,
9516,
7526,
5383,
3131,
816,
-1516,
-3817,
-6041,
-8142,
-10078,
-11810,
-13303,
-14527,
-15455,
-16071,
-16361,
-16320,
-15947,
-15252,
-14247,
-12954,
-11399,
-9612,
-7630,
-5494,
-3247,
-934,
1398,
3702,
5931,
8039,
9985,
11728,
13234,
14471,
15415,
16047,
16353,
16329,
15973,
15293,
14304,
13024,
11481,
9705,
7733,
5603,
3360,
1049,
-1283,
-3589,
-5823,
-7939,
-9893,
-11647,
-13166,
-14417,
-15376,
-16024,
-16347,
-16339,
-15999,
-15336,
-14361,
-13096,
-11565,
-9800,
-7836,
-5714,
-3475,
-1167,
1166,
3474,
5713,
7835,
9799,
11564,
13095,
14360,
15335,
15998,
16338,
16346,
16023,
15375,
14416,
13165,
11646,
9892,
7938,
5822,
3588,
1282,
-1050,
-3361,
-5604,
-7734,
-9706,
-11482,
-13025,
-14305,
-15294,
-15974,
-16330,
-16354,
-16048,
-15416,
-14472,
-13235,
-11729,
-9986,
-8040,
-5932,
-3703,
-1399,
933,
3246,
5493,
7629,
9611,
11398,
12953,
14246,
15251,
15946,
16319,
16360,
16070,
15454,
14526,
13302,
11809,
10077,
8141,
6040,
3816,
1515,
-817,
-3132,
-5384,
-7527,
-9517,
-11314,
-12882,
-14189,
-15209,
-15920,
-16309,
-16367,
-16093,
-15494,
-14580,
-13371,
-11891,
-10170,
-8243,
-6149,
-3930,
-1632,
700,
3017,
5273,
7422,
9421,
11229,
12809,
14130,
15164,
15891,
16296,
16371,
16114,
15530,
14632,
13437,
11970,
10260,
8343,
6256,
4042,
1747,
-584,
-2903,
-5163,
-7319,
-9326,
-11144,
-12737,
-14071,
-15121,
-15863,
-16285,
-16376,
-16136,
-15568,
-14685,
-13505,
-12050,
-10352,
-8444,
-6365,
-4156,
-1864,
466,
2787,
5051,
7213,
9229,
11058,
12662,
14010,
15074,
15833,
16270,
16378,
16154,
15603,
14736,
13569,
12128,
10441,
8543,
6471,
4268,
1979,
-351,
-2673,
-4941,
-7109,
-9133,
-10972,
-12589,
-13950,
-15029,
-15803,
-16257,
-16382,
-16174,
-15639,
-14787,
-13635,
-12207,
-10532,
-8643,
-6579,
-4382,
-2096,
233,
2557,
4829,
7003,
9035,
10884,
12513,
13888,
14981,
15771,
16241,
16383,
16192,
15673,
14836,
13699,
12284,
10620,
8741,
6685,
4493,
2210,
-117,
-2442,
-4718,
-6898,
-8939,
-10798,
-12438,
-13826,
-14935,
-15740,
-16227,
-16384,
-16210,
-15707,
-14886,
-13763,
-12362,
-10710,
-8840,
-6792,
-4606,
-2327,
-1,
2326,
4605,
6791,
8839,
10709,
12361,
13762,
14885,
15706,
16209,
16383,
16226,
15739,
14934,
13825,
12437,
10797,
8938,
6897,
4717,
2441,
116,
-2211,
-4494,
-6686,
-8742,
-10621,
-12285,
-13700,
-14837,
-15674,
-16193,
-16384,
-16242,
-15772,
-14982,
-13889,
-12514,
-10885,
-9036,
-7004,
-4830,
-2558,
-234,
2095,
4381,
6578,
8642,
10531,
12206,
13634,
14786,
15638,
16173,
16381,
16256,
15802,
15028,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[NH] ={
-57,
-65,
-79,
-88,
-69,
0,
145,
385,
724,
1151,
1639,
2146,
2619,
3004,
3257,
3344,
3257,
3004,
2619,
2146,
1639,
1151,
724,
385,
145,
0,
-69,
-88,
-79,
-65,
-57,
};

DATA rtest[] ={
0,
9721,
-5978,
1874,
2390,
-6451,
9965,
-12636,
14236,
-14630,
13785,
-11773,
8763,
-5011,
835,
3413,
-7371,
10704,
-13132,
14446,
-14537,
13397,
-11122,
7905,
-4018,
};

#pragma DATA_SECTION (db,".dbuffer")
DATA db[NH+1];
DATA r[NX/D];

