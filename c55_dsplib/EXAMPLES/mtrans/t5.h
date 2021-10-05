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

/* Test for mtrans: rand */
#define row 20
#define col 10
#define FNAME "t5"
#define MAXERROR 0

DATA x[row*col] ={
16537,
5662,
12087,
19563,
10998,
14159,
23693,
16737,
30978,
6919,
20916,
7153,
20970,
13410,
25691,
16039,
26778,
18952,
11190,
28910,
4790,
14374,
9870,
21342,
26455,
16998,
31123,
20295,
27188,
23601,
5558,
11678,
11714,
18830,
22418,
20980,
24909,
25414,
20010,
4151,
21924,
32536,
21335,
7427,
21415,
14147,
15021,
22809,
12207,
12128,
6124,
26663,
14324,
18556,
14908,
4622,
26458,
1227,
6351,
17742,
16102,
25436,
11842,
3625,
13841,
21909,
17498,
15787,
8818,
10399,
11234,
27308,
9169,
16410,
21427,
15792,
4943,
6836,
15559,
18255,
29445,
16853,
5864,
5456,
12023,
24257,
17930,
10562,
27808,
14711,
5870,
3263,
12248,
20954,
27259,
16154,
9685,
27412,
26135,
21616,
8410,
12503,
22548,
14047,
29772,
19687,
20787,
18497,
18440,
30849,
23365,
14050,
13194,
8262,
27768,
11150,
8116,
15530,
25889,
16912,
22229,
14231,
16038,
17393,
27651,
20506,
32095,
29303,
22573,
12345,
8357,
7550,
16823,
11450,
25044,
17078,
9720,
19554,
8529,
16199,
20871,
17492,
7817,
13602,
17164,
12430,
23038,
11370,
15042,
29201,
28421,
8938,
12341,
8473,
11022,
15198,
10850,
15710,
18294,
16183,
22356,
14138,
27848,
13133,
14122,
23874,
24339,
22890,
20724,
18488,
8098,
10399,
18049,
24009,
13464,
12092,
16050,
11057,
22903,
27830,
27111,
18771,
13638,
26855,
7097,
13907,
8585,
13062,
21107,
26257,
17634,
16083,
19391,
10304,
18733,
21469,
23361,
17514,
11175,
16285,
};

DATA rtest[] ={
16537,
20916,
4790,
5558,
21924,
6124,
16102,
11234,
29445,
5870,
8410,
23365,
22229,
8357,
20871,
28421,
22356,
8098,
27111,
17634,
5662,
7153,
14374,
11678,
32536,
26663,
25436,
27308,
16853,
3263,
12503,
14050,
14231,
7550,
17492,
8938,
14138,
10399,
18771,
16083,
12087,
20970,
9870,
11714,
21335,
14324,
11842,
9169,
5864,
12248,
22548,
13194,
16038,
16823,
7817,
12341,
27848,
18049,
13638,
19391,
19563,
13410,
21342,
18830,
7427,
18556,
3625,
16410,
5456,
20954,
14047,
8262,
17393,
11450,
13602,
8473,
13133,
24009,
26855,
10304,
10998,
25691,
26455,
22418,
21415,
14908,
13841,
21427,
12023,
27259,
29772,
27768,
27651,
25044,
17164,
11022,
14122,
13464,
7097,
18733,
14159,
16039,
16998,
20980,
14147,
4622,
21909,
15792,
24257,
16154,
19687,
11150,
20506,
17078,
12430,
15198,
23874,
12092,
13907,
21469,
23693,
26778,
31123,
24909,
15021,
26458,
17498,
4943,
17930,
9685,
20787,
8116,
32095,
9720,
23038,
10850,
24339,
16050,
8585,
23361,
16737,
18952,
20295,
25414,
22809,
1227,
15787,
6836,
10562,
27412,
18497,
15530,
29303,
19554,
11370,
15710,
22890,
11057,
13062,
17514,
30978,
11190,
27188,
20010,
12207,
6351,
8818,
15559,
27808,
26135,
18440,
25889,
22573,
8529,
15042,
18294,
20724,
22903,
21107,
11175,
6919,
28910,
23601,
4151,
12128,
17742,
10399,
18255,
14711,
21616,
30849,
16912,
12345,
16199,
29201,
16183,
18488,
27830,
26257,
16285,
};

DATA r[row*col];
