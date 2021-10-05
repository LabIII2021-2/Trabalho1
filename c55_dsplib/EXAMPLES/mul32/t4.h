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

/* This is a test for mul32: rand */
#define NX 64
#define FNAME "t4"
#define MAXERROR 100

LDATA x[NX] ={
1365552825,
688103297,
-678663154,
-903030089,
-682000219,
146353629,
975346294,
-819010618,
1453684059,
292339756,
-556513880,
870674220,
200001571,
-236714045,
835576368,
520970942,
1266120272,
1961931457,
97015108,
1632535078,
-1404502214,
2060291182,
-981528387,
-1063630982,
1613637791,
1019119537,
-1560984001,
-2096779362,
1691609705,
-1292062943,
-864391633,
693321246,
-925865461,
-132167471,
-1869063919,
2097172851,
355552005,
-328548217,
66615805,
-713101646,
-288135160,
-1176918651,
342733633,
1118147376,
128076502,
603496361,
-1249412440,
-516124552,
1216765596,
776648915,
-167078450,
291292969,
1263498763,
-1893107015,
441775176,
-1931387622,
-363425861,
-837440553,
1607733969,
-2082810041,
1150723078,
2022061389,
2104678218,
1240527456,
};

LDATA y[NX] ={
-263433246,
-7252172,
-1228395285,
616233054,
-772864016,
1975910830,
973278688,
-378120276,
1050296999,
-996559304,
-257997324,
1861167256,
787327596,
-1234422528,
1456871446,
553070332,
-1572776775,
-1257729563,
460369919,
557808276,
-556242167,
322724977,
-208607918,
-1958758766,
-2030521362,
-804431142,
-2092030087,
-498306866,
786398445,
-1748553439,
-1995507132,
482686643,
466130684,
-2079587766,
-2077032020,
-1330986393,
373274662,
-1899984733,
-568734064,
564521995,
934639249,
827425998,
-1786188196,
-196023535,
-249820578,
-630221469,
-1487600570,
754312587,
855529166,
977046555,
-92829094,
235520983,
-1627427498,
-211489062,
927117481,
1687073135,
-974420019,
-1053152530,
1570097954,
-1149431451,
1309283229,
1753878687,
-1151389986,
-1119532046,
};

LDATA rtest[NX] ={
-167513273,
-2323763,
388206270,
-259129792,
245447003,
134660732,
442044698,
144208092,
710971656,
-135662921,
66859224,
754590309,
73326172,
136068625,
566862221,
134172650,
-927282758,
-1149056105,
20797754,
424050529,
363794785,
309621647,
95346287,
970157100,
-1525751318,
-381754476,
1520675371,
486541330,
619459544,
1052041119,
803218999,
155836765,
-200967445,
127988799,
1807746293,
-1299804322,
61801893,
290682816,
-17642360,
-187457337,
-125403716,
-453467057,
-285071680,
-102065132,
-14899367,
-177107921,
865490481,
-181290902,
484743367,
353354097,
7222285,
31946975,
-957517247,
186437473,
190724380,
-1517307093,
164904367,
410691200,
1175468702,
1114815177,
701575739,
1651444647,
-1128439523,
-646715165,
};

LDATA r[NX]; 
