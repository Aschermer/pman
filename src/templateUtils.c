#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void writeFile(char *fileName, char *fileContents)
{
    FILE *f = fopen(fileName, "w");
    fputs(fileContents, f);
}

void defaultTemplate(char *name)
{
    mkdir(name, 0777);
    chdir(name);
}