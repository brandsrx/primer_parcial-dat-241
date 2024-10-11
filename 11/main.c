#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10 // Tamaño de los vectores

int main(int argc, char *argv[]) {
    int rank, size;
    int vector1[N], vector2[N], result[N];
    int i;

    // Inicializa MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Solo el maestro inicializa los vectores
        for (i = 0; i < N; i++) {
            vector1[i] = rand() % 10; // Inicializa con números aleatorios
            vector2[i] = rand() % 10; // Inicializa con números aleatorios
        }

        printf("Vector 1: ");
        for (i = 0; i < N; i++) {
            printf("%d ", vector1[i]);
        }
        printf("\n");

        printf("Vector 2: ");
        for (i = 0; i < N; i++) {
            printf("%d ", vector2[i]);
        }
        printf("\n");
    }

    // Envía los vectores a todos los procesos
    MPI_Bcast(vector1, N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector2, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada proceso realiza la suma de su parte
    for (i = rank; i < N; i += size) {
        result[i] = vector1[i] + vector2[i];
    }

    // El maestro recopila los resultados
    MPI_Gather(result, N / size, MPI_INT, result, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Solo el maestro imprime el resultado
    if (rank == 0) {
        printf("Resultado de la suma: ");
        for (i = 0; i < N; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    // Finaliza MPI
    MPI_Finalize();
    return 0;
}
    