#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#define SIZE (1024 *1024)

void *copyFunction(void *filename){
    size_t c;
    char buffer[SIZE];
    FILE *fp1, *fp2; //file pointers
    fp1 = fopen(filename, "rb"); //opens file give in read mode
    if(fp1 == NULL){ //base case for file not existing
        printf("Cannot open file %s \n", (char *)filename);
        exit(0);
    }
    char copyName[30]; //new file name buffer
    strcpy(copyName, filename); //copy old name onto buffer
    strcat(copyName, "_copy"); //add _copy to the original file name to denote copy
    fp2 = fopen(copyName, "wb"); //creates a new file with filename_copy

    while (0 < (c = fread(buffer, 1, sizeof(buffer), fp1)))
        fwrite(buffer, 1, c, fp2);


    fclose(fp1); //close files
    fclose(fp2);

    pthread_exit(NULL); //close thread to free memory
}

int main(int argc, char *argv[]){
    clock_t start, end;
    double cpuTimeUsed;
    start = clock();
    int i; //iteration int
    pthread_t tid; //thread id
    char filename[30]; //filename buffer
    for(i = 1; i < 11; i++){ //iterates through the arguments given and creates a thread for each file
        strcpy(filename, argv[i]); //copies argument to filename buffer for passing argument to thread
        pthread_create(&tid, NULL, copyFunction ,filename); //create a thread
        pthread_join(tid, NULL); //need the delay here for things to work
    }

    end = clock();
    cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The clock time used was: %f \n", cpuTimeUsed);
    return 0;
}