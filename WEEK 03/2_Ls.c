// gcc 2_Ls.c && ./a.out .
// gcc 2_Ls.c && ./a.out testDir


#include <stdio.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
	struct dirent *link;
	DIR *dp;
	dp = opendir(argv[1]);
	printf("Reading directory: %s \n", argv[1]);
    while ((link = readdir(dp)) != 0)
    {
        printf("%s\n", link->d_name);
    }
    closedir(dp);
}
