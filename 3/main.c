#include<stdio.h>

int suma(int *a, int *b) {
    return *a + *b;
}

int resta(int *a, int *b) {
    return *a - *b;
}

int multiplicacion(int *a, int *b) {
    return (*a) * (*b);
}

float division(int *a, int *b) {
    if (*b == 0) return 0.0; 
    return (float)(*a) / (*b); 
}

int main() {
    int a = 10, b = 4;

    // Imprimir los resultados de cada operación utilizando punteros
    printf("Resultado de la suma: %d\n", suma(&a, &b));
    printf("Resultado de la resta: %d\n", resta(&a, &b));
    printf("Resultado de la multiplicacion: %d\n", multiplicacion(&a, &b));
    printf("Resultado de la division: %.2f\n", division(&a, &b));

    return 0;
}
