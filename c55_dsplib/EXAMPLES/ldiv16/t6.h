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

/* Test for divQ31byQ15: rand */
#define NX 256
#define FNAME "t6"
#define MAXERROR 3.000000e-004

LDATA x[256] = {
-563919933, 
-287199578, 
-19438334, 
-1065307360, 
-796532707, 
-445365941, 
-1184016805, 
-1021435324, 
-1779247692, 
-1866881065, 
-1677654745, 
-1920965975, 
-1843773925, 
-1166151682, 
-454980816, 
-1543903340, 
-1664757803, 
-195690020, 
-2131745052, 
-883175546, 
-983294377, 
-744051578, 
-1474387147, 
-1651073835, 
-1253993362, 
-1505818122, 
-703437488, 
-132591051, 
-1410579573, 
-938530721, 
-1892172396, 
-1784513237, 
-1548560284, 
-951733267, 
-1104688855, 
-102599839, 
-1649437414, 
-1119572565, 
-1016785393, 
-445128702, 
-1733002855, 
-194131563, 
-167081973, 
-2118994324, 
-499183356, 
-113080822, 
-400923329, 
-163574271, 
-1720140273, 
-699496316, 
-156544930, 
-1409143124, 
-870819777, 
-825735365, 
-2140237856, 
-38627716, 
-215793990, 
-659798566, 
-1203334555, 
-642048399, 
-838130671, 
-1503484079, 
-309157770, 
-1906810477, 
-1521362419, 
-1938218375, 
-1293970620, 
-1431700163, 
-119755039, 
-346699522, 
-1592515011, 
-2055360606, 
-2134846137, 
-913930447, 
-549966365, 
-414827729, 
-778311108, 
-1607882595, 
-1837557821, 
-748288238, 
-115777434, 
-395380091, 
-149793285, 
-1481889632, 
-1570203282, 
-995463813, 
-1796846160, 
-1694390304, 
-1681883213, 
-747775640, 
-2034147632, 
-1655086504, 
-714184059, 
-1479758647, 
-1488994576, 
-599835376, 
-97911274, 
-1865866075, 
-2000860297, 
-1878560118, 
-1790671889, 
-190229545, 
-1854866934, 
-822496063, 
-1569849946, 
-1673611230, 
-616540355, 
-968522756, 
-125953300, 
-1439104417, 
-634610829, 
-121492898, 
-898519310, 
-257366926, 
-537704894, 
-1332261600, 
-589352660, 
-1797877151, 
-94049878, 
-1726085426, 
-480622930, 
-830441119, 
-1798989488, 
-2080795556, 
-1527657972, 
-62138987, 
-106301853, 
-1657754694, 
-89064554, 
-687499147, 
-2029438152, 
-859334219, 
-1303209044, 
-1684988270, 
-1755783420, 
-1982655617, 
-2131541361, 
-453585058, 
-2109284983, 
-262118705, 
-1390405952, 
-596700299, 
-67751306, 
-1813189181, 
-1797539269, 
-1474467910, 
-2084387233, 
-1379489544, 
-2089092692, 
-443096700, 
-1651943, 
-1910748201, 
-810457833, 
-1862787760, 
-1481699732, 
-1858029274, 
-1667894027, 
-1295905892, 
-1857265185, 
-1629814038, 
-155657882, 
-1307600904, 
-1049555192, 
-1947990739, 
-2100885564, 
-1804885199, 
-333899465, 
-259515918, 
-1745926682, 
-18672545, 
-618411202, 
-276242380, 
-1117483511, 
-1082321169, 
-1530013657, 
-2016612859, 
-1583838530, 
-1747491143, 
-178048326, 
-1882744649, 
-2118609887, 
-1353578862, 
-647163286, 
-237625048, 
-872371159, 
-1810992492, 
-1467398286, 
-1646270643, 
-2129397383, 
-1295139233, 
-751902457, 
-1964946217, 
-496477807, 
-65065093, 
-612468275, 
-468233375, 
-1637316503, 
-1727155017, 
-1582236054, 
-614641888, 
-48104193, 
-779274691, 
-975120443, 
-326294623, 
-424992039, 
-712306554, 
-706559407, 
-385164756, 
-63410093, 
-1101820172, 
-391983332, 
-769720049, 
-1489603393, 
-728142695, 
-1378647738, 
-132715712, 
-1100226784, 
-1952083324, 
-700435894, 
-1041786572, 
-1671645609, 
-590537874, 
-2000925147, 
-77042547, 
-1701544504, 
-1801484876, 
-776913658, 
-2146993629, 
-1426717377, 
-1556711265, 
-2051861506, 
-1945842436, 
-1267020924, 
-393220746, 
-278062469, 
-2099046875, 
-585882961, 
-326397222, 
-582826647, 
-96424950, 
-737980364, 
-553395507, 
-1406674760, 
-249060965, 
-1401782637, 
-2019758429, 
-604700056, 
-89734122, 
-1810683322, 
-1253372149, 
-1945545286, 
-1181230984, 
-280993024, 
-1306492053, 
-1604634875, 
-1386454242, 
}; 

