//# Name: Diego Meseguer
//# Date: 04/25/23
//# Title: Lab3 – Step 6
//# Description: This program implements the producer-consumer message communication 
// using shared memory

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

const int SIZE = 99;

typedef struct {
    int is_full;
    char message[SIZE];
} shared_memory;

int main(void) {
    int shmid;
    key_t key = 1000;
    shared_memory *shm; // pointer to shared memory segment

    pid_t pid; // process id

    shmid = shmget(key, sizeof(shared_memory), IPC_CREAT | 0666);
    shm = shmat(shmid, NULL, 0);

    (*shm).is_full = 0;

    pid = fork();

    if (pid == 0) { // Consumer
        while (1) {
            if ((*shm).is_full) {
                printf("Consumer received: %s\n", (*shm).message);
                (*shm).is_full = 0;
            }
        }

        exit(0);
    }

    else { // Parent
        char message[SIZE];
        printf("Enter message to send: ");

        while (1) {
            fgets(message, SIZE, stdin);
            message[strcspn(message, "\n")] = 0;

            while ((*shm).is_full) {
            }

            strcpy(shm->message, message);
            (*shm).is_full = 1;
        }
        exit(0);
    }

    return 0;
}



