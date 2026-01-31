#include <stdio.h>

void renameProject(char *oldName, char *newName) {
    
    // Unfortunately due to how the projects are structured 
    // there is no better way to do this.
    rename(oldName, newName);
    
    return;
}