#include<stdio.h>

// Función que calcula π iterativamente usando punteros
double calcularPiIterativo(int *n) {
    double pi = 0.0;
    for (int i = 0; i < *n; i++) {
        double termino = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
        pi += termino;
    }
    return pi * 4;
}

int main() {
    int n = 1000000; // Número de iteraciones
    printf("Valor de pi calculado iterativamente: %.15f\n", calcularPiIterativo(&n));
    return 0;
}
