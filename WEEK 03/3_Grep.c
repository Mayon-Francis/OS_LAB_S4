// gcc 3_Grep.c && ./a.out test.txt Heyy
// gcc 3_Grep.c && ./a.out test.txt Hey

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 1024

void usage() {
	printf("usage:\t /a.out filename word \n"); 
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char fline[max];
	char *newLine;
	int count=0;
	int occurences=0;
	if(argc != 3) {
		usage();
		exit(1);
	}
	
	if( !(fp=fopen(argv[1], "r"))) {
		printf("grep: couldn't open file: %S \n", argv[1]);
		exit(1);
	}
	
	while( fgets(fline,max, fp) !=NULL) {
		count++;
		
		if(newLine = strchr(fline, '\n')) {
			*newLine='\0';
			
			if(strstr(fline, argv[2])!=NULL) {
				printf("%s: %d %s \n", argv[1], count, fline);
				occurences++;
			}
		}
	}
	
	printf("Total No. of occurences: %d\n", occurences);
	

}