DATA y[256] = {
-7650, 
-10941, 
-28478, 
-29642, 
-32281, 
-23325, 
-6006, 
-476, 
-32200, 
-5919, 
-12415, 
-14411, 
-24772, 
-5833, 
-24144, 
-8073, 
-11153, 
-25754, 
-13038, 
-12946, 
-11158, 
-26760, 
-11910, 
-27188, 
-15087, 
-12341, 
-10293, 
-10573, 
-4037, 
-32346, 
-22597, 
-7240, 
-22699, 
-2403, 
-10528, 
-30333, 
-30453, 
-32378, 
-25325, 
-15852, 
-17754, 
-9726, 
-13682, 
-16083, 
-30334, 
-26437, 
-20330, 
-23710, 
-7508, 
-22482, 
-11856, 
-441, 
-16290, 
-1714, 
-5636, 
-2702, 
-29063, 
-6157, 
-3007, 
-27644, 
-28767, 
-7777, 
-9117, 
-11416, 
-8061, 
-11038, 
-3818, 
-23850, 
-19025, 
-25789, 
-31602, 
-30109, 
-4897, 
-21621, 
-17494, 
-2826, 
-25278, 
-4521, 
-11252, 
-3566, 
-16773, 
-241, 
-20535, 
-15356, 
-26827, 
-16321, 
-18934, 
-11128, 
-10694, 
-1399, 
-26481, 
-29124, 
-14253, 
-1011, 
-31990, 
-4253, 
-31888, 
-15745, 
-26467, 
-9317, 
-24554, 
-2168, 
-28273, 
-15676, 
-3435, 
-1888, 
-21788, 
-18437, 
-17330, 
-27876, 
-28316, 
-15320, 
-8986, 
-19704, 
-21024, 
-23420, 
-4305, 
-12242, 
-24866, 
-719, 
-11781, 
-25237, 
-10443, 
-10951, 
-28354, 
-32031, 
-24177, 
-28951, 
-30497, 
-4820, 
-26859, 
-31706, 
-8719, 
-15188, 
-23724, 
-20695, 
-32346, 
-3631, 
-4391, 
-24437, 
-14108, 
-27550, 
-13292, 
-21919, 
-11187, 
-4469, 
-14169, 
-640, 
-6822, 
-27768, 
-5472, 
-26482, 
-11830, 
-10847, 
-7469, 
-20323, 
-18299, 
-16940, 
-12842, 
-27001, 
-32702, 
-6874, 
-15939, 
-25781, 
-29379, 
-27613, 
-19415, 
-19407, 
-31042, 
-1907, 
-27854, 
-20173, 
-22576, 
-27246, 
-3387, 
-22193, 
-8717, 
-19304, 
-19668, 
-16204, 
-27221, 
-15574, 
-11758, 
-32238, 
-5347, 
-6441, 
-9903, 
-17633, 
-30061, 
-5875, 
-26444, 
-18175, 
-32344, 
-22652, 
-4085, 
-5399, 
-21854, 
-3910, 
-17050, 
-14392, 
-12586, 
-11079, 
-12563, 
-10318, 
-16052, 
-9373, 
-15886, 
-12915, 
-1092, 
-5829, 
-22356, 
-13511, 
-28502, 
-24434, 
-6455, 
-10885, 
-32322, 
-14367, 
-17873, 
-3115, 
-23523, 
-30637, 
-17152, 
-534, 
-2545, 
-14379, 
-11393, 
-7449, 
-29289, 
-32733, 
-15016, 
-32544, 
-17979, 
-26357, 
-6975, 
-12499, 
-32260, 
-3577, 
-7809, 
-3047, 
-7912, 
-20293, 
-21919, 
-16251, 
-14269, 
-7629, 
-7214, 
-16906, 
-6482, 
-17334, 
-26124, 
-13776, 
-10929, 
-10592, 
-1884, 
-7532, 
}; 

