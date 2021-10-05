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

/* Test for cfft: both */
#define NX 32
#define FNAME "t11"
#define MAXERROR 16
#define SCALING 1

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
724,	724,	/* 0 */ 
660,	660,	/* 1 */ 
486,	486,	/* 2 */ 
245,	245,	/* 3 */ 
0,	0,	/* 4 */ 
-195,	-195,	/* 5 */ 
-302,	-302,	/* 6 */ 
-310,	-310,	/* 7 */ 
-242,	-242,	/* 8 */ 
-136,	-136,	/* 9 */ 
-41,	-41,	/* 10 */ 
10,	10,	/* 11 */ 
0,	0,	/* 12 */ 
-62,	-62,	/* 13 */ 
-145,	-145,	/* 14 */ 
-215,	-215,	/* 15 */ 
-242,	-242,	/* 16 */ 
-215,	-215,	/* 17 */ 
-145,	-145,	/* 18 */ 
-62,	-62,	/* 19 */ 
-1,	-1,	/* 20 */ 
10,	10,	/* 21 */ 
-41,	-41,	/* 22 */ 
-136,	-136,	/* 23 */ 
-242,	-242,	/* 24 */ 
-310,	-310,	/* 25 */ 
-302,	-302,	/* 26 */ 
-195,	-195,	/* 27 */ 
-1,	-1,	/* 28 */ 
245,	245,	/* 29 */ 
486,	486,	/* 30 */ 
660,	660,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
-1,	-1,	 /* 0 */ 
120,	120,	 /* 1 */ 
120,	120,	 /* 2 */ 
120,	120,	 /* 3 */ 
0,	0,	 /* 4 */ 
0,	0,	 /* 5 */ 
-1,	0,	 /* 6 */ 
-1,	0,	 /* 7 */ 
-1,	0,	 /* 8 */ 
-1,	0,	 /* 9 */ 
0,	0,	 /* 10 */ 
-1,	0,	 /* 11 */ 
0,	-1,	 /* 12 */ 
0,	0,	 /* 13 */ 
0,	0,	 /* 14 */ 
0,	0,	 /* 15 */ 
0,	0,	 /* 16 */ 
0,	0,	 /* 17 */ 
0,	-1,	 /* 18 */ 
0,	-1,	 /* 19 */ 
-1,	0,	 /* 20 */ 
0,	-1,	 /* 21 */ 
0,	0,	 /* 22 */ 
0,	-1,	 /* 23 */ 
0,	-1,	 /* 24 */ 
-1,	-1,	 /* 25 */ 
0,	-1,	 /* 26 */ 
0,	0,	 /* 27 */ 
0,	0,	 /* 28 */ 
120,	120,	 /* 29 */ 
120,	120,	 /* 30 */ 
120,	120,	 /* 31 */ 
};

DATA error;

