/******************************************************************************************** * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/  *  *  *  Redistribution and use in source and binary forms, with or without  *  modification, are permitted provided that the following conditions  *  are met: * *    Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer. * *    Redistributions in binary form must reproduce the above copyright *    notice, this list of conditions and the following disclaimer in the  *    documentation and/or other materials provided with the    *    distribution. * *    Neither the name of Texas Instruments Incorporated nor the names of *    its contributors may be used to endorse or promote products derived *    from this software without specific prior written permission. * *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS  *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT  *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT  *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. **********************************************************************************************//* Test for iircas4 : rand */
#define NX 32
#define NBIQ 3
#define FNAME "t5"
#define MAXERROR 20

DATA x[NX] ={
-670,
981,
-468,
-507,
768,
485,
-744,
-999,
805,
-616,
-412,
330,
-442,
-63,
-891,
999,
169,
-157,
31,
-340,
-138,
-561,
163,
532,
61,
287,
-596,
-246,
579,
370,
-80,
138,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2  ... */
11568,
14720,
-17685,
18514,

-17334,
-19071,
-3328,
19270,

4044,
10536,
-7668,
11358,
};

DATA rtest[NX] ={
-669,
820,
-1764,
1383,
-1936,
1961,
-1835,
1263,
-1509,
-475,
-1381,
-1694,
-1682,
-1845,
-2845,
-659,
-3416,
925,
-3079,
1545,
-2651,
718,
-2403,
216,
-1799,
841,
-1608,
1267,
-1378,
1604,
-876,
2025,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

