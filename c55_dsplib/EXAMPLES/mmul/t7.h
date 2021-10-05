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

/* Test for mmul: rand */
#define row1 12
#define col1 5
#define row2 5
#define col2 8
#define FNAME "t7"
#define MAXERROR 10

DATA x1[row1*col1] ={
3392,
3942,
2679,
1889,
4076,
3905,
5068,
2532,
4641,
1660,
542,
4743,
2625,
1747,
5560,
2665,
4152,
2291,
1773,
3900,
2438,
1980,
1918,
4996,
3215,
1753,
4556,
4149,
2495,
5046,
5367,
4122,
4545,
3996,
3867,
4461,
5018,
1326,
2400,
2968,
3171,
5001,
3033,
2765,
2724,
3724,
4237,
3106,
747,
4522,
3213,
5759,
3486,
1557,
3901,
2774,
3745,
2980,
3906,
2837,
};

DATA x2[row2*col2] ={
3023,
742,
4429,
1602,
5138,
344,
4133,
1521,
3783,
4056,
496,
4438,
2324,
3069,
2931,
4234,
4594,
2275,
2077,
2085,
2767,
2036,
3740,
3024,
2481,
3780,
3076,
3642,
3313,
5628,
4597,
3882,
899,
4257,
2010,
2357,
2940,
4669,
4787,
1816,
};

DATA rtest[] ={
1399,
1498,
1115,
1373,
1594,
1477,
1947,
1364,
1697,
1642,
1302,
1674,
1804,
1707,
2128,
1712,
1251,
1705,
817,
1430,
1319,
1705,
1850,
1395,
1288,
1444,
974,
1316,
1435,
1419,
1787,
1298,
1189,
1427,
1147,
1296,
1478,
1647,
1874,
1316,
1597,
1835,
1113,
1607,
1653,
1850,
2189,
1628,
2017,
1910,
1688,
1832,
2269,
1962,
2690,
1889,
1440,
1477,
1170,
1462,
1676,
1434,
1933,
1427,
1579,
1574,
1123,
1528,
1632,
1553,
1979,
1552,
1449,
1498,
1112,
1362,
1628,
1402,
1969,
1346,
1675,
1714,
1128,
1612,
1714,
1613,
2107,
1616,
1480,
1552,
1161,
1471,
1602,
1640,
1987,
1508,
};

DATA r[row1*col2];

