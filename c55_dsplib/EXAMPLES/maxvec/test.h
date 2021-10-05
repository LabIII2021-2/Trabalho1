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

/* This is a test for maxvec: rand */
#define NX 161
#define FNAME "t8"
#define MAXERROR 0

DATA x[NX] ={
13055,
14910,
-1417,
3594,
-24836,
-3228,
14148,
25745,
-14870,
-16072,
23960,
-17541,
19980,
26764,
-17571,
-17085,
-29508,
-27632,
9228,
-20259,
22535,
-21372,
-21575,
32394,
-3946,
-10483,
-12176,
-8843,
-6997,
5998,
-24921,
-30270,
-2714,
24239,
28458,
-15438,
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
25580,
15394,
12276,
-10086,
-21887,
-22570,
-20243,
-5083,
23329,
-639,
20705,
-2571,
-2795,
-3232,
-5753,
26319,
-32403,
-13278,
-29547,
12660,
9837,
31653,
3451,
-6549,
-19741,
8205,
15293,
-8134,
-32121,
-5253,
16624,
19259,
27522,
22591,
-8667,
7916,
15156,
-20062,
26529,
4535,
8636,
-17406,
3196,
28284,
-10801,
10192,
-7085,
8343,
13046,
-6739,
-5661,
10172,
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
13341,
-986,
-25257,
10803,
-8823,
-23591,
4376,
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
19859,
-27271,
29193,
27259,
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
-25341,
26099,
};

DATA r_testval = 32731;
DATA r_testidx = 121;

DATA r_val;
DATA r_idx;
