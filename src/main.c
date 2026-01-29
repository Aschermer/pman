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

// 32 bit flags
enum OPTIONFLAGS{
    NONE = 0x0000
};

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

void renameProject(char *oldName, char *newName) {
    
    // Unfortunately due to how the projects are structured 
    // there is no better way to do this.
    rename(oldName, newName);
    
    return;
}

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

int parseOptions(char *arg)
{
    return(0);
}

void parseCommands(char *command, uint32_t optionBits, char *option1, char *option2)
{
    for(int i = 0; command[i] != '\0'; i++)
    {
        command[i] = tolower(command[i]);
    }

    printf("Parsed Command: %s\n", command);
    printf("Option1: %s\n", option1);
    printf("Option2: %s\n", option2);

    if((strcmp(option1, "pman") == 0) || (strcmp(option2, "pman") == 0))
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
        createProject(option1, option2);
    }
    else if(strcmp(command, "delete") == 0)
    {
        deleteProject(option1);
    }
    else if(strcmp(command, "rename") == 0)
    {
        renameProject(option1, option2);
    }
    else if(strcmp(command, "copy") == 0)
    {
        copyProject(option1, option2);
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
    int32_t optionBits = 0;
    char *option1 = 0;
    char *option2 = 0;
    

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
                optionBits = optionBits | parseOptions(argv[i]);
                printf("Parsed Option: %s\n", argv[i]);
            }
            else
            {
                if(option1 == 0)
                {
                    option1 = argv[i];
                    printf("Parsed Option1: %s\n", option1);
                }
                else if(option2 == 0)
                {
                    option2 = argv[i];
                    printf("Parsed Option2: %s\n", option2);
                }
            }
        }
    }

    if(option1 == 0)
    {
        option1 = malloc(1 * sizeof(char));
        option1 = "";
        printf("Defaulted Option1\n");
    }
    if(option2 == 0)
    {
        option2 = malloc(1 * sizeof(char));
        option2 = "";
        printf("Defaulted Option2\n");
    }

    if(chdir("/files/Projects") != 0)
    {
        printf("Failed to Change Directories\n");
        return -1;
    }
    char *cwd = (char *)malloc(100 * sizeof(char));
    getcwd(cwd, 100);
    printf("Set Directory to: %s\n", cwd);

    parseCommands(argv[1], optionBits, option1, option2);

    return(0);
}
