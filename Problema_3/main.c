#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <math.h>

//problema de valores de frontera. shooting no lineal.

int funcion (double x, const double y[], double f[], void *params){
  // ecuacion no lineal de difusion
  (void)(x); /*avoid unused paramater warning */
  double *p = (double*)params; // cambio de puntero void a puntero double
  double a = p[0]; // area seccion transversal
  double k = p[1]; // conductividad termica
  double per = p[2]; // perimetro lamina
  double hc = p[3]; // coeficiente de conveccion
  double Tamb = p[4]; // temperatura ambiente
  double cSB = p[5]; // cte de stefan-boltzmann

  f[0] = y[1]; // y[0]=T y[1]=T'. f[0]=T' f[1]=T''
  f[1] = (per*hc/(a*k))*(y[0]-Tamb) + (per*cSB/(a*k))*((y[0])*(y[0])*(y[0])*(y[0]) - Tamb*Tamb*Tamb*Tamb);
  return GSL_SUCCESS;
}

int solucion_pvi(int nf, double *x, double h,
                 gsl_odeiv2_driver *d, double *Y){
  double xi = 0;
  int status = 0;
  for (int n=1; n<=nf ; ++n) {
      xi = *x + h;
      status = gsl_odeiv2_driver_apply (d, x, xi, Y);
      if (status != GSL_SUCCESS){
        printf ("error, return value=%d\n", status);
        break;
      }
      printf("%.3f %.3f %.3f\n", *x, Y[0], Y[1]);
    }
  return 0;
}

int main() {

  double h = 0.001;
  double x0 = 0.0;
  double xf = 0.1; // longitud H
  int nf = (xf- x0)/h;
  double params[6] = {0.0002, 120.0, 0.106, 15.0, 293.15, 5.67037321e-8};

  gsl_odeiv2_system sys = {funcion, NULL, 2, params};

  gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                  1e-6, 1e-6, 0.0);
  
  double cond_final = 273.15;

  double tol = 1e-9;
  double error = tol + 1;
  double  y1_0 = 0.0; //posicion inicial
  double  y1_1 = 0.1; //"posicion final"???
  double  y1_2 = 0.0;

  // Primera ejecucion
  double x = 0;
  double Y[2] = {773.15, 0.0};
  y1_0 = Y[1];
  solucion_pvi(nf, &x, h, d, Y);
  //printf("Condicion final %f %f %f\n", x, Y[0], Y[1]);
  double error_0 = fabs(Y[1] - cond_final);

  // Segunda ejecucion

  int nmax = 10;
  int n = 0;
  while (error > tol && n<nmax){
    x = 0;
    Y[0] = 773.15;
    Y[1] = y1_1;
    printf("%.3f %.3f %.3f\n", x, Y[0], Y[1]);
    solucion_pvi(nf, &x, h, d, Y);
    error = fabs(Y[1] - cond_final);

    printf("\n");
    //printf("%f\n\n",error);

    y1_2 = y1_1 - (y1_1 - y1_0)/(error - error_0) * error; //metodo secante
    y1_0 = y1_1;
    y1_1 = y1_2;
    error_0 = error;

    ++n;
  }

  x = 0;
  Y[0] = 773.15;
  Y[1] = y1_1;
  
  gsl_odeiv2_driver_free (d);

  return 0;
}
