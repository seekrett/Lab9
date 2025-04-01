/*
Task 1 Compose a dense square matrix multiplication program in C. Implement matrix
multiplication blocking. Generate two 640x640 matrixes, and do matrix multiplication
with two version of matrix multiplication program, compare their output.
*/

// include statements
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 640
#define BLOCK_SIZE 40

// Populates a 1D array with random numbers
void createMatrix(double *matrix) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        matrix[i] = (double)rand() / RAND_MAX;
    }
}

// set matrix to 0
void zeroMatrix(double *matrix) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        matrix[i] = 0.0;
    }
}

// standard matrix multiplication
void multiplyStandard(double *A, double *B, double *C) {
    zeroMatrix(C);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i * SIZE + j] += A[i * SIZE + k] * B[k * SIZE + j];
            }
        }
    }
}

// blocked matrix multiplication
void multiplyBlocked(double *A, double *B, double *C) {
    zeroMatrix(C);
    for (int ii = 0; ii < SIZE; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < SIZE; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < SIZE; kk += BLOCK_SIZE) {
                for (int i = ii; i < ii + BLOCK_SIZE && i < SIZE; i++) {
                    for (int j = jj; j < jj + BLOCK_SIZE && j < SIZE; j++) {
                        double sum = C[i * SIZE + j];
                        for (int k = kk; k < kk + BLOCK_SIZE && k < SIZE; k++) {
                            sum += A[i * SIZE + k] * B[k * SIZE + j];
                        }
                        C[i * SIZE + j] = sum;
                    }
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));
    
    // Allocate matrices
    double *A = malloc(SIZE * SIZE * sizeof(double));
    double *B = malloc(SIZE * SIZE * sizeof(double));
    double *C_standard = malloc(SIZE * SIZE * sizeof(double));
    double *C_blocked = malloc(SIZE * SIZE * sizeof(double));
    
    // Initialize matrices
    createMatrix(A);
    createMatrix(B);
    
    // Time standard multiplication
    clock_t start_std = clock();
    multiplyStandard(A, B, C_standard);
    double time_std = (double)(clock() - start_std) / CLOCKS_PER_SEC;
    
    // Time blocked multiplication
    clock_t start_block = clock();
    multiplyBlocked(A, B, C_blocked);
    double time_block = (double)(clock() - start_block) / CLOCKS_PER_SEC;
    
    // Print results
    printf("640x640 Matrix Multiplication\n");
    printf("----------------------------\n");
    printf("Standard: %.3f seconds\n", time_std);
    printf("Blocked:  %.3f seconds\n", time_block);
    printf("Speedup:  %.2fx faster\n", time_std / time_block);
    
    // Free memory
    free(A); free(B);
    free(C_standard); free(C_blocked);
    
    return 0;
}