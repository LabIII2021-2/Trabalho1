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

/* Test for dlms: rand */
#define NX 100
#define NH 12
#define STEP 655
#define FNAME "t6"
#define MAXERROR 20

DATA x[NX] ={
16027,
-15208,
-3938,
28401,
12014,
-18838,
22232,
8439,
-24001,
-19194,
7025,
8512,
-8489,
4924,
-3184,
-29891,
-30987,
-12276,
-31925,
-7605,
12000,
-26684,
-30452,
7365,
7113,
-31735,
-31696,
-20312,
5696,
-28995,
-8679,
8614,
14262,
12626,
-27258,
-2992,
-3813,
-9618,
-22702,
11510,
13055,
14909,
-1417,
3594,
-24835,
-3228,
14147,
25745,
-14870,
-16072,
23959,
-17541,
19979,
26764,
-17571,
-17085,
-29507,
-27631,
9228,
-20258,
22535,
-21372,
-21575,
32393,
-3946,
-10483,
-12176,
-8843,
-6997,
5998,
-24921,
-30269,
-2714,
24239,
28457,
-15437,
-22263,
24435,
-17179,
9557,
30597,
10808,
24273,
-32118,
-23789,
20889,
-4577,
25579,
15394,
12276,
-10086,
-21887,
-22570,
-20243,
-5083,
23328,
-639,
20704,
-2571,
-2795,
};

DATA des[NX] ={
-3232,
-5753,
26319,
-32402,
-13278,
-29546,
12660,
9837,
31652,
3451,
-6549,
-19740,
8205,
15293,
-8134,
-32121,
-5253,
16624,
19258,
27522,
22591,
-8667,
7916,
15156,
-20061,
26529,
4535,
8636,
-17406,
3196,
28283,
-10801,
10192,
-7085,
8343,
13046,
-6739,
-5661,
10171,
22123,
-8415,
-4899,
6203,
4308,
14191,
741,
18114,
-699,
-20585,
13148,
31634,
20095,
13340,
-986,
-25257,
10803,
-8823,
-23590,
4375,
21168,
11399,
32731,
30253,
-28911,
-9155,
3179,
-15613,
6379,
-29539,
4656,
13163,
30296,
16417,
15728,
-4465,
8799,
19858,
-27271,
29193,
27258,
6683,
-16151,
24474,
878,
15246,
-5097,
30236,
-28046,
3500,
-13633,
23459,
-10764,
11809,
-29266,
-9395,
-112,
-4297,
4093,
7642,
-25340,
};

DATA htest[NH] ={ /* C54x: hn-1 ... h0 (backward order) */
-753,
481,
1445,
-2282,
-1169,
376,
-2054,
-2327,
-767,
986,
-1730,
-2667,
};

DATA rtest[NX] ={
0,
0,
4,
26,
-307,
787,
-156,
-457,
-361,
375,
-150,
-71,
377,
61,
-859,
752,
2236,
28,
-1686,
262,
555,
463,
1732,
2315,
-259,
1391,
5677,
3189,
1305,
4888,
6036,
381,
-1269,
1552,
3173,
770,
-582,
2254,
4767,
2674,
-2141,
-1114,
679,
559,
-2189,
1869,
213,
-923,
-353,
2579,
-2188,
-4241,
1581,
381,
-3642,
-490,
4108,
2482,
2602,
1069,
2709,
-849,
2340,
2555,
-1414,
1269,
5343,
1297,
-1752,
3348,
2612,
2518,
4227,
-1521,
-2467,
3427,
5007,
-3164,
-5066,
1383,
-1858,
-3275,
-4996,
2432,
-577,
-7362,
-597,
1407,
-2297,
-1960,
-5172,
5024,
-1165,
618,
4294,
-420,
1248,
2285,
1105,
955,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NH+2];

#pragma DATA_SECTION (h,".coeffs")
DATA h[NH];

DATA r[NX];

DATA error;

