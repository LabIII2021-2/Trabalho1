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
#define NX 64
#define FNAME "t4"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

LDATA x[NX] ={
-522331747,	/* 0 */ 
1546083445,	/* 1 */ 
1518785326,	/* 2 */ 
401809464,	/* 3 */ 
-14805636,	/* 4 */ 
1716823833,	/* 5 */ 
1381248588,	/* 6 */ 
622323122,	/* 7 */ 
1365552825,	/* 8 */ 
688103297,	/* 9 */ 
-678663154,	/* 10 */ 
-903030089,	/* 11 */ 
-682000219,	/* 12 */ 
146353629,	/* 13 */ 
975346294,	/* 14 */ 
-819010618,	/* 15 */ 
1453684059,	/* 16 */ 
292339756,	/* 17 */ 
-556513880,	/* 18 */ 
870674220,	/* 19 */ 
200001571,	/* 20 */ 
-236714045,	/* 21 */ 
835576368,	/* 22 */ 
520970942,	/* 23 */ 
1266120272,	/* 24 */ 
1961931457,	/* 25 */ 
97015108,	/* 26 */ 
1632535078,	/* 27 */ 
-1404502214,	/* 28 */ 
2060291182,	/* 29 */ 
-981528387,	/* 30 */ 
-1063630982,	/* 31 */ 
1613637791,	/* 32 */ 
1019119537,	/* 33 */ 
-1560984001,	/* 34 */ 
-2096779362,	/* 35 */ 
1691609705,	/* 36 */ 
-1292062943,	/* 37 */ 
-864391633,	/* 38 */ 
693321246,	/* 39 */ 
-925865461,	/* 40 */ 
-132167471,	/* 41 */ 
-1869063919,	/* 42 */ 
2097172851,	/* 43 */ 
355552005,	/* 44 */ 
-328548217,	/* 45 */ 
66615805,	/* 46 */ 
-713101646,	/* 47 */ 
-288135160,	/* 48 */ 
-1176918651,	/* 49 */ 
342733633,	/* 50 */ 
1118147376,	/* 51 */ 
128076502,	/* 52 */ 
603496361,	/* 53 */ 
-1249412440,	/* 54 */ 
-516124552,	/* 55 */ 
1216765596,	/* 56 */ 
776648915,	/* 57 */ 
-167078450,	/* 58 */ 
291292969,	/* 59 */ 
1263498763,	/* 60 */ 
-1893107015,	/* 61 */ 
441775176,	/* 62 */ 
-1931387622,	/* 63 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

LDATA rtest[NX] ={
162580852, 
-23570881, 
54701666, 
-151116086, 
20429413, 
73043449, 
41382316, 
-168150467, 
-109317734, 
-56504827, 
-79505394, 
-109453862, 
-82163356, 
-69455274, 
-86422787, 
81373902, 
30170339, 
-65153509, 
35448282, 
-168655811, 
155656706, 
-44037800, 
-78487807, 
-31672833, 
-33111457, 
-56234305, 
-63206190, 
-11322806, 
7465217, 
-131734952, 
-600703, 
-73895746, 
140396847, 
-86663917, 
-187106686, 
39208180, 
24067648, 
-117285654, 
-110508479, 
231535069, 
-48702286, 
-90126475, 
-140306223, 
38483471, 
-76610442, 
-64473031, 
18459265, 
60058697, 
83642088, 
-173872231, 
-30884878, 
-62607557, 
-69324497, 
89219655, 
-21347714, 
-263376397, 
149524082, 
64123867, 
-13189003, 
-160201778, 
11198950, 
11203094, 
127581943, 
13916330, 
};

LDATA error;

