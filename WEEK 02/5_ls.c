#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define FILE 8
#define FOLDER 84
void printFiles(char path[100])
{
    struct dirent *dptr;
    DIR *dirp;
    if ((dirp = opendir(path)) == NULL)
    {
    }
    while (dptr = readdir(dirp))
    {
        if (strcmp(dptr->d_name, ".") == 0)
        {
            continue;
        }
        if (strcmp(dptr->d_name, "..") == 0)
        {
            continue;
        }

        printf("%-10s\t", dptr->d_name);
        if (dptr->d_type == FILE)
        {
            printf("FILE \n");
        }
        else
        {
            printf("FOLDER\n");
        }
    }
}

int main()
{
    char rootPath[100] = ".";
    printFiles(rootPath);
    return 0;
}