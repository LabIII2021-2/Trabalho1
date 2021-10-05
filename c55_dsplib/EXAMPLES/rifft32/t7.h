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
#define NX 512
#define FNAME "t7"
#define MAXERROR 20

#pragma DATA_SECTION (x,".input")

LDATA x[NX] ={
-2072704159,	/* 0 */ 
1371645020,	/* 1 */ 
520234750,	/* 2 */ 
258625831,	/* 3 */ 
-1099266253,	/* 4 */ 
1382873760,	/* 5 */ 
-1016895326,	/* 6 */ 
1089243095,	/* 7 */ 
685600622,	/* 8 */ 
-1227967874,	/* 9 */ 
438544922,	/* 10 */ 
450656385,	/* 11 */ 
684985427,	/* 12 */ 
-1359806849,	/* 13 */ 
586405846,	/* 14 */ 
-1415869989,	/* 15 */ 
170068446,	/* 16 */ 
529920981,	/* 17 */ 
798311516,	/* 18 */ 
761618897,	/* 19 */ 
1618310782,	/* 20 */ 
-2091910160,	/* 21 */ 
-814234807,	/* 22 */ 
1198516377,	/* 23 */ 
-827574248,	/* 24 */ 
1832386133,	/* 25 */ 
767519262,	/* 26 */ 
-1828092440,	/* 27 */ 
-1843777387,	/* 28 */ 
-2096033060,	/* 29 */ 
-1171748685,	/* 30 */ 
69794815,	/* 31 */ 
-179493578,	/* 32 */ 
872664417,	/* 33 */ 
354230119,	/* 34 */ 
39535522,	/* 35 */ 
-1828229366,	/* 36 */ 
-1317408247,	/* 37 */ 
-517044601,	/* 38 */ 
-960109544,	/* 39 */ 
1163312284,	/* 40 */ 
-799084692,	/* 41 */ 
593476003,	/* 42 */ 
2089579789,	/* 43 */ 
12350247,	/* 44 */ 
1922679074,	/* 45 */ 
1408719376,	/* 46 */ 
1793215192,	/* 47 */ 
-1661643300,	/* 48 */ 
1340436501,	/* 49 */ 
1753299009,	/* 50 */ 
-1475705745,	/* 51 */ 
-1622825241,	/* 52 */ 
1128031082,	/* 53 */ 
952529705,	/* 54 */ 
651222924,	/* 55 */ 
1090909940,	/* 56 */ 
700705410,	/* 57 */ 
1646927339,	/* 58 */ 
-978478502,	/* 59 */ 
-345999249,	/* 60 */ 
-1232559581,	/* 61 */ 
-1994383496,	/* 62 */ 
-1798708305,	/* 63 */ 
1505522301,	/* 64 */ 
-686252336,	/* 65 */ 
-145348726,	/* 66 */ 
1776921872,	/* 67 */ 
-1165637597,	/* 68 */ 
1554815508,	/* 69 */ 
672604221,	/* 70 */ 
1679949331,	/* 71 */ 
-50918110,	/* 72 */ 
2115685351,	/* 73 */ 
-544006537,	/* 74 */ 
134755372,	/* 75 */ 
-1368599072,	/* 76 */ 
8350020,	/* 77 */ 
-334137255,	/* 78 */ 
688961531,	/* 79 */ 
745759420,	/* 80 */ 
1964021757,	/* 81 */ 
-1323294203,	/* 82 */ 
-1669645702,	/* 83 */ 
279376307,	/* 84 */ 
2014852291,	/* 85 */ 
-2045299949,	/* 86 */ 
1589905841,	/* 87 */ 
-2031846357,	/* 88 */ 
83866690,	/* 89 */ 
-1321466126,	/* 90 */ 
926284764,	/* 91 */ 
-1070745166,	/* 92 */ 
1863248851,	/* 93 */ 
-1558104212,	/* 94 */ 
92857952,	/* 95 */ 
1697208597,	/* 96 */ 
1899848785,	/* 97 */ 
-708240664,	/* 98 */ 
-268993427,	/* 99 */ 
-123872039,	/* 100 */ 
-1506050020,	/* 101 */ 
-1563794124,	/* 102 */ 
139564877,	/* 103 */ 
969660724,	/* 104 */ 
-435023576,	/* 105 */ 
-608027035,	/* 106 */ 
-922125681,	/* 107 */ 
1583117989,	/* 108 */ 
542884009,	/* 109 */ 
-1111545305,	/* 110 */ 
2053139729,	/* 111 */ 
603385910,	/* 112 */ 
-1160175196,	/* 113 */ 
778750677,	/* 114 */ 
712134895,	/* 115 */ 
-1568717469,	/* 116 */ 
-2050670601,	/* 117 */ 
-1021243454,	/* 118 */ 
-1646890143,	/* 119 */ 
-1849579107,	/* 120 */ 
1515673362,	/* 121 */ 
-1372832010,	/* 122 */ 
-2008046150,	/* 123 */ 
1004605152,	/* 124 */ 
156822875,	/* 125 */ 
-961849077,	/* 126 */ 
-564911434,	/* 127 */ 
-2091928174,	/* 128 */ 
1671460241,	/* 129 */ 
1571889310,	/* 130 */ 
-1055395829,	/* 131 */ 
298387048,	/* 132 */ 
-1463300119,	/* 133 */ 
405251552,	/* 134 */ 
-725347086,	/* 135 */ 
681168037,	/* 136 */ 
1561640894,	/* 137 */ 
290410877,	/* 138 */ 
2063444995,	/* 139 */ 
1253281847,	/* 140 */ 
-1491949822,	/* 141 */ 
1430198040,	/* 142 */ 
-1323304859,	/* 143 */ 
596883069,	/* 144 */ 
725777228,	/* 145 */ 
1168491341,	/* 146 */ 
-516127218,	/* 147 */ 
-250863342,	/* 148 */ 
-72749498,	/* 149 */ 
464263827,	/* 150 */ 
-1391448966,	/* 151 */ 
-2138570052,	/* 152 */ 
1246377947,	/* 153 */ 
58442224,	/* 154 */ 
-1231547283,	/* 155 */ 
-1702999841,	/* 156 */ 
-1471580641,	/* 157 */ 
-397180414,	/* 158 */ 
-396140956,	/* 159 */ 
-1920978161,	/* 160 */ 
1897391861,	/* 161 */ 
-1503209834,	/* 162 */ 
-496560030,	/* 163 */ 
-811416160,	/* 164 */ 
-1423491364,	/* 165 */ 
1703420456,	/* 166 */ 
-761316630,	/* 167 */ 
1004906027,	/* 168 */ 
-382625357,	/* 169 */ 
-430339118,	/* 170 */ 
23715328,	/* 171 */ 
-1420178489,	/* 172 */ 
106270443,	/* 173 */ 
606400175,	/* 174 */ 
-2077708193,	/* 175 */ 
1446621739,	/* 176 */ 
1303229835,	/* 177 */ 
849394429,	/* 178 */ 
-163674363,	/* 179 */ 
-1792485890,	/* 180 */ 
1377331316,	/* 181 */ 
-1318337137,	/* 182 */ 
-234676186,	/* 183 */ 
-2091621011,	/* 184 */ 
-821365584,	/* 185 */ 
1611958984,	/* 186 */ 
1439784160,	/* 187 */ 
-716779542,	/* 188 */ 
1634953437,	/* 189 */ 
-87235781,	/* 190 */ 
261179736,	/* 191 */ 
497774102,	/* 192 */ 
695281439,	/* 193 */ 
500885836,	/* 194 */ 
795090729,	/* 195 */ 
43602558,	/* 196 */ 
918862934,	/* 197 */ 
65310899,	/* 198 */ 
454644654,	/* 199 */ 
2004272084,	/* 200 */ 
1383345357,	/* 201 */ 
-782676597,	/* 202 */ 
376617102,	/* 203 */ 
-1588112900,	/* 204 */ 
-1054934929,	/* 205 */ 
1301377646,	/* 206 */ 
720820535,	/* 207 */ 
-2088750013,	/* 208 */ 
264454930,	/* 209 */ 
-195139770,	/* 210 */ 
1739069732,	/* 211 */ 
-935527049,	/* 212 */ 
-1867976409,	/* 213 */ 
-100527034,	/* 214 */ 
2077319116,	/* 215 */ 
1813796240,	/* 216 */ 
262809629,	/* 217 */ 
654164154,	/* 218 */ 
1171032837,	/* 219 */ 
-1691292942,	/* 220 */ 
-2142659291,	/* 221 */ 
179356172,	/* 222 */ 
-2117817854,	/* 223 */ 
-208982207,	/* 224 */ 
-1306990823,	/* 225 */ 
1233147020,	/* 226 */ 
509171671,	/* 227 */ 
-2080613563,	/* 228 */ 
1678537126,	/* 229 */ 
1123894247,	/* 230 */ 
1748027368,	/* 231 */ 
1110432622,	/* 232 */ 
-512209791,	/* 233 */ 
-725301114,	/* 234 */ 
17515030,	/* 235 */ 
277292267,	/* 236 */ 
1147489149,	/* 237 */ 
1201902757,	/* 238 */ 
-68292235,	/* 239 */ 
1297866117,	/* 240 */ 
-124489402,	/* 241 */ 
-1276513159,	/* 242 */ 
341909166,	/* 243 */ 
715041657,	/* 244 */ 
759125211,	/* 245 */ 
1900381261,	/* 246 */ 
1160163088,	/* 247 */ 
1019541806,	/* 248 */ 
1572927179,	/* 249 */ 
2108396119,	/* 250 */ 
16867220,	/* 251 */ 
554362778,	/* 252 */ 
1256626082,	/* 253 */ 
-220527930,	/* 254 */ 
104602519,	/* 255 */ 
-1410870669,	/* 256 */ 
-1586119891,	/* 257 */ 
-1207705093,	/* 258 */ 
-1694278894,	/* 259 */ 
-1539910232,	/* 260 */ 
-184801258,	/* 261 */ 
1237398254,	/* 262 */ 
-940229031,	/* 263 */ 
-1181913789,	/* 264 */ 
1755927995,	/* 265 */ 
-2115794898,	/* 266 */ 
381094426,	/* 267 */ 
180876786,	/* 268 */ 
659314539,	/* 269 */ 
-801210546,	/* 270 */ 
-1154548589,	/* 271 */ 
-360467050,	/* 272 */ 
-864066211,	/* 273 */ 
740534598,	/* 274 */ 
1882113313,	/* 275 */ 
-673608159,	/* 276 */ 
270395145,	/* 277 */ 
-1636697495,	/* 278 */ 
-1421400707,	/* 279 */ 
-949541988,	/* 280 */ 
243992694,	/* 281 */ 
-61887894,	/* 282 */ 
1942089739,	/* 283 */ 
-1151276074,	/* 284 */ 
-91652337,	/* 285 */ 
113901452,	/* 286 */ 
1257100512,	/* 287 */ 
-1318390243,	/* 288 */ 
1759044596,	/* 289 */ 
1813138367,	/* 290 */ 
-2090295992,	/* 291 */ 
1149002014,	/* 292 */ 
1921129869,	/* 293 */ 
1345502418,	/* 294 */ 
1820153070,	/* 295 */ 
-1292667651,	/* 296 */ 
748416154,	/* 297 */ 
1834210347,	/* 298 */ 
-670735547,	/* 299 */ 
405803493,	/* 300 */ 
495963300,	/* 301 */ 
-2132778808,	/* 302 */ 
2070021194,	/* 303 */ 
1715724074,	/* 304 */ 
827803715,	/* 305 */ 
-259159568,	/* 306 */ 
863300498,	/* 307 */ 
471175167,	/* 308 */ 
-859398592,	/* 309 */ 
1529015186,	/* 310 */ 
-1665970729,	/* 311 */ 
-895151695,	/* 312 */ 
-1728780245,	/* 313 */ 
-440413571,	/* 314 */ 
-715845115,	/* 315 */ 
1907782770,	/* 316 */ 
1453939190,	/* 317 */ 
-1037442650,	/* 318 */ 
-1963041280,	/* 319 */ 
-2121996448,	/* 320 */ 
319590773,	/* 321 */ 
1047446153,	/* 322 */ 
1317696399,	/* 323 */ 
590802331,	/* 324 */ 
-1068174746,	/* 325 */ 
-1527479266,	/* 326 */ 
650842067,	/* 327 */ 
1915737186,	/* 328 */ 
1356587785,	/* 329 */ 
1847712285,	/* 330 */ 
-816214016,	/* 331 */ 
-992823656,	/* 332 */ 
156540347,	/* 333 */ 
-1446064087,	/* 334 */ 
-1241172864,	/* 335 */ 
-1216161183,	/* 336 */ 
651867160,	/* 337 */ 
-1920619574,	/* 338 */ 
-1162573124,	/* 339 */ 
719043604,	/* 340 */ 
-811952471,	/* 341 */ 
-830422483,	/* 342 */ 
947718103,	/* 343 */ 
1951465933,	/* 344 */ 
-1584090114,	/* 345 */ 
-1854051563,	/* 346 */ 
-1609475661,	/* 347 */ 
-1433716778,	/* 348 */ 
1766847853,	/* 349 */ 
-1562094031,	/* 350 */ 
502441257,	/* 351 */ 
-992117053,	/* 352 */ 
-1199618871,	/* 353 */ 
914311486,	/* 354 */ 
210417073,	/* 355 */ 
1895387489,	/* 356 */ 
-730652143,	/* 357 */ 
878174152,	/* 358 */ 
1904307401,	/* 359 */ 
350409966,	/* 360 */ 
1632586516,	/* 361 */ 
1071966642,	/* 362 */ 
-516987874,	/* 363 */ 
968681439,	/* 364 */ 
-1448125862,	/* 365 */ 
1959187952,	/* 366 */ 
-1304556770,	/* 367 */ 
1186119156,	/* 368 */ 
486552733,	/* 369 */ 
-1450350314,	/* 370 */ 
-2013906094,	/* 371 */ 
-907741543,	/* 372 */ 
2023003352,	/* 373 */ 
1934686452,	/* 374 */ 
-1167908970,	/* 375 */ 
1969157602,	/* 376 */ 
772408093,	/* 377 */ 
-1911201557,	/* 378 */ 
428772311,	/* 379 */ 
-458888571,	/* 380 */ 
-1222370677,	/* 381 */ 
-1363946817,	/* 382 */ 
-1817645842,	/* 383 */ 
-2115387557,	/* 384 */ 
1240189493,	/* 385 */ 
-2070879250,	/* 386 */ 
1623083909,	/* 387 */ 
-633264950,	/* 388 */ 
953987629,	/* 389 */ 
2011779836,	/* 390 */ 
-1478746861,	/* 391 */ 
-1447450166,	/* 392 */ 
-801372056,	/* 393 */ 
-2021088731,	/* 394 */ 
-611434317,	/* 395 */ 
-2030498707,	/* 396 */ 
1261164111,	/* 397 */ 
2143965345,	/* 398 */ 
-1673845390,	/* 399 */ 
526515310,	/* 400 */ 
-1577934100,	/* 401 */ 
-815834253,	/* 402 */ 
-1568418080,	/* 403 */ 
-1188185609,	/* 404 */ 
-444283729,	/* 405 */ 
-1566890053,	/* 406 */ 
-1112033247,	/* 407 */ 
1835984265,	/* 408 */ 
-467671413,	/* 409 */ 
48368406,	/* 410 */ 
-1748323018,	/* 411 */ 
-2054082092,	/* 412 */ 
-1462140557,	/* 413 */ 
1479536743,	/* 414 */ 
1628288962,	/* 415 */ 
-1344235313,	/* 416 */ 
2109927545,	/* 417 */ 
910570167,	/* 418 */ 
1594839383,	/* 419 */ 
-87474647,	/* 420 */ 
-17156994,	/* 421 */ 
-912452441,	/* 422 */ 
-1885553536,	/* 423 */ 
-1020091423,	/* 424 */ 
-1347363922,	/* 425 */ 
1791207855,	/* 426 */ 
-1617843888,	/* 427 */ 
-2089527194,	/* 428 */ 
-559618135,	/* 429 */ 
853071748,	/* 430 */ 
1672066324,	/* 431 */ 
402701038,	/* 432 */ 
-1474353921,	/* 433 */ 
-787234221,	/* 434 */ 
-1144943164,	/* 435 */ 
-2111100029,	/* 436 */ 
-442750563,	/* 437 */ 
643614351,	/* 438 */ 
-1782230584,	/* 439 */ 
1154412572,	/* 440 */ 
2017151726,	/* 441 */ 
922454831,	/* 442 */ 
1210895788,	/* 443 */ 
-1127036676,	/* 444 */ 
-1306695737,	/* 445 */ 
-1016886792,	/* 446 */ 
918108040,	/* 447 */ 
2051070133,	/* 448 */ 
588875358,	/* 449 */ 
197223019,	/* 450 */ 
1494744906,	/* 451 */ 
1297369813,	/* 452 */ 
722798239,	/* 453 */ 
734291384,	/* 454 */ 
1377016413,	/* 455 */ 
2020461396,	/* 456 */ 
-56151101,	/* 457 */ 
1363380625,	/* 458 */ 
607982731,	/* 459 */ 
-831639996,	/* 460 */ 
691129125,	/* 461 */ 
-609750874,	/* 462 */ 
1881864016,	/* 463 */ 
-52964644,	/* 464 */ 
-1756507369,	/* 465 */ 
746537185,	/* 466 */ 
63904092,	/* 467 */ 
-1195688022,	/* 468 */ 
966311248,	/* 469 */ 
-1854181250,	/* 470 */ 
1993199214,	/* 471 */ 
-1255479832,	/* 472 */ 
-1455340590,	/* 473 */ 
593596952,	/* 474 */ 
-2146289003,	/* 475 */ 
-705880538,	/* 476 */ 
-965842318,	/* 477 */ 
-1956043781,	/* 478 */ 
-1744026842,	/* 479 */ 
-386519569,	/* 480 */ 
1360906044,	/* 481 */ 
1591199570,	/* 482 */ 
-2050405083,	/* 483 */ 
975620143,	/* 484 */ 
1494539729,	/* 485 */ 
981732161,	/* 486 */ 
1954438282,	/* 487 */ 
671455754,	/* 488 */ 
1040588554,	/* 489 */ 
-665799314,	/* 490 */ 
1649196778,	/* 491 */ 
-656016045,	/* 492 */ 
-1891844047,	/* 493 */ 
937989717,	/* 494 */ 
1967818601,	/* 495 */ 
-1473735644,	/* 496 */ 
-359224748,	/* 497 */ 
-1743432601,	/* 498 */ 
-214956846,	/* 499 */ 
1585339045,	/* 500 */ 
-465453935,	/* 501 */ 
-1061679956,	/* 502 */ 
-625362321,	/* 503 */ 
1043478068,	/* 504 */ 
647753821,	/* 505 */ 
1888707836,	/* 506 */ 
1429218420,	/* 507 */ 
-128931186,	/* 508 */ 
557712759,	/* 509 */ 
-1897378988,	/* 510 */ 
181175372,	/* 511 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

LDATA rtest[NX] ={
-50555151,	-34056730,	 /* 0 */ 
-38428724,	16505004,	 /* 1 */ 
15012883,	-51610534,	 /* 2 */ 
17671915,	-15485721,	 /* 3 */ 
23367353,	59016296,	 /* 4 */ 
19449399,	-15105613,	 /* 5 */ 
-49236931,	20478704,	 /* 6 */ 
40437989,	-43480050,	 /* 7 */ 
31232871,	38946573,	 /* 8 */ 
-21134133,	-39893713,	 /* 9 */ 
109208513,	31377422,	 /* 10 */ 
20064520,	-20926836,	 /* 11 */ 
-27078346,	4369147,	 /* 12 */ 
-73446069,	-49344528,	 /* 13 */ 
-10034616,	26537825,	 /* 14 */ 
-38999809,	29070788,	 /* 15 */ 
-79864912,	-67504330,	 /* 16 */ 
14020050,	-90798520,	 /* 17 */ 
33868512,	56900187,	 /* 18 */ 
14051235,	-20486277,	 /* 19 */ 
-19086449,	24283598,	 /* 20 */ 
38703764,	16136463,	 /* 21 */ 
-663101,	-52888324,	 /* 22 */ 
-3657369,	-44528088,	 /* 23 */ 
-25955776,	-8259262,	 /* 24 */ 
-32798006,	-44552877,	 /* 25 */ 
18842543,	41182598,	 /* 26 */ 
27999015,	-58839642,	 /* 27 */ 
50553588,	65795481,	 /* 28 */ 
-62479635,	-59740105,	 /* 29 */ 
-24608798,	717390,	 /* 30 */ 
-24415254,	39058545,	 /* 31 */ 
-65013817,	28569890,	 /* 32 */ 
28802403,	-51362718,	 /* 33 */ 
-37817415,	-15455979,	 /* 34 */ 
-10557443,	38716199,	 /* 35 */ 
-18746263,	12128341,	 /* 36 */ 
41266317,	-11915753,	 /* 37 */ 
11478435,	-62377618,	 /* 38 */ 
-48750897,	-37931967,	 /* 39 */ 
-25960602,	26877868,	 /* 40 */ 
-17964319,	-32456207,	 /* 41 */ 
13967437,	9488827,	 /* 42 */ 
10608957,	86371880,	 /* 43 */ 
12704451,	-13697449,	 /* 44 */ 
86576442,	-48166977,	 /* 45 */ 
-14519068,	95967051,	 /* 46 */ 
-65234076,	32326765,	 /* 47 */ 
-69323751,	-4824433,	 /* 48 */ 
8790062,	-46941361,	 /* 49 */ 
28762754,	-60005363,	 /* 50 */ 
-1214685,	25494011,	 /* 51 */ 
-17855005,	-10409567,	 /* 52 */ 
-22292584,	12417078,	 /* 53 */ 
52855032,	-31117108,	 /* 54 */ 
32070093,	39167157,	 /* 55 */ 
-34082964,	32281521,	 /* 56 */ 
-37764153,	5294762,	 /* 57 */ 
40164839,	36763992,	 /* 58 */ 
37571909,	24435744,	 /* 59 */ 
-24884747,	20568016,	 /* 60 */ 
-92097002,	41214922,	 /* 61 */ 
21673942,	34986433,	 /* 62 */ 
87407185,	12102581,	 /* 63 */ 
61773371,	-36571774,	 /* 64 */ 
-7827492,	-46369203,	 /* 65 */ 
-15191099,	14418665,	 /* 66 */ 
15774808,	-94505654,	 /* 67 */ 
-80411234,	29037085,	 /* 68 */ 
-64544950,	-28138966,	 /* 69 */ 
-10737082,	-6435052,	 /* 70 */ 
34376697,	-39469642,	 /* 71 */ 
-75792966,	10526418,	 /* 72 */ 
23214863,	-25034237,	 /* 73 */ 
-13351359,	26937036,	 /* 74 */ 
-21312379,	-39133328,	 /* 75 */ 
47964199,	17285977,	 /* 76 */ 
-42913706,	67481229,	 /* 77 */ 
62343216,	-32417264,	 /* 78 */ 
38808276,	77363020,	 /* 79 */ 
4604321,	3536128,	 /* 80 */ 
18667757,	-56393701,	 /* 81 */ 
91127598,	22900406,	 /* 82 */ 
11971966,	2245879,	 /* 83 */ 
73928310,	-19747431,	 /* 84 */ 
-131729,	-18261746,	 /* 85 */ 
2127247,	-22001360,	 /* 86 */ 
-28045035,	9871265,	 /* 87 */ 
1959609,	-77772937,	 /* 88 */ 
95313812,	-29464112,	 /* 89 */ 
-2277356,	46704766,	 /* 90 */ 
-54791392,	-34591760,	 /* 91 */ 
-18841727,	35006613,	 /* 92 */ 
-41120234,	-33654683,	 /* 93 */ 
42044263,	-45292124,	 /* 94 */ 
66079470,	-12509419,	 /* 95 */ 
-9796557,	-30656158,	 /* 96 */ 
-15724005,	-11358483,	 /* 97 */ 
-20592861,	-8540327,	 /* 98 */ 
-28549536,	2500307,	 /* 99 */ 
12612756,	-87904697,	 /* 100 */ 
7027536,	19997244,	 /* 101 */ 
20680444,	40250926,	 /* 102 */ 
29819286,	-37321746,	 /* 103 */ 
30450150,	44654026,	 /* 104 */ 
-39941586,	-20597851,	 /* 105 */ 
-36523130,	84651403,	 /* 106 */ 
-4493761,	-1393578,	 /* 107 */ 
-68510792,	-34612716,	 /* 108 */ 
-47995360,	39640172,	 /* 109 */ 
1952165,	-11981604,	 /* 110 */ 
-31408474,	873019,	 /* 111 */ 
-35844848,	-22809370,	 /* 112 */ 
34424505,	-9118195,	 /* 113 */ 
7363942,	-4084941,	 /* 114 */ 
20470882,	-18273660,	 /* 115 */ 
-19007216,	-23705634,	 /* 116 */ 
5754114,	-50141535,	 /* 117 */ 
4878701,	-30478405,	 /* 118 */ 
21106872,	-9656938,	 /* 119 */ 
8957049,	-52160548,	 /* 120 */ 
5174963,	11989370,	 /* 121 */ 
7960332,	-598427,	 /* 122 */ 
-20794269,	69371781,	 /* 123 */ 
36452048,	-67790865,	 /* 124 */ 
5301820,	-108006059,	 /* 125 */ 
19086607,	37952036,	 /* 126 */ 
19483747,	27249840,	 /* 127 */ 
-50936273,	-50611269,	 /* 128 */ 
11855383,	-3226155,	 /* 129 */ 
-44907258,	-29736041,	 /* 130 */ 
11664809,	-17087661,	 /* 131 */ 
-19119428,	29130518,	 /* 132 */ 
63307250,	58749175,	 /* 133 */ 
57746469,	-6282819,	 /* 134 */ 
-22548524,	2667168,	 /* 135 */ 
34685247,	-50542319,	 /* 136 */ 
-5802520,	-17822258,	 /* 137 */ 
9949726,	49470427,	 /* 138 */ 
-26446611,	13321623,	 /* 139 */ 
-30575660,	1356958,	 /* 140 */ 
-53751185,	21025209,	 /* 141 */ 
-68528142,	-24784824,	 /* 142 */ 
122509013,	10763039,	 /* 143 */ 
13121923,	3344511,	 /* 144 */ 
9849590,	-2790766,	 /* 145 */ 
-8694603,	-38397955,	 /* 146 */ 
76913812,	-29688288,	 /* 147 */ 
-13200522,	-5078062,	 /* 148 */ 
-47342119,	-70656227,	 /* 149 */ 
-38924296,	-32080040,	 /* 150 */ 
11997459,	-13708940,	 /* 151 */ 
54543993,	6663250,	 /* 152 */ 
-6326679,	75138745,	 /* 153 */ 
6375576,	9373596,	 /* 154 */ 
-35792356,	4727480,	 /* 155 */ 
-34719271,	48217835,	 /* 156 */ 
22733637,	-46549571,	 /* 157 */ 
-20120501,	24376132,	 /* 158 */ 
-34022811,	15393686,	 /* 159 */ 
-16001735,	17813193,	 /* 160 */ 
-12301190,	4838324,	 /* 161 */ 
11800264,	-30858498,	 /* 162 */ 
-28492603,	-54636358,	 /* 163 */ 
-14022640,	34343967,	 /* 164 */ 
27547181,	6283175,	 /* 165 */ 
44439311,	-5858951,	 /* 166 */ 
-41206483,	-109386909,	 /* 167 */ 
-15688092,	20890195,	 /* 168 */ 
-5275089,	-38561779,	 /* 169 */ 
61869619,	13804217,	 /* 170 */ 
-48791003,	-51524675,	 /* 171 */ 
7478576,	-141871316,	 /* 172 */ 
-40632029,	-17570743,	 /* 173 */ 
2895351,	-31974162,	 /* 174 */ 
-10676881,	6570427,	 /* 175 */ 
20830335,	13943541,	 /* 176 */ 
70243265,	-41396541,	 /* 177 */ 
25547881,	-16848345,	 /* 178 */ 
34098975,	-37302142,	 /* 179 */ 
-65933011,	-7903653,	 /* 180 */ 
14254580,	12557064,	 /* 181 */ 
-19473287,	38743270,	 /* 182 */ 
-16714357,	7229745,	 /* 183 */ 
44274091,	22410222,	 /* 184 */ 
19862515,	-21670289,	 /* 185 */ 
-7003593,	-3270893,	 /* 186 */ 
1026274,	17643085,	 /* 187 */ 
535797,	-54137741,	 /* 188 */ 
20545604,	27056600,	 /* 189 */ 
-31737886,	-5013332,	 /* 190 */ 
7918229,	28569285,	 /* 191 */ 
44185447,	-19004930,	 /* 192 */ 
-23698109,	-37117716,	 /* 193 */ 
3234827,	126298885,	 /* 194 */ 
-52700458,	18817235,	 /* 195 */ 
-37935664,	-73908949,	 /* 196 */ 
-3034705,	-16953857,	 /* 197 */ 
22666879,	11383255,	 /* 198 */ 
8794309,	-68933335,	 /* 199 */ 
38783079,	-105883656,	 /* 200 */ 
83889903,	31910046,	 /* 201 */ 
-30236344,	-55306763,	 /* 202 */ 
36860968,	64786163,	 /* 203 */ 
16456741,	-14374914,	 /* 204 */ 
-47551839,	24769387,	 /* 205 */ 
1408455,	73110110,	 /* 206 */ 
99056414,	-10558575,	 /* 207 */ 
-29439078,	38815498,	 /* 208 */ 
12387489,	1748427,	 /* 209 */ 
25881702,	35493964,	 /* 210 */ 
-19496868,	-26707417,	 /* 211 */ 
-82271501,	30087895,	 /* 212 */ 
22588784,	-51076931,	 /* 213 */ 
-17633328,	-43152475,	 /* 214 */ 
-5117987,	10271774,	 /* 215 */ 
-67802918,	22125868,	 /* 216 */ 
28326830,	81074265,	 /* 217 */ 
-13799860,	72885770,	 /* 218 */ 
32463739,	-42311865,	 /* 219 */ 
47104405,	-20841819,	 /* 220 */ 
-11812494,	15100778,	 /* 221 */ 
-13338673,	15719753,	 /* 222 */ 
21083279,	3730966,	 /* 223 */ 
-20716712,	53433860,	 /* 224 */ 
11359436,	-30491012,	 /* 225 */ 
2588938,	44768245,	 /* 226 */ 
-11958173,	20824734,	 /* 227 */ 
-54512241,	48619826,	 /* 228 */ 
-14890212,	32972164,	 /* 229 */ 
-17464119,	25085886,	 /* 230 */ 
17063966,	73153496,	 /* 231 */ 
6031039,	55944458,	 /* 232 */ 
-5258025,	27114847,	 /* 233 */ 
-60706870,	-23068166,	 /* 234 */ 
15011202,	-23166876,	 /* 235 */ 
-35237638,	-63509017,	 /* 236 */ 
28923081,	-42495126,	 /* 237 */ 
7037303,	-27369171,	 /* 238 */ 
-33979985,	-71803280,	 /* 239 */ 
11419509,	-13256640,	 /* 240 */ 
57563751,	10679762,	 /* 241 */ 
36465683,	-23970103,	 /* 242 */ 
-43299646,	40024475,	 /* 243 */ 
-98618794,	42546725,	 /* 244 */ 
17579412,	-373707,	 /* 245 */ 
-32091798,	-31038427,	 /* 246 */ 
3934542,	76016690,	 /* 247 */ 
13652484,	-28121836,	 /* 248 */ 
44526036,	-39783073,	 /* 249 */ 
-2845972,	-48313830,	 /* 250 */ 
-71520030,	-7702395,	 /* 251 */ 
-42407968,	26669483,	 /* 252 */ 
15082108,	70692398,	 /* 253 */ 
43491361,	-17844450,	 /* 254 */ 
25268793,	8215776,	 /* 255 */ 
};

LDATA error;
