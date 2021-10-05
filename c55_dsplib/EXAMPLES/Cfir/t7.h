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


#define NX 64
#define NH 64
#define FNAME "t7"
#define MAXERROR 24

DATA x[2*NX] ={
-20501, -14779, 
-4223, -17175, 
-8764, -9007, 
-16656, -1353, 
-23928, -24432, 
-15841, -4508, 
-6295, -7597, 
-17237, -468, 
-20123, -22863, 
-14373, -23472, 
-3261, -6391, 
-9218, -4446, 
-23220, -18166, 
-14645, -7275, 
-17156, -17290, 
-20833, -22554, 
-16978, -3063, 
-24496, -22673, 
-13827, -6366, 
-7953, -21503, 
-4353, -13672, 
-6001, -10016, 
-20579, -8938, 
-11009, -11484, 
-11672, -19447, 
-1982, -8019, 
-13716, -18631, 
-23475, -6869, 
-871, -14747, 
-24246, -14893, 
-11010, -14463, 
-1615, -20896, 
-2492, -2993, 
-9389, -24042, 
-7375, -1872, 
-1497, -9029, 
-13466, -22932, 
-20235, -9028, 
-9419, -6052, 
-11837, -5661, 
-15619, -4718, 
-5572, -11224, 
-4221, -12655, 
-16752, -13733, 
-9930, -9180, 
-5363, -22665, 
-23751, -11206, 
-3515, -19438, 
-7801, -17941, 
-4870, -17408, 
-2023, -4370, 
-15038, -14464, 
-12977, -11626, 
-22412, -1961, 
-1841, -15259, 
-7902, -8875, 
-8822, -20307, 
-101, -5265, 
-12300, -15591, 
-14008, -5482, 
-4199, -16168, 
-21709, -5550, 
-9863, -20943, 
-19140, -20933, 
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[2*NH] ={ /* b0 b1 b2 ... b(NH-1) */
-340, -434, 
-854, -73, 
-68, -531, 
-485, -434, 
-789, -285, 
-682, -940, 
-819, -154, 
-920, -105, 
-724, -924, 
-146, -850, 
-258, -590, 
-288, -31, 
-582, -359, 
-490, -311, 
-32, -513, 
-204, -153, 
-556, -167, 
-41, -432, 
-757, -855, 
-444, -664, 
-467, -375, 
-487, -770, 
-587, -252, 
-453, -425, 
-174, -795, 
-746, -71, 
-576, -752, 
-899, -934, 
-655, -293, 
-176, -565, 
-300, -585, 
-111, -92, 
-865, -54, 
-476, -496, 
-537, -926, 
-617, -170, 
-82, -888, 
-791, -857, 
-577, -286, 
-31, -804, 
-879, -888, 
-644, -883, 
-823, -262, 
-833, -911, 
-788, -287, 
-854, -734, 
-441, -353, 
-224, -459, 
-549, -400, 
-155, -672, 
-184, -102, 
-934, -855, 
-335, -667, 
-837, -168, 
-739, -6, 
-86, -878, 
-806, -26, 
-747, -73, 
-141, -39, 
-271, -412, 
-867, -47, 
-171, -643, 
-614, -692, 
-789, -885, 
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[2*NH + 2] ;

DATA rtest[2*NX] ={
17, 425, 
318, 664, 
-153, 1028, 
202, 1081, 
429, 1645, 
652, 2812, 
421, 2228, 
1177, 2932, 
1368, 3914, 
417, 4477, 
833, 4075, 
1071, 3801, 
1229, 5380, 
942, 5595, 
190, 5357, 
1701, 5542, 
1743, 6627, 
133, 6970, 
917, 6962, 
1001, 7020, 
1267, 8326, 
1222, 8737, 
434, 9327, 
1138, 8633, 
641, 9514, 
949, 9684, 
349, 10517, 
407, 11608, 
355, 9982, 
284, 11062, 
1619, 11786, 
118, 12442, 
681, 12469, 
111, 12079, 
937, 13414, 
398, 13279, 
-665, 14337, 
1010, 14443, 
-1575, 14093, 
-2, 14532, 
1085, 14598, 
-599, 16567, 
666, 16629, 
83, 16350, 
894, 17083, 
217, 17646, 
358, 18453, 
543, 17601, 
62, 18983, 
238, 19961, 
-91, 18001, 
-973, 20664, 
13, 20812, 
-1198, 20588, 
40, 20668, 
-631, 21785, 
314, 21698, 
-91, 21399, 
887, 21097, 
1110, 20589, 
-569, 21822, 
873, 22505, 
640, 21113, 
-1393, 25083, 
};