// Floating point representation of numerator
// -2.625957e-001, 
// -1.337377e-001, 
// -9.051680e-003, 
// -4.960724e-001, 
// -3.709144e-001, 
// -2.073897e-001, 
// -5.513508e-001, 
// -4.756429e-001, 
// -8.285268e-001, 
// -8.693342e-001, 
// -7.812189e-001, 
// -8.945195e-001, 
// -8.585741e-001, 
// -5.430317e-001, 
// -2.118670e-001, 
// -7.189360e-001, 
// -7.752133e-001, 
// -9.112527e-002, 
// -9.926711e-001, 
// -4.112607e-001, 
// -4.578821e-001, 
// -3.464760e-001, 
// -6.865650e-001, 
// -7.688412e-001, 
// -5.839362e-001, 
// -7.012012e-001, 
// -3.275636e-001, 
// -6.174252e-002, 
// -6.568523e-001, 
// -4.370374e-001, 
// -8.811114e-001, 
// -8.309787e-001, 
// -7.211046e-001, 
// -4.431853e-001, 
// -5.144108e-001, 
// -4.777677e-002, 
// -7.680791e-001, 
// -5.213416e-001, 
// -4.734776e-001, 
// -2.072792e-001, 
// -8.069923e-001, 
// -9.039955e-002, 
// -7.780361e-002, 
// -9.867336e-001, 
// -2.324504e-001, 
// -5.265736e-002, 
// -1.866945e-001, 
// -7.617021e-002, 
// -8.010027e-001, 
// -3.257284e-001, 
// -7.289691e-002, 
// -6.561834e-001, 
// -4.055071e-001, 
// -3.845130e-001, 
// -9.966259e-001, 
// -1.798743e-002, 
// -1.004869e-001, 
// -3.072426e-001, 
// -5.603463e-001, 
// -2.989771e-001, 
// -3.902850e-001, 
// -7.001143e-001, 
// -1.439628e-001, 
// -8.879278e-001, 
// -7.084396e-001, 
// -9.025533e-001, 
// -6.025520e-001, 
// -6.666873e-001, 
// -5.576529e-002, 
// -1.614445e-001, 
// -7.415726e-001, 
// -9.571019e-001, 
// -9.941152e-001, 
// -4.255820e-001, 
// -2.560980e-001, 
// -1.931692e-001, 
// -3.624294e-001, 
// -7.487287e-001, 
// -8.556795e-001, 
// -3.484489e-001, 
// -5.391307e-002, 
// -1.841132e-001, 
// -6.975293e-002, 
// -6.900586e-001, 
// -7.311829e-001, 
// -4.635490e-001, 
// -8.367217e-001, 
// -7.890120e-001, 
// -7.831879e-001, 
// -3.482102e-001, 
// -9.472238e-001, 
// -7.707097e-001, 
// -3.325679e-001, 
// -6.890663e-001, 
// -6.933671e-001, 
// -2.793201e-001, 
// -4.559349e-002, 
// -8.688616e-001, 
// -9.317232e-001, 
// -8.747727e-001, 
// -8.338466e-001, 
// -8.858253e-002, 
// -8.637397e-001, 
// -3.830046e-001, 
// -7.310183e-001, 
// -7.793360e-001, 
// -2.870990e-001, 
// -4.510036e-001, 
// -5.865158e-002, 
// -6.701352e-001, 
// -2.955137e-001, 
// -5.657454e-002, 
// -4.184057e-001, 
// -1.198458e-001, 
// -2.503884e-001, 
// -6.203827e-001, 
// -2.744387e-001, 
// -8.372018e-001, 
// -4.379539e-002, 
// -8.037712e-001, 
// -2.238075e-001, 
// -3.867043e-001, 
// -8.377198e-001, 
// -9.689459e-001, 
// -7.113712e-001, 
// -2.893572e-002, 
// -4.950066e-002, 
// -7.719522e-001, 
// -4.147391e-002, 
// -3.201417e-001, 
// -9.450308e-001, 
// -4.001587e-001, 
// -6.068540e-001, 
// -7.846338e-001, 
// -8.176004e-001, 
// -9.232460e-001, 
// -9.925763e-001, 
// -2.112170e-001, 
// -9.822124e-001, 
// -1.220585e-001, 
// -6.474582e-001, 
// -2.778602e-001, 
// -3.154916e-002, 
// -8.443320e-001, 
// -8.370444e-001, 
// -6.866026e-001, 
// -9.706184e-001, 
// -6.423749e-001, 
// -9.728096e-001, 
// -2.063330e-001, 
// -7.692455e-004, 
// -8.897615e-001, 
// -3.773988e-001, 
// -8.674281e-001, 
// -6.899702e-001, 
// -8.652123e-001, 
// -7.766737e-001, 
// -6.034532e-001, 
// -8.648565e-001, 
// -7.589413e-001, 
// -7.248385e-002, 
// -6.088991e-001, 
// -4.887372e-001, 
// -9.071039e-001, 
// -9.783011e-001, 
// -8.404652e-001, 
// -1.554841e-001, 
// -1.208465e-001, 
// -8.130105e-001, 
// -8.695081e-003, 
// -2.879702e-001, 
// -1.286354e-001, 
// -5.203688e-001, 
// -5.039951e-001, 
// -7.124681e-001, 
// -9.390585e-001, 
// -7.375323e-001, 
// -8.137390e-001, 
// -8.291021e-002, 
// -8.767213e-001, 
// -9.865546e-001, 
// -6.303093e-001, 
// -3.013589e-001, 
// -1.106528e-001, 
// -4.062295e-001, 
// -8.433091e-001, 
// -6.833106e-001, 
// -7.666045e-001, 
// -9.915779e-001, 
// -6.030962e-001, 
// -3.501319e-001, 
// -9.149994e-001, 
// -2.311905e-001, 
// -3.029829e-002, 
// -2.852028e-001, 
// -2.180382e-001, 
// -7.624349e-001, 
// -8.042692e-001, 
// -7.367861e-001, 
// -2.862149e-001, 
// -2.240026e-002, 
// -3.628781e-001, 
// -4.540758e-001, 
// -1.519428e-001, 
// -1.979023e-001, 
// -3.316936e-001, 
// -3.290174e-001, 
// -1.793563e-001, 
// -2.952763e-002, 
// -5.130750e-001, 
// -1.825315e-001, 
// -3.584288e-001, 
// -6.936506e-001, 
// -3.390679e-001, 
// -6.419829e-001, 
// -6.180057e-002, 
// -5.123330e-001, 
// -9.090096e-001, 
// -3.261659e-001, 
// -4.851197e-001, 
// -7.784206e-001, 
// -2.749906e-001, 
// -9.317534e-001, 
// -3.587573e-002, 
// -7.923434e-001, 
// -8.388818e-001, 
// -3.617786e-001, 
// -9.997718e-001, 
// -6.643671e-001, 
// -7.249002e-001, 
// -9.554725e-001, 
// -9.061035e-001, 
// -5.900026e-001, 
// -1.831077e-001, 
// -1.294829e-001, 
// -9.774449e-001, 
// -2.728230e-001, 
// -1.519906e-001, 
// -2.713998e-001, 
// -4.490137e-002, 
// -3.436489e-001, 
// -2.576949e-001, 
// -6.550340e-001, 
// -1.159780e-001, 
// -6.527559e-001, 
// -9.405233e-001, 
// -2.815854e-001, 
// -4.178571e-002, 
// -8.431651e-001, 
// -5.836469e-001, 
// -9.059651e-001, 
// -5.500535e-001, 
// -1.308476e-001, 
// -6.083828e-001, 
// -7.472163e-001, 
// -6.456181e-001, 


