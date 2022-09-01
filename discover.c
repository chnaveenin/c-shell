#include "discover.h"

void discover_rec(char *path) {
    DIR *curr_dir;
    struct dirent *dir_con;

    curr_dir = opendir(path);
    if (curr_dir) {
        dir_con = readdir(curr_dir);
        while (dir_con != NULL) {
            printf("%s/%s", path, dir_con->d_name);
            if (IsDir(dir_con->d_name)) {
                strcat(path, "/");
                strcat(path, dir_con->d_name);
                discover_rec(path);
            }

            else {
                dir_con = readdir(curr_dir);
            }
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

    char *path;
    path = ALLOC(MAXLEN);

    if (cmd == NULL) {
        discover_rec(".");
    }

    return;
}