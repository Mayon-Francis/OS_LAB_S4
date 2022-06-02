//  gcc file1.c && ./a.out test.txt

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE *fp;
	char ch;
	int sc = 0;
	fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("Unable to open file, %s \n", argv[1]);
	} else {
		printf("Opened file %s \n", argv[1]);
		
		ch = fgetc(fp);
		while(!feof(fp)) {
			printf("%c",ch);  
			ch = fgetc(fp);
			if(ch == ' ') {
				sc++;
			}
		}
		printf("No. of spaces: %d \n", sc);
		fclose(fp);
	}
}
