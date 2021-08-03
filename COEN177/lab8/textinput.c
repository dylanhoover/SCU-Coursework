#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("textInput.txt", "w");
    for(i = 0; i < 10; i++){
        sprintf(buffer, "%d\n", rand()%10);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}