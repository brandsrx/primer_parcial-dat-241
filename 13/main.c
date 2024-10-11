#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define VECTOR_SIZE 10
#define STRING_LENGTH 20

int main(int argc, char** argv) {
    int rank, size;
    char data[VECTOR_SIZE][STRING_LENGTH]; // Vector de cadenas

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Proceso maestro
        // Inicializar el vector de cadenas
        for (int i = 0; i < VECTOR_SIZE; i++) {
            snprintf(data[i], STRING_LENGTH, "Cadena %d", i);
        }

        // Enviar cadenas a los procesos 1 y 2
        for (int i = 1; i < size; i++) {
            MPI_Send(data, VECTOR_SIZE * STRING_LENGTH, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // Procesos trabajadores (1 y 2)
        // Recibir cadenas del proceso maestro
        MPI_Recv(data, VECTOR_SIZE * STRING_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Desplegar cadenas en posiciones pares o impares
        printf("Proceso %d despliega: ", rank);
        for (int i = rank - 1; i < VECTOR_SIZE; i += 2) {
            printf("%s ", data[i]);
        }
        printf("\n");
    }

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}

