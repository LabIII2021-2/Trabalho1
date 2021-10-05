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

/* Test for logn: nois */
#define NX 55
#define FNAME "t2"
#define MAXERROR 40

DATA x[NX] ={
31131,
7573,
19883,
15923,
29203,
24970,
14956,
606,
26913,
14571,
20164,
25948,
30203,
24187,
5775,
13293,
30650,
30042,
13442,
29280,
1897,
11562,
26643,
323,
4551,
6644,
6511,
19783,
8918,
6514,
500,
24468,
14583,
30531,
15268,
13717,
27726,
17206,
6640,
22022,
27461,
643,
22322,
12434,
27254,
16475,
23246,
14053,
9981,
6214,
6338,
22353,
9920,
17748,
4943,
};

long rtest[] ={
-1680,
-48000,
-16370,
-23648,
-3774,
-8906,
-25701,
-130741,
-6450,
-26557,
-15910,
-7647,
-2671,
-9949,
-56881,
-29564,
-2189,
-2846,
-29198,
-3688,
-93365,
-34136,
-6780,
-151363,
-64689,
-52291,
-52951,
-16536,
-42643,
-52936,
-137026,
-9571,
-26528,
-2317,
-25024,
-28535,
-5475,
-21108,
-52310,
-13022,
-5790,
-128788,
-12579,
-31754,
-6038,
-22532,
-11250,
-27743,
-38955,
-54482,
-53836,
-12534,
-39154,
-20093,
-61978,
};

long r[NX];

