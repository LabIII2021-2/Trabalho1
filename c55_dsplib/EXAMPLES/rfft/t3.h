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

/* Test for rfft: rand */
#define NX 32
#define FNAME "t3"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
-23664,	/* 0 */ 
-19478,	/* 1 */ 
-19743,	/* 2 */ 
6801,	/* 3 */ 
-14929,	/* 4 */ 
-19737,	/* 5 */ 
-31764,	/* 6 */ 
16171,	/* 7 */ 
-3598,	/* 8 */ 
28296,	/* 9 */ 
-2229,	/* 10 */ 
-5331,	/* 11 */ 
22687,	/* 12 */ 
1648,	/* 13 */ 
-19486,	/* 14 */ 
11280,	/* 15 */ 
22156,	/* 16 */ 
-31478,	/* 17 */ 
11878,	/* 18 */ 
-7898,	/* 19 */ 
21742,	/* 20 */ 
184,	/* 21 */ 
13726,	/* 22 */ 
-4660,	/* 23 */ 
-12804,	/* 24 */ 
-20337,	/* 25 */ 
-20090,	/* 26 */ 
11940,	/* 27 */ 
-12925,	/* 28 */ 
2730,	/* 29 */ 
-22879,	/* 30 */ 
12968,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
-3401, 
-2345, 
-4184, 
-591, 
-892, 
1005, 
2399, 
2230, 
-1025, 
338, 
-2230, 
-2524, 
-338, 
741, 
-668, 
2506, 
2789, 
3107, 
-1854, 
-293, 
1704, 
2639, 
-261, 
-2871, 
-1132, 
2227, 
752, 
639, 
1386, 
2535, 
-5412, 
-2333, 
};

DATA error;

