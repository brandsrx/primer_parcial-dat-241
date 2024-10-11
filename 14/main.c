#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  

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
    int A[N][N], B[N][N], C[N][N];  
    int row[N];  
    int resultRow[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }
        }
        
        for (int i = 1; i < size && i < N; i++) {
            MPI_Send(A[i], N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        multiplyRowByMatrix(A[0], B, C[0]);
    } else if (rank < N) {
        MPI_Recv(row, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        multiplyRowByMatrix(row, B, resultRow);

        MPI_Send(resultRow, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        for (int i = 1; i < size && i < N; i++) {
            MPI_Recv(C[i], N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

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
