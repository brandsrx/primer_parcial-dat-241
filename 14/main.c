#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  // Tamaño de las matrices (N x N)

void multiplyRowByMatrix(int *row, int matrix[N][N], int *result) {
    for (int j = 0; j < N; j++) {
        result[j] = 0;
        for (int k = 0; k < N; k++) {
            result[j] += row[k] * matrix[k][j];
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N];  // Matrices A, B y C (resultado)
    int row[N];  // Fila temporal
    int resultRow[N];  // Resultado temporal para la fila

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Inicializar las matrices A y B
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }
        }
        
        // Enviar las filas de la matriz A a los demás procesos
        for (int i = 1; i < size && i < N; i++) {
            MPI_Send(A[i], N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // Calcular la fila 0 en el proceso 0
        multiplyRowByMatrix(A[0], B, C[0]);
    } else if (rank < N) {
        // Recibir una fila de la matriz A
        MPI_Recv(row, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Multiplicar la fila recibida por la matriz B
        multiplyRowByMatrix(row, B, resultRow);

        // Enviar la fila resultado al proceso 0
        MPI_Send(resultRow, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // El proceso 0 recibe las filas calculadas y las inserta en la matriz C
    if (rank == 0) {
        for (int i = 1; i < size && i < N; i++) {
            MPI_Recv(C[i], N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Imprimir la matriz resultado
        printf("Matriz A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }

        printf("Matriz B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", B[i][j]);
            }
            printf("\n");
        }

        printf("Matriz C (resultado):\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
