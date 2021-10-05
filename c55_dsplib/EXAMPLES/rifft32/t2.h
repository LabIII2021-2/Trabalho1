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

/* Test for rifft32: rand */
#define NX 16
#define FNAME "t2"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

LDATA x[NX] ={
1380295216,	/* 0 */ 
-237473492,	/* 1 */ 
495728582,	/* 2 */ 
1253734642,	/* 3 */ 
1811491747,	/* 4 */ 
1022990021,	/* 5 */ 
-1390287280,	/* 6 */ 
-404948233,	/* 7 */ 
1870141083,	/* 8 */ 
1790411875,	/* 9 */ 
-385347988,	/* 10 */ 
1690542790,	/* 11 */ 
-1898652503,	/* 12 */ 
-631863368,	/* 13 */ 
1344905360,	/* 14 */ 
-2104919172,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

LDATA rtest[NX] ={
151211866,	-41608664,	 /* 0 */ 
-80605382,	98819026,	 /* 1 */ 
-182839509,	-165846040,	 /* 2 */ 
-193384769,	362902692,	 /* 3 */ 
143087032,	212280204,	 /* 4 */ 
-288592570,	-136411557,	 /* 5 */ 
498928596,	-250207383,	 /* 6 */ 
237900163,	324513894,	 /* 7 */ 
};

LDATA error;

