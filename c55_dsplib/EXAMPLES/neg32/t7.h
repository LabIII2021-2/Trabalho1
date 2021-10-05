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
#define FNAME "t7"
#define MAXERROR 10

LDATA x[NX] ={
1216887163,
776726510,
-167095142,
291322072,
1263624999,
-1893296156,
441819314,
-1931580587,
-363462171,
-837524222,
1607894597,
-2083018134,
1150838046,
2022263413,
2104888497,
1240651397,
-263459565,
-7252896,
-1228518014,
616294622,
-772941232,
1976108243,
973375928,
-378158054,
1050401935,
-996658870,
-258023100,
1861353205,
787406258,
-1234545859,
1457017002,
553125590,
};

LDATA rtest[NX] ={
-1216887164,
-776726511,
167095141,
-291322073,
-1263625000,
1893296155,
-441819315,
1931580586,
363462170,
837524221,
-1607894598,
2083018133,
-1150838047,
-2022263414,
-2104888498,
-1240651398,
263459564,
7252895,
1228518013,
-616294623,
772941231,
-1976108244,
-973375929,
378158053,
-1050401936,
996658869,
258023099,
-1861353206,
-787406259,
1234545858,
-1457017003,
-553125591,
};

LDATA r[NX]; 
