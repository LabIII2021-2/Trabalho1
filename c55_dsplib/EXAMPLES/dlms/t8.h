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

/* Test for dlms: rand */
#define NX 32
#define NH 3
#define STEP 1310
#define FNAME "t8"
#define MAXERROR 20

DATA x[NX] ={
-10371,
-6436,
-12604,
-5796,
-14029,
-6939,
197,
14547,
-12701,
-25417,
-3717,
-2179,
-31807,
10751,
14683,
-14311,
-15610,
13662,
18602,
31860,
-1747,
26398,
-3208,
19956,
21552,
-21872,
-6953,
1360,
14294,
4534,
-2569,
-3585,
};

DATA des[NX] ={
-27018,
-3704,
-8763,
-12942,
23058,
17005,
29475,
3797,
-31835,
6302,
20722,
31266,
-18225,
13348,
1445,
28370,
13982,
-17824,
-3301,
-21483,
30724,
-9456,
-29554,
16733,
25874,
-14015,
-16306,
28359,
-24184,
28889,
13228,
22785,
};

DATA htest[NH] ={ /* C54x: hn-1 ... h0 (backward order) */
-1196,
-682,
288,
};

DATA rtest[NX] ={
0,
0,
-132,
-84,
-278,
-297,
34,
78,
-203,
-299,
990,
634,
-84,
1967,
1659,
-2089,
-401,
1676,
-50,
-1293,
-2019,
-1756,
-512,
-1254,
-1700,
-769,
596,
668,
403,
-525,
-840,
-176,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NH+2];

#pragma DATA_SECTION (h,".coeffs")
DATA h[NH];

DATA r[NX];

DATA error;