// Floating point representation of denominator
// -2.334485e-001 
// -3.338763e-001 
// -8.690552e-001 
// -9.045870e-001 
// -9.851357e-001 
// -7.118066e-001 
// -1.832688e-001 
// -1.451649e-002 
// -9.826373e-001 
// -1.806071e-001 
// -3.788613e-001 
// -4.397780e-001 
// -7.559685e-001 
// -1.779924e-001 
// -7.367881e-001 
// -2.463655e-001 
// -3.403552e-001 
// -7.859371e-001 
// -3.978831e-001 
// -3.950629e-001 
// -3.404984e-001 
// -8.166364e-001 
// -3.634531e-001 
// -8.296909e-001 
// -4.603989e-001 
// -3.766058e-001 
// -3.141100e-001 
// -3.226540e-001 
// -1.231700e-001 
// -9.871095e-001 
// -6.895978e-001 
// -2.209208e-001 
// -6.927039e-001 
// -7.332169e-002 
// -3.212801e-001 
// -9.256785e-001 
// -9.293308e-001 
// -9.880695e-001 
// -7.728463e-001 
// -4.837480e-001 
// -5.417958e-001 
// -2.967967e-001 
// -4.175161e-001 
// -4.907940e-001 
// -9.257104e-001 
// -8.067637e-001 
// -6.203959e-001 
// -7.235653e-001 
// -2.291182e-001 
// -6.860700e-001 
// -3.618068e-001 
// -1.343314e-002 
// -4.971242e-001 
// -5.229662e-002 
// -1.719742e-001 
// -8.244280e-002 
// -8.869202e-001 
// -1.878741e-001 
// -9.173744e-002 
// -8.436239e-001 
// -8.778812e-001 
// -2.373335e-001 
// -2.781997e-001 
// -3.483602e-001 
// -2.459773e-001 
// -3.368380e-001 
// -1.165065e-001 
// -7.278426e-001 
// -5.805673e-001 
// -7.870063e-001 
// -9.644000e-001 
// -9.188363e-001 
// -1.494332e-001 
// -6.597965e-001 
// -5.338450e-001 
// -8.623676e-002 
// -7.714233e-001 
// -1.379551e-001 
// -3.433815e-001 
// -1.088172e-001 
// -5.118565e-001 
// -7.354353e-003 
// -6.266741e-001 
// -4.686217e-001 
// -8.186837e-001 
// -4.980557e-001 
// -5.778052e-001 
// -3.395726e-001 
// -3.263470e-001 
// -4.266982e-002 
// -8.081342e-001 
// -8.887836e-001 
// -4.349461e-001 
// -3.083373e-002 
// -9.762561e-001 
// -1.297842e-001 
// -9.731234e-001 
// -4.804713e-001 
// -8.077086e-001 
// -2.843110e-001 
// -7.493272e-001 
// -6.613518e-002 
// -8.628107e-001 
// -4.783777e-001 
// -1.047983e-001 
// -5.761275e-002 
// -6.649166e-001 
// -5.626362e-001 
// -5.288441e-001 
// -8.506897e-001 
// -8.641356e-001 
// -4.675018e-001 
// -2.742107e-001 
// -6.012969e-001 
// -6.415815e-001 
// -7.147206e-001 
// -1.313648e-001 
// -3.735873e-001 
// -7.588277e-001 
// -2.191835e-002 
// -3.594992e-001 
// -7.701513e-001 
// -3.186648e-001 
// -3.341766e-001 
// -8.652820e-001 
// -9.775067e-001 
// -7.378005e-001 
// -8.834848e-001 
// -9.306818e-001 
// -1.470695e-001 
// -8.196693e-001 
// -9.675814e-001 
// -2.660737e-001 
// -4.634832e-001 
// -7.239703e-001 
// -6.315418e-001 
// -9.871137e-001 
// -1.107939e-001 
// -1.339794e-001 
// -7.457531e-001 
// -4.305194e-001 
// -8.407352e-001 
// -4.056356e-001 
// -6.688999e-001 
// -3.413873e-001 
// -1.363658e-001 
// -4.323767e-001 
// -1.951873e-002 
// -2.081684e-001 
// -8.474064e-001 
// -1.669728e-001 
// -8.081367e-001 
// -3.610134e-001 
// -3.309999e-001 
// -2.279122e-001 
// -6.201822e-001 
// -5.584145e-001 
// -5.169400e-001 
// -3.918943e-001 
// -8.240044e-001 
// -9.979744e-001 
// -2.097760e-001 
// -4.863915e-001 
// -7.867706e-001 
// -8.965502e-001 
// -8.426633e-001 
// -5.924850e-001 
// -5.922430e-001 
// -9.473073e-001 
// -5.818485e-002 
// -8.500283e-001 
// -6.156259e-001 
// -6.889414e-001 
// -8.314655e-001 
// -1.033519e-001 
// -6.772756e-001 
// -2.660037e-001 
// -5.890958e-001 
// -6.002061e-001 
// -4.944778e-001 
// -8.306941e-001 
// -4.752545e-001 
// -3.587973e-001 
// -9.838025e-001 
// -1.631484e-001 
// -1.965378e-001 
// -3.022152e-001 
// -5.381122e-001 
// -9.173874e-001 
// -1.792830e-001 
// -8.069800e-001 
// -5.546453e-001 
// -9.870422e-001 
// -6.912582e-001 
// -1.246490e-001 
// -1.647406e-001 
// -6.669049e-001 
// -1.192947e-001 
// -5.203132e-001 
// -4.391833e-001 
// -3.840913e-001 
// -3.381010e-001 
// -3.833668e-001 
// -3.148600e-001 
// -4.898470e-001 
// -2.860392e-001 
// -4.847921e-001 
// -3.941342e-001 
// -3.329737e-002 
// -1.778826e-001 
// -6.822493e-001 
// -4.123032e-001 
// -8.697983e-001 
// -7.456457e-001 
// -1.969691e-001 
// -3.321541e-001 
// -9.863736e-001 
// -4.384206e-001 
// -5.454391e-001 
// -9.505078e-002 
// -7.178411e-001 
// -9.349656e-001 
// -5.234081e-001 
// -1.628808e-002 
// -7.765042e-002 
// -4.388037e-001 
// -3.476753e-001 
// -2.273204e-001 
// -8.938242e-001 
// -9.989266e-001 
// -4.582362e-001 
// -9.931422e-001 
// -5.486623e-001 
// -8.043379e-001 
// -2.128569e-001 
// -3.814374e-001 
// -9.844790e-001 
// -1.091460e-001 
// -2.382968e-001 
// -9.296496e-002 
// -2.414314e-001 
// -6.192701e-001 
// -6.688892e-001 
// -4.959216e-001 
// -4.354314e-001 
// -2.328026e-001 
// -2.201322e-001 
// -5.159021e-001 
// -1.977868e-001 
// -5.289878e-001 
// -7.972411e-001 
// -4.203851e-001 
// -3.334997e-001 
// -3.232347e-001 
// -5.748876e-002 
// -2.298515e-001 


