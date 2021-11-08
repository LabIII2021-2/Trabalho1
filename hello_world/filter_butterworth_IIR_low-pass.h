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


#endif
