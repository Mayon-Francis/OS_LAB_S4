//  gcc 1_Cp.c && ./a.out test.txt testCopy.txt

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void usage() {
	printf("usage:\t /a.out source dest \n"); 
}

#define requiredArgCount 2

int main(int argc, char* argv[]) {
	FILE *fp;
	FILE *fp2;
	char ch;
	fp = fopen(argv[1], "r");
	
	fp2 = fopen(argv[2], "r");
	if(fp2) {
		printf("%s already exists, do you want to overwrite it? (y/n): ", argv[2]);
		char overWrite = 'n';
		scanf("%c", &overWrite);
		if(!(overWrite == 'y' || overWrite == 'Y')) {
			printf("Aborting\n");
			exit(0);
		}
	}
	
	fp2 = fopen(argv[2], "w");
	if(argc != requiredArgCount+1) {
		usage();
		exit(1);
	}
	if(fp == NULL) {
		printf("Unable to open file, %s \n", argv[1]);
	} else {	
		
		ch = fgetc(fp);
		while(!feof(fp)) {
			fprintf(fp2, "%c", ch); 
			ch = fgetc(fp);
		}
		printf("copied %s to %s \n", argv[1], argv[2]);
		fclose(fp);
		fclose(fp2);
	}
}


