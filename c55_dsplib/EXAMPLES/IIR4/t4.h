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

/* Test for iircas4 : rand */
#define NX 16
#define NBIQ 4
#define FNAME "t4"
#define MAXERROR 20

DATA x[NX] ={
-808,
170,
-1429,
809,
-498,
1473,
1447,
382,
-15,
1635,
1316,
592,
1301,
655,
-647,
-861,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2  ... */
-6245,
1831,
13310,
11592,

1340,
-2168,
2676,
17963,

8930,
7650,
-5096,
888,

-7500,
4770,
7972,
14947,
};

DATA rtest[NX] ={
-807,
-213,
-2125,
136,
-1587,
1821,
1584,
2634,
1700,
2578,
2252,
2767,
3114,
2390,
1147,
-277,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ+2];  // index + (2*NBIQ+1)
DATA *dp = dbuffer;

DATA r[NX];