float rtest[256] = {
1.124802e+000, 
4.005409e-001, 
1.041525e-002, 
5.483874e-001, 
3.765102e-001, 
2.913503e-001, 
3.008102e+000, 
3.274342e+001, 
8.431418e-001, 
4.812695e+000, 
2.061940e+000, 
2.033975e+000, 
1.135708e+000, 
3.050585e+000, 
2.875437e-001, 
2.918134e+000, 
2.277610e+000, 
1.159429e-001, 
2.494850e+000, 
1.040954e+000, 
1.344675e+000, 
4.242648e-001, 
1.888947e+000, 
9.266363e-001, 
1.268272e+000, 
1.861839e+000, 
1.042806e+000, 
1.913533e-001, 
5.331617e+000, 
4.427392e-001, 
1.277703e+000, 
3.760982e+000, 
1.040978e+000, 
6.043403e+000, 
1.601084e+000, 
5.161208e-002, 
8.264676e-001, 
5.276213e-001, 
6.126323e-001, 
4.284712e-001, 
1.489440e+000, 
3.045664e-001, 
1.863374e-001, 
2.010402e+000, 
2.511022e-001, 
6.526748e-002, 
3.009151e-001, 
1.052697e-001, 
3.495905e+000, 
4.747561e-001, 
2.014749e-001, 
4.875696e+001, 
8.156940e-001, 
7.351063e+000, 
5.794435e+000, 
2.181392e-001, 
1.132971e-001, 
1.635168e+000, 
6.106228e+000, 
3.543945e-001, 
4.445670e-001, 
2.949897e+000, 
5.174260e-001, 
2.548670e+000, 
2.879810e+000, 
2.679368e+000, 
5.171405e+000, 
9.159753e-001, 
9.604819e-002, 
2.051345e-001, 
7.689339e-001, 
1.041626e+000, 
6.652066e+000, 
6.449966e-001, 
4.796971e-001, 
2.239833e+000, 
4.698190e-001, 
5.426751e+000, 
2.491904e+000, 
3.201899e+000, 
1.053254e-001, 
2.503328e+001, 
1.113058e-001, 
1.472509e+000, 
8.931077e-001, 
9.306766e-001, 
1.448067e+000, 
2.323359e+000, 
2.399804e+000, 
8.155933e+000, 
1.172109e+000, 
8.671410e-001, 
7.645818e-001, 
2.233365e+001, 
7.102299e-001, 
2.152072e+000, 
4.685171e-002, 
1.808247e+000, 
1.153539e+000, 
3.076586e+000, 
1.112792e+000, 
1.338871e+000, 
1.001062e+000, 
8.006056e-001, 
6.973511e+000, 
1.352610e+001, 
4.317817e-001, 
8.015667e-001, 
1.108999e-001, 
7.877382e-001, 
3.419760e-001, 
1.210075e-001, 
1.525742e+000, 
1.993051e-001, 
3.902552e-001, 
8.680059e-001, 
2.088922e+000, 
2.240927e+000, 
5.771283e-002, 
3.663140e+001, 
6.225044e-001, 
5.021011e-001, 
2.628593e+000, 
2.899317e+000, 
8.221137e-001, 
2.960150e-002, 
6.709011e-002, 
8.737290e-001, 
4.456233e-002, 
2.176432e+000, 
1.152938e+000, 
4.135621e-001, 
2.280696e+000, 
1.692842e+000, 
1.129284e+000, 
1.461847e+000, 
1.005526e+000, 
1.906130e+000, 
7.329796e+000, 
1.636704e-001, 
1.503821e+000, 
3.304873e-001, 
7.777632e-002, 
1.262241e+000, 
2.451799e+000, 
5.034369e+000, 
2.244705e+000, 
3.288959e+001, 
4.672680e+000, 
2.434860e-001, 
4.606478e-003, 
1.100963e+000, 
1.045360e+000, 
2.620437e+000, 
3.027038e+000, 
1.395034e+000, 
1.390789e+000, 
1.167294e+000, 
2.206792e+000, 
9.210395e-001, 
7.263014e-002, 
2.902590e+000, 
1.004764e+000, 
1.152941e+000, 
1.091153e+000, 
9.973694e-001, 
2.624209e-001, 
2.040449e-001, 
8.582155e-001, 
1.494077e-001, 
3.387738e-001, 
2.089488e-001, 
7.552908e-001, 
6.061407e-001, 
6.892871e+000, 
1.386521e+000, 
2.772451e+000, 
1.381299e+000, 
1.381331e-001, 
1.772920e+000, 
1.187591e+000, 
1.326183e+000, 
8.398476e-001, 
1.124719e-001, 
2.489495e+000, 
4.290258e+000, 
2.261004e+000, 
1.424607e+000, 
1.080870e+000, 
3.363788e+000, 
4.338648e-001, 
1.649667e+000, 
2.342212e-001, 
4.382900e-002, 
2.287766e+000, 
1.323333e+000, 
1.143199e+000, 
6.740229e+000, 
1.416012e+000, 
6.516600e-001, 
5.831970e-002, 
1.073273e+000, 
1.184363e+000, 
4.825413e-001, 
4.039910e-001, 
1.159600e+000, 
6.786630e-001, 
4.550637e-001, 
8.860451e-001, 
2.884275e+000, 
2.675430e-001, 
8.692914e-001, 
7.974719e-001, 
4.547178e-001, 
3.258946e+000, 
1.860433e-001, 
5.194025e-001, 
2.073253e+000, 
5.979860e-001, 
5.103179e+000, 
1.084355e+000, 
2.941180e-001, 
1.780066e+000, 
2.201453e+000, 
1.020177e+001, 
1.911710e+000, 
1.040530e+000, 
4.397976e+000, 
7.432818e-001, 
7.256753e-001, 
2.085037e+000, 
9.123402e-001, 
1.075321e+000, 
2.276463e-001, 
6.083006e-001, 
2.562518e+000, 
2.771192e-001, 
1.392347e+000, 
1.138843e+000, 
4.828776e-001, 
1.423241e+000, 
4.161112e-001, 
9.792488e-001, 
2.338545e-001, 
1.499019e+000, 
4.039726e+000, 
1.279039e+000, 
8.099101e-002, 
4.262394e+000, 
1.103320e+000, 
1.136375e+000, 
1.308374e+000, 
3.923152e-001, 
1.882127e+000, 
1.299617e+001, 
2.808764e+000, 
}; 

DATA r[256];
DATA rexp[256];