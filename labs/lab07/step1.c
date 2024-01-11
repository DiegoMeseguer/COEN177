#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i < 100; i++) {
        sprintf(buffer, "%d\n", rand() % 1000);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}

