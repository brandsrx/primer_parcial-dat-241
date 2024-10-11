#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define VECTOR_SIZE 10
#define STRING_LENGTH 20

int main(int argc, char** argv) {
    int rank, size;
    char data[VECTOR_SIZE][STRING_LENGTH]; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < VECTOR_SIZE; i++) {
            snprintf(data[i], STRING_LENGTH, "Cadena %d", i);
        }

        for (int i = 1; i < size; i++) {
            MPI_Send(data, VECTOR_SIZE * STRING_LENGTH, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(data, VECTOR_SIZE * STRING_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Proceso %d despliega: ", rank);
        for (int i = rank - 1; i < VECTOR_SIZE; i += 2) {
            printf("%s ", data[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

