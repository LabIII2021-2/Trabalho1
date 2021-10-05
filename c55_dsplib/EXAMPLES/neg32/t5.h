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
#define FNAME "t5"
#define MAXERROR 10

LDATA x[NX] ={
-839161936,
-1332926872,
-1316703026,
782642707,
-847120364,
178987821,
-1499489000,
849967422,
-522383933,
1546237914,
1518937068,
401849609,
-14807115,
1716995361,
1381386588,
622385298,
1365689258,
688172046,
-678730959,
-903120311,
-682068358,
146368251,
975443741,
-819092445,
1453829297,
292368964,
-556569481,
870761209,
200021554,
-236737695,
835659850,
521022992,
};

LDATA rtest[NX] ={
839161935,
1332926871,
1316703025,
-782642708,
847120363,
-178987822,
1499488999,
-849967423,
522383932,
-1546237915,
-1518937069,
-401849610,
14807114,
-1716995362,
-1381386589,
-622385299,
-1365689259,
-688172047,
678730958,
903120310,
682068357,
-146368252,
-975443742,
819092444,
-1453829298,
-292368965,
556569480,
-870761210,
-200021555,
236737694,
-835659851,
-521022993,
};

LDATA r[NX]; 
