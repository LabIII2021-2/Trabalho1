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

#define NA 24
#define NB 24  // NB <= NA 
#define FNAME "t5"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
4706,
3471,
6016,
775,
-6499,
1286,
4230,
6382,
-3721,
2724,
295,
5791,
2854,
-3639,
-674,
-4386,
6271,
-1931,
-6033,
3415,
5281,
-2861,
-3329,
5788,
};

DATA b[NB] ={
-4937,
5897,
2700,
4651,
-3890,
-601,
-5605,
4697,
830,
-2418,
-1674,
4920,
-1710,
-5703,
-4016,
-6027,
892,
-5058,
295,
-5123,
3610,
-1672,
4326,
-6065,
};

DATA rtest[NA+NB-1] ={
-871,
-21,
-895,
992,
645,
-973,
-1832,
-1879,
780,
-2286,
-779,
-4647,
1121,
-151,
1397,
-2107,
-4069,
-20,
1025,
-1759,
-4957,
2384,
2696,
2490,
-1580,
-2298,
-778,
3123,
1027,
-2248,
-2937,
1799,
3652,
-2410,
-1842,
434,
1346,
-1616,
431,
-480,
-353,
1842,
-959,
-763,
309,
1543,
-872,
};

