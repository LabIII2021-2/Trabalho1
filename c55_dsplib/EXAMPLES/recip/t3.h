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
#define NX 16
#define FNAME "t3"
#define MAXERROR 5.000000e-004

DATA x[NX] = {
17177,
-2853,
-31555,
21064,
-3624,
7565,
19132,
27644,
15611,
-21216,
-6180,
28539,
27322,
-5881,
25798,
-28974,
};

float xf[NX] = {
5.241937e-001,
-8.706467e-002,
-9.629927e-001,
6.428143e-001,
-1.105933e-001,
2.308647e-001,
5.838741e-001,
8.436259e-001,
4.764145e-001,
-6.474677e-001,
-1.885876e-001,
8.709394e-001,
8.338089e-001,
-1.794596e-001,
7.872991e-001,
-8.842174e-001,
};

float rtest[NX] = {
1.907692e+000,
-1.148572e+001,
-1.038429e+000,
1.555659e+000,
-9.042141e+000,
4.331541e+000,
1.712698e+000,
1.185359e+000,
2.099013e+000,
-1.544479e+000,
-5.302576e+000,
1.148186e+000,
1.199316e+000,
-5.572285e+000,
1.270165e+000,
-1.130944e+000,
};

