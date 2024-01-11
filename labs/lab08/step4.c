// Name: Diego Meseguer
// Date: 06/03/2023
// Title: Lab8 - Step 4
// Description: This program reads the files created in step 1 from beginning to end
// and it also accepts the size of the buffer as a command line argument and it also
// performs a write operation on a newly created file for each read operation

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int SIZE = atoi(argv[2]);
    char buffer[SIZE];
    FILE *fp, *output;

    fp = fopen(argv[1], "rb");
    output = fopen("output.txt", "w");

    while (fread(buffer, sizeof(buffer), 1, fp)) {
        fwrite(buffer, sizeof(buffer), 1, output);
    }

    fclose(fp);
    fclose(output);

    return 0;
}

