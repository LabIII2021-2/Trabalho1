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
#define NX 8
#define FNAME "t1"
#define MAXERROR 3.000000e-004

LDATA x[8] = {
-383525191, 
-1192490433, 
-825852736, 
-446811806, 
-167905366, 
-562195654, 
-1768954968, 
-1276236177, 
}; 

DATA y[8] = {
-1635, 
-25195, 
-12883, 
-16844, 
-3562, 
-7796, 
-17811, 
-32162, 
}; 

// Floating point representation of numerator
// -1.785928e-001, 
// -5.552966e-001, 
// -3.845676e-001, 
// -2.080630e-001, 
// -7.818703e-002, 
// -2.617928e-001, 
// -8.237338e-001, 
// -5.942938e-001, 


// Floating point representation of denominator
// -4.987071e-002 
// -7.688615e-001 
// -3.931574e-001 
// -5.140175e-001 
// -1.087010e-001 
// -2.379032e-001 
// -5.435323e-001 
// -9.814963e-001 


float rtest[8] = {
3.579284e+000, 
7.222052e-001, 
9.781505e-001, 
4.047618e-001, 
7.192680e-001, 
1.100362e+000, 
1.515474e+000, 
6.054915e-001, 
}; 

DATA r[8];
DATA rexp[8];
