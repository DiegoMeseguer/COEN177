#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

const int SIZE =  999;

int main(void) {
    int fds[2]; 
    char message[SIZE];

    pipe(fds);

    if (fork() == 0) { // Consumer
        close(fds[1]);

        while (1) {
            if (read(fds[0], message, SIZE) > 0) {
                printf("Consumer read: %s\n", message);
            }
        }

    } else if(fork()==0) { // Producer
        close(fds[0]);
        printf("Enter message: ");

        while (1) {
            fgets(message, SIZE, stdin);

            if (write(fds[1], message, strlen(message) + 1) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }
    else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }

    return 0;
}

