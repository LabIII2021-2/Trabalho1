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

/* Test for expn: nois */
#define NX 50
#define FNAME "t6"
#define MAXERROR 10

DATA x[NX] ={
5124,
4001,
24989,
23650,
21351,
24705,
21728,
28947,
8917,
13743,
6979,
1166,
2659,
27869,
11147,
15273,
29939,
7489,
28245,
21514,
29199,
15994,
32524,
12232,
17410,
5941,
16446,
13833,
21639,
22072,
31367,
6286,
3644,
18514,
31754,
778,
28512,
881,
17022,
6300,
23449,
8213,
30598,
4495,
17091,
29331,
30877,
10979,
14330,
15437,
};

DATA rtest[] ={
4789,
4628,
8781,
8430,
7858,
8706,
7949,
9909,
5377,
6230,
5068,
4244,
4442,
9588,
5756,
6528,
10213,
5148,
9698,
7898,
9985,
6673,
11051,
5949,
6968,
4910,
6766,
6247,
7928,
8033,
10668,
4962,
4578,
7207,
10795,
4194,
9778,
4208,
6886,
4964,
8378,
5263,
10421,
4698,
6900,
10025,
10510,
5726,
6343,
6561,
};

DATA r[NX];

