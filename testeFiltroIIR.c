#include "stdio.h"
#include <math.h>
#include <stdlib.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define PI 3.14159265358979323846

/*
float* conv(float* x, float* h, int x_size, int h_size){
  int y_size, x_start, x_end, h_start;
  y_size = x_size + h_size - 1;

  float *y = (float*) calloc(y_size, sizeof(float));

  for (int i = 0; i < y_size; i++){
    x_start = MAX(0, i-h_size+1);
    x_end   = MIN(i+1, x_size);
    h_start = MIN(i, h_size-1);
    for (int j = x_start; j < x_end; j++) {
      y[i] += h[h_start--]*x[j];
    }
    printf("%f ", y[i]);
  }

  return y;
}
*/

//função y(n) = b0x(n) + b1x(n–1) + b2x(n–2) – a1y(n–1) – a2y(n–2)
//recebe o n atual, o vetor do sinal de entrada x, um vetor de saída y, b0, b1, b2, a1, a2
//retorna o valor do sinal de saida no ponto n
float iir_df1(int n, float x[], float y[], float b0, float b1, float b2, float a1, float a2) {
  float yn_menos1, yn_menos2;
  printf("n: %d\n", n);
  if (n > 1) {
    //if (y[n-1] == 0)
      yn_menos1 = iir_df1(n-1, x, y, b0, b1, b2, a1, a2);
    //else
      //yn_menos1 = y[n-1];
    //if (y[n-2] == 0)
      yn_menos2 = iir_df1(n-2, x, y, b0, b1, b2, a1, a2);
    //else
      //yn_menos2 = y[n-2];
    y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] - a1*yn_menos1 - a2*yn_menos2;
  }
  else if (n == 1){
    yn_menos1 = iir_df1(n-1, x, y, b0, b1, b2, a1, a2);
    y[n] = b0*x[n] + b1*x[n-1] - a1*yn_menos1;
  }
  else //n = 0 
    y[n] = b0*x[n];
  return y[n];
}

int main(){
  float x[12];
  float y[12];
  
  printf("x[n]: ");
  for (int i = 0; i <= 12; i++) {
    x[i] = sin(i*PI/6);
    printf("%f ", x[i]);
  }
  printf("\n");

  //filtro exemplo: b0 = 1, b1 = 2, b2 = 1, a1 = 0.75, a2 = 0.125
  iir_df1(12, x, y, 1, 2, 1, 0.75, 0.124);

  printf("y[n]: ");
  for (int i = 0; i <= 12; i++) {
    printf("%f ", y[i]);
  }
  printf("\n");
}