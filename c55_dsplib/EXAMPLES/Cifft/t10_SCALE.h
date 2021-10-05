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

/* Test for cfft: sine */
#define NX 16
#define FNAME "t10"
#define MAXERROR 16
#define SCALING 1

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
0,	0,	/* 0 */ 
1708,	0,	/* 1 */ 
2047,	0,	/* 2 */ 
1058,	0,	/* 3 */ 
0,	0,	/* 4 */ 
-141,	0,	/* 5 */ 
351,	0,	/* 6 */ 
508,	0,	/* 7 */ 
0,	0,	/* 8 */ 
-509,	0,	/* 9 */ 
-352,	0,	/* 10 */ 
140,	0,	/* 11 */ 
0,	0,	/* 12 */ 
-1059,	0,	/* 13 */ 
-2048,	0,	/* 14 */ 
-1709,	0,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
-1,	0,	 /* 0 */ 
-1,	424,	 /* 1 */ 
-1,	424,	 /* 2 */ 
-1,	424,	 /* 3 */ 
0,	0,	 /* 4 */ 
0,	0,	 /* 5 */ 
0,	0,	 /* 6 */ 
0,	-1,	 /* 7 */ 
-1,	0,	 /* 8 */ 
0,	0,	 /* 9 */ 
0,	-1,	 /* 10 */ 
0,	-1,	 /* 11 */ 
0,	-1,	 /* 12 */ 
-1,	-425,	 /* 13 */ 
-1,	-425,	 /* 14 */ 
-1,	-425,	 /* 15 */ 
};

DATA error;

