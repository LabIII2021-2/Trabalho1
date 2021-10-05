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
#define NX 32
#define FNAME "t4"
#define MAXERROR 10

float x[32] = {
-5.944696e-001, 
-6.025565e-001, 
2.075850e-001, 
-4.556241e-001, 
-6.023715e-001, 
-9.694521e-001, 
4.935713e-001, 
-1.098071e-001, 
8.636291e-001, 
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
8.334771e-002, 
-6.982540e-001, 
3.957970e-001, 
-2.432540e-001, 
}; 

DATA rtest[32] = {
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
-20092, 
11942, 
-12927, 
2731, 
-22881, 
12969, 
-7971, 
}; 

DATA r[32];
