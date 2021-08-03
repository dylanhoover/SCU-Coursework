#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {
    int pageno;
    int ref_bit;
}ref_page;

int main(int argc, char *argv[]){
    int cacheSize = atoi(argv[1]); //Size of cache passed by user

    ref_page cache[cacheSize]; //cache that stores that pages
    char pageCache[100]; // cache that holds the input from test file
    int totalFaults = 0; //keeps track of the total page faults
    int totalRequests = 0;

    int i, j, temp, oldest;
    
    for(i = 0; i < cacheSize; i++){
        cache[i].pageno = -1;
        cache[i].ref_bit = -1;
    }

    while(fgets(pageCache, 100, stdin)){
        ++totalRequests;
        int page_num = atoi(pageCache); //stores number read from file as an int
        for(i = 0; i < cacheSize; i++){
            temp = 0;
            oldest = cache[i].ref_bit;
            if(page_num == cache[i].pageno){
                for(j = 0; j < cacheSize; j++){
                    if(cache[j].ref_bit < cache[i].ref_bit)
                    cache[j].ref_bit++;
                }
                cache[i].ref_bit = 0;
                break;
            }
            for(j = 0; j < cacheSize; j++){
                cache[j].ref_bit++;
            }
            if(i == cacheSize - 1){
                for(j = 0; j < cacheSize; j++){
                    if(oldest < cache[j].ref_bit){
                        temp = j;
                        oldest = cache[j].ref_bit;
                    }
                }
                //printf("Page fault at page %d \n", page_num);
                cache[temp].pageno = page_num;
                cache[temp].ref_bit = 0;
                totalFaults++;

            }
        }
    }
   float hitRate = ((float)totalRequests - (float)totalFaults) / (float)totalRequests;

    printf("%d Total page faults\n", totalFaults);
    printf("%d Total Requests\n", totalRequests);
    printf("%.4f Hit Rate\n", hitRate);
    return 0;

}