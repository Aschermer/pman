#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "templates/c.c"

void createProject(char *name, char *rawTemplate, uint32_t flags)
{
    char template[128];
    for(int i = 0; rawTemplate[i] != '\0'; i++)
    {
        template[i] = tolower(rawTemplate[i]);
    }

    if(strcmp(template, "empty") == 0 || strcmp(template, "e") == 0)
    {
        createDefaultTemplate(name);
    }
    else if(strcmp(template, "c") == 0)
    {
        createDefaultTemplate(name);
        templateC();
    }
    else
    {
        printf("Please Provide A Format (\"Empty\" for an empty project)");
    }

    return;
}