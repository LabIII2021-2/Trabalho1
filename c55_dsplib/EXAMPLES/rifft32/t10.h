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

/* Test for rifft32: sine */
#define NX 16
#define FNAME "t10"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

LDATA x[NX] ={
0,	/* 0 */ 
1441296806,	/* 1 */ 
1727988566,	/* 2 */ 
893480651,	/* 3 */ 
0,	/* 4 */ 
-118751616,	/* 5 */ 
296475966,	/* 6 */ 
429064539,	/* 7 */ 
0,	/* 8 */ 
-429064540,	/* 9 */ 
-296475967,	/* 10 */ 
118751615,	/* 11 */ 
0,	/* 12 */ 
-893480652,	/* 13 */ 
-1727988567,	/* 14 */ 
-1441296807,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

LDATA rtest[NX] ={
45040525,	221719743,	 /* 0 */ 
-120277624,	66033043,	 /* 1 */ 
-81488509,	-66644557,	 /* 2 */ 
-23436495,	-348860290,	 /* 3 */ 
45040525,	-168698189,	 /* 4 */ 
113517544,	-120277624,	 /* 5 */ 
171569558,	-59272965,	 /* 6 */ 
210358674,	115676633,	 /* 7 */ 
};

LDATA error;

