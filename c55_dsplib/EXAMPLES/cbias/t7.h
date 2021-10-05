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

#define NA 24
#define NB 24  // NB <= NA 
#define FNAME "t7"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
1550,
2165,
1560,
2476,
135,
2862,
203,
1416,
6243,
4309,
-2439,
1173,
-4947,
-3287,
4053,
2245,
-6507,
823,
-608,
5417,
-2915,
-5819,
-314,
6470,
};

DATA b[NB] ={
5649,
818,
2037,
3647,
-5269,
-6675,
558,
-6597,
-651,
-4072,
3841,
1586,
-6482,
5228,
3500,
5445,
3458,
-1596,
-2260,
54,
863,
3574,
3743,
-213,
};

DATA rtest[NA+NB-1] ={
0,
7,
17,
18,
21,
9,
8,
12,
19,
59,
84,
35,
17,
-4,
-57,
53,
64,
25,
21,
-119,
-89,
17,
-64,
-54,
-12,
-71,
-5,
61,
17,
-2,
-15,
131,
150,
-110,
-12,
17,
22,
-10,
-10,
-8,
52,
-86,
-24,
2,
-25,
4,
46,
};

