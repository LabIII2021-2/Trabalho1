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

/* This is a test for add: rand */
#define NX 32
#define FNAME "t8"
#define MAXERROR 2

#define ADD_SCALE 0

DATA x[NX] ={
-2011,
-56,
-9373,
4701,
-5898,
15076,
7426,
-2886,
8013,
-7604,
-1969,
14200,
6007,
-9419,
11116,
4220,
-12001,
-9597,
3512,
4256,
-4245,
2462,
-1592,
-14946,
-15494,
-6138,
-15963,
-3803,
6000,
-13342,
-15227,
3682,
};

DATA y[NX] ={
3557,
-15868,
-15848,
-10156,
2848,
-14497,
-4340,
4307,
7131,
6313,
-13629,
-1496,
-1906,
-4809,
-11351,
5756,
6528,
7455,
-708,
1797,
-12418,
-1614,
7074,
12873,
-7435,
-8036,
11980,
-8770,
9990,
13382,
-8785,
-8542,
};

DATA rtest[NX] ={
1547,
-15923,
-25221,
-5454,
-3049,
579,
3087,
1422,
15145,
-1291,
-15597,
12705,
4101,
-14228,
-234,
9976,
-5473,
-2142,
2804,
6053,
-16662,
849,
5482,
-2073,
-22928,
-14174,
-3982,
-12573,
15990,
41,
-24011,
-4859,
};

DATA r[NX]; 
