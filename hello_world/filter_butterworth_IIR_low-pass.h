#ifndef FILTER_BUTTERWORTH_IIR_LOW_PASS_H_
#define FILTER_BUTTERWORTH_IIR_LOW_PASS_H_

// Coeficientes do numerador
DATA b[7] = {
    969,
    5817,
    14543,
    19390,
    14543,
    5817,
    969
};

// Coeficientes do denominador
DATA a[7] = {
    32767,
    0,
    25483,
    0,
    3742,
    0,
    57
};

// Filtro cascata
DATA hcas[15] = {
    969, //b0
    1939, //b1
    969, //b2
    0, //a1
    567, //a2
    16384 , //b0
    32767 , //b1
    16384 , //b2
    0, //a1
    5622, //a2
    16384 , //b0
    32767 , //b1
    16384 , //b2
    0, //a1
    19293, //a2
};


// Filtro paralelo 1
DATA hpar1[15] = {
    -14765, //b0
    1943, //b1
    0, //b2
    0, //a1
    567, //a2
};

// Filtro paralelo 2
DATA hpar2[15] = {
    -3120, //b0
    -1292, //b1
    0, //b2
    0, //a1
    5622, //a2
};

// Filtro paralelo 3
DATA hpar3[15] = {
    612, //b0
    -469, //b1
    0, //b2
    0, //a1
    19293, //a2
};


#endif
