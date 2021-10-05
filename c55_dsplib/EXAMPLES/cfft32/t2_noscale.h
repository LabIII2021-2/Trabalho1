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
#define NX 16
#define FNAME "t16"
#define MAXERROR 16
#pragma DATA_SECTION (x,".input")
LDATA x[2*NX] ={
-18187058, 46331372,
54834337, 44286577,
27689626, -30515381,
7743059, -77363268,
22536296, 60019827,
-17048265, 13112998,
28734391, 681949,
9009481, -13622328,
20970687, -51502515,
-35142830, 7428049,
51528547, -46119851,
14576909, -28161749,
-64328405, -7000883,
15768554, 25364231,
42760128, 12607556,
21425929, -45144568,
};


#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
182871386, -89597984,
97461209, 54951311,
-48484356, -32580910,
5233612, 141355547,
64762596, 145537110,
103713920, -158282011,
90230369, -101980077,
-250868143, 193552350,
40537038, 58602132,
-50410519, 59469182,
-42213642, -99246572,
-198509886, 242656933,
-444204940, 76849946,
-39312750, 87738262,
178770581, 1047211,
19430597, 161229521,
};
