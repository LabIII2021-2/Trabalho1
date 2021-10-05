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

/* Test for sqrtv: rand */
#define NX 40
#define FNAME "t2"
#define MAXERROR 20

DATA x[NX] ={
20166,
25950,
30205,
24189,
5775,
13294,
30653,
30045,
13443,
29283,
1896,
11562,
26645,
323,
4551,
6644,
6511,
19785,
8919,
6514,
500,
24470,
14584,
30533,
15269,
13718,
27728,
17208,
6640,
22024,
27463,
643,
22324,
12434,
27256,
16476,
23247,
14053,
9981,
6214,
};

DATA rtest[NX] = {
25706,
29160,
31460,
28153,
13757,
20871,
31693,
31377,
20988,
30976,
7884,
19465,
29548,
3253,
12212,
14755,
14607,
25462,
17095,
14610,
4049,
28317,
21861,
31631,
22368,
21201,
30143,
23746,
14750,
26864,
29998,
4592,
27046,
20185,
29885,
23235,
27600,
21459,
18085,
14270,
};

DATA r[NX];
