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
#define NX 16
#define FNAME "t2"
#define MAXERROR 16
#define SCALING 1

#pragma DATA_SECTION (x,".input")

LDATA x[2*NX] ={
1485,	-188,	/* 0 */ 
1422,	1473,	/* 1 */ 
-307,	-117,	/* 2 */ 
1343,	-278,	/* 3 */ 
-1509,	1181,	/* 4 */ 
-503,	85,	/* 5 */ 
1068,	-1015,	/* 6 */ 
-1673,	587,	/* 7 */ 
-1233,	1153,	/* 8 */ 
-1015,	-1640,	/* 9 */ 
-1028,	618,	/* 10 */ 
354,	-412,	/* 11 */ 
-778,	1132,	/* 12 */ 
-1028,	9,	/* 13 */ 
-1654,	714,	/* 14 */ 
842,	-243,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

LDATA rtest[2*NX] ={
-263,	191,	 /* 0 */ 
377,	285,	 /* 1 */ 
139,	100,	 /* 2 */ 
239,	80,	 /* 3 */ 
-25,	68,	 /* 4 */ 
-168,	-418,	 /* 5 */ 
292,	125,	 /* 6 */ 
-428,	-194,	 /* 7 */ 
-232,	243,	 /* 8 */ 
-4,	-153,	 /* 9 */ 
77,	-363,	 /* 10 */ 
501,	59,	 /* 11 */ 
10,	316,	 /* 12 */ 
460,	-234,	 /* 13 */ 
125,	-201,	 /* 14 */ 
379,	-99,	 /* 15 */ 
};

DATA error;

