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

/* Test for mtrans: nois */
#define row 12
#define col 15
#define FNAME "t8"
#define MAXERROR 0

DATA x[row*col] ={
10412,
-4192,
-3094,
2731,
6895,
8231,
3750,
-10230,
-15386,
-1240,
-1569,
-4636,
1272,
2051,
481,
10203,
1860,
-9509,
-9631,
14769,
3922,
4475,
-9931,
16028,
4690,
2908,
-15902,
14673,
-10192,
-15683,
-445,
-5311,
-15596,
6734,
6791,
-14560,
8826,
-9449,
-15038,
-15155,
6989,
-10973,
16070,
-6203,
-2355,
-2224,
13206,
8670,
16299,
-11858,
-5290,
1503,
8722,
-14822,
12931,
6995,
11962,
-14884,
15079,
-15720,
-11780,
-8700,
-1926,
10610,
-5767,
-8527,
-3029,
13564,
-12647,
15268,
-8026,
1899,
15850,
14394,
-15589,
2471,
-3151,
-13274,
8794,
9465,
1123,
-9421,
-8818,
-6240,
-10007,
-12616,
-15249,
-5953,
-9263,
-785,
-9729,
-5698,
-16272,
-3624,
-6955,
5799,
4179,
-5011,
6871,
-11339,
-12825,
-10902,
-1532,
10015,
879,
-2699,
-3434,
-9387,
-16244,
9758,
-9176,
10873,
6518,
-12343,
-9247,
-12584,
-10798,
7099,
-7603,
14917,
-9699,
-7196,
9428,
-2312,
-9345,
5337,
8607,
-15829,
408,
1794,
-4874,
-13219,
14203,
10126,
8977,
6080,
4660,
10460,
-5648,
-3754,
-12472,
8628,
1917,
-13231,
12755,
7443,
8385,
1650,
-2854,
-11124,
10847,
-6846,
-11521,
9348,
14179,
11589,
6597,
3480,
6343,
-5954,
-3871,
-8408,
-12528,
4041,
3983,
-7065,
15266,
4465,
-2121,
15842,
-10880,
10418,
-1635,
-7370,
-1584,
6709,
8610,
800,
1571,
8107,
};

DATA rtest[] ={
10412,
10203,
-445,
-2224,
-11780,
2471,
-9729,
-2699,
-9699,
6080,
10847,
-7065,
-4192,
1860,
-5311,
13206,
-8700,
-3151,
-5698,
-3434,
-7196,
4660,
-6846,
15266,
-3094,
-9509,
-15596,
8670,
-1926,
-13274,
-16272,
-9387,
9428,
10460,
-11521,
4465,
2731,
-9631,
6734,
16299,
10610,
8794,
-3624,
-16244,
-2312,
-5648,
9348,
-2121,
6895,
14769,
6791,
-11858,
-5767,
9465,
-6955,
9758,
-9345,
-3754,
14179,
15842,
8231,
3922,
-14560,
-5290,
-8527,
1123,
5799,
-9176,
5337,
-12472,
11589,
-10880,
3750,
4475,
8826,
1503,
-3029,
-9421,
4179,
10873,
8607,
8628,
6597,
10418,
-10230,
-9931,
-9449,
8722,
13564,
-8818,
-5011,
6518,
-15829,
1917,
3480,
-1635,
-15386,
16028,
-15038,
-14822,
-12647,
-6240,
6871,
-12343,
408,
-13231,
6343,
-7370,
-1240,
4690,
-15155,
12931,
15268,
-10007,
-11339,
-9247,
1794,
12755,
-5954,
-1584,
-1569,
2908,
6989,
6995,
-8026,
-12616,
-12825,
-12584,
-4874,
7443,
-3871,
6709,
-4636,
-15902,
-10973,
11962,
1899,
-15249,
-10902,
-10798,
-13219,
8385,
-8408,
8610,
1272,
14673,
16070,
-14884,
15850,
-5953,
-1532,
7099,
14203,
1650,
-12528,
800,
2051,
-10192,
-6203,
15079,
14394,
-9263,
10015,
-7603,
10126,
-2854,
4041,
1571,
481,
-15683,
-2355,
-15720,
-15589,
-785,
879,
14917,
8977,
-11124,
3983,
8107,
};

DATA r[row*col];

