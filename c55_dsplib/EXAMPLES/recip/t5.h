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

/* Test for rand: rand */
#define NX 64
#define FNAME "t5"
#define MAXERROR 5.000000e-004

DATA x[NX] = {
2731,
-22880,
12969,
-7971,
23594,
23177,
6132,
-226,
26199,
21078,
9497,
20839,
10501,
-10357,
-13781,
-10408,
2233,
14884,
-12498,
22184,
4461,
-8493,
13287,
3052,
-3612,
12751,
7950,
19321,
29940,
1480,
24913,
-21433,
31441,
-14978,
-16231,
24625,
15552,
-23821,
-31998,
25814,
-19717,
-13191,
10580,
-14129,
-2017,
-28523,
32004,
5426,
-5014,
1017,
-10882,
-4397,
-17960,
5230,
17063,
1954,
9210,
-19066,
-7876,
18568,
11852,
-2550,
4445,
19281,
};

float xf[NX] = {
8.334771e-002,
-6.982540e-001,
3.957970e-001,
-2.432540e-001,
7.200232e-001,
7.073103e-001,
1.871258e-001,
-6.895101e-003,
7.995384e-001,
6.432583e-001,
2.898208e-001,
6.359487e-001,
3.204551e-001,
-3.160588e-001,
-4.205482e-001,
-3.176129e-001,
6.815804e-002,
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
3.228852e-001,
-4.311828e-001,
-6.155143e-002,
-8.704378e-001,
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
};

float rtest[NX] = {
1.199793e+001,
-1.432144e+000,
2.526548e+000,
-4.110929e+000,
1.388844e+000,
1.413807e+000,
5.343998e+000,
-1.450305e+002,
1.250722e+000,
1.554585e+000,
3.450408e+000,
1.572454e+000,
3.120562e+000,
-3.163969e+000,
-2.377849e+000,
-3.148487e+000,
1.467178e+001,
2.201545e+000,
-2.621784e+000,
1.477122e+000,
7.345114e+000,
-3.858428e+000,
2.466214e+000,
1.073626e+001,
-9.071151e+000,
2.569806e+000,
4.121667e+000,
1.695944e+000,
1.094467e+000,
2.213335e+001,
1.315297e+000,
-1.528847e+000,
1.042216e+000,
-2.187679e+000,
-2.018810e+000,
1.330701e+000,
2.106984e+000,
-1.375587e+000,
-1.024080e+000,
1.269364e+000,
-1.661892e+000,
-2.484139e+000,
3.097076e+000,
-2.319202e+000,
-1.624658e+001,
-1.148847e+000,
1.023887e+000,
6.039254e+000,
-6.535628e+000,
3.223362e+001,
-3.011168e+000,
-7.452297e+000,
-1.824484e+000,
6.265125e+000,
1.920381e+000,
1.676552e+001,
3.558048e+000,
-1.718623e+000,
-4.160370e+000,
1.764735e+000,
2.764787e+000,
-1.285186e+001,
7.371510e+000,
1.699463e+000,
};

