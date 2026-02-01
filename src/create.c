#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "flags.h"

#include "templateUtils.c"

#include "templates/c.c"

void createProject(char *name, char *rawTemplate, uint32_t flags)
{
    char template[128];
    for(int i = 0; rawTemplate[i] != '\0'; i++)
    {
        template[i] = tolower(rawTemplate[i]);
    }

    mkdir(name, 0777);
    chdir(name);
    printf("Created Project Directory\n");

    if((flags | FLAG_GIT_REPO) != 0)
    {
        createGitRepo();
        printf("Created Git Repo\n");
    }

    if(strcmp(template, "empty") == 0)
    {
        
    }
    else if(strcmp(template, "c") == 0)
    {
        templateC();
    }
    else
    {
        printf("Please Provide A Format (\"Empty\" for an empty project)");
    }

    return;
}