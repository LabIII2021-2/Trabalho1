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

/* Test for dlms: sine */
#define NX 40
#define NH 21
#define STEP 1638
#define FNAME "t2"
#define MAXERROR 20

DATA x[NX] ={
0,
11585,
16384,
11585,
0,
-11586,
-16384,
-11586,
-1,
11585,
16384,
11585,
0,
-11586,
-16384,
-11586,
-1,
11585,
16384,
11585,
0,
-11586,
-16384,
-11586,
-1,
11585,
16384,
11585,
0,
-11586,
-16384,
-11586,
-1,
11585,
16384,
11585,
0,
-11586,
-16384,
-11586,
};

DATA des[NX] ={
32767,
23170,
0,
-23171,
-32768,
-23171,
-1,
23170,
32767,
23170,
0,
-23171,
-32768,
-23171,
-1,
23170,
32767,
23170,
0,
-23171,
-32768,
-23171,
-1,
23170,
32767,
23170,
-1,
-23171,
-32768,
-23171,
-1,
23170,
32767,
23170,
-1,
-23171,
-32768,
-23171,
-1,
23170,
};

DATA htest[NH] ={ /* C54x: hn-1 ... h0 (backward order) */
-155,
-1991,
-2909,
-2116,
205,
2827,
4100,
2963,
-253,
-3815,
-5501,
-3957,
288,
4915,
7057,
5061,
-307,
-6074,
-8695,
-6223,
304,
};

DATA rtest[NX] ={
0,
0,
0,
145,
0,
-145,
207,
873,
1637,
1449,
-376,
-2946,
-4748,
-3788,
463,
5808,
8947,
6878,
-448,
-9094,
-13706,
-10329,
343,
12418,
18468,
13665,
-93,
-15001,
-22046,
-16135,
-50,
16968,
24730,
17962,
124,
-18465,
-26743,
-19315,
-156,
19603,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NH+2];

#pragma DATA_SECTION (h,".coeffs")
DATA h[NH];

DATA r[NX];

DATA error;

