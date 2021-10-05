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

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

LDATA rtest[NX] ={
-183951144,	-5140013,	 /* 0 */ 
-396249023,	-54829487,	 /* 1 */ 
99108823,	-6230952,	 /* 2 */ 
215738631,	40263744,	 /* 3 */ 
-4394073,	25687055,	 /* 4 */ 
-229147005,	-159911617,	 /* 5 */ 
29678911,	-125544625,	 /* 6 */ 
-26076336,	-42206185,	 /* 7 */ 
187072750,	142729374,	 /* 8 */ 
-130581845,	-71883878,	 /* 9 */ 
68494075,	196926879,	 /* 10 */ 
74544504,	-102231242,	 /* 11 */ 
-128282846,	84661174,	 /* 12 */ 
-639824,	-87817076,	 /* 13 */ 
-58121233,	168353825,	 /* 14 */ 
-224015062,	-71404673,	 /* 15 */ 
};

LDATA error;

