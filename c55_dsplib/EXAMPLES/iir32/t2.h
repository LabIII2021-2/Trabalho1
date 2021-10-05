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

#define NX 16
#define NBIQ 3
#define NH   5 * NBIQ 
#define FNAME "t2"
#define MAXERROR 10

DATA x[NX] ={
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
};

#pragma DATA_SECTION(h,".coeffs")
LDATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
-93717979,
48915125,
-52447574,
755077,
48661168,
53122916,
-52944976,
-83307855,
56229492,
-32351536,
-32648967,
11186728,
-82293866,
-19087792,
89065726,
};

#pragma DATA_SECTION(dbuffer,".dbuffer")
LDATA dbuffer[2*NBIQ+1] ;

LDATA *dp = dbuffer;

DATA r[NX] ;

DATA rtest[NX] ={
0,
-1,
1,
1,
0,
1,
1,
-1,
-2,
0,
-4,
2,
-1,
-2,
1,
1,
};

