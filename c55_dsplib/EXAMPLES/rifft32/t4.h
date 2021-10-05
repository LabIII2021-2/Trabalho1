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

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

LDATA rtest[NX] ={
85664479,	-17817443,	 /* 0 */ 
35459990,	-61345806,	 /* 1 */ 
74187947,	40905207,	 /* 2 */ 
-118929994,	-88735025,	 /* 3 */ 
-9745032,	22951060,	 /* 4 */ 
-212378197,	51243940,	 /* 5 */ 
-54934135,	-74218287,	 /* 6 */ 
-52857486,	106238431,	 /* 7 */ 
-30347771,	138138871,	 /* 8 */ 
15232971,	-16773340,	 /* 9 */ 
122101470,	-45614924,	 /* 10 */ 
-64372777,	-16840806,	 /* 11 */ 
-45550277,	-25325540,	 /* 12 */ 
-16102983,	43933679,	 /* 13 */ 
-506539,	-55729337,	 /* 14 */ 
13409764,	-63163158,	 /* 15 */ 
156556340,	-130754800,	 /* 16 */ 
-168798166,	-6251306,	 /* 17 */ 
64358391,	-231423298,	 /* 18 */ 
-125292699,	142860081,	 /* 19 */ 
-3944480,	-46986325,	 /* 20 */ 
-122102265,	59362433,	 /* 21 */ 
-10736219,	-115842144,	 /* 22 */ 
70993563,	74088244,	 /* 23 */ 
176479186,	-81498069,	 /* 24 */ 
-32131191,	-118284244,	 /* 25 */ 
-64234730,	73925954,	 /* 26 */ 
143844076,	-202049478,	 /* 27 */ 
82270367,	116769339,	 /* 28 */ 
179442295,	-29541424,	 /* 29 */ 
-10240597,	-80812058,	 /* 30 */ 
179142607,	121485756,	 /* 31 */ 
};

LDATA error;

