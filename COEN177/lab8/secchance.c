
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
    int index;
} ref_page;

int main(int argc, char *argv[]){
	int cacheSize = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[cacheSize]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i,j;
    int totalFaults = 0; // keeps track of the total page faults
    int schance = 0;
    int replace = 0;
    int totalRequests = 0;
    
    for (i = 0; i < cacheSize; i++){//initialise cache array
        cache[i].pageno = -1;
        cache[i].index = 0;
    }

    while (fgets(pageCache, 100, stdin)){ 
        ++totalRequests;
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        for(i = 0; i < cacheSize; i++){ //this first for loop checks to see if the page is in the cache
            if(page_num == cache[i].pageno){
                cache[i].index = 1;
                schance=0;
                break;
            }
            if(i == cacheSize - 1) //if i reaches the end of the cache size
                schance = 1;
        }
        if(schance== 1){
            for(j = replace; j < cacheSize; j++){  //goes from whatever number replacements have been done up to cache size
                if(cache[j].index == 1){ //if the index is 1 that means it can be skipped
                    cache[j].index = 0; //reset back to 0
                    replace++; //increment replace
                    if(replace == cacheSize){ //if replace is equal to cache size then we reset the variables
                        replace = 0;
                        j = -1;
                    }
                }
                else{ //page replacement section
                    cache[j].pageno = page_num; //swap pages
                    cache[j].index = 0; //set the index back to 0
                    totalFaults++; //increment the faults
                    if(replace + 1 != cacheSize) //if we haven't reached the total number of replacements possible
                        replace++; //increment the replace
                    else
                        replace = 0; //otherwise leave it at 0
                    //printf("Page fault at page %d \n", page_num);
                    break;
                }
            }
        }
    }

    float hitRate = ((float)totalRequests - (float)totalFaults) / (float)totalRequests;

    printf("%d Total page faults\n", totalFaults);
    printf("%d Total Requests\n", totalRequests);
    printf("%.4f Hit Rate\n", hitRate);
    return 0;

}
