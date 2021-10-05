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
#define NBIQ 4
#define NH   5 * NBIQ 
#define FNAME "t3"
#define MAXERROR 10

DATA x[NX] ={
23593,
23177,
6131,
-226,
26199,
21078,
9496,
20838,
10500,
-10357,
-13781,
-10408,
2233,
14884,
-12499,
22183,
};

#pragma DATA_SECTION(h,".coeffs")
LDATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
63701277,
128780948,
122632856,
-14796093,
18273043,
-97571160,
-61351598,
6064044,
52228693,
-34785562,
-131061686,
-66483519,
102043544,
32563907,
54422526,
105736074,
100862347,
-87790080,
79140351,
12501335,
};

#pragma DATA_SECTION(dbuffer,".dbuffer")
LDATA dbuffer[2*NBIQ+1] ;

LDATA *dp = dbuffer;

DATA r[NX] ;

DATA rtest[NX] ={
-1,
0,
0,
-1,
-1,
-1,
0,
0,
-1,
-1,
0,
0,
0,
1,
0,
-1,
};

