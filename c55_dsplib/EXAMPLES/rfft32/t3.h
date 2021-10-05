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
#define NX 32
#define FNAME "t3"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

LDATA x[NX] ={
-1550796758,	/* 0 */ 
-1276486005,	/* 1 */ 
-1293850865,	/* 2 */ 
445740725,	/* 3 */ 
-978347568,	/* 4 */ 
-1293453512,	/* 5 */ 
-2081674443,	/* 6 */ 
1059830416,	/* 7 */ 
-235785447,	/* 8 */ 
1854444029,	/* 9 */ 
-146038586,	/* 10 */ 
-349362936,	/* 11 */ 
1486860965,	/* 12 */ 
108018346,	/* 13 */ 
-1276992163,	/* 14 */ 
739250865,	/* 15 */ 
1452062442,	/* 16 */ 
-2062926265,	/* 17 */ 
778501621,	/* 18 */ 
-517573324,	/* 19 */ 
1424910539,	/* 20 */ 
12080036,	/* 21 */ 
899582813,	/* 22 */ 
-305374425,	/* 23 */ 
-839078104,	/* 24 */ 
-1332793713,	/* 25 */ 
-1316571487,	/* 26 */ 
782564521,	/* 27 */ 
-847035737,	/* 28 */ 
178969940,	/* 29 */ 
-1499339201,	/* 30 */ 
849882510,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

LDATA rtest[NX] ={
-222836899, 
-153637600, 
-274171773, 
-38728025, 
-58451608, 
65896873, 
157221121, 
146207942, 
-67114584, 
22203120, 
-146113604, 
-165372616, 
-22091302, 
48577163, 
-43769018, 
164267866, 
182786645, 
203659546, 
-121461374, 
-19176155, 
111692077, 
172975572, 
-17061108, 
-188116952, 
-74134546, 
145982100, 
49305474, 
41921283, 
90866986, 
166137499, 
-354664523, 
-152891204, 
};

LDATA error;

