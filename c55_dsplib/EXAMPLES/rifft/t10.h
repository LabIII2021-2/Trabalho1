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

/* Test for rfft: sine */
#define NX 16
#define FNAME "t10"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
0,	/* 0 */ 
21992,	/* 1 */ 
26367,	/* 2 */ 
13633,	/* 3 */ 
0,	/* 4 */ 
-1813,	/* 5 */ 
4523,	/* 6 */ 
6547,	/* 7 */ 
0,	/* 8 */ 
-6548,	/* 9 */ 
-4524,	/* 10 */ 
1812,	/* 11 */ 
0,	/* 12 */ 
-13634,	/* 13 */ 
-26368,	/* 14 */ 
-21993,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

DATA rtest[NX] ={
687,	3383,	 /* 0 */ 
-1836,	1007,	 /* 1 */ 
-1244,	-1017,	 /* 2 */ 
-358,	-5324,	 /* 3 */ 
687,	-2575,	 /* 4 */ 
1732,	-1836,	 /* 5 */ 
2617,	-905,	 /* 6 */ 
3209,	1765,	 /* 7 */ 
};

DATA error;

