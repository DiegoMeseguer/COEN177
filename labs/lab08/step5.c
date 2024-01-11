// Name: Diego Meseguer
// Date: 06/03/2023
// Title: Lab8 - Step 5
// Description: This program reads the files created in step 1 from beginning to end
// and it also accepts the size of the buffer as a command line argument and it also
// performs a write operation on a newly created file for each read operation and it
// also creates multiple threads in order to have multiples copies of each file made

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int *SIZE;
char *filename;

void* routine(void *args) {
    char buffer[*SIZE];
    FILE *fp, *output;

    fp = fopen(filename, "rb");
    output = fopen("output.txt", "w");

    while (fread(buffer, sizeof(buffer), 1, fp)) {
        fwrite(buffer, sizeof(buffer), 1, output);
    }

    fclose(fp);
    fclose(output);

    return NULL;
}

int main(int argc, char* argv[]) {

    int i;
    int THREAD_NUM = atoi(argv[3]);
    pthread_t threads[THREAD_NUM];
    int size = atoi(argv[2]);
    SIZE = &size;
    filename = argv[1];

    for(i = 0; i < THREAD_NUM; i++) {
        pthread_create(&threads[i], NULL, &routine, NULL);
    }

    for(int i = 0; i < THREAD_NUM; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

