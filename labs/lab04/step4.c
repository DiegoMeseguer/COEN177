// Name: Diego Meseguer
// Date: 05/02/2023
// Title: Lab4 – Step 4
// Description: This program computes the matrix multiplication of two matrices
// A and B using multithreading for each row. So we have N threads.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

// Global pointer
int *ptrN, *ptrM, *ptrL;
double **matrixA, **matrixB, **matrixC;

// Function definitions
void printMatrix(double **matrix, int size1, int size2) {
    for(int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void *multiplyRow(void *arg) {

    int i = ((int)(unsigned long)(size_t *)arg);

        for(int j = 0; j < *ptrL; j++) {
            int temp = 0;
            for (int k = 0; k < *ptrM; k++) {
                temp += matrixA[i][k] * matrixB[k][j];
            }
            matrixC[i][j] = temp;
        }
    return NULL;
 }



int main(int argc, char *argv[]) {
    
    if(argc != 4)
        printf("Error, incorrect number of arguments\n");

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int L = atoi(argv[3]);
    ptrN = &N;
    ptrM = &M;
    ptrL = &L;

    // N threads
    pthread_t threads[N];

    // Create and fill matrix A
    matrixA = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        matrixA[i] = (double *)malloc(M * sizeof(double));
    }

    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrixA[i][j] = (rand() % 9) + 1;
     
    // Create and fill matrix B
    matrixB = (double **)malloc(M * sizeof(double *));
    for (int i = 0; i < M; i++) {
        matrixB[i] = (double *)malloc(L * sizeof(double));
    }

    srand(0);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < L; j++)
            matrixB[i][j] = (rand() % 9) + 1;

    // Create and fill matrix C
    matrixC = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        matrixC[i] = (double *)malloc(L * sizeof(double));
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < L; j++)
          matrixC[i][j] = 0;

    int i;
   for(i = 0; i< N; i++) {
        pthread_create(&threads[i], NULL, multiplyRow, (void*)(size_t)i);
   }


    for(i = 0; i < N; i++) {
         pthread_join(threads[i], NULL); 
    }




    printMatrix(matrixA, N, M);
    printMatrix(matrixB, M, L);
    printMatrix(matrixC, N, L);




    



    



    return 0;
}

