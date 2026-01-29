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

void createProject(char *option1, char *option2)
{
    mkdir(option1, 0777);
    if(strcmp(option2, "c") == 0)
    {
        
        chdir(option1);
        mkdir("bin", 0777);
        mkdir("obj", 0777);
        mkdir("src", 0777);
    }
    return;
}