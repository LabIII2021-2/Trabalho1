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

#define NA 32
#define NB 32  // NB <= NA 
#define FNAME "t8"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
5033,
-4301,
2164,
-2349,
1705,
-420,
4898,
-2993,
1855,
-1943,
-270,
-362,
2385,
-3013,
2516,
4230,
-1032,
-872,
5263,
4418,
2300,
-2255,
3815,
5452,
-2316,
5770,
-687,
-5721,
-2411,
2222,
-83,
-4826,
};

DATA b[NB] ={
-3525,
5533,
-1551,
-4178,
-5622,
1629,
2754,
-5483,
-4610,
4556,
3057,
957,
2148,
5411,
583,
3211,
1278,
5660,
-5234,
5623,
-3421,
4778,
1917,
-437,
-5233,
-459,
3474,
-2440,
2260,
-2789,
2470,
2553,
};

DATA rtest[NA+NB-1] ={
392,
22,
-195,
173,
-180,
217,
-92,
-6,
-35,
83,
-12,
-23,
81,
-175,
156,
-34,
108,
-90,
147,
-100,
146,
-56,
30,
-31,
88,
-29,
20,
-72,
60,
-37,
64,
-53,
36,
10,
106,
46,
13,
95,
21,
7,
122,
38,
-113,
-100,
165,
-55,
-249,
-82,
29,
-203,
-43,
48,
-87,
-152,
64,
414,
-136,
-215,
188,
313,
-8,
-403,
519,
};

