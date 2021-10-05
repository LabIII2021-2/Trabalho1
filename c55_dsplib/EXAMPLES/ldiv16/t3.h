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

/* Test for divQ31byQ15: rand */
#define NX 32
#define FNAME "t3"
#define MAXERROR 3.000000e-004

LDATA x[32] = {
-440618371, 
-92677988, 
-1025229409, 
-257392648, 
-1776063146, 
-43493208, 
-1564555084, 
-1605610486, 
-266842236, 
-564131089, 
-1854311863, 
-2122236333, 
-227852380, 
-1719837888, 
-1505980850, 
-727046524, 
-1536720837, 
-1139832157, 
-2008367226, 
-25050530, 
-895948033, 
-1238032350, 
-1040430580, 
-1430328292, 
-1217823800, 
-1662259985, 
-902357860, 
-514612218, 
-1009697159, 
-771963458, 
-1698510504, 
-1331829896, 
}; 

DATA y[32] = {
-22787, 
-26554, 
-26430, 
-10413, 
-22848, 
-15019, 
-27825, 
-9900, 
-20370, 
-4588, 
-4796, 
-13319, 
-16497, 
-3285, 
-5845, 
-11636, 
-5965, 
-11134, 
-21563, 
-23275, 
-21588, 
-15268, 
-8942, 
-22634, 
-5293, 
-14154, 
-20631, 
-9741, 
-14858, 
-18191, 
-10009, 
-12409, 
}; 

// Floating point representation of numerator
// -2.051789e-001, 
// -4.315655e-002, 
// -4.774096e-001, 
// -1.198578e-001, 
// -8.270439e-001, 
// -2.025310e-002, 
// -7.285527e-001, 
// -7.476706e-001, 
// -1.242581e-001, 
// -2.626940e-001, 
// -8.634812e-001, 
// -9.882433e-001, 
// -1.061020e-001, 
// -8.008619e-001, 
// -7.012770e-001, 
// -3.385574e-001, 
// -7.155914e-001, 
// -5.307757e-001, 
// -9.352189e-001, 
// -1.166506e-002, 
// -4.172083e-001, 
// -5.765037e-001, 
// -4.844882e-001, 
// -6.660485e-001, 
// -5.670934e-001, 
// -7.740501e-001, 
// -4.201931e-001, 
// -2.396350e-001, 
// -4.701769e-001, 
// -3.594735e-001, 
// -7.909306e-001, 
// -6.201816e-001, 


// Floating point representation of denominator
// -6.953826e-001 
// -8.103462e-001 
// -8.065688e-001 
// -3.177768e-001 
// -6.972356e-001 
// -4.583261e-001 
// -8.491270e-001 
// -3.021015e-001 
// -6.216270e-001 
// -1.399884e-001 
// -1.463449e-001 
// -4.064371e-001 
// -5.034475e-001 
// -1.002308e-001 
// -1.783708e-001 
// -3.550896e-001 
// -1.820257e-001 
// -3.397724e-001 
// -6.580294e-001 
// -7.102741e-001 
// -6.588064e-001 
// -4.659210e-001 
// -2.728868e-001 
// -6.907098e-001 
// -1.615040e-001 
// -4.319275e-001 
// -6.295864e-001 
// -2.972601e-001 
// -4.534288e-001 
// -5.551198e-001 
// -3.054328e-001 
// -3.786899e-001 


float rtest[32] = {
2.950499e-001, 
5.325578e-002, 
5.918940e-001, 
3.771728e-001, 
1.186125e+000, 
4.418761e-002, 
8.579772e-001, 
2.474714e+000, 
1.998866e-001, 
1.876189e+000, 
5.899615e+000, 
2.431320e+000, 
2.107505e-001, 
7.988628e+000, 
3.931470e+000, 
9.534075e-001, 
3.931014e+000, 
1.562103e+000, 
1.421196e+000, 
1.642280e-002, 
6.332723e-001, 
1.237285e+000, 
1.775409e+000, 
9.642607e-001, 
3.510772e+000, 
1.792008e+000, 
6.673883e-001, 
8.061143e-001, 
1.036933e+000, 
6.475305e-001, 
2.589391e+000, 
1.637691e+000, 
}; 

DATA r[32];
DATA rexp[32];
