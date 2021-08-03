#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
    clock_t start, end;
    double cpuTimeUsed;
    start = clock();
    char filename[30]; //filename buffer

    char buffer[1024];
    ssize_t readIn, writeOut;

    strcpy(filename, argv[1]);
    
    int fp1 = open(filename, O_RDONLY); //opens file give in read mode
    if(fp1 < 0){ //base case for file not existing
        printf("Cannot open file %s \n", (char *)filename);
        exit(0);
    }


    char copyName[30]; //new file name buffer
    strcpy(copyName, filename); //copy old name onto buffer
    strcat(copyName, "_copy"); //add _copy to the original file name to denote copy
    int fp2 = open(copyName, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU); //creates a new file with filename_copy

    while((readIn = read(fp1, buffer, 1024)) > 0){
        writeOut = write(fp2, buffer, readIn);
    }

    close(fp1); //close files
    close(fp2);


    end = clock();
    cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The clock time used was: %f \n", cpuTimeUsed);
    return 0;
}