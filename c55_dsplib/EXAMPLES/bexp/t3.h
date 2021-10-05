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

/* Test for bexp: rand */
#define NX 100
#define FNAME "t3"
#define MAXERROR 100

DATA x[NX] ={
17724,
17390,
15610,
14564,
19756,
18104,
14999,
13728,
13679,
23015,
11759,
11624,
15091,
17346,
20097,
13289,
12510,
20975,
15093,
8585,
22581,
20409,
19207,
19216,
19268,
15004,
23060,
20289,
29046,
7307,
20224,
18628,
7940,
27532,
26961,
6035,
4113,
15459,
4546,
15392,
13963,
18484,
10536,
3859,
32480,
16752,
12509,
13593,
11452,
13534,
13392,
11460,
13081,
16193,
24744,
18730,
10555,
15459,
25453,
11451,
19883,
28851,
11863,
24135,
986,
9049,
18410,
21371,
14831,
24620,
27165,
21890,
15643,
9736,
11294,
10426,
24565,
13274,
29096,
19452,
14241,
19581,
11143,
21977,
15382,
16067,
4288,
25105,
20951,
18295,
12447,
16502,
13576,
16312,
21436,
13553,
881,
7324,
17469,
13216,
};

DATA rtest = 0;

DATA r;

