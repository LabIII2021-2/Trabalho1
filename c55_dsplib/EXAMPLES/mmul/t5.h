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
#define row1 3
#define col1 10
#define row2 10
#define col2 6
#define FNAME "t5"
#define MAXERROR 10

DATA x1[row1*col1] ={
938,
2824,
1847,
3409,
3602,
2580,
2998,
1118,
519,
2084,
3326,
4461,
4258,
2045,
3048,
4230,
6342,
4084,
2925,
857,
3237,
6082,
3695,
4998,
1769,
4217,
2727,
5358,
947,
5140,
};

DATA x2[row2*col2] ={
1223,
3884,
3771,
931,
2267,
3040,
1566,
2691,
2554,
2803,
1282,
2967,
2447,
3968,
2520,
3245,
2498,
3186,
2770,
3330,
3026,
3922,
1193,
1705,
3773,
3830,
5161,
3361,
5517,
4592,
3944,
5169,
3433,
2354,
3084,
5147,
1134,
3548,
1492,
3473,
2456,
4842,
5800,
5198,
3423,
3868,
4266,
3100,
4410,
5762,
3482,
521,
3806,
2899,
2671,
3194,
3542,
3090,
4629,
4233,
};

DATA rtest[] ={
1863,
2537,
2156,
2068,
2014,
2473,
3094,
4440,
3289,
3041,
3183,
4017,
3410,
4523,
3653,
3482,
3358,
4038,
};

DATA r[row1*col2];

