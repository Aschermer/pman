#ifndef FILE_INCLUDED

#include <git2/global.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include <sys/stat.h>
#include <dirent.h>

#include <git2.h>

#endif

void deleteProject(char *path)
{
    printf("Deleting %s\n", path);
    char *newPath = (char *)malloc((strlen(path) + 3) * sizeof(char));
    newPath[0] = '.';
    newPath[1] = '/';
    newPath[2] = '\0';
    strcat(newPath, path);
    if(chdir(newPath) != 0)
    {
        printf("Failed to Change Directories\n");
    }
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(!(strcmp(dir->d_name, ".") == 0) && !(strcmp(dir->d_name, "..") == 0))
            {
                printf("Name: %10s  Type: %d\n", dir->d_name, dir->d_type);
                if(dir->d_type == 4)
                {
                    deleteProject(dir->d_name);
                }
                if(dir->d_type == 8)
                {
                    remove(dir->d_name);
                }
            }
        }
        closedir(d);
        chdir("..");
        rmdir(path);
    }
    return;
}