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

/* Test for cfft: rand */
#define NX 8
#define FNAME "t1"
#define MAXERROR 16
#define SCALING 1

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
25635,	18304,	/* 0 */ 
-15313,	-3150,	/* 1 */ 
6084,	6574,	/* 2 */ 
-799,	16626,	/* 3 */ 
22285,	24023,	/* 4 */ 
14926,	13566,	/* 5 */ 
-2480,	-18438,	/* 6 */ 
-27423,	-5371,	/* 7 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
2865,	6517,	 /* 0 */ 
-1015,	-4888,	 /* 1 */ 
5434,	3294,	 /* 2 */ 
2785,	4096,	 /* 3 */ 
10016,	1098,	 /* 4 */ 
8104,	1316,	 /* 5 */ 
5644,	10253,	 /* 6 */ 
-8201,	-3386,	 /* 7 */ 
};

DATA error;

