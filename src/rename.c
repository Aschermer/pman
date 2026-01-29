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

void renameProject(char *oldName, char *newName) {
    
    // Unfortunately due to how the projects are structured 
    // there is no better way to do this.
    rename(oldName, newName);
    
    return;
}