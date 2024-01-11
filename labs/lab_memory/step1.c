// Name: Diego Meseguer
// Date: 06/02/2023
// Title: Lab7 - Step 1
// Description: This prgram generates the testInput.txt file to test the page
// replacement aglorithms

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for(i = 0; i < 10000; i++) {
        sprintf(buffer, "%d\n", rand()% 1000);
        fputs(buffer, fp);
    }   
    fclose(fp);

return 0;
}


