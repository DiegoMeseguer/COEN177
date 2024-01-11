// Name: Diego Meseguer
// Date: 06/03/2023
// Title: Lab8 - Step 3
// Description: This program reads the files created in step 1 from beginning to end
// and it also accepts the size of the buffer as a command line argument

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int SIZE = atoi(argv[2]);
    char buffer[SIZE];
    FILE *fp;

    fp = fopen(argv[1], "rb");

    while (fread(buffer, sizeof(buffer), 1, fp)) {
    }

    fclose(fp);

    return 0;
}

