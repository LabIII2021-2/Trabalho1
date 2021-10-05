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
#define NX 32
#define FNAME "t4"
#define MAXERROR 5.000000e-004

DATA x[NX] = {
-9642,
20524,
-32122,
-23666,
-19480,
-19745,
6802,
-14930,
-19739,
-31767,
16173,
-3598,
28299,
-2229,
-5331,
22690,
1648,
-19487,
11281,
22159,
-31481,
11880,
-7898,
21745,
184,
13728,
-4660,
-12805,
-20339,
-20091,
11942,
-12926,
};

float xf[NX] = {
-2.942637e-001,
6.263330e-001,
-9.802774e-001,
-7.222182e-001,
-5.944696e-001,
-6.025565e-001,
2.075850e-001,
-4.556242e-001,
-6.023715e-001,
-9.694521e-001,
4.935714e-001,
-1.098071e-001,
8.636292e-001,
-6.801132e-002,
-1.627011e-001,
6.924428e-001,
5.030499e-002,
-5.947053e-001,
3.442749e-001,
6.762369e-001,
-9.607210e-001,
3.625543e-001,
-2.410380e-001,
6.635920e-001,
5.625768e-003,
4.189428e-001,
-1.422153e-001,
-3.907653e-001,
-6.206925e-001,
-6.131377e-001,
3.644464e-001,
-3.944712e-001,
};

float rtest[NX] = {
-3.398312e+000,
1.596595e+000,
-1.020119e+000,
-1.384623e+000,
-1.682172e+000,
-1.659595e+000,
4.817305e+000,
-2.194791e+000,
-1.660105e+000,
-1.031510e+000,
2.026050e+000,
-9.106876e+000,
1.157904e+000,
-1.470344e+001,
-6.146241e+000,
1.444163e+000,
1.987874e+001,
-1.681505e+000,
2.904655e+000,
1.478772e+000,
-1.040885e+000,
2.758207e+000,
-4.148724e+000,
1.506950e+000,
1.777535e+002,
2.386961e+000,
-7.031594e+000,
-2.559081e+000,
-1.611104e+000,
-1.630955e+000,
2.743887e+000,
-2.535039e+000,
};

