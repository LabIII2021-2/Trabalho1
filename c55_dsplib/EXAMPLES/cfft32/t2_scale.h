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
#define MAXERROR 10
#define SCALING 1

#pragma DATA_SECTION (x,".input")

LDATA x[2*NX] ={
1558015820,	-196433018,	/* 0 */ 
1491593362,	1544938593,	/* 1 */ 
-321033674,	-121664846,	/* 2 */ 
1408392358,	-291054502,	/* 3 */ 
-1581768704,	1238704891,	/* 4 */ 
-526405806,	89990158,	/* 5 */ 
1120441578,	-1063863047,	/* 6 */ 
-1753609607,	615870403,	/* 7 */ 
-1291969843,	1209714217,	/* 8 */ 
-1063441367,	-1718625288,	/* 9 */ 
-1077908044,	648570235,	/* 10 */ 
371346904,	-431190692,	/* 11 */ 
-815062030,	1187093948,	/* 12 */ 
-1077577009,	10063886,	/* 13 */ 
-1734244408,	749443059,	/* 14 */ 
882945447,	-254407643,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

LDATA rtest[2*NX] ={
-275642814,	201071897,	 /* 0 */ 
397436492,	-103600753,	 /* 1 */ 
131697436,	-210356249,	 /* 2 */ 
482982241,	-245052003,	 /* 3 */ 
10569348,	331968784,	 /* 4 */ 
525557780,	62475668,	 /* 5 */ 
81179505,	-380090274,	 /* 6 */ 
-3452385,	-159487877,	 /* 7 */ 
-242298350,	255373782,	 /* 8 */ 
-448513956,	-203353846,	 /* 9 */ 
306327824,	131933904,	 /* 10 */ 
-176118236,	-437969914,	 /* 11 */ 
-25324375,	71355544,	 /* 12 */ 
250918834,	84618789,	 /* 13 */ 
146514411,	105383207,	 /* 14 */ 
396182058,	299296314,	 /* 15 */ 
};

LDATA error;

