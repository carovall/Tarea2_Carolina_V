#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

int func(double t, const double y[], double f[], void *params){
  (void)(t); /*avoid unused paramater warning */
  double *p = (double*)params; // cambio de puntero void a puntero double
  double c = p[0];
  double m = p[1];
  double k = p[2];
  f[0] = y[1]; //v =u'
  f[1] = -(c/m)*y[1] - (k/m)*y[0]; //v'=f(u,u')
  return GSL_SUCCESS;
}

//funcion para sol analitica
double y_real(double t){
  double y_r = (-0.09/(4.0*(260.0+23.0*sqrt(130.0))))*exp(-5.0*(23.0 + 2.0*sqrt(130.0))*t) + (0.01-(-0.09/(4.0*(260.0+23.0*sqrt(130.0)))))*exp(5.0*(2.0*sqrt(130.0)-23.0)*t);
  return y_r;
}

int main (int argc, char *argv[]){

  double params[3]= {460.0, 2.0, 450.0};

  gsl_odeiv2_system sys = {func, NULL, 2, params}; //sist 2 ecuaciones

  double h = 0.008;
  int i;
  gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45,
                                  h, 1e-6, 0.0);
                                   //paso h //error abs e-6 // error relativo 0

  double t = 0.0, t1 = 0.5; // tiempo
  double y[2] = { 0.01, 0.0 }; //condiciones iniciales u=0.01, v=0

  for (i = 1; i <= 100; i++)
    {
      double ti = i * t1 / 100.0;
      double yExacta = y_real(i*0.5/100.0);

      int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

      double error = fabs(yExacta - y[0]);

      if (status != GSL_SUCCESS)
        {
          printf ("error, return value=%d\n", status);
          break;
        }

      printf ("%.6f %.12f %.12f %.12f\n", t, y[0], y[1], error);
    }

  gsl_odeiv2_driver_free (d);
  return 0;
}
