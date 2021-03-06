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

#define NX 152
#define NLAGS 152 // max NLAGS = N 
#define FNAME "t7"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
-547,
-460,
825,
1794,
-683,
-398,
503,
349,
1151,
60,
1469,
-57,
-1670,
1066,
2565,
1629,
1082,
-80,
-2049,
876,
-716,
-1914,
354,
1717,
924,
2654,
2453,
-2345,
-743,
257,
-1267,
517,
-2396,
377,
1067,
2457,
1331,
1275,
-363,
713,
1610,
-2212,
2367,
2211,
542,
-1310,
1985,
71,
1236,
-414,
2452,
-2275,
283,
-1106,
1902,
-874,
957,
-2374,
-762,
-10,
-349,
332,
619,
-2056,
2116,
1353,
1547,
1674,
903,
-1591,
-1207,
671,
195,
-2342,
-2185,
-1216,
-484,
-138,
2174,
511,
-910,
-116,
516,
-1800,
1751,
2424,
507,
-2506,
1659,
585,
1071,
-2168,
-400,
-662,
-1775,
1770,
1800,
-258,
2427,
-1876,
1966,
1432,
-297,
641,
2401,
744,
-1344,
-783,
-1660,
-50,
-483,
-194,
589,
-2280,
-988,
576,
-1728,
643,
-1351,
464,
32,
-188,
220,
2351,
-842,
-522,
-1023,
-471,
-1138,
-563,
16,
1179,
-1031,
-2062,
-302,
-177,
-2580,
872,
1191,
-1161,
-1267,
1108,
1508,
2584,
-142,
2141,
-261,
1618,
1748,
-1774,
-564,
110,
};

DATA rtest[NLAGS] ={ // lag0, lag1,... 
59,
2,
0,
0,
3,
-7,
6,
-4,
1,
-10,
2,
3,
5,
-6,
3,
-8,
-1,
4,
1,
6,
7,
-1,
2,
2,
1,
1,
-2,
-5,
-1,
-3,
0,
-1,
-4,
3,
2,
-5,
5,
-4,
-3,
3,
1,
2,
11,
0,
-4,
3,
2,
-2,
-3,
-5,
1,
-2,
2,
9,
-4,
2,
2,
0,
2,
6,
-3,
3,
3,
4,
-1,
2,
-4,
0,
-11,
2,
0,
-3,
-5,
-1,
-5,
6,
4,
0,
-2,
3,
-1,
6,
0,
-1,
-4,
-3,
0,
3,
0,
1,
-5,
-2,
-1,
-2,
-1,
5,
-2,
0,
3,
-1,
-2,
2,
-1,
-2,
0,
0,
2,
0,
4,
3,
-4,
-4,
3,
-2,
-2,
-1,
-1,
1,
0,
0,
0,
0,
1,
-1,
-1,
-3,
-3,
0,
4,
2,
-2,
1,
2,
0,
1,
1,
-1,
1,
1,
1,
1,
0,
0,
-1,
0,
1,
0,
-1,
0,
0,
0,
0,
};

