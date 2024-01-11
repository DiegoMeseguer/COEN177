// Name: Diego Meseguer
// Date: 05/13/2023
// Title: Lab5 – step 4
// Description: This program solves the consumer producer problem
// using semaphores

//argv[1] = # Producer threads
//argv[2] = # Consumer threads

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <sys/ipc.h>

sem_t *semafull;
sem_t *semaempty;
pthread_mutex_t mutex;

const int SIZE = 10;
int buffer[SIZE]; // Buffer is the shared resource
int counter = 0;

void* producer(void *args) {
    while(1) {
        int x = rand() % 100;
        sleep(1);

        sem_wait(semaempty);
        pthread_mutex_lock(&mutex);
            buffer[counter] = x;
            printf("Producer %d, produced\n", (int)args);
            counter++;
        pthread_mutex_unlock(&mutex);
        sem_post(semafull);
    }    

    return NULL;
}

void* consumer(void *args) {
    while(1) {
        int y;
        sem_wait(semafull);
        pthread_mutex_lock(&mutex);
            y = buffer[counter - 1];
            printf("\t\tConsumer %d, consumed the product %d\n", (int)args, y); 
            counter--;
        pthread_mutex_unlock(&mutex);
        sem_post(semaempty); // Informs producer that there is a new empty space
        sleep(1);
        
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int prodNum = atoi(argv[1]);
    int consNum = atoi(argv[2]);
    pthread_t producerArr[prodNum];
    pthread_t consumerArr[consNum];
    pthread_mutex_init(&mutex, NULL);
    semafull = sem_open("full", IPC_CREAT, 0660, 0);
    semaempty = sem_open("empty", IPC_CREAT, 0660, 10);
    srand(time(NULL));

    //Create producer and consumer threads
    for(int i = 0; i < prodNum; i++) {
        pthread_create(&producerArr[i], NULL, producer, (void *)(size_t)i);
    }
    for(int i = 0; i < consNum; i++) {
        pthread_create(&consumerArr[i], NULL, consumer, (void *)(size_t)i);
    }

    //Join producer and consumer threads
    for(int i = 0; i < prodNum; i++) {
        pthread_join(producerArr[i], NULL);
    }
    for(int i = 0; i < consNum; i++) {
        pthread_join(consumerArr[i], NULL);
    }

    sem_unlink("full");
    sem_unlink("empty");
    pthread_mutex_destroy(&mutex);

    return 0;
}

