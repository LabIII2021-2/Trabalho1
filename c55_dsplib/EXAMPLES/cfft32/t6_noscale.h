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
#define NX 256
#define FNAME "t16"
#define MAXERROR 520
#pragma DATA_SECTION (x,".input")
LDATA x[2*NX] ={
4652824, -20050083,
-28841173, -16166946,
-25241340, 32996495,
41259036, 59126958,
38612909, 47895652,
-20401934, 30593691,
27050171, 10966348,
7285770, 2336011,
-12531274, -50323684,
-27918309, -14033242,
9625636, -705878,
-61031875, 7664655,
-52782846, -33829437,
67634517, -22301019,
-2415316, 18729298,
88211562, -39880854,
-8164362, -26020841,
5814194, 9094663,
30977689, 51505236,
-5991244, -35308748,
-17505512, 20990263,
48048671, -26763890,
-29196297, -10520052,
27096606, -20206806,
-17134055, 42247054,
24948194, 28805952,
28450746, -70641873,
-27846847, -12111042,
17884325, 18574281,
34656642, -52223576,
-35300067, -6934551,
12150521, -14279677,
-1234354, 16568449,
-41192614, -29222810,
-9230786, 2678572,
-5383313, -17502634,
-36358738, -47441299,
-65572499, -12894739,
-30517328, -15365320,
-187191, -9780133,
-57830724, -10107401,
42381840, -53304363,
-20147201, 36718167,
-69253825, 44431667,
3721554, -4243952,
49916051, -24735113,
1778457, 7171214,
5435172, -13439528,
-901873, 2178949,
5824251, -58988544,
29600638, 56597872,
6116786, 10985728,
25343509, 24023858,
17046811, 53641723,
4425163, -69281208,
9398734, -24952137,
-32978891, 5911771,
-31678318, 17711332,
-438138, -18560722,
11889854, 10008611,
-30021446, -41158094,
27249924, -6364473,
3675464, -10123819,
91658762, 32110113,
13793528, -17896789,
-43851011, -30235288,
12878409, -29949060,
16760562, 9352174,
-17139120, -25025121,
7882676, 53803307,
-20059682, 19269291,
696953, 10759383,
14074164, -5079570,
39966810, 10595221,
25877656, 45087178,
-88725365, -75089180,
9577438, 43382741,
27719069, -12698973,
-272546, 84605,
28804405, 29683618,
25997579, 19543793,
43820254, -54165038,
41322368, -50454643,
32164059, 19246349,
-55517408, -30552551,
-33232176, -54736585,
22992706, -12050680,
-32711210, -13341784,
-20358334, -38967000,
23044974, -37239990,
672728, 9753346,
35695223, -64096973,
-44998166, 44116303,
16089700, 22324411,
-54827069, -9231313,
-48407805, -772476,
9857669, -30466635,
-4709837, -35019316,
-37927942, 12533106,
-9815948, 30250407,
-19546660, 42900655,
-30076457, -4310279,
8341668, 20562874,
-49984809, 65649853,
10519605, 76045298,
-67950557, -12547970,
17749949, 75096121,
11524971, -5354621,
25440722, -23598204,
-23217660, 18907152,
22823005, -1687667,
-35988505, 39043691,
30191341, 22105943,
-71239160, -52012345,
9553359, -101640339,
-24606234, 18138794,
-25950180, -33856368,
5094963, 30469008,
-11302580, 53093288,
32573324, -32852749,
-3598255, 33819581,
34007144, 5318089,
-15949990, -19694008,
2313516, 52817418,
13374530, -17335868,
37457693, 41198127,
20818885, 53146051,
-9652754, -70093544,
-46029075, 98970318,
-23013926, 45503999,
11129493, 35234434,
-33477989, -25741957,
9778369, -8645395,
37147387, -46031486,
8219447, -42535468,
5535669, -30029482,
13630862, 19766544,
40801559, 61828378,
48601056, 45230277,
-34397906, -16483706,
6892685, -73067055,
19759607, 7952384,
-8859163, -24676306,
83728971, -59707409,
28720838, 15033402,
-28553266, 19502308,
27242133, 28742975,
23496213, -8934312,
25499299, -14007973,
-57475695, -6905708,
51573875, -5849309,
-54017495, 7300675,
37229514, 56515551,
-37235488, 4010704,
12934207, 21832777,
32387771, 69795260,
27457499, -11382498,
1243151, 24498519,
-31071820, 9863964,
-3755367, -28491366,
-26945205, -85022179,
-55868329, -79824030,
-30245985, -11619089,
19741739, -20499655,
18594500, -13696640,
-13930881, -47500028,
2073491, 7620965,
15348857, 6978449,
6677799, -24149738,
8642206, 25426266,
69817705, -55134476,
-76411377, -35460761,
11375705, -8444368,
9727225, -43568438,
22221787, 41381171,
-19490435, 50151281,
29788011, 7916774,
5767035, -47122468,
28481721, 22105359,
32338723, -85785714,
44356208, -17949791,
-2159057, 107458893,
44192968, 14737027,
7650992, -38584287,
-47970663, 29754887,
-5023132, -9508872,
-16943900, 34740118,
-58020360, -12243269,
-14008043, 45029627,
-20634920, 33852117,
24185252, 7176433,
11387159, -10041632,
29623365, 8584874,
9537687, -6403047,
-4883557, -2652829,
-3008017, 23483110,
9702629, -26727452,
39085237, -26886613,
27035791, -254967,
-45487846, -24387712,
4056492, -50026357,
-7455054, 29203581,
19184154, -8914574,
-10071042, -52569576,
38060015, -13241803,
-6018202, -4826966,
-49226590, -78324338,
46820034, -45551461,
14791991, -60924397,
18971141, 37192465,
-23274112, -4768580,
27980009, 37337918,
-75073961, 18765786,
36830824, 16051425,
-54255, -22796364,
-54176090, 9561895,
-41229230, -44725882,
6959343, -24292744,
7413583, -22266734,
-33758210, 6658647,
-15202409, -60225788,
46957859, -46562563,
-15500939, 6636006,
1097764, 49302457,
26802717, 12297472,
30092144, -14857079,
4626879, -1629490,
-54329539, 2607466,
-55250920, 65696564,
14385016, -2444370,
-24737362, 31501235,
18955776, -2671209,
-46444927, -26875728,
15444031, 10382549,
21118611, 35293438,
12745561, -55841663,
-34001708, -36600907,
-11651534, -6433416,
14828116, 15549167,
-53359610, -31009226,
-23535639, -21798880,
-36158278, 20900828,
33628912, -44798771,
58031736, 35154604,
23791173, 28968457,
-25095254, -21555746,
7679347, 22146272,
-7499302, 43423319,
-28631167, 10555522,
11597311, 28842483,
3683085, 4317450,
-38018479, 555925,
-22921822, -2442792,
-9323308, -33363502,
21971102, -25077184,
-41889153, -1033942,
};


