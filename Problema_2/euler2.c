#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//caja anclada a un resorte (amortiguado)
// y'' + k_a y' + k_r y = 0
// A sistema de EDOs de 1er orden:
// y_0' = y'
// y_1' = y''
// entonces:
// y_0' = y_1
// y_1' = - k_a*y_1 - k_r*y_0
#define K_A 230
#define K_R 225


void funcion(double *, double *, double *);

void funcion(double *t, double *Y_a, double *F){
    F[0] = Y_a[1];
    F[1] = -K_A*Y_a[1] - K_R*Y_a[0];
}

double y_real(double i) {
 return (-0.09/(4.0*(260.0+23.0*sqrt(130.0))))*exp(-5.0*(23.0 + 2.0*sqrt(130.0))*i) + (0.01-(-0.09/(4.0*(260.0+23.0*sqrt(130.0)))))*exp(5.0*(2.0*sqrt(130.0)-23.0)*i);
}

int main(int argc, char* argv[]){
   double h = 0.005;
   double t0 = 0.0;
   double tf = 0.5;
   double n_f = (tf-t0)/h;
   int nf=(int)n_f;
   double Y_a[2] = {0.01,0.0};
   double Y_s[2] = {0.01,0.0};
   double F[2] = {0.01,0};
   double error=0.0;

   for (int n=0; n<=nf; n++){
      error=fabs(y_real(h*n)-Y_a[0]);
      printf("%.6f %.12f %.12f %.12f\n", h*n, Y_a[0], Y_a[1], error); // y[0] posicion, y[1] vel
      funcion(0, Y_a, F);
      for (int i=0; i<2; i++){
        Y_s[i] = Y_a[i] + h*F[i];
        Y_a[i] = Y_s[i];
      }
    }
}

