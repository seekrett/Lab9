/*
Task 1 Compose a dense square matrix multiplication program in C. Implement matrix
multiplication blocking. Generate two 640x640 matrixes, and do matrix multiplication
with two version of matrix multiplication program, compare their output.
*/

// include statements
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define block_size 10

// set matrix C to 0
void setMatrixProduct(int size, double *C) {
    // set product matrix C to 0
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size; j++) {
            C[i] = 0.0;
        }
    }
}

// normal matrix multiplication
void multiplyMatrices(int size, double *A, double *B, double *C) {
    // set product to 0
    setMatrixProduct(size, C);

    // multiply ijk
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i * size + j] += A[i * size + k] * B[k * size + j];
            }
        }
    }
}

// register reuse multiplication
void multiplyByRegReuse(int size, double *A, double *B, double *C) {
    // set product to 0
    setMatrixProduct(size, C);

    // multiply ijk
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            register double sum = 0.0;
            for (int k = 0; k < size; k++) {
                sum += A[i * size + k] * B[k * size + j];
            }
            C[i * size + j] = sum;
        }
    }
}

// blocked multiplication
void multiplyByBlocks(int size, double *A, double *B, double *C) {
    for (int ii = 0; ii < size; ii+= block_size) {
        for (int jj = 0; jj < size; jj+= block_size) {
            for (int kk = 0; kk < size; kk+= block_size) {

                // process the current block
                for (int i = ii; i < ii + block_size; i++) {
                    for (int j = jj; jj < jj + block_size; j++) {
                        register double sum = C[i * size + j];

                        for (int k = kk; k < kk + block_size; k++) {
                            sum += A[i * size + k] * B[k * size + j];
                        }

                        C[i * size + j] = sum;
                    }
                }
            }
        }
    }
}

// main function
int main() {
    // universal variable declarations
    int sizes[] = {20, 40, 80, 160, 320, 640, 1280};        // matrix sizes
    int numOfSizes = sizeof(sizes) / sizeof(sizes[0]);      // total num of sizes 
    int numOfOrders = 6;                                    // num of multiplication orders
    
    // for each size,
    for (int i = 0; i < numOfSizes; i++) {
        // local variable declarations
        int size = sizes[i];                                // tracks current size dealing with

        // initiallize each matrix via malloc
        double **A = (double **)malloc(size * sizeof(double *));
        double **B = (double **)malloc(size * sizeof(double *));
        double **C = (double **)malloc(size * sizeof(double *));
        for (int i = 0; i < size; i++) {
            A[i] = (double *)malloc(size * sizeof(double));
            B[i] = (double *)malloc(size * sizeof(double));
            C[i] = (double *)malloc(size * sizeof(double));
        }
    }
}