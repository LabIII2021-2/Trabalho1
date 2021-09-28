// LOW PASS IIR FILTER

#include "stdio.h"
#include <math.h>

int i,w,wc,c,N; float H[100];

float mul(float, int);

void main()

{

N = 6;

wc = 16000;

for(w=0;w<100;w++) {

H[w]=1/sqrt(1+mul((w/(float)wc),2*N));

printf("H[%d]=%f\n",w,H[w]);

}

}

float mul(float a,int x)

{

for(i=0;i<x-1;i++) a*=a; return(a);

}
