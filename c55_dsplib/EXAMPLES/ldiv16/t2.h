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
#define NX 16
#define FNAME "t2"
#define MAXERROR 3.000000e-004

LDATA x[16] = {
-1191646326, 
-146427077, 
-1146768408, 
-1248440750, 
-330236988, 
-1019727240, 
-1712301745, 
-704079419, 
-347637989, 
-2105308093, 
-684452078, 
-1332554354, 
-361215299, 
-1067701191, 
-623905428, 
-1226444295, 
}; 

DATA y[16] = {
-2115, 
-2723, 
-19325, 
-3485, 
-30872, 
-21206, 
-6123, 
-32445, 
-28217, 
-26124, 
-26257, 
-12983, 
-23849, 
-26254, 
-32268, 
-8298, 
}; 

// Floating point representation of numerator
// -5.549036e-001, 
// -6.818542e-002, 
// -5.340057e-001, 
// -5.813505e-001, 
// -1.537786e-001, 
// -4.748475e-001, 
// -7.973526e-001, 
// -3.278625e-001, 
// -1.618816e-001, 
// -9.803605e-001, 
// -3.187228e-001, 
// -6.205190e-001, 
// -1.682040e-001, 
// -4.971871e-001, 
// -2.905286e-001, 
// -5.711076e-001, 


// Floating point representation of denominator
// -6.453030e-002 
// -8.309556e-002 
// -5.897298e-001 
// -1.063505e-001 
// -9.421087e-001 
// -6.471319e-001 
// -1.868335e-001 
// -9.901387e-001 
// -8.611091e-001 
// -7.972348e-001 
// -8.012782e-001 
// -3.962075e-001 
// -7.278121e-001 
// -8.011857e-001 
// -9.847261e-001 
// -2.532143e-001 


float rtest[16] = {
8.597201e+000, 
8.205288e-001, 
9.054746e-001, 
5.466196e+000, 
1.632229e-001, 
7.337453e-001, 
4.267132e+000, 
3.311265e-001, 
1.879907e-001, 
1.229691e+000, 
3.977572e-001, 
1.566138e+000, 
2.311086e-001, 
6.205465e-001, 
2.950304e-001, 
2.255249e+000, 
}; 

DATA r[16];
DATA rexp[16];
