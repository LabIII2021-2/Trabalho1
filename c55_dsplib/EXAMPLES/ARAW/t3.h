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

#define NX 128
#define NLAGS 128 // max NLAGS = N 
#define FNAME "t3"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
-1539,
282,
2499,
-955,
900,
-627,
737,
1153,
-596,
-501,
899,
1955,
-744,
-433,
548,
380,
1254,
65,
1601,
-62,
-1820,
1162,
2796,
1776,
1179,
-88,
-2233,
954,
-780,
-2086,
386,
1871,
1007,
2893,
2674,
-2556,
-810,
281,
-1380,
563,
-2611,
411,
1163,
2677,
1451,
1390,
-395,
777,
1755,
-2411,
2580,
2409,
590,
-1428,
2163,
77,
1347,
-451,
2672,
-2479,
309,
-1205,
2073,
-952,
1043,
-2587,
-831,
-10,
-380,
361,
675,
-2240,
2306,
1474,
1686,
1824,
984,
-1733,
-1315,
731,
213,
-2552,
-2381,
-1325,
-527,
-151,
2369,
557,
-991,
-127,
562,
-1962,
1908,
2642,
553,
-2730,
1807,
637,
1167,
-2363,
-436,
-721,
-1934,
1929,
1961,
-281,
2644,
-2044,
2142,
1560,
-324,
698,
2616,
811,
-1464,
-854,
-1809,
-55,
-526,
-212,
642,
-2485,
-1076,
627,
-1883,
701,
-1472,
506,
};

DATA rtest[NLAGS] ={ // lag0, lag1,...  
9141, 
11, 
46, 
-147, 
237, 
-1017, 
913, 
-606, 
13, 
-1109, 
474, 
499, 
1183, 
-1005, 
606, 
-1231, 
35, 
1032, 
-72, 
803, 
975, 
161, 
-144, 
81, 
297, 
-19, 
-197, 
-867, 
-235, 
470, 
379, 
57, 
372, 
-142, 
-32, 
-157, 
1302, 
-452, 
-523, 
496, 
775, 
195, 
1498, 
-163, 
-444, 
-220, 
496, 
-1062, 
44, 
-487, 
250, 
18, 
209, 
932, 
52, 
307, 
578, 
-598, 
37, 
68, 
-260, 
642, 
717, 
121, 
-415, 
700, 
-730, 
-203, 
-794, 
373, 
108, 
-151, 
-60, 
-315, 
-397, 
530, 
-104, 
-593, 
1, 
163, 
-440, 
383, 
490, 
-490, 
-278, 
-12, 
548, 
256, 
58, 
-77, 
490, 
6, 
-148, 
-465, 
53, 
341, 
164, 
-121, 
-50, 
-164, 
-508, 
227, 
530, 
-557, 
90, 
-248, 
-9, 
161, 
-268, 
18, 
-50, 
-28, 
-222, 
-58, 
-132, 
-139, 
127, 
-113, 
104, 
-135, 
-232, 
269, 
-158, 
65, 
-33, 
-7, 
73, 
-24, 
};

