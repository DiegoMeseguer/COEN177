// Name: Diego Meseguer
// Date: 06/02/2023
// Title: Lab7 - Step 3
// Description: This prgram implements the LRU page replacement algorithm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {     //to
        int pageno;
        int id;
} ref_page;

int main(int argc, char *argv[]) {
    int CACHE_SIZE = atoi(argv[1]);     // Size of Cache passed by user (number of frames)
    ref_page cache[CACHE_SIZE]; 
    char pageCache[100];

    float hit;
    int totalFaults=0; 
    int placeInArray=0;
    int i, j, k;
    int page_num, oldest;
    
    for(i = 0; i < CACHE_SIZE; i++) {
        cache[i].pageno = -1;                                      
        cache[i].id = 0;                                               
    }

    int numberOfRequests = 0;
    while(fgets(pageCache, 100, stdin)) {
        numberOfRequests++;
        page_num = atoi(pageCache);
        oldest = cache[i].id;
                                                
        for(i = 0; i < CACHE_SIZE; i++) {                                   
            if(cache[i].pageno == page_num) {                          
                for(j = 0; j < CACHE_SIZE; j++) {                           
                    if(cache[j].id < cache[i].id) { 
                        cache[j].id++;
                    }
                }

                cache[i].id = 0;                                    
                break;

            }
            else if(i == (CACHE_SIZE - 1)) {                                   
                printf("Page %d caused fault\n", page_num);           
                totalFaults++;  
                for(j = 0; j < CACHE_SIZE; j++)                       
                    cache[j].id++;
    
                for(k = 0; k < CACHE_SIZE ; k++) {                    
                    if(cache[k].id > oldest) {     
                        oldest = cache[k].id;                 
                        placeInArray = k;                             
                    }
                }
                cache[placeInArray].pageno = page_num;
                cache[placeInArray].id = 0;
            }
        }
    }
    
    hit = (numberOfRequests - totalFaults) / ((float)numberOfRequests);
    printf("%d Total Page Requests\n", numberOfRequests);
    printf("%d Total Page Faults\n", totalFaults);
    printf("Hit rate for LRU: %f\n", hit);

    return 0;

}


