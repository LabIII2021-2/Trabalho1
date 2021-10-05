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

/* Test for dlms: nois */
#define NX 50
#define NH 10
#define STEP 983
#define FNAME "t7"
#define MAXERROR 20

DATA x[NX] ={
26099,
16682,
19079,
20640,
11141,
-19604,
-14871,
8272,
2415,
-28869,
-26938,
-14988,
-5960,
-1702,
26803,
6307,
-11210,
-1430,
6368,
-22188,
21592,
29892,
6261,
-30884,
20454,
7216,
13205,
-26726,
-4923,
-8155,
-21879,
21833,
22193,
-3172,
29923,
-23125,
24243,
17657,
-3660,
7904,
29601,
9175,
-16560,
-9654,
-20457,
-614,
-5946,
-2391,
7270,
-28104,
};

DATA des[NX] ={
-3018,
-168,
-6360,
-2508,
-6626,
-939,
-2314,
109,
1549,
11687,
7261,
9287,
9364,
8412,
-6401,
-2164,
-830,
551,
-10758,
-4780,
-7416,
337,
-5790,
11210,
-6581,
365,
-6531,
10106,
-14460,
13444,
8411,
2729,
-6041,
2248,
-607,
5387,
-20366,
7230,
-13141,
-3582,
856,
2873,
-824,
6101,
-4640,
6795,
11879,
-2334,
5540,
11473,
};

DATA htest[NH] ={ /* C54x: hn-1 ... h0 (backward order) */
3446,
498,
-138,
184,
656,
-1951,
324,
-2104,
156,
-2132,
};

DATA rtest[NX] ={
0,
0,
-42,
-49,
-214,
-63,
3,
67,
69,
285,
438,
739,
798,
716,
-498,
-534,
-226,
-895,
-1674,
-157,
-599,
-1118,
-362,
1386,
-962,
-1573,
-793,
1323,
-595,
2432,
2655,
503,
-2814,
1293,
-1213,
193,
-4405,
-588,
-3163,
-1392,
-1057,
99,
389,
1935,
-893,
2818,
4163,
-230,
1913,
4800,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NH+3];

#pragma DATA_SECTION (h,".coeffs")
DATA h[2*NH];

DATA r[NX];

DATA error;

