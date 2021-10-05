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

/* Test for expn: nois */
#define NX 55
#define FNAME "t2"
#define MAXERROR 10

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

DATA rtest[] ={
10591,
5161,
7514,
6659,
9986,
8776,
6465,
4172,
9312,
6390,
7579,
9042,
10296,
8569,
4885,
6145,
10437,
10245,
6173,
10010,
4340,
5829,
9236,
4137,
4706,
5017,
4996,
7491,
5377,
4997,
4159,
8643,
6392,
10399,
6527,
6225,
9546,
6925,
5016,
8021,
9469,
4177,
8095,
5986,
9410,
6772,
8326,
6289,
5554,
4951,
4970,
8102,
5544,
7040,
4763,
};

DATA r[NX];

