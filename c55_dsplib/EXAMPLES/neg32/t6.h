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

/* This is a test for neg32: rand */
#define NX 32
#define FNAME "t6"
#define MAXERROR 10

LDATA x[NX] ={
1266246771,
1962127474,
97024800,
1632698185,
-1404642538,
2060497026,
-981626452,
-1063737249,
1613799010,
1019221357,
-1561139959,
-2096988851,
1691778714,
-1292192033,
-864477995,
693390516,
-925957964,
-132180676,
-1869250657,
2097382379,
355587529,
-328581042,
66622461,
-713172892,
-288163947,
-1177036237,
342767876,
1118259090,
128089298,
603556657,
-1249537269,
-516176118,
};

LDATA rtest[NX] ={
-1266246772,
-1962127475,
-97024801,
-1632698186,
1404642537,
-2060497027,
981626451,
1063737248,
-1613799011,
-1019221358,
1561139958,
2096988850,
-1691778715,
1292192032,
864477994,
-693390517,
925957963,
132180675,
1869250656,
-2097382380,
-355587530,
328581041,
-66622462,
713172891,
288163946,
1177036236,
-342767877,
-1118259091,
-128089299,
-603556658,
1249537268,
516176117,
};

LDATA r[NX]; 
