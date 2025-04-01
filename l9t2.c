/*
Task 2 Generate random dense square matrices, with size of [20x20, 40x40, 80x80,
160x160, 320x320, 640x640, 1280x1280]. Record and plot elapsed times with different
Block size. Which block size is the fastest? Show your answer in the report
*/

// include statements
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define block_size 40

// Populates a 1D array with random numbers
void createMatrix(int size, double *matrix) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = (double)rand() / RAND_MAX; // Random value between 0.0 and 1.0
    }
}

// set matrix C to 0
void setMatrixProduct(int size, double *C) {
    // set all elements to 0
    for (int i = 0; i < size * size; i++) {
        C[i] = 0.0;
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
    setMatrixProduct(size, C);  // Initialize C to 0
    
    for (int ii = 0; ii < size; ii += block_size) {
        for (int jj = 0; jj < size; jj += block_size) {
            for (int kk = 0; kk < size; kk += block_size) {
                // process the current block with bounds checking
                for (int i = ii; i < ii + block_size && i < size; i++) {
                    for (int j = jj; j < jj + block_size && j < size; j++) {
                        register double sum = C[i * size + j];
                        for (int k = kk; k < kk + block_size && k < size; k++) {
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
    // variable declarations
    srand(time(NULL));
    int sizes[] = {20, 40, 80, 160, 320, 640, 1280};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    // header
    printf("Matrix Size\tNormal (s)\tRegReuse (s)\tBlocked (s)\tVerified\n");
    printf("------------------------------------------------------------\n");
    
    // initialize each matrix per size
    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        
        double *A = malloc(size * size * sizeof(double));
        double *B = malloc(size * size * sizeof(double));
        double *C_normal = malloc(size * size * sizeof(double));
        double *C_reg = malloc(size * size * sizeof(double));
        double *C_block = malloc(size * size * sizeof(double));
        
        // Initialize matrices
        createMatrix(size, A);
        createMatrix(size, B);

        // multiply normally
        clock_t startNorm = clock();
        multiplyMatrices(size, A, B, C_normal);
        clock_t endNorm = clock();
        double normTime = (double)(endNorm - startNorm) / CLOCKS_PER_SEC;

        // multiply by register reuse
        clock_t startReg = clock();
        multiplyByRegReuse(size, A, B, C_reg);
        clock_t endReg = clock();
        double regTime = (double)(endReg - startReg) / CLOCKS_PER_SEC;

        // multiply by blocks
        clock_t startBloc = clock();
        multiplyByBlocks(size, A, B, C_block);
        clock_t endBloc = clock();
        double blocTime = (double)(endBloc - startBloc) / CLOCKS_PER_SEC;

        // print output
        printf("%dx%d\t\t%.4f\t\t%.4f\t\t%.4f\n", 
               size, size, normTime, regTime, blocTime);

        // Free memory
        free(A); free(B); 
        free(C_normal); free(C_reg); free(C_block);
    }
}