// Name: Diego Meseguer
// Date: 06/03/2023
// Title: Lab8 - Step 2
// Description: This program reads the files created in step 1 from beginning to end

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    char buffer[10000];
    FILE *fp;

    fp = fopen(argv[1], "rb");

    while (fread(buffer, sizeof(buffer), 1, fp)) {
    }

    fclose(fp);

    return 0;
}

