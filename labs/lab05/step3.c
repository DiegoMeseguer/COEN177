// Name: Diego Meseguer
// Date: 05/13/2023
// Title: Lab5 – step 3
// Description: This program uses mutex locks for synchronization. We
// replaced the calls to sem_wait and sem_post with the respective
// calls to mutex_lock and mutex_unlock

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>

#define NTHREADS 10

void *go(void *arg);
//void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t mutex;

int main() {
    pthread_mutex_init(&mutex, NULL);
    //signal(SIGINT,cleanup);
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i],NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)arg);
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)arg);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

/*void cleanup(int sigtype){
    sem_unlink("mutex");
    printf("\n Terminating\n");
    exit(0);
}*/

