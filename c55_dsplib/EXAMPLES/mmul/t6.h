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
#define row1 8
#define col1 8
#define row2 8
#define col2 4
#define FNAME "t6"
#define MAXERROR 10

DATA x1[row1*col1] ={
2105,
4549,
3155,
3072,
2376,
1815,
5358,
5494,
4196,
2743,
2989,
2945,
3826,
3531,
1842,
2371,
4182,
5155,
2553,
2657,
3311,
1304,
5600,
4326,
3200,
5345,
2321,
3899,
2864,
4555,
4185,
2550,
5893,
2317,
3055,
1562,
1394,
2172,
4974,
3144,
2891,
1859,
3056,
1449,
2915,
4619,
6119,
3861,
3372,
581,
3837,
2074,
4041,
1514,
2558,
5491,
3158,
2310,
5652,
3115,
2254,
3704,
5094,
4280,
};

DATA x2[row2*col2] ={
1548,
1855,
2391,
3101,
543,
2270,
5732,
1576,
1678,
1359,
2727,
133,
4481,
1228,
3992,
3812,
3557,
3365,
4116,
5564,
1537,
3132,
710,
3275,
6180,
637,
1394,
3986,
3509,
5833,
1637,
948,
};

DATA rtest[] ={
2699,
2180,
2426,
2184,
1982,
1850,
2147,
2179,
2717,
2143,
2642,
2462,
2479,
2059,
2600,
2547,
2215,
1687,
1871,
2013,
2623,
2021,
1886,
2357,
2229,
2055,
1843,
1911,
2740,
2136,
2278,
2292,
};

DATA r[row1*col2];

