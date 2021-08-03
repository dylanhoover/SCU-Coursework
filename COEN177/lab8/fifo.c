#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {
    int pageno;
}ref_page;

int main(int argc, char *argv[]){
    int cacheSize = atoi(argv[1]); //Size of cache passed by user

    ref_page cache[cacheSize]; //cache that stores that pages
    char pageCache[100]; // cache that holds the input from test file
    int totalFaults = 0; //keeps track of the total page faults
    int totalRequests = 0;
    int i;
    int counter = 0;
    
    for(i = 0; i < cacheSize; i++){
        cache[i].pageno = -1;
    }

    while(fgets(pageCache, 100, stdin)){
        ++totalRequests;
        bool foundInCache = false;
        int page_num = atoi(pageCache);
        for(i = 0; i < cacheSize; i++){
            if(cache[i].pageno == page_num){
                foundInCache = true;
                break;
            }
        }
        if(foundInCache == false){
            cache[counter].pageno = page_num;
            totalFaults++;
            if(counter > cacheSize - 2){
                counter = 0;
            }
            else{
                counter++;
            }

        }
                
        
    }

    float hitRate = ((float)totalRequests - (float)totalFaults) / (float)totalRequests;

    printf("%d Total page faults\n", totalFaults);
    printf("%d Total Requests\n", totalRequests);
    printf("%.4f Hit Rate\n", hitRate);

    return 0;
}