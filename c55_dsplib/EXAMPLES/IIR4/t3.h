/******************************************************************************************** * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/  *  *  *  Redistribution and use in source and binary forms, with or without  *  modification, are permitted provided that the following conditions  *  are met: * *    Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer. * *    Redistributions in binary form must reproduce the above copyright *    notice, this list of conditions and the following disclaimer in the  *    documentation and/or other materials provided with the    *    distribution. * *    Neither the name of Texas Instruments Incorporated nor the names of *    its contributors may be used to endorse or promote products derived *    from this software without specific prior written permission. * *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS  *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT  *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT  *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. **********************************************************************************************//* Test for iircas4 : rand */
#define NX 16
#define NBIQ 3
#define FNAME "t3"
#define MAXERROR 20

DATA x[NX] ={
-1478,
-1217,
-1233,
424,
-933,
-1233,
-1984,
1009,
-225,
1766,
-140,
-333,
1416,
102,
-1217,
704,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2  ... */
13295,
8236,
-4739,
-12204,

-18889,
-2797,
13046,
-12055,

7128,
-7683,
110,
7165,
};

DATA rtest[NX] ={
-1478,
-1046,
-261,
1354,
-222,
-1447,
-1547,
1842,
895,
1323,
-446,
-1542,
1453,
229,
-1777,
724,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

