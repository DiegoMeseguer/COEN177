// Name: Diego Meseguer
// Date: 05/13/2023
// Title: Lab5 – step 5
// Description: This program solves the consumer producer problem
// using conditional variables

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

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

const int SIZE = 10;
int buffer[SIZE]; // Buffer is the shared resource
int counter = 0;

void* producer(void *args) {
    while(1) {
        int x = rand() % 100;
        sleep(1);
        
        pthread_mutex_lock(&mutex);
        while(counter > 9) {
            pthread_cond_wait(&empty, &mutex);
        }
            buffer[counter] = x;
            printf("Producer %d, produced\n", (int)args);
            counter++;
    
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }    

    return NULL;
}

void* consumer(void *args) {
    while(1) {
        int y;
        pthread_mutex_lock(&mutex);
            while(counter < 1) {
                pthread_cond_wait(&full, &mutex);
            }
            y = buffer[counter - 1];
            printf("\t\tConsumer %d, consumed the product %d\n", (int)args, y); 
            counter--;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        sleep(1);
        
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int prodNum = atoi(argv[1]);
    int consNum = atoi(argv[2]);
    pthread_t producerArr[prodNum];
    pthread_t consumerArr[consNum];
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_mutex_init(&mutex, NULL);
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

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}

