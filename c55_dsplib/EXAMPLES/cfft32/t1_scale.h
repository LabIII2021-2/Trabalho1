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
#define NX 8
#define FNAME "t1"
#define MAXERROR 10
#define SCALING 1

#pragma DATA_SECTION (x,".input")

LDATA x[2*NX] ={
1680065448,	1199622173,	/* 0 */ 
-1003500347,	-206389520,	/* 1 */ 
398779948,	430840440,	/* 2 */ 
-52319125,	1089627682,	/* 3 */ 
1460486785,	1574377453,	/* 4 */ 
978251910,	889086261,	/* 5 */ 
-162480368,	-1208306332,	/* 6 */ 
-1797140109,	-351942739,	/* 7 */ 
};

#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
187768018,	427114427,	 /* 0 */ 
-66454239,	-320305308,	 /* 1 */ 
356158056,	215906840,	 /* 2 */ 
182530370,	268500414,	 /* 3 */ 
656444935,	72019006,	 /* 4 */ 
531135597,	86301408,	 /* 5 */ 
369905106,	671959539,	 /* 6 */ 
-537422399,	-221874156,	 /* 7 */ 
};

LDATA error;

