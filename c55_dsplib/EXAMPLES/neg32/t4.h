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
#define FNAME "t4"
#define MAXERROR 10

LDATA x[NX] ={
1870327929,
1790590755,
-385386488,
1690711692,
-1898842198,
-631926498,
1345039729,
-2105129474,
-1550951698,
-1276613538,
-1293980133,
445785259,
-978445315,
-1293582741,
-2081882423,
1059936303,
-235809005,
1854629306,
-146053176,
-349397841,
1487009518,
108029138,
-1277119747,
739324723,
1452207518,
-2063132372,
778579401,
-517625035,
1425052902,
12081243,
899672691,
-305404935,
};

LDATA rtest[NX] ={
-1870327930,
-1790590756,
385386487,
-1690711693,
1898842197,
631926497,
-1345039730,
2105129473,
1550951697,
1276613537,
1293980132,
-445785260,
978445314,
1293582740,
2081882422,
-1059936304,
235809004,
-1854629307,
146053175,
349397840,
-1487009519,
-108029139,
1277119746,
-739324724,
-1452207519,
2063132371,
-778579402,
517625034,
-1425052903,
-12081244,
-899672692,
305404934,
};

LDATA r[NX]; 
