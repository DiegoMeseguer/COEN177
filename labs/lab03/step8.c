//# Name: Diego Meseguer
//# Date: 04/25/23
//# Title: Lab3 – Step 8
//# Description: This program fixes the program in step 7 so two threads don't print the same
// value of i

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];

int main() {
    int i;
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &arr[i]);
            for (i = 0; i < NTHREADS; i++) {
                 printf("Thread %d returned\n", i);
                 pthread_join(threads[i],NULL);
            }
        printf("Main thread done.\n");
        return 0;
    }


void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long) pthread_self(), *(int *)arg);
    return 0;
}

