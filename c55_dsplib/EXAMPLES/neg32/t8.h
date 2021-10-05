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
#define FNAME "t8"
#define MAXERROR 10

LDATA x[NX] ={
-1572933911,
-1257855223,
460415914,
557864007,
-556297741,
322757221,
-208628760,
-1958954466,
-2030724231,
-804511513,
-2092239102,
-498356652,
786477014,
-1748728137,
-1995706503,
482734868,
466177255,
-2079795538,
-2077239536,
-1331119371,
373311956,
-1900174561,
-568790886,
564578397,
934732629,
827508666,
-1786366654,
-196043120,
-249845538,
-630284434,
-1487749196,
754387950,
};

LDATA rtest[NX] ={
1572933910,
1257855222,
-460415915,
-557864008,
556297740,
-322757222,
208628759,
1958954465,
2030724230,
804511512,
2092239101,
498356651,
-786477015,
1748728136,
1995706502,
-482734869,
-466177256,
2079795537,
2077239535,
1331119370,
-373311957,
1900174560,
568790885,
-564578398,
-934732630,
-827508667,
1786366653,
196043119,
249845537,
630284433,
1487749195,
-754387951,
};

LDATA r[NX]; 
