#include <stdio.h>
#include <math.h>

// a = d²x/dt² = f(x)
// d²x/dt² = d(v²/2)/dx
// d(v²/2)/dx = y'= f(x)     donde y=mitad del cuadrado de la velocidad
// y = y0 + integral(f(x)dx) evaluada desde x0 a x

// f(x): aceleracion, en funcion de posicion x
double func(double x) {
    return -0.3*(9.8) + -80*(0.3*0.4 + x)*(1 - 0.4/sqrt(0.16 + x*x))/0.8;
}

double trapecio(double x0, double xn, int n) {
    double h = (xn - x0) / n;  // paso
    double integral = (func(x0) + func(xn)) / 2.0; // primer y ultimo termino
    
    for (int i = 1; i < n; i++) { //sumatoria termino intermedios
        double x = x0 + i * h;
        integral += func(x);
    }
    
    integral *= h; //multiplicar por h
    return integral;
}

int main() {
    double x0 = 0.4; // valor inicial x
    double y0 = 0.0; // valor inicial y
    double xn = 0.0; // valor de x para el cual se busca resultado de rapidez
    double n = 1000;

    double resultado = y0 + trapecio(x0, xn, n); // se calcula y
    double rapidez = sqrt(2*resultado); // se calcula v
    printf("la rapidez cuando x = %.2f es %.4f\n", xn, rapidez);

    return 0;
}
