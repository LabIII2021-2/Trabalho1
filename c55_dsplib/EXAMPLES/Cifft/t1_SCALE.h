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
3204,	2288,	/* 0 */ 
-1915,	-394,	/* 1 */ 
760,	821,	/* 2 */ 
-100,	2078,	/* 3 */ 
2785,	3002,	/* 4 */ 
1865,	1695,	/* 5 */ 
-310,	-2305,	/* 6 */ 
-3428,	-672,	/* 7 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
358,	814,	 /* 0 */ 
-1026,	-424,	 /* 1 */ 
705,	1281,	 /* 2 */ 
1013,	164,	 /* 3 */ 
1252,	137,	 /* 4 */ 
348,	512,	 /* 5 */ 
679,	411,	 /* 6 */ 
-127,	-611,	 /* 7 */ 
};

DATA error;

