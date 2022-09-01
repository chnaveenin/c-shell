#include "discover.h"

void discover_rec(char *path) {
    DIR *curr_dir;
    struct dirent *dir_con;

    curr_dir = opendir(path);

    if (curr_dir) {
        dir_con = readdir(curr_dir);

        if (strncmp(dir_con->d_name, ".", 1) != 0) {
            printf("%s/%s\n", path, dir_con->d_name);
        }

        while (dir_con != NULL) {
            if (strncmp(dir_con->d_name, ".", 1) != 0) {
                printf("%s/%s\n", path, dir_con->d_name);

                // printf("%d\n", IsDir(dir_con->d_name));

                if (IsDir(dir_con->d_name)) {
                    char path1[MAXLEN] = "";
                    strcpy(path1, path);
                    strcat(path1, "/");
                    strcat(path1, dir_con->d_name);
                    printf("path1 = %s\n", path1);
                    discover_rec(path1);
                }
            }

            dir_con = readdir(curr_dir);
        }
        closedir(curr_dir);
    }

    else {
        perror("directory:");
    }

    return;
}

void discover(char *cmd) {
    int pos = allign_str(cmd);
    cmd = cmd + pos;

    char path[MAXLEN];
    path[0] = '\0';

    if (cmd[0] == '\0')
        strcat(path, ".");
    else
        strcpy(path, cmd);
    printf("%s\n", path);

    discover_rec(path);

    return;
}