#include <git2/global.h>
#include <git2/repository.h>
#include <git2/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <git2.h>

#include "templateUtils.h"

void writeFile(char *fileName, char *fileContents)
{
    FILE *f = fopen(fileName, "w");
    fputs(fileContents, f);
}

void createGitRepo()
{
    git_libgit2_init();

    git_repository *repo = NULL;

    if(git_repository_init(&repo, ".", 0) != 0)
    {
        printf("ERROR CREATING REPO\n");
    }

    git_signature *sig;
    git_index *index;
    git_oid tree_id, commit_id;
    git_tree *tree;

    if(git_signature_default(&sig, repo) < 0)
    {
        printf("Error creating initial commit signature\n");
    }

    if(git_repository_index(&index, repo) < 0)
    {
        printf("Error opening repo index\n");
    }

    if(git_index_write_tree(&tree_id, index) < 0)
    {
        printf("Error writing initial tree\n");
    }

    if(git_tree_lookup(&tree, repo, &tree_id))
    {
        printf("Error looking up git tree\n");
    }

    if(git_commit_create_v(&commit_id, repo, "HEAD", sig, sig, NULL, "Initial Commit", tree, 0) < 0)
    {
        printf("Error creating commit\n");
    }

    git_index_free(index);
    git_repository_free(repo);
    git_libgit2_shutdown();
}