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
#define NX 32
#define FNAME "t3"
#define MAXERROR 10
#define SCALING 1

#pragma DATA_SECTION (x,".input")

LDATA x[2*NX] ={
-759715774,	1146367113,	/* 0 */ 
-1206734394,	1776366550,	/* 1 */ 
-1192046512,	87839150,	/* 2 */ 
708547403,	1478125392,	/* 3 */ 
-766920752,	-1271660507,	/* 4 */ 
162042468,	1865423139,	/* 5 */ 
-1357527550,	-888692716,	/* 6 */ 
769498270,	-963029820,	/* 7 */ 
-472928165,	1461015463,	/* 8 */ 
1399850593,	922728390,	/* 9 */ 
1375134406,	-1413341814,	/* 10 */ 
363805213,	-1898460167,	/* 11 */ 
-13405278,	1531612578,	/* 12 */ 
1554441883,	-1169856054,	/* 13 */ 
1250606273,	-782635080,	/* 14 */ 
563462079,	627745004,	/* 15 */ 
1236395060,	-838294543,	/* 16 */ 
623020583,	-119666706,	/* 17 */ 
-614473314,	-1692282680,	/* 18 */ 
-817619004,	1898816438,	/* 19 */ 
-617494751,	321922913,	/* 20 */ 
132511098,	-297473218,	/* 21 */ 
883095342,	60315098,	/* 22 */ 
-741546327,	-645654519,	/* 23 */ 
1316190598,	-260882539,	/* 24 */ 
264689453,	-1065602427,	/* 25 */ 
-503877257,	310316938,	/* 26 */ 
788323443,	1012389902,	/* 27 */ 
181084869,	115962671,	/* 28 */ 
-214324976,	546416005,	/* 29 */ 
756545242,	-1131239554,	/* 30 */ 
471696068,	-467308063,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

LDATA rtest[2*NX] ={
172572697,	8040073,	 /* 0 */ 
-185525506,	135860670,	 /* 1 */ 
64250770,	332904282,	 /* 2 */ 
-52006049,	-29165753,	 /* 3 */ 
168186218,	40667059,	 /* 4 */ 
84899676,	92401131,	 /* 5 */ 
2028156,	121963320,	 /* 6 */ 
34041927,	239625788,	 /* 7 */ 
28795646,	220201070,	 /* 8 */ 
251660347,	-26017060,	 /* 9 */ 
-168885142,	25221128,	 /* 10 */ 
-190644282,	109167750,	 /* 11 */ 
189602689,	35343846,	 /* 12 */ 
14416216,	276409217,	 /* 13 */ 
277588663,	-247729088,	 /* 14 */ 
-71822982,	-278525299,	 /* 15 */ 
-128781295,	-210769918,	 /* 16 */ 
-101308003,	106274090,	 /* 17 */ 
-232352009,	-133770855,	 /* 18 */ 
208864128,	175258503,	 /* 19 */ 
-7469877,	164229804,	 /* 20 */ 
-121570771,	267916556,	 /* 21 */ 
171875909,	23423074,	 /* 22 */ 
-199563334,	-453903512,	 /* 23 */ 
-59686324,	258284167,	 /* 24 */ 
-10847548,	20021870,	 /* 25 */ 
-33500620,	-141850214,	 /* 26 */ 
-450675298,	65561702,	 /* 27 */ 
-33234328,	-138944731,	 /* 28 */ 
-277623,	70578628,	 /* 29 */ 
-172651517,	-203176739,	 /* 30 */ 
-207696322,	220866541,	 /* 31 */ 
};

LDATA error;

