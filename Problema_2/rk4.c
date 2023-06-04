#include <stdio.h>
#include <math.h>

//funcion oscilador amortiguado
double f(double t, double y, double dy)
{
    double aceleracion = -230 * dy - 225 * y;
    return aceleracion;
}

//funcion para sol analitica
double y_real(double t){
  double y_r = (-0.09/(4.0*(260.0+23.0*sqrt(130.0))))*exp(-5.0*(23.0 + 2.0*sqrt(130.0))*t) + (0.01-(-0.09/(4.0*(260.0+23.0*sqrt(130.0)))))*exp(5.0*(2.0*sqrt(130.0)-23.0)*t);
  return y_r;
}

// funcion para metodo RK4
void resolver_rk4(double t0, double y0, double dy0, double h, double tf, double (*y_real)(double))
{
    double t = t0;
    double y = y0;
    double dy = dy0;

    while (t <= tf) {
        double yExacta = y_real(t);
        double error = fabs(yExacta - y);
        printf("%.6f %.12f %.12f %.12f\n", t, y, dy, error);

        double k1 = h * f(t, y, dy);
        double k2 = h * f(t + h / 2, y + dy / 2, dy + k1 / 2);
        double k3 = h * f(t + h / 2, y + dy / 2, dy + k2 / 2);
        double k4 = h * f(t + h, y + dy, dy + k3);

        y = y + (dy + (k1 + 2 * k2 + 2 * k3 + k4) / 6) * h;
        dy = dy + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

        t = t + h;
    }
}

int main()
{
    double t0 = 0.0;
    double y0 = 0.01;
    double dy0 = 0.0;
    double h = 0.008;
    double tf = 0.5;

    resolver_rk4(t0, y0, dy0, h, tf, y_real);

    return 0;
}
