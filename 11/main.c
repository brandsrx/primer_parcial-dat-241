#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10 

int main(int argc, char *argv[]) {
    int rank, size;
    int vector1[N], vector2[N], result[N];
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (i = 0; i < N; i++) {
            vector1[i] = rand() % 10; 
            vector2[i] = rand() % 10; 
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

    MPI_Bcast(vector1, N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector2, N, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = rank; i < N; i += size) {
        result[i] = vector1[i] + vector2[i];
    }

    MPI_Gather(result, N / size, MPI_INT, result, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultado de la suma: ");
        for (i = 0; i < N; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
    