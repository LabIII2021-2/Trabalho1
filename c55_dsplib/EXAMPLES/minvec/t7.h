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

/* This is a test for minvec: rand */
#define NX 160
#define FNAME "t7"
#define MAXERROR 0

DATA x[NX] ={
28538,
27322,
-5881,
25798,
-28975,
-9643,
20523,
-32122,
-23666,
-19480,
-19745,
6802,
-14930,
-19739,
-31768,
16173,
-3599,
28299,
-2229,
-5332,
22689,
1648,
-19488,
11281,
22158,
-31481,
11880,
-7899,
21744,
184,
13727,
-4661,
-12805,
-20339,
-20092,
11942,
-12927,
2731,
-22881,
12969,
-7971,
23593,
23177,
6131,
-226,
26199,
21078,
9496,
20838,
10500,
-10357,
-13781,
-10408,
2233,
14884,
-12499,
22183,
4461,
-8493,
13286,
3052,
-3613,
12751,
7950,
19321,
29939,
1480,
24912,
-21434,
31440,
-14979,
-16232,
24624,
15552,
-23822,
-31998,
25814,
-19718,
-13191,
10580,
-14129,
-2017,
-28523,
32003,
5425,
-5014,
1016,
-10883,
-4398,
-17961,
5230,
17063,
1954,
9209,
-19067,
-7877,
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
};

DATA r_testval = -32122;
DATA r_testidx = 7;

DATA r_val;
DATA r_idx;
