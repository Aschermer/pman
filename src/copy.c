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

void copyProject(char *dstPath, char *srcPath)
{
    char originalPath[4096];
    char newPath[4096];

    strcpy(originalPath, dstPath);
    strcpy(newPath, srcPath);
    
    struct dirent *dir;
    
    DIR *d;
    d = opendir(originalPath);
    if (!d) 
    {
        printf("Failed to Open File %s\n", originalPath);
    }

    mkdir(newPath, 0777);

    while ((dir = readdir(d)) != NULL)
    {
        if(!(strcmp(dir->d_name, ".") == 0) && !(strcmp(dir->d_name, "..") == 0))
        {
            printf("Name: %10s  Type: %d\n", dir->d_name, dir->d_type);

            strcat(originalPath, "/");
            strcat(newPath, "/");

            strcat(originalPath, dir->d_name);
            strcat(newPath, dir->d_name);

            if(dir->d_type == 4)
            {
                copyProject(originalPath, newPath);
            }
            else if(dir->d_type == 8)
            {
                FILE *srcFile = fopen(originalPath, "r");
                FILE *dstFile = fopen(newPath, "w");

                char byteBuffer[1024];
                int bytesRead;
                while((bytesRead = fread(byteBuffer, 1, sizeof(byteBuffer), srcFile)))
                {
                    if(fwrite(byteBuffer, 1, bytesRead, dstFile) != bytesRead)
                    {
                        printf("Error Copying File %s to %s\n", originalPath, newPath);
                        break;
                    }
                }

                fclose(srcFile);
                fclose(dstFile);
            }

            strcpy(originalPath, dstPath);
            strcpy(newPath, srcPath);
        }
    }
    closedir(d);
    return;
}