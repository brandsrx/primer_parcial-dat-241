#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
void fibonacci(int n) {
    long long *fib = (long long *)malloc(n * sizeof(long long));

    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    printf("Serie de Fibonacci hasta %d términos:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%lld ", fib[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Ingrese el número de términos de la serie Fibonacci: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Por favor, ingrese un número mayor o igual a 2.\n");
        return 1;
    }

    fibonacci(n);

    return 0;
}