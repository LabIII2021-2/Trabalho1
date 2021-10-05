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

/* Test for rfft32: rand */
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

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

LDATA rtest[NX] ={
-130078063, 
25785630, 
113004049, 
77025626, 
96853949, 
-62281418, 
-91489332, 
-184674187, 
21096811, 
33277129, 
-1573042, 
27099555, 
-2995411, 
-24591281, 
-33869337, 
-69691492, 
45215367, 
-31493756, 
-53298356, 
7522042, 
32350097, 
-18027039, 
-17884755, 
82344980, 
-191895759, 
22652269, 
-70860243, 
136117964, 
-110436409, 
-93204536, 
-110304475, 
-55704398, 
10184502, 
68546699, 
-8329676, 
146572246, 
-91841350, 
169031427, 
-9039641, 
-191179540, 
38175116, 
-51116878, 
31533639, 
-82252341, 
10101766, 
14135231, 
61824059, 
-205219838, 
73892957, 
32438787, 
-27099433, 
-40564390, 
90460397, 
-15746864, 
44237914, 
11205811, 
-80039243, 
-27313391, 
169985903, 
-38521450, 
-24974872, 
-46342446, 
-178334925, 
16202988, 
11812954, 
-9618896, 
42968057, 
-76157209, 
-55264281, 
63407977, 
33266526, 
-47702036, 
-79777116, 
-158614035, 
2477462, 
40744184, 
-101848537, 
124524371, 
168743355, 
33764110, 
-19715058, 
-13103852, 
-61442540, 
-41907753, 
-52976188, 
-15134795, 
-18726968, 
8726746, 
-57576722, 
53770227, 
-36016541, 
101436019, 
-80280089, 
41642714, 
170157666, 
-68472759, 
-37538227, 
112704118, 
-68683373, 
-63010806, 
22176009, 
-13651915, 
2431209, 
-71729129, 
101607152, 
160944016, 
-95230716, 
75910558, 
-26382753, 
60202255, 
2690328, 
85670736, 
-11631754, 
33117005, 
18911723, 
40030161, 
54822751, 
-9509625, 
30777877, 
-151577160, 
57922534, 
570031, 
73108537, 
-98669797, 
76186139, 
9091330, 
68813573, 
10513019, 
};

LDATA error;