#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
-99489392, -598986422,
-133932183, -156318704,
-461760123, 90724560,
113446574, 339991139,
103441873, 17730653,
-468270693, -112676169,
335128020, -743759297,
-135120458, 764553945,
-944265487, 479692378,
302111316, -611686173,
-259555918, 1443553977,
278872245, -288644052,
-214955503, 72649861,
-150468694, -929001246,
-183027789, -433278362,
904072055, -60577945,
765752865, -496008386,
1471773718, 20448830,
-532869218, 375148675,
-47219532, -721360808,
577128856, -795977102,
481487738, -884233985,
106010857, -342852597,
697027839, 8746216,
-495356010, 446074002,
402599732, 265284435,
-73525219, 60832913,
-276755735, -1161719104,
188001339, 1600515026,
-727312131, -682987917,
-279864164, 540806554,
284898366, -171885827,
54709958, 130110315,
265679842, -401653587,
511242108, 122140034,
-540870753, -206340976,
205731520, -566717474,
383820542, -101611128,
355505894, -762445848,
-494031873, 325676459,
152770107, -482503440,
-371526418, 635376373,
-325691167, 25542093,
118402235, -709475672,
-78597940, 1326200679,
-174068535, 453040939,
-404541398, -250408582,
-74367576, -253667913,
-940566200, 315556748,
-232913216, 642657931,
144262636, 35112609,
-469882512, -686650968,
-442367342, 52622441,
685647647, -50383950,
-109027040, 90246564,
-460631090, 962425612,
693524324, 154653055,
181719455, -358694004,
55939365, -654861618,
-117362455, 233575775,
719012843, 457811371,
-334588480, 393357720,
-209964449, 512918364,
-796303371, -704400504,
-647526257, -604254133,
-152177966, 145115407,
78004724, -136124697,
-354637693, -48519283,
401440281, -282152329,
-170686140, 628077777,
-797754152, -578894882,
-679324514, 430155930,
-790537606, -25862111,
231764970, -6348859,
1328018840, 280275809,
821906660, -264263732,
-1181418191, 154656308,
98605495, -511619830,
1458285280, -108970896,
150259394, -441632725,
1165663755, 870459332,
286006132, -261843694,
-383500895, -168841592,
-140812625, 47308984,
599110399, 142315601,
-299870905, 342312708,
-532572073, -275734686,
378101788, 107842311,
341492198, -649085404,
-775156278, 150210309,
-305965245, -984798485,
-458215019, -63144932,
-135329961, 585314724,
-89323640, -919169829,
-69357551, -263152690,
-530976916, -666804614,
-62836698, 1041706517,
468474913, -272932483,
1422170827, 698917636,
-68104010, -1018428580,
-177771742, 181200251,
655203155, -774665969,
8839972, 228009997,
-298204058, 169332069,
217341504, 271967206,
235856380, -299115939,
-627723596, -202046491,
-530781948, -407045091,
263418621, -793277205,
345305913, -15071987,
-1017850036, -310910749,
-70133446, 458637853,
-91358733, 222107548,
471512618, -437722258,
593960869, 853423850,
-265513356, -352099995,
419275545, 983793361,
-816001012, 358532498,
832687156, 720623028,
690380795, -663925716,
-554276885, 444975934,
411676797, -136238812,
-724689547, -238580114,
1103004925, -994669819,
366709090, -905334038,
282926335, 324328965,
-66920997, 442235678,
-1017870973, -713469844,
201305088, 467407156,
-502862264, 252064260,
516840421, -42025420,
950009843, 194875955,
-12708808, 279025601,
-65518160, -553309882,
72371173, 261398903,
1133876336, 18102531,
-14727856, -382017921,
24005692, -36294999,
65745121, 757463407,
-820307070, -268230278,
50299090, -611106579,
-535762127, -227844494,
204806472, 55471802,
426785708, 118362932,
-239616166, 203561999,
-125026298, 422526564,
1070897227, -342240556,
-356944744, -139875156,
-146660737, 989372120,
-66251656, -652211940,
-49920719, 509092463,
-678776870, -343408253,
712971374, 257114282,
-269052577, 424712364,
-217057939, 783616405,
1226683326, 526418710,
289005925, 380795790,
210958089, -179989008,
-438617761, -290674152,
-217882550, -518933437,
252912708, -488574111,
-249769415, -1061565247,
-547528724, 806210604,
454610685, -264484085,
-956866824, 309991294,
173829503, 501493825,
-394544241, -546453222,
1021525412, 766213740,
-838681552, 238356167,
336802838, -548876032,
754165811, -208720481,
153859483, -26961645,
207672169, 41311656,
729258568, 812065947,
148211678, 899171627,
243184301, 88888702,
1395557456, -469261008,
310636806, -207827864,
-1819768567, -23539898,
738048842, 227367243,
-389486925, 259671058,
-704556353, 100117183,
497946249, 290895198,
1046690937, -221247695,
855331469, 307379229,
635939675, 181127577,
129508240, 46483788,
1023978668, -351584926,
-848948534, -205848082,
-209376455, -326086834,
301709110, -222907567,
-156364072, 491543367,
-581991835, 24840795,
135314327, -227535659,
-471435677, -149839642,
549759025, -503502395,
-622801013, 115497590,
735985632, -956266165,
252969943, 978891564,
438393727, -238234118,
289448369, -83907485,
-621430560, 595397863,
-653443230, 925758366,
81492551, 59196083,
284714456, -336008953,
-380887100, -534940508,
33513243, -891500622,
-74863788, -265525359,
451139139, -725327913,
-46110804, 264499577,
-856212430, 497845558,
68827832, -229289816,
-576926289, -34403904,
347723139, -813273499,
-428172748, -402664055,
641906174, 812985835,
-277819681, -295906265,
1506475772, 355659747,
274289317, -147969742,
-429459335, -26082024,
-301760645, -734857123,
856047503, 180244956,
-350954065, -159330139,
-151843160, -112342183,
-37961404, -249201973,
-195663779, -633403477,
-829738787, 709747533,
288115819, -223899671,
-234782224, -219456933,
-1553672371, -1174914323,
-446424250, 48626661,
-196323209, -234976282,
-89175774, -510703945,
157018990, 301577607,
-916072202, 650241699,
321587, -742516555,
-12815290, 796367349,
-175512248, 338417975,
-733462562, 5744418,
-205977907, 825376017,
132855397, -587813744,
-709431611, 197647292,
-621622311, -666989717,
147791045, 80790716,
146867206, 654319885,
-559729912, -164411881,
679844180, 643584779,
664259007, -1120883209,
-639901165, 228985264,
-379624016, 569680913,
-639371462, -298154024,
-407131167, 209335078,
1306282834, 1083375919,
-26820127, -237445302,
120872302, 1104771305,
-379031431, -467413244,
};
