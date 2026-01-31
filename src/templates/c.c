#include <sys/stat.h>

#include "templateUtils.c"

char *buildScriptText = 
"#!/usr/bin/bash"
"\n"
"gcc ./src/main.c -o ./bin/main -g";

char *gitIgnoreText = 
"/bin"
"/obj"
"/.vscode";

void templateC() 
{
    writeFile("build", buildScriptText);
    writeFile(".gitignore", gitIgnoreText);
    

    mkdir("bin", 0777);
    mkdir("obj", 0777);
    mkdir("src", 0777);
}