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

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
645,	624,	/* 0 */ 
-386,	597,	/* 1 */ 
153,	-129,	/* 2 */ 
-21,	564,	/* 3 */ 
560,	-634,	/* 4 */ 
375,	-211,	/* 5 */ 
-63,	448,	/* 6 */ 
-691,	-703,	/* 7 */ 
460,	-518,	/* 8 */ 
-80,	-427,	/* 9 */ 
165,	-432,	/* 10 */ 
418,	148,	/* 11 */ 
604,	-327,	/* 12 */ 
341,	-432,	/* 13 */ 
-465,	-695,	/* 14 */ 
-136,	353,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
1889,	-1768,	 /* 0 */ 
-1351,	2072,	 /* 1 */ 
-2773,	1766,	 /* 2 */ 
-48,	2030,	 /* 3 */ 
3315,	632,	 /* 4 */ 
1549,	160,	 /* 5 */ 
0,	426,	 /* 6 */ 
-17,	-2384,	 /* 7 */ 
2238,	-1554,	 /* 8 */ 
-298,	-515,	 /* 9 */ 
3282,	2057,	 /* 10 */ 
-1660,	2080,	 /* 11 */ 
1644,	-727,	 /* 12 */ 
2066,	2674,	 /* 13 */ 
-749,	17,	 /* 14 */ 
1232,	3015,	 /* 15 */ 
};

DATA error;

