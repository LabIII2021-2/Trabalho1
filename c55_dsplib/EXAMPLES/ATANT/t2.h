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

/* Test for maxval: rand */
#define NX 50
#define FNAME "t2"
#define MAXERROR 40

DATA x[NX] ={
29499,
-17621,
7002,
-919,
25644,
17176,
-2853,
-31556,
21063,
-3624,
7564,
19132,
27643,
15611,
-21217,
-6180,
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
};

DATA rtest[NX] ={
24017,
-16167,
6898,
-919,
21759,
15820,
-2846,
-25119,
18720,
-3610,
7434,
17317,
22963,
14568,
-18829,
-6108,
23479,
22774,
-5819,
21854,
-23725,
-9378,
18335,
-25410,
-20496,
-17575,
-17770,
6706,
-14010,
-17766,
-25228,
15023,
-3584,
23342,
-2226,
-5286,
19845,
1647,
-17581,
10864,
19483,
-25080,
11397,
-7751,
19197,
184,
13000,
-4630,
-12207,
-18203,
};

DATA r[NX];
