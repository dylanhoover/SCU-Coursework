#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	int SIZE = atoi(argv[2]);
	char *buffer[SIZE];
	FILE *in = fopen(argv[1], "rb");
	FILE *out = fopen("output.txt", "wb");
	while(fread(buffer, SIZE, 1, in)){
		fwrite(buffer, SIZE, 1, out);
	}
	fclose(in);
	fclose(out);
	return 0;
}

