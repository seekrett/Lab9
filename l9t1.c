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
                C[i * size + j] = A[i * size + k] * B[k * size + j];
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