#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "templates/c.c"

void createProject(char *name, char *rawTemplate)
{
    char template[128];
    for(int i = 0; rawTemplate[i] != '\0'; i++)
    {
        template[i] = tolower(rawTemplate[i]);
    }
    printf("%s\n", template);

    if(strcmp(template, "empty") == 0 || strcmp(template, "e") == 0)
    {
        defaultTemplate(name);
    }
    else if(strcmp(template, "c") == 0)
    {
        defaultTemplate(name);
        templateC();
    }
    else
    {
        printf("Please Provide A Format (\"Empty\" for an empty project)");
    }

    return;
}