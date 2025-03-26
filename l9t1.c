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

// normal matrix multiplication
void multiplyMatrices(int size, double **A, double **B, double **C) {
    // set product matrix C to 0
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0.0;
        }
    }

    // multiply ijk
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] = A[i][k] * B[k][j];
            }
        }
    }
}