#include <git2/global.h>
#include <git2/repository.h>
#include <git2/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <git2.h>

void writeFile(char *fileName, char *fileContents)
{
    FILE *f = fopen(fileName, "w");
    fputs(fileContents, f);
}

void defaultTemplate(char *name)
{
    mkdir(name, 0777);
    chdir(name);

    git_libgit2_init();

    git_repository *repo = NULL;

    if(git_repository_init(&repo, ".", 0) != 0)
    {
        printf("ERROR CREATING REPO\n");
    }

    git_repository_free(repo);
    git_libgit2_shutdown();

}