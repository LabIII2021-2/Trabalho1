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
#define NX 400
#define NK 9
#define FNAME "t1"
#define MAXERROR 10

DATA x[NX] ={
0,
2326,
4606,
6792,
8840,
10709,
12361,
13763,
14886,
15707,
16210,
16384,
16226,
15740,
14934,
13826,
12438,
10797,
8938,
6898,
4718,
2442,
117,
-2211,
-4494,
-6685,
-8742,
-10621,
-12284,
-13699,
-14837,
-15673,
-16192,
-16383,
-16242,
-15772,
-14982,
-13888,
-12513,
-10885,
-9036,
-7003,
-4829,
-2557,
-233,
2095,
4381,
6579,
8643,
10531,
12207,
13635,
14787,
15639,
16174,
16381,
16257,
15803,
15029,
13950,
12588,
10972,
9133,
7109,
4941,
2672,
350,
-1979,
-4269,
-6472,
-8543,
-10442,
-12129,
-13570,
-14736,
-15604,
-16155,
-16379,
-16271,
-15833,
-15075,
-14011,
-12663,
-11058,
-9229,
-7214,
-5052,
-2788,
-467,
1863,
4156,
6364,
8443,
10352,
12050,
13504,
14685,
15568,
16135,
16376,
16284,
15863,
15120,
14071,
12736,
11144,
9326,
7318,
5163,
2903,
583,
-1747,
-4043,
-6256,
-8343,
-10261,
-11971,
-13438,
-14633,
-15531,
-16114,
-16371,
-16297,
-15892,
-15165,
-14130,
-12810,
-11229,
-9421,
-7423,
-5273,
-3017,
-700,
1631,
3930,
6148,
8242,
10170,
11891,
13371,
14580,
15493,
16093,
16366,
16308,
15920,
15208,
14189,
12882,
11314,
9517,
7526,
5384,
3132,
817,
-1515,
-3816,
-6040,
-8141,
-10078,
-11810,
-13303,
-14526,
-15455,
-16071,
-16361,
-16319,
-15947,
-15251,
-14247,
-12954,
-11398,
-9611,
-7630,
-5494,
-3246,
-933,
1399,
3703,
5931,
8040,
9986,
11729,
13234,
14472,
15416,
16047,
16354,
16329,
15973,
15294,
14304,
13025,
11482,
9706,
7733,
5604,
3361,
1050,
-1283,
-3589,
-5822,
-7938,
-9893,
-11647,
-13165,
-14417,
-15376,
-16024,
-16346,
-16338,
-15999,
-15335,
-14361,
-13095,
-11565,
-9799,
-7836,
-5713,
-3475,
-1166,
1166,
3475,
5713,
7836,
9799,
11565,
13095,
14361,
15335,
15999,
16338,
16346,
16024,
15376,
14417,
13165,
11647,
9893,
7938,
5822,
3589,
1283,
-1050,
-3361,
-5604,
-7733,
-9706,
-11482,
-13025,
-14304,
-15294,
-15973,
-16329,
-16354,
-16047,
-15416,
-14472,
-13234,
-11729,
-9986,
-8040,
-5931,
-3703,
-1399,
933,
3246,
5494,
7630,
9611,
11398,
12954,
14247,
15251,
15947,
16319,
16361,
16071,
15455,
14526,
13303,
11810,
10078,
8141,
6040,
3816,
1515,
-817,
-3132,
-5384,
-7526,
-9517,
-11314,
-12882,
-14189,
-15208,
-15920,
-16308,
-16366,
-16093,
-15493,
-14580,
-13371,
-11891,
-10170,
-8242,
-6148,
-3930,
-1631,
700,
3017,
5273,
7423,
9421,
11229,
12810,
14130,
15165,
15892,
16297,
16371,
16114,
15531,
14633,
13438,
11971,
10261,
8343,
6256,
4043,
1747,
-583,
-2903,
-5163,
-7318,
-9326,
-11144,
-12736,
-14071,
-15120,
-15863,
-16284,
-16376,
-16135,
-15568,
-14685,
-13504,
-12050,
-10352,
-8443,
-6364,
-4156,
-1863,
467,
2788,
5052,
7214,
9229,
11058,
12663,
14011,
15075,
15833,
16271,
16379,
16155,
15604,
14736,
13570,
12129,
10442,
8543,
6472,
4269,
1979,
-350,
-2672,
-4941,
-7109,
-9133,
-10972,
-12588,
-13950,
-15029,
-15803,
-16257,
-16381,
-16174,
-15639,
-14787,
-13635,
-12207,
-10531,
-8643,
-6579,
-4381,
-2095,
233,
2557,
4829,
};

#pragma DATA_SECTION (k,".coeffs")
DATA k[NK] ={
0,
15567,
3787,
9943,
7962,
14603,
12486,
7479,
303,
};

DATA rtest[] ={
0,
2326,
2265,
2388,
2052,
2047,
1832,
2338,
2838,
3138,
2756,
2350,
1859,
1632,
1572,
1641,
1442,
986,
354,
-189,
-575,
-757,
-901,
-1135,
-1529,
-1968,
-2325,
-2498,
-2513,
-2458,
-2441,
-2486,
-2537,
-2497,
-2317,
-2015,
-1668,
-1347,
-1075,
-814,
-509,
-130,
299,
723,
1088,
1382,
1627,
1860,
2099,
2327,
2505,
2602,
2613,
2559,
2469,
2358,
2220,
2033,
1785,
1477,
1133,
778,
427,
80,
-271,
-632,
-995,
-1342,
-1652,
-1916,
-2133,
-2309,
-2448,
-2548,
-2599,
-2590,
-2520,
-2393,
-2220,
-2010,
-1765,
-1485,
-1171,
-827,
-463,
-91,
278,
636,
982,
1310,
1617,
1892,
2128,
2317,
2457,
2547,
2587,
2578,
2517,
2405,
2241,
2031,
1779,
1493,
1178,
840,
485,
118,
-253,
-618,
-970,
-1301,
-1605,
-1877,
-2112,
-2305,
-2451,
-2547,
-2590,
-2581,
-2520,
-2408,
-2248,
-2042,
-1795,
-1510,
-1195,
-856,
-500,
-134,
234,
599,
951,
1284,
1591,
1866,
2102,
2296,
2444,
2542,
2589,
2583,
2525,
2415,
2257,
2053,
1807,
1525,
1212,
874,
519,
153,
-217,
-581,
-934,
-1268,
-1576,
-1853,
-2092,
-2288,
-2438,
-2539,
-2588,
-2585,
-2529,
-2422,
-2266,
-2064,
-1821,
-1540,
-1228,
-892,
-537,
-171,
198,
563,
917,
1252,
1562,
1840,
2080,
2279,
2432,
2535,
2587,
2586,
2533,
2429,
2275,
2075,
1834,
1555,
1244,
909,
555,
190,
-180,
-545,
-899,
-1236,
-1547,
-1827,
-2069,
-2270,
-2425,
-2531,
-2585,
-2587,
-2537,
-2435,
-2284,
-2086,
-1847,
-1570,
-1261,
-926,
-573,
-208,
161,
527,
882,
1219,
1532,
1813,
2058,
2261,
2419,
2527,
2584,
2588,
2541,
2441,
2293,
2097,
1860,
1584,
1277,
943,
591,
226,
-143,
-509,
-865,
-1203,
-1517,
-1800,
-2047,
-2252,
-2412,
-2523,
-2582,
-2589,
-2544,
-2448,
-2301,
-2108,
-1873,
-1599,
-1293,
-961,
-609,
-245,
124,
491,
847,
1187,
1502,
1787,
2036,
2243,
2405,
2518,
2580,
2590,
2548,
2454,
2310,
2119,
1885,
1613,
1309,
978,
627,
263,
-106,
-473,
-830,
-1170,
-1487,
-1773,
-2024,
-2234,
-2398,
-2514,
-2579,
-2591,
-2551,
-2459,
-2318,
-2129,
-1898,
-1628,
-1325,
-995,
-645,
-282,
87,
454,
812,
1154,
1472,
1760,
2012,
2224,
2391,
2509,
2577,
2592,
2554,
2465,
2326,
2140,
1910,
1642,
1341,
1012,
663,
300,
-69,
-436,
-795,
-1137,
-1456,
-1746,
-2001,
-2215,
-2384,
-2504,
-2574,
-2592,
-2557,
-2471,
-2334,
-2150,
-1923,
-1656,
-1356,
-1029,
-680,
-318,
50,
418,
777,
1120,
1441,
1733,
1989,
2205,
2376,
2500,
2572,
2593,
2560,
2476,
2342,
2161,
1935,
1671,
1372,
1046,
698,
337,
-32,
-400,
-759,
-1104,
-1426,
-1719,
-1977,
-2195,
-2369,
-2495,
-2570,
-2593,
-2563,
-2482,
-2350,
-2171,
-1947,
-1685,
-1388,
-1063,
-716,
-355,
13,
381,
742,
1087,
1410,
1705,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NK];
DATA *dp = dbuffer;

DATA r[NX];
