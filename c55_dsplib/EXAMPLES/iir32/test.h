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

#define NX 16
#define NBIQ 8
#define NH   5 * NBIQ 
#define FNAME "t4"
#define MAXERROR 10

DATA x[NX] ={
-19718,
-13191,
10580,
-14129,
-2017,
-28523,
32003,
5425,
-5014,
1016,
-10883,
-4398,
-17961,
5230,
17063,
1954,
};

#pragma DATA_SECTION(h,".coeffs")
LDATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
-77159047,
123506654,
126391349,
-118330904,
37722257,
91063480,
60835940,
131555412,
27613682,
-78096009,
34570318,
-23634858,
77540642,
-120723679,
-32260979,
-98308281,
65650061,
-16466208,
-22716366,
76055379,
-78615881,
-62291124,
-453306,
-52345217,
48545363,
28775968,
-16126430,
-76782307,
100493321,
-10443437,
34866469,
116334470,
38518379,
-130188517,
18207613,
-34768578,
49212846,
-48308784,
71927313,
78976491,
};

#pragma DATA_SECTION(dbuffer,".dbuffer")
LDATA dbuffer[2*NBIQ+1] ;

LDATA *dp = dbuffer;

DATA r[NX] ;

DATA rtest[NX] ={
-1,
-1,
-1,
0,
-1,
-1,
-1,
-1,
-1,
-1,
-1,
0,
0,
-1,
0,
-1,
};

