// Name: Diego Meseguer
// Date: 05/02/2023
// Title: Lab4 – Step 5
// Description: This program computes the matrix multiplication of
// matrices A and B using multithreading to create N*L threads,
// each computing  the ith row multiplied by jth column. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

// Global pointer
int *ptrN, *ptrM, *ptrL;
double **matrixA, **matrixB, **matrixC;

typedef struct {
    int row;
    int col;
} index;

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

    index *myArg = (index *)arg;

        int temp = 0;
        for (int k = 0; k < *ptrM; k++) {
               temp += matrixA[(*myArg).row][k] * matrixB[k][(*myArg).col];
         }
         matrixC[(*myArg).row][(*myArg).col] = temp;

        free(myArg);
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

    // N * L threads
    pthread_t threads[N * L];

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

    int counter = 0;
    int i;
    int j;
   for(i = 0; i< N; i++) {
        for(j = 0; j < L; j++) {
            index *myArg = (index *)malloc(sizeof(index));
            myArg->row = i;
            myArg->col = j;
            pthread_create(&threads[counter], NULL, multiplyRow, myArg);
            counter++;
        }
   }


   for(int i = 0; i < counter; i++) {
        pthread_join(threads[i], NULL); 
   }

    printMatrix(matrixA, N, M);
    printMatrix(matrixB, M, L);
    printMatrix(matrixC, N, L);

    return 0;
}

