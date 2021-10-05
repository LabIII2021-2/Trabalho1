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

/* Test for sine: rand */
#define NX 64
#define FNAME "t5"
#define MAXERROR 10

DATA x[NX] ={
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
};

DATA rtest[NX] ={
-30984,
8482,
-26616,
31027,
-22675,
25246,
26060,
18172,
-710,
19298,
29505,
25880,
29824,
27692,
-27448,
-31753,
-27535,
6962,
32429,
-30521,
27831,
13591,
-23829,
31333,
9452,
-11123,
30800,
22627,
31477,
8776,
4635,
22409,
-29004,
4158,
-32471,
-32765,
23062,
32663,
-24786,
-2419,
20262,
-31109,
-31245,
27824,
-32006,
-6297,
-12973,
2399,
16287,
-15152,
3188,
-28315,
-13409,
-32395,
15751,
32698,
6104,
25317,
-31691,
-22459,
32052,
29723,
-7931,
13546,
};

DATA r[NX];
