// Name: Diego Meseguer
// Date: 05/02/2023
// Title: Lab4 – Step 1
// Description: This program computes ...

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NTHREADS 20

void *go(void *);
pthread_t threads[NTHREADS];

int main() {
    int i;

    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);

    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned
            long)pthread_self(), (int)(unsigned long)(size_t *)arg);
    sleep(15);
    pthread_exit(0);
}




