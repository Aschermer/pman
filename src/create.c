#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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