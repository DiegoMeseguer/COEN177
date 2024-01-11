// Name: Diego Meseguer
// Date: 06/02/2023
// Title: Lab7 - Step 2
// Description: This prgram generates reads the output of cat testInput.txt so
// it can be pipelined into the page replacement programs

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    FILE *fp;
    char* pageCache;

    fp = fopen("testInput.txt", "r");

    while (fgets(pageCache, 100, fp)) {
        int page_num = atoi(pageCache); // Stores number read from file as an int
        printf("%d\n", page_num);
    }

    return 0;
}


