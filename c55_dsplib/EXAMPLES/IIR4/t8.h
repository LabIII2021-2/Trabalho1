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

/* Test for iircas4 : rand */
#define NX 100
#define NBIQ 8
#define FNAME "t8"
#define MAXERROR 20

DATA x[NX] ={
-321,
-53,
166,
192,
274,
225,
-87,
79,
151,
-201,
265,
45,
86,
-174,
31,
282,
-108,
101,
-71,
83,
130,
-68,
-57,
101,
221,
-85,
-49,
61,
43,
141,
7,
180,
-7,
-206,
131,
316,
200,
133,
-10,
-253,
107,
-89,
-236,
43,
211,
113,
326,
302,
-289,
-92,
31,
-156,
63,
-296,
46,
131,
302,
164,
157,
-45,
87,
198,
-273,
291,
272,
66,
-162,
244,
8,
152,
-51,
302,
-281,
34,
-137,
234,
-108,
117,
-293,
-94,
-2,
-43,
40,
76,
-254,
260,
166,
190,
206,
111,
-196,
-149,
82,
24,
-289,
-270,
-150,
-60,
-17,
267,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C55x: a1 b1 a2 b2 ... */

3784,
13100,
-18531,
4742,

-6726,
13315,
12272,
17761,

-858,
-1903,
4329,
5505,

3820,
17954,
7923,
-9936,

-13313,
-13875,
-16036,
-5792,

12955,
14546,
-2954,
-12274,

17935,
10594,
-4893,
-368,


3757,
-2196,
-13128,
-3568,

};

DATA rtest[NX] ={
-321,
-348,
-218,
76,
380,
527,
400,
423,
511,
335,
606,
507,
688,
390,
407,
621,
526,
664,
390,
544,
583,
542,
432,
447,
671,
571,
504,
429,
485,
635,
584,
730,
628,
433,
491,
742,
995,
1060,
915,
573,
650,
500,
338,
291,
446,
617,
907,
1097,
745,
604,
468,
399,
474,
87,
171,
207,
602,
719,
811,
668,
694,
856,
543,
849,
913,
1098,
805,
936,
850,
1063,
891,
1121,
747,
789,
508,
760,
625,
712,
335,
201,
193,
131,
265,
204,
24,
213,
362,
603,
756,
749,
542,
305,
369,
376,
159,
-193,
-376,
-384,
-301,
-29,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ+2];  // index + (2*NBIQ+1)
DATA *dp = dbuffer;

DATA r[NX];

