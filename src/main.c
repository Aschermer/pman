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

#include "flags.h"

#include "create.c"
#include "delete.c"
#include "rename.c"
#include "copy.c"

void printHelp() 
{
    const char *manPage = "\n\n"
        "Project Manager (pman)\n"
        "NAME\n"
        "        pman - create, delete, rename, and copy projects\n"
        "\n"
        "CREATE\n"
        "        pman [OPTIONS] create NAME TEMPLATE\n"
        "\n"
        "DELETE\n"
        "        pman [OPTIONS] delete NAME\n"
        "\n"
        "RENAME\n"
        "        pman [OPTIONS] rename OLD NEW\n"
        "\n"
        "COPY\n"
        "        pman [OPTIONS] copy SRC DST\n"
        "\n";
    printf("%s", manPage);
    return;
}

uint32_t parseOptions(char *arg)
{
    uint32_t flags = FLAG_NONE;
    for(int i = 0; arg[i] != '\0'; i++)
    {
        switch (arg[i]) {
            case 'g':
            {
                flags |= FLAG_GIT_REPO;
                break;
            }
        }
    }
    return(flags);
}

void parseCommands(char *command, char *arg1, char *arg2, uint32_t flags)
{
    for(int i = 0; command[i] != '\0'; i++)
    {
        command[i] = tolower(command[i]);
    }


    if((strcmp(arg1, "pman") == 0) || (strcmp(arg2, "pman") == 0))
    {
        printf("Cannot Edit PMAN Directory\n");
        return;
    }

    if((strcmp(command, "-h") == 0) || (strcmp(command, "--help") == 0) || (strcmp(command, "help") == 0))
    {
        printHelp();
    }
    else if(strcmp(command, "create") == 0)
    {
        createProject(arg1, arg2, flags);
    }
    else if(strcmp(command, "delete") == 0)
    {
        deleteProject(arg1, flags);
    }
    else if(strcmp(command, "rename") == 0)
    {
        renameProject(arg1, arg2, flags);
    }
    else if(strcmp(command, "copy") == 0)
    {
        copyProject(arg1, arg2, flags);
    }
    else 
    {
        printf("\"%s\" is not a valid command\n", command);
    }
    return;
}


int main(int argc, char *argv[])
{
    int commandID = -1;
    int32_t flags = 0;
    char *arg1 = 0;
    char *arg2 = 0;
    

    if(argc == 1)
    {
        printf("No Arguments Given");
        return(0);
    }


    if(argc > 2)
    {
        for(int i = 2; i < argc; i++)
        {
            if(argv[i][0] == '-')
            {
                flags |= parseOptions(argv[i]);
            }
            else
            {
                if(arg1 == 0)
                {
                    arg1 = argv[i];
                }
                else if(arg2 == 0)
                {
                    arg2 = argv[i];
                }
            }
        }
    }

    if(arg1 == 0)
    {
        arg1 = malloc(1 * sizeof(char));
        arg1 = "";
    }
    if(arg2 == 0)
    {
        arg2 = malloc(1 * sizeof(char));
        arg2 = "";
    }

    if(chdir("/files/Projects") != 0)
    {
        printf("Failed to Change Directories\n");
        return -1;
    }
    char *cwd = (char *)malloc(100 * sizeof(char));
    getcwd(cwd, 100);

    parseCommands(argv[1], arg1, arg2, flags);

    return(0);
}
