#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <tms320.h>
#include <Dsplib.h>
#include <inttypes.h>

//#include "t1.h"
//#include "t2.h"
//#include "t4.h"
//#include "t6.h"
//#include "t7.h"
//#include "t8.h"
//#include "test.h"
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

void cas51() {
#define NX 16
#define NBIQ 2
    DATA h[5*NBIQ] ={ /* C54x: b0 b1 b2 a1 a2 ... */
    -17385, //b0
    12314, //b1
    -14200, //b2
    17123, //a1
    -3529, //a2
    -5786, //b0
    -19274, //b1
    -11688, //b2
    16393, //a1
    15478, //a2
    };

    DATA x[NX] ={
    1841,
    -1101,
    437,
    -58,
    1601,
    1072,
    -179,
    -1971,
    1315,
    -227,
    472,
    1194,
    1726,
    974,
    -1325,
    -386,
    };

    short i;
    DATA dbuffer[4*NBIQ+1];
    DATA *dp = dbuffer;

    DATA r[NX];
        // clear
        for (i = 0; i < NX; i++) r[i] = 0;               // clear output buffer (optional)
        for (i = 0; i < 4*NBIQ+1; i++) dbuffer[i] = 0;   // clear delay buffer (a must)

        // compute
        iircas51(x, h, r, dp, NBIQ, NX);
        printf("cas51!");
}



DATA x_sin_at(int n, DATA x_input[128]) {
    if(n < 0)
        return 0;
    else
        return x_input[n];
}

DATA v_at(int n, DATA v_input[128]) {
    if(n < 0)
        return 0;
    else
        return v_input[n];
}



void filterIIRType2() {
    DATA v[128] = {0};
    DATA y[128] = {0};
    int i = 0;
    for(i = 0; i < 128; i++) {
        v[i] = x_sin_at(i, x_sin);

        v[i] = sumQ15(v[i], multiplyQ15(-a[1], v_at(i - 1, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[2], v_at(i - 2, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[3], v_at(i - 3, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[4], v_at(i - 4, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[5], v_at(i - 5, v)));
        v[i] = sumQ15(v[i], multiplyQ15(-a[6], v_at(i - 6, v)));

        y[i] = v_at(i, v);
        y[i] = sumQ15(y[i], multiplyQ15(b[1], v_at(i - 1, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[2], v_at(i - 2, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[3], v_at(i - 3, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[4], v_at(i - 4, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[5], v_at(i - 5, v)));
        y[i] = sumQ15(y[i], multiplyQ15(b[6], v_at(i - 6, v)));
    }
    return;
}

void main()
{
    //cas4();
    //cas51();
    //cas52();
    //testeFloat();
    filterIIRType2();

    return;
}




