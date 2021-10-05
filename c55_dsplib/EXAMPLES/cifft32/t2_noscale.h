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
27367743, -72835750,
23887679, -1986014,
43293598, -33911240,
22434510, 20617959,
39957895, 17036954,
-40347765, 56788523,
-664027, 19840151,
-5258560, -21595471,
-53824180, 12762000,
8633697, -33860298,
-35449349, -654669,
47484269, -1618021,
-27014351, 1449,
17741671, -10665593,
7359181, 36742228,
-30933885, -62880679,
};


#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
44668126, -76218471,
53132777, -67329895,
489712, -93079734,
4561611, 16805232,
-103805126, -88862869,
-31418926, -25612502,
-109704947, 166881376,
10237403, -249289618,
-42615106, 34180717,
268820973, 106962954,
103006902, -58846382,
140122412, -198803663,
47700534, -41240765,
-33909152, -88522573,
-151391591, -323403872,
237988285, -178991935,
};
