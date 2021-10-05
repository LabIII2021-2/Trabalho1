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

/*Test for cfft: rand*/
#define NX 64
#define FNAME "t64"
#define MAXERROR 100
#pragma DATA_SECTION (x,".input")
LDATA x[2*NX] ={
377316, 65678934,
-21647501, 16929632,
27035772, 62563212,
7772079, -11402191,
-33210824, -38244650,
44949037, -7084129,
9714076, 39937993,
49624222, -37453751,
38185884, 21316263,
-22955882, -20180042,
-43350180, 18494690,
-2447000, -36904522,
-11093058, 2885366,
-28307446, -67261984,
16702378, -16545285,
49945452, 15503759,
-18336688, -10771130,
-28412489, 41491923,
-8265682, -21182230,
22247399, -78021139,
-28662108, -41326864,
-40309436, 35421682,
-4022151, -3799167,
-2190904, 12724633,
16283817, 31682086,
-19981359, -71149713,
-5022016, -21631835,
-14587854, -23632444,
-2661881, -34163016,
51511162, -6109654,
-20350188, 51036735,
-45209989, -1289791,
15749884, 41186320,
-30318676, -23360757,
1203921, 252480,
-21056454, -26269531,
17964974, 19694390,
18551692, -8429121,
-6834718, 16110685,
-68931698, 22419563,
4448000, -2628023,
53450221, 29835682,
34172229, 77486830,
-53029508, 17603953,
-2639456, -395517,
-22872609, 30639921,
-34378296, 1877058,
-41418030, -37147102,
9690755, 16290600,
-14405018, -167942,
1872377, -9268333,
-12343789, 42830638,
-15601917, 62525349,
12447372, -17534181,
24437120, 3470349,
70872335, -27100208,
-45543355, 22831730,
-34313103, -79342469,
34823937, 33222742,
-13079502, 7345036,
-46347583, 8779935,
10587854, 40716441,
52118172, -9216295,
23752977, -4467251,
};


#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
-143645934, 117306343,
613104695, 116289524,
2574189, 196243962,
-32759080, 234015557,
-142273212, 217879171,
11422061, 314943115,
210384766, 185888518,
111624250, -562939346,
167903929, -31461386,
-254586428, -95345044,
-223381487, -197829460,
81575958, 425262108,
-216670849, 175208759,
-311336011, -240931790,
9449653, 8531598,
-594229429, -281878116,
-240928628, -79413773,
77671991, -269251009,
-35568896, 182930661,
-407526485, 163146408,
-129991723, -46089742,
413848520, 165339190,
143001815, 182954659,
-8186879, -79393808,
341675730, 35675287,
-2148379, 119737784,
367469503, 64394169,
44786509, 207076746,
47005343, -99858120,
216863856, -303169370,
64326086, 121991072,
-246364250, 278796411,
100566956, 658996461,
-172217805, -23205152,
10079607, 285037930,
39316691, -347524448,
134077365, -265066842,
81890183, -282766733,
-142334499, 241841776,
-211245748, 108061015,
4180037, 453292890,
96331009, 209362802,
351692489, 398521474,
-570656414, 350186721,
333211234, 58195028,
-39328170, -423059891,
-517221199, -507218876,
-18408312, 158005518,
-121577354, -35521939,
-461432285, 492622168,
281197324, 19335367,
274554800, -25565789,
12449426, 262936496,
92896374, -100526345,
-203969488, -119758449,
820977508, 317201773,
58670168, 365820357,
-147621021, 47492050,
-269273058, 437279545,
204616135, -131223417,
-84952216, 10256593,
-28331999, 215911436,
347943322, 121388599,
-167024022, 27093579,
};
