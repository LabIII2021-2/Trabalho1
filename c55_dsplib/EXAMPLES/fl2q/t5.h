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

/* Test for div32by32: rand */
#define NX 64
#define FNAME "t5"
#define MAXERROR 10

float x[64] = {
7.200232e-001, 
7.073103e-001, 
1.871258e-001, 
-6.895101e-003, 
7.995383e-001, 
6.432583e-001, 
2.898208e-001, 
6.359487e-001, 
3.204551e-001, 
-3.160588e-001, 
-4.205482e-001, 
-3.176129e-001, 
6.815803e-002, 
4.542264e-001, 
-3.814197e-001, 
6.769921e-001, 
1.361449e-001, 
-2.591729e-001, 
4.054798e-001, 
9.314230e-002, 
-1.102396e-001, 
3.891345e-001, 
2.426203e-001, 
5.896422e-001, 
9.136869e-001, 
4.518070e-002, 
7.602844e-001, 
-6.540877e-001, 
9.594938e-001, 
-4.571055e-001, 
-4.953413e-001, 
7.514838e-001, 
4.746120e-001, 
-7.269625e-001, 
-9.764866e-001, 
7.877959e-001, 
-6.017239e-001, 
-4.025540e-001, 
3.228851e-001, 
-4.311828e-001, 
-6.155143e-002, 
-8.704377e-001, 
9.766699e-001, 
1.655834e-001, 
-1.530075e-001, 
3.102350e-002, 
-3.320970e-001, 
-1.341868e-001, 
-5.481003e-001, 
1.596137e-001, 
5.207300e-001, 
5.964623e-002, 
2.810530e-001, 
-5.818612e-001, 
-2.403633e-001, 
5.666573e-001, 
3.616915e-001, 
-7.780975e-002, 
1.356574e-001, 
5.884213e-001, 
-8.816348e-001, 
2.057382e-001, 
-8.994624e-001, 
-1.692503e-001, 
}; 

DATA rtest[64] = {
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
}; 

DATA r[64];
