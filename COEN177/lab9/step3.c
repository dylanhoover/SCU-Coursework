#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	int SIZE = atoi(argv[2]);
	char *buffer[SIZE];
	FILE *fp;
	fp = fopen(argv[1], "rb");
	while(fread(buffer, SIZE, 1, fp)){}
	fclose(fp);
	return 0;
}

