#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// funcion que aproxima valor de 1ra derivada usando diferencia adelantada, hasta terminos de 3er orden
double derivada(double (*fun)(double), double x, double h) {
    return (fun(x+h) - fun(x) - (fun(x+2*h) - 2*fun(x+h) + fun(x))/2 + (fun(x+3*h) - 3*fun(x+2*h) + 3*fun(x+h) - fun(x))/3)/h;
}


// funcion que aproxima valor de 2da derivada usando diferencia adelantada, hasta terminos de 3er orden
double derivada2(double (*fun)(double), double x, double h) {
    return (fun(x+2*h) - 2*fun(x+h) + fun(x) - (fun(x+3*h) - 3*fun(x+2*h) + 3*fun(x+h) - fun(x)) + (fun(x+4*h) - 4*fun(x+3*h) + 6*fun(x+2*h) - 4*fun(x+h) + fun(x))*11/12)/(h*h);
}


// funcion dada que describe posicion del piston, donde x representa el tiempo en segundos
double miFuncion(double x) {
    return 0.09*(cos(523.6*x) + sqrt(6.25-sin(523.6*x)*sin(523.6*x)));
}


void plot(double (*miFuncion)(double), double (*derivada)(double (*)(double), double, double)) { // guardar datos para grafico velocidad vs angulo theta
    double h = 0.0001;  // paso

    FILE *archivo = fopen("datos.dat", "w");
     for (double x = 0.0 ; x <= M_PI/261.8 ; x += M_PI/(261.8*36.0)) { // evaluar para theta entre 0 y 2pi, es decir, tiempo x entre 0 y 2pi/523.6. Con paso cada 10 grados
         double resultado = derivada(miFuncion, x, h);
         fprintf(archivo, "%f %f\n",523.6*180.0*x/M_PI, resultado);
     }
    fclose(archivo);
 }

void maximo(double (*miFuncion)(double), double (*derivada2)(double (*)(double), double, double)){
    double h = 0.0001;  // paso
    double maxResultado = -999999.99; // inicializar
    double* max_x= NULL;
    int contador = 0;
    for (double x = 0.0 ; x <= M_PI/261.8 ; x += M_PI/(261.8*360.0)) {
         double resultado2 = derivada2(miFuncion, x, h);
         if (resultado2 > maxResultado){
            maxResultado = resultado2;
            contador = 1;
            max_x = realloc(max_x, sizeof(double));
            max_x[0] = x;
         } else if (resultado2 == maxResultado){
            contador++;
            max_x = realloc(max_x, contador*sizeof(double));
            max_x[contador-1] = x;
          }
     }
    printf("Máxima aceleración (módulo):  %.6f m/s²\n", maxResultado);
    printf("valores correspondientes de theta: ");
    for (int i= 0; i< contador; i++){
       printf("%.2f grados ", 523.6*180.0*max_x[i]/M_PI);
    }
    printf("\n");
    free(max_x);
}

int main(){
    plot(miFuncion, derivada);
    maximo(miFuncion, derivada2);
    return 0;
}
