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

/* Test for rifft32: rand */
#define NX 128
#define FNAME "t5"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

LDATA x[NX] ={
-363425861,	/* 0 */ 
-837440553,	/* 1 */ 
1607733969,	/* 2 */ 
-2082810041,	/* 3 */ 
1150723078,	/* 4 */ 
2022061389,	/* 5 */ 
2104678218,	/* 6 */ 
1240527456,	/* 7 */ 
-263433246,	/* 8 */ 
-7252172,	/* 9 */ 
-1228395285,	/* 10 */ 
616233054,	/* 11 */ 
-772864016,	/* 12 */ 
1975910830,	/* 13 */ 
973278688,	/* 14 */ 
-378120276,	/* 15 */ 
1050296999,	/* 16 */ 
-996559304,	/* 17 */ 
-257997324,	/* 18 */ 
1861167256,	/* 19 */ 
787327596,	/* 20 */ 
-1234422528,	/* 21 */ 
1456871446,	/* 22 */ 
553070332,	/* 23 */ 
-1572776775,	/* 24 */ 
-1257729563,	/* 25 */ 
460369919,	/* 26 */ 
557808276,	/* 27 */ 
-556242167,	/* 28 */ 
322724977,	/* 29 */ 
-208607918,	/* 30 */ 
-1958758766,	/* 31 */ 
-2030521362,	/* 32 */ 
-804431142,	/* 33 */ 
-2092030087,	/* 34 */ 
-498306866,	/* 35 */ 
786398445,	/* 36 */ 
-1748553439,	/* 37 */ 
-1995507132,	/* 38 */ 
482686643,	/* 39 */ 
466130684,	/* 40 */ 
-2079587766,	/* 41 */ 
-2077032020,	/* 42 */ 
-1330986393,	/* 43 */ 
373274662,	/* 44 */ 
-1899984733,	/* 45 */ 
-568734064,	/* 46 */ 
564521995,	/* 47 */ 
934639249,	/* 48 */ 
827425998,	/* 49 */ 
-1786188196,	/* 50 */ 
-196023535,	/* 51 */ 
-249820578,	/* 52 */ 
-630221469,	/* 53 */ 
-1487600570,	/* 54 */ 
754312587,	/* 55 */ 
855529166,	/* 56 */ 
977046555,	/* 57 */ 
-92829094,	/* 58 */ 
235520983,	/* 59 */ 
-1627427498,	/* 60 */ 
-211489062,	/* 61 */ 
927117481,	/* 62 */ 
1687073135,	/* 63 */ 
-974420019,	/* 64 */ 
-1053152530,	/* 65 */ 
1570097954,	/* 66 */ 
-1149431451,	/* 67 */ 
1309283229,	/* 68 */ 
1753878687,	/* 69 */ 
-1151389986,	/* 70 */ 
-1119532046,	/* 71 */ 
-1933596388,	/* 72 */ 
-1810645528,	/* 73 */ 
604737100,	/* 74 */ 
-1327499308,	/* 75 */ 
1476760560,	/* 76 */ 
-1400447710,	/* 77 */ 
-1413792706,	/* 78 */ 
2122770668,	/* 79 */ 
-258570441,	/* 80 */ 
-686920130,	/* 81 */ 
-797850783,	/* 82 */ 
-579425968,	/* 83 */ 
-458486783,	/* 84 */ 
393058447,	/* 85 */ 
-1633012527,	/* 86 */ 
-1983523341,	/* 87 */ 
-177802649,	/* 88 */ 
1588409317,	/* 89 */ 
1864845144,	/* 90 */ 
-1011581960,	/* 91 */ 
-1458853034,	/* 92 */ 
1601240994,	/* 93 */ 
-1125682927,	/* 94 */ 
626277815,	/* 95 */ 
2005065677,	/* 96 */ 
708303323,	/* 97 */ 
1590615315,	/* 98 */ 
-2104635715,	/* 99 */ 
-1558874741,	/* 100 */ 
1368908945,	/* 101 */ 
-299904543,	/* 102 */ 
1676251396,	/* 103 */ 
1008822194,	/* 104 */ 
804468244,	/* 105 */ 
-660877972,	/* 106 */ 
-1434226438,	/* 107 */ 
-1478984809,	/* 108 */ 
-1326512677,	/* 109 */ 
-333034854,	/* 110 */ 
1528751130,	/* 111 */ 
-41871800,	/* 112 */ 
1356793807,	/* 113 */ 
-168475442,	/* 114 */ 
-183143227,	/* 115 */ 
-211768462,	/* 116 */ 
-376978561,	/* 117 */ 
1724728573,	/* 118 */ 
-2123288462,	/* 119 */ 
-870048970,	/* 120 */ 
-1936138732,	/* 121 */ 
829620758,	/* 122 */ 
644637651,	/* 123 */ 
2074209286,	/* 124 */ 
226207234,	/* 125 */ 
-429138064,	/* 126 */ 
-1293564088,	/* 127 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

LDATA rtest[NX] ={
-53997837,	52705160,	 /* 0 */ 
133857955,	53528052,	 /* 1 */ 
59214342,	-34851875,	 /* 2 */ 
-163256385,	-19781190,	 /* 3 */ 
50664280,	-15567541,	 /* 4 */ 
-51553102,	79044932,	 /* 5 */ 
-646079,	74635319,	 /* 6 */ 
-32184854,	37139371,	 /* 7 */ 
26567256,	-30507655,	 /* 8 */ 
2997880,	17259131,	 /* 9 */ 
33572899,	-70381312,	 /* 10 */ 
29342682,	-89547681,	 /* 11 */ 
-52199297,	-20924721,	 /* 12 */ 
-32037171,	138063892,	 /* 13 */ 
-129346610,	37701491,	 /* 14 */ 
-149302137,	-21608890,	 /* 15 */ 
65425892,	-71147215,	 /* 16 */ 
39161382,	126271404,	 /* 17 */ 
-25555696,	322350626,	 /* 18 */ 
-40275763,	43400233,	 /* 19 */ 
28992010,	50302573,	 /* 20 */ 
7206841,	-6018210,	 /* 21 */ 
4290468,	132169538,	 /* 22 */ 
1224652,	-140155159,	 /* 23 */ 
72178174,	-16982053,	 /* 24 */ 
-24372439,	9941116,	 /* 25 */ 
100256620,	-35012898,	 /* 26 */ 
48071950,	13160377,	 /* 27 */ 
-100024665,	9959293,	 /* 28 */ 
161068586,	-17179923,	 /* 29 */ 
-26063060,	-59518723,	 /* 30 */ 
-181524167,	4424185,	 /* 31 */ 
9961334,	18476910,	 /* 32 */ 
42454060,	-83802285,	 /* 33 */ 
-57879333,	60955299,	 /* 34 */ 
38480603,	28273349,	 /* 35 */ 
-63494934,	-173406455,	 /* 36 */ 
-5059814,	-101974081,	 /* 37 */ 
-115348000,	-5869266,	 /* 38 */ 
162313121,	60701674,	 /* 39 */ 
-21703515,	10208197,	 /* 40 */ 
-4546374,	-47024298,	 /* 41 */ 
-50868130,	-69625742,	 /* 42 */ 
1896590,	-73711008,	 /* 43 */ 
-52096855,	-82847216,	 /* 44 */ 
-8483659,	26029771,	 /* 45 */ 
-150268982,	8530227,	 /* 46 */ 
118963368,	-65196227,	 /* 47 */ 
-96482856,	28395966,	 /* 48 */ 
-33388951,	-68003003,	 /* 49 */ 
37382970,	10313169,	 /* 50 */ 
-40095102,	-191864697,	 /* 51 */ 
-41792549,	125968450,	 /* 52 */ 
-146161393,	11474198,	 /* 53 */ 
-31308795,	-20609431,	 /* 54 */ 
-57309148,	58008738,	 /* 55 */ 
3313117,	-9741236,	 /* 56 */ 
13524000,	63201583,	 /* 57 */ 
48770179,	96325309,	 /* 58 */ 
77054697,	-51868701,	 /* 59 */ 
24651825,	-61824772,	 /* 60 */ 
141172351,	62365014,	 /* 61 */ 
110122505,	62360536,	 /* 62 */ 
44256428,	-58587979,	 /* 63 */ 
};

LDATA error;
