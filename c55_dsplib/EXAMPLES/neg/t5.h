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

/* This is a test for neg: rand */
#define NX 64
#define FNAME "t5"
#define MAXERROR 10

DATA x[NX] ={
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
};

DATA rtest[NX] ={
12805,
20339,
20091,
-11942,
12926,
-2731,
22880,
-12969,
7971,
-23594,
-23177,
-6132,
226,
-26199,
-21078,
-9497,
-20839,
-10501,
10357,
13781,
10408,
-2233,
-14884,
12498,
-22184,
-4461,
8493,
-13287,
-3052,
3612,
-12751,
-7950,
-19321,
-29940,
-1480,
-24913,
21433,
-31441,
14978,
16231,
-24625,
-15552,
23821,
31998,
-25814,
19717,
13191,
-10580,
14129,
2017,
28523,
-32004,
-5426,
5014,
-1017,
10882,
4397,
17960,
-5230,
-17063,
-1954,
-9210,
19066,
7876,
};

DATA r[NX]; 
