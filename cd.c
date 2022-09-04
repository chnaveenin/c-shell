#include "cd.h"
#include "prompt.h"

void cd(char *path) {
    int pos = allign_str(path);
    path = path + pos;

    if (strcmp(path, "-") == 0) {
        if (prev_dir) {
            chdir(prev_dir);
            commands("pwd");
            prev_dir = pr_path;
        }
        return;
    }

    else {
        getcwd(prev_dir, MAXLEN);

        if (strcmp(path, "~") == 0 || strcmp(path, "\0") == 0) {
            if (chdir(root) != 0) {
                perror("cderr");
            }
        }

        else {
            if (chdir(path) != 0) {
                perror("cderr");
            }
        }
    }
    return;
}