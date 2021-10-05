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

/* This is a test for minval: rand */
#define NX 128
#define FNAME "t7"
#define MAXERROR 0

DATA x[NX] ={
18568,
11851,
-2550,
4445,
19281,
-28890,
6741,
-29474,
-5546,
-12780,
24534,
-31785,
17560,
30857,
32118,
18930,
-4021,
-111,
-18746,
9403,
-11795,
30153,
14852,
-5771,
16027,
-15208,
-3938,
28401,
12014,
-18838,
22232,
8440,
-24002,
-19194,
7025,
8512,
-8489,
4924,
-3184,
-29892,
-30987,
-12276,
-31926,
-7605,
12000,
-26684,
-30453,
7365,
7113,
-31736,
-31697,
-20312,
5696,
-28995,
-8680,
8614,
14262,
12626,
-27258,
-2992,
-3813,
-9618,
-22702,
11511,
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
};

DATA rtest = -32403;
DATA r;
