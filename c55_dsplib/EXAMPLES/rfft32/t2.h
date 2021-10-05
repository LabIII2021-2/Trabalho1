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

/* Test for rfft32: rand */
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

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

LDATA rtest[NX] ={
350421830, 
53112447, 
-136080735, 
-212432866, 
18903700, 
-302121892, 
-158817495, 
361892591, 
193642304, 
-94353439, 
-222049299, 
-265757696, 
398295931, 
-282651578, 
394486060, 
87452909, 
};

LDATA error;

