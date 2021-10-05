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
#define NX 16
#define FNAME "t2"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
21061,	/* 0 */ 
-3624,	/* 1 */ 
7564,	/* 2 */ 
19130,	/* 3 */ 
27641,	/* 4 */ 
15609,	/* 5 */ 
-21215,	/* 6 */ 
-6180,	/* 7 */ 
28536,	/* 8 */ 
27319,	/* 9 */ 
-5880,	/* 10 */ 
25795,	/* 11 */ 
-28972,	/* 12 */ 
-9642,	/* 13 */ 
20521,	/* 14 */ 
-32119,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
5347, 
810, 
-2077, 
-3242, 
288, 
-4611, 
-2424, 
5522, 
2954, 
-1440, 
-3389, 
-4056, 
6077, 
-4313, 
6019, 
1334, 
};

DATA error;

