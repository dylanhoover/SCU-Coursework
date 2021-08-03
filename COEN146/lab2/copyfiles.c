#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define SIZE (1024 *1024)


int main(int argc, char *argv[]){
    clock_t start, end;
    start = clock();
    double cpuTimeUsed;
    char c; //used for copying
    FILE *fp1, *fp2; //file pointers
    size_t readFile;
    char buffer[SIZE];


    fp1 = fopen(argv[1], "rb"); //opens file give in read mode
    if(fp1 == NULL){ //base case for file not existing
        printf("Cannot open file %s \n", argv[1]);
        exit(0);
    }

    char copyName[30]; //new file name buffer
    strcpy(copyName, argv[1]); //copy old name onto buffer
    strcat(copyName, "_copy"); //add _copy to the original file name to denote copy
    fp2 = fopen(copyName, "wb"); //creates a new file with filename_copy

    while (0 < (readFile = fread(buffer, 1, sizeof(buffer), fp1)))
        fwrite(buffer, 1, readFile, fp2);
    

    fclose(fp2); //close files
    fclose(fp1);

    end = clock();
    cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The clock time used was: %f \n", cpuTimeUsed);
    
    return 0;

}