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

/* Test for mmul: rand */
#define row1 8
#define col1 10
#define row2 10
#define col2 4
#define FNAME "t4"
#define MAXERROR 10

DATA x1[row1*col1] ={
4264,
4589,
2186,
4179,
4626,
2018,
2279,
1607,
1461,
3706,
2630,
3603,
3758,
2945,
3296,
3294,
5090,
4308,
2087,
1501,
2277,
4494,
4112,
3869,
3388,
5923,
3548,
3844,
3515,
2896,
2351,
5431,
2060,
4056,
4305,
2645,
5180,
1279,
1923,
4402,
3541,
4070,
1801,
5069,
4009,
3295,
3110,
2258,
3485,
2595,
2556,
5307,
2348,
2357,
3359,
2957,
3933,
4837,
3471,
5278,
2282,
4911,
1628,
2765,
3730,
5783,
1301,
1793,
3643,
1336,
4165,
1203,
3007,
5087,
1978,
3459,
3099,
2276,
2546,
582,
};

DATA x2[row2*col2] ={
1785,
4013,
4127,
2561,
5610,
4487,
5069,
3100,
1214,
2338,
2447,
4451,
3902,
1981,
5799,
2693,
5499,
292,
3576,
4239,
938,
1578,
5476,
4216,
1865,
3920,
2532,
5143,
991,
4135,
3363,
3111,
2949,
2583,
4949,
4248,
4831,
3714,
2495,
740,
};

DATA rtest[] ={
3287,
2708,
3835,
3049,
2727,
2937,
3865,
3661,
3306,
3252,
4753,
4123,
3571,
3021,
4077,
3491,
3269,
2846,
4291,
3479,
3525,
3475,
4322,
3675,
2799,
2367,
3968,
3195,
2141,
2306,
3531,
3012,
};

DATA r[row1*col2];

