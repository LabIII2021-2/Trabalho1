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

/* This is a test for power: rand */
#define NX 128
#define FNAME "t5"
#define MAXERROR 10

DATA x[NX] ={
-111,
-16,
-223,
250,
42,
-40,
7,
-86,
-35,
-141,
40,
133,
15,
71,
-149,
-62,
145,
92,
-20,
34,
150,
-226,
52,
-231,
-44,
-100,
191,
-249,
137,
241,
250,
147,
-32,
-1,
-147,
73,
-93,
235,
116,
-46,
125,
-119,
-31,
221,
93,
-148,
173,
65,
-188,
-150,
54,
66,
-67,
38,
-25,
-234,
-243,
-96,
-250,
-60,
93,
-209,
-238,
57,
55,
-248,
-248,
-159,
44,
-227,
-68,
67,
111,
98,
-213,
-24,
-30,
-76,
-178,
89,
101,
116,
-12,
28,
-195,
-26,
110,
201,
-117,
-126,
187,
-138,
156,
209,
-138,
-134,
-231,
-216,
72,
-159,
176,
-167,
-169,
253,
-31,
-82,
-96,
-70,
-55,
46,
-195,
-237,
-22,
189,
222,
-121,
-174,
190,
-135,
74,
239,
84,
189,
-251,
-186,
163,
-36,
199,
};

LDATA rtest = 5509504;
LDATA r;
