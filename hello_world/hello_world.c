#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <tms320.h>
#include <Dsplib.h>
#include <inttypes.h>

#include "sin_composition_input_signal.h"
#include "random_input_signal.h"
#include "filter_butterworth_IIR_low-pass.h"

DATA multiplyQ15(DATA a, DATA b) {
    LDATA temp;
    DATA output;
    temp = (LDATA) a * b;
    temp = temp + (1 << 14);
    temp = temp >> 15;
    if (temp > INT16_MAX)
        output = INT16_MAX;
    else if (temp < INT16_MIN)
        output = INT16_MIN;
    else
        output = (DATA) temp;
    return output;
}

DATA sumQ15(DATA a, DATA b) {
    LDATA temp;
    DATA output;
    temp = (LDATA) a + b;
    if (temp > INT16_MAX)
        output = INT16_MAX;
    else if (temp < INT16_MIN)
        output = INT16_MIN;
    else
        output = (DATA) temp;
    return output;
}

void iirCascata(DATA signal[128])
{
    DATA dbuffer[13] = {0};
    DATA *dp = dbuffer;
    DATA r[128] = {0};
    iircas51(signal, hcas, r, dp, 3, 128);
    int i;

    // Compensando ganho do numerador -> multiplicação por 4
    for(i = 0; i < 128; i++) {
        r[i] = sumQ15(sumQ15(r[i], r[i]), sumQ15(r[i], r[i]));
    }
    return;
}

DATA get_at(int n, DATA arr[128]) {
    if(n < 0)
        return 0;
    else
        return arr[n];
}

void iirFormaDireta1(DATA signal[128])
{
    DATA r[128] = {0};
    int i;
    for (i = 0; i < 128; i++)
    {
        r[i] = multiplyQ15(b[0], get_at(i, signal));
        r[i] = sumQ15(r[i], multiplyQ15(b[1], get_at(i-1, signal)));
        r[i] = sumQ15(r[i], multiplyQ15(b[2], get_at(i-2, signal)));
        r[i] = sumQ15(r[i], multiplyQ15(b[3], get_at(i-3, signal)));
        r[i] = sumQ15(r[i], multiplyQ15(b[4], get_at(i-4, signal)));
        r[i] = sumQ15(r[i], multiplyQ15(b[5], get_at(i-5, signal)));
        r[i] = sumQ15(r[i], multiplyQ15(b[6], get_at(i-6, signal)));

        r[i] = sumQ15(r[i], multiplyQ15(-a[1], get_at(i-1, r)));
        r[i] = sumQ15(r[i], multiplyQ15(-a[2], get_at(i-2, r)));
        r[i] = sumQ15(r[i], multiplyQ15(-a[3], get_at(i-3, r)));
        r[i] = sumQ15(r[i], multiplyQ15(-a[4], get_at(i-4, r)));
        r[i] = sumQ15(r[i], multiplyQ15(-a[5], get_at(i-5, r)));
        r[i] = sumQ15(r[i], multiplyQ15(-a[6], get_at(i-6, r)));
    }
    return;
}

void iirFormaDireta2(DATA signal[128]) {
    DATA v[128] = {0};
    DATA y[128] = {0};
    int i = 0;
    for(i = 0; i < 128; i++) {
        v[i] = get_at(i, signal);
        v[i] = sumQ15(v[i], multiplyQ15(-a[1], get_at(i - 1, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[2], get_at(i - 2, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[3], get_at(i - 3, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[4], get_at(i - 4, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[5], get_at(i - 5, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[6], get_at(i - 6, v)));

        y[i] = multiplyQ15(b[0], get_at(i, v));
        y[i] = sumQ15(y[i], multiplyQ15(b[1], get_at(i - 1, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[2], get_at(i - 2, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[3], get_at(i - 3, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[4], get_at(i - 4, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[5], get_at(i - 5, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[6], get_at(i - 6, v)));
    }
    return;
}

void iirFormaTransposta2(DATA signal[128]) {
    DATA v[128] = {0};
    DATA y[128] = {0};
    int i = 0;
    for(i = 0; i < 128; i++) {

        if (i > 4) {
            v[i - 5] = sumQ15(multiplyQ15(b[6], get_at(i - 6, signal)), multiplyQ15(a[6], get_at(i - 6, y)));
        }
        if (i > 3) {
            v[i - 4] = sumQ15(sumQ15(multiplyQ15(b[5], get_at(i - 5, signal)), multiplyQ15(-a[5], get_at(i - 5, y))), get_at(i - 5, v));
        }
        if (i > 2) {
            v[i - 3] = sumQ15(sumQ15(multiplyQ15(b[4], get_at(i - 4, signal)), multiplyQ15(-a[4], get_at(i - 4, y))), get_at(i - 4, v));
        }
        if (i > 1) {
            v[i - 2] = sumQ15(sumQ15(multiplyQ15(b[3], get_at(i - 3, signal)), multiplyQ15(-a[3], get_at(i - 3, y))), get_at(i - 3, v));
        }
        if (i > 0) {
            v[i - 1] = sumQ15(sumQ15(multiplyQ15(b[2], get_at(i - 2, signal)), multiplyQ15(-a[2], get_at(i - 2, y))), get_at(i - 2, v));
        }
        v[i] = sumQ15(sumQ15(multiplyQ15(b[1], get_at(i - 1, signal)), multiplyQ15(-a[1], get_at(i - 1, y))), get_at(i - 1, v));

        y[i] = sumQ15(multiplyQ15(b[0], get_at(i, signal)), get_at(i, v));

    }
    return;
}

void main()
{
    iirFormaDireta1(x_sin);
    iirFormaDireta2(x_sin);
    iirFormaDireta1(x_random);
    iirFormaDireta2(x_random);
    iirCascata(x_sin);
    iirCascata(x_random);
    iirFormaTransposta2(x_sin);
    //iirFormaTransposta2();
    return;
}




