// Name: Diego Meseguer
// Date: 06/02/2023
// Title: Lab7 - Step 3
// Description: This prgram implements the Second Chance page replacement algorithm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    int chance_2;
}   ref_page;

int main(int argc, char* argv[]) {

    int CACHE_SIZE = atoi(argv[1]);         // Size of Cache passed by user (number of frames)
    ref_page cache[CACHE_SIZE];             // Cache that stores pages 
    char pageCache[100];

    int totalFaults = 0;
    int c = 0;
    int i, j, k;
    int page_num;
    float hit;

    for(i = 0; i < CACHE_SIZE; i++) {                             
        cache[i].pageno = -1;
        cache[i].chance_2 = 0;
    }

    bool exists;
    int numberOfRequests = 0;

    while(fgets(pageCache, 100, stdin)) {
        numberOfRequests++;
        page_num = atoi(pageCache);

        for(i = 0; i < CACHE_SIZE; i++) {                          
            if(cache[i].pageno == page_num) {                  
                cache[i].chance_2 = 1;                     
                exists = false;                                     
                break;
            }
            if(i == CACHE_SIZE - 1) {                                 
                exists = true;
            }                              
        }
    
        if(exists) {                                           
            printf("Page %d caused fault\n", page_num);
            totalFaults++;
            for(k = c; k < CACHE_SIZE; k++) {                
                if(cache[k].chance_2 == 1) {               
                    cache[k].chance_2 = 0;                 
                    c++;                  
                    if(c == CACHE_SIZE) {                    
                        c = 0;                           
                        k = 0;                                 
                    }
                }
                else {                                   
                    cache[k].pageno = page_num;                
                    cache[k].chance_2 = 0;
                    c = (c + 1) % CACHE_SIZE;
                    break;
                }
            }
        }
    }

    hit = (numberOfRequests - totalFaults) / ((float)numberOfRequests);
    printf("%d Total Page Requests\n", numberOfRequests);
    printf("%d Total Page Faults\n", totalFaults);
    printf("Hit rate for Second Chance: %f\n", hit);

    return 0;
}

