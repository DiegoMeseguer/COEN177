// Name: Diego Meseguer
// Date: 06/02/2023
// Title: Lab7 - Step 3
// Description: This prgram implements the FIFO page replacement algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct {    //to 
    int pageno;
} ref_page;

int main(int argc, char *argv[]) {
	int CACHE_SIZE = atoi(argv[1]);         // Size of Cache passed by user (number of frames)
    ref_page cache[CACHE_SIZE];             // Cache that stores pages 
    char pageCache[100];                    // Cache that holds the input from test file

    int i;
    int totalFaults = 0;                    // keeps track of the total page faults
    int placeInArray = 0;
    
    for(i = 0; i < CACHE_SIZE; i++) {       //initialise cache array  
        cache[i].pageno = -1;
    }

    int numberOfRequests = 0;
    while(fgets(pageCache, 100, stdin)) {
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        numberOfRequests++;

    	//bool foundInCache = false;

        for (i=0; i < CACHE_SIZE; i++) {
            if (cache[i].pageno == page_num){
                break;  //break out loop
            }
            if (i == (CACHE_SIZE - 1)) {
                printf("Page %d caused page fault\n", page_num);
                totalFaults++;
                cache[placeInArray].pageno = page_num;
                placeInArray = (placeInArray + 1)  % CACHE_SIZE;

    
            }
        }
    }

    double hit = (numberOfRequests - totalFaults) / ((double)numberOfRequests);
    printf("%d Total Page Requests\n", numberOfRequests);
    printf("%d Total Page Faults\n", totalFaults);
    printf("Hit rate for FIFO: %f\n", hit);
    return 0;

}

