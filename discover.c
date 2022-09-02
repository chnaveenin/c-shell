#include "discover.h"

void discover_rec(char *path, char *file, int flag_d, int flag_f) {
    DIR *curr_dir;
    struct dirent *dir_con;

    if (path[0] == '\0') {
        path = ".";
    }

    else if (path[0] == '~') {
        strcpy(path, root);
    }

    curr_dir = opendir(path);

    if (((flag_d && flag_f) || (!flag_d && !flag_f))) {
        if (curr_dir) {
            dir_con = readdir(curr_dir);
            
            while (dir_con != NULL) {
                if (dir_con->d_name[0] != '.') {

                    if (file[0] == '\0') {
                        printf("%s/%s\n", path, dir_con->d_name);
                    }

                    else {
                        if (strcmp(file, dir_con->d_name) == 0) {
                            printf("%s/%s\n", path, dir_con->d_name);
                        }
                    }

                    if (IsDir(dir_con->d_name)) {
                        char path1[MAXLEN] = "";
                        strcpy(path1, path);
                        strcat(path1, "/");
                        strcat(path1, dir_con->d_name);

                        discover_rec(path1, file, flag_d, flag_f);
                    }
                }

                dir_con = readdir(curr_dir);
            }
            closedir(curr_dir);
        }

        else {
            perror("directory:");
        }
    }

    else if (flag_d) {
        if (curr_dir) {
            dir_con = readdir(curr_dir);
            
            while (dir_con != NULL) {
                if (dir_con->d_name[0] != '.') {
                    if (IsDir(dir_con->d_name)) {

                        if (file[0] == '\0') {
                            printf("%s/%s\n", path, dir_con->d_name);
                        }

                        else {
                            if (strcmp(file, dir_con->d_name) == 0) {
                                printf("%s/%s\n", path, dir_con->d_name);
                            }
                        }

                        char path1[MAXLEN] = "";
                        strcpy(path1, path);
                        strcat(path1, "/");
                        strcat(path1, dir_con->d_name);

                        printf("%s\n", path1);

                        discover_rec(path1, file, flag_d, flag_f);
                    }
                }
                dir_con = readdir(curr_dir);
            }
            closedir(curr_dir);
        }

        else {
            perror("directory:");
        }
    }

    else if (flag_f) {
        if (curr_dir) {
            dir_con = readdir(curr_dir);
            
            while (dir_con != NULL) {
                if (dir_con->d_name[0] != '.') {
                    if (!IsDir(dir_con->d_name)) {
                        if (file[0] == '\0') {
                            printf("%s/%s\n", path, dir_con->d_name);
                        }

                        else {
                            if (strcmp(file, dir_con->d_name) == 0) {
                                printf("%s/%s\n", path, dir_con->d_name);
                            }
                        }
                    }

                    else {
                        char path1[MAXLEN] = "";
                        strcpy(path1, path);
                        strcat(path1, "/");
                        strcat(path1, dir_con->d_name);

                        // printf("%s\n", path1);

                        discover_rec(path1, file, flag_d, flag_f);
                    }
                }
                dir_con = readdir(curr_dir);
            }
            closedir(curr_dir);
        }
        else {
            perror("directory:");
        }
    }

    return;
}

void discover(char *flags_paths) {
    char *check[3];
    check[0] = "-d";
    check[1] = "-f";

    char flags[2] = {0, 0};

    char path[MAXLEN] = "";
    char file[MAXLEN] = "";

    char *token;
    token = strtok(flags_paths, " ");

    while (token != NULL) {
        int done = 1;
        int pos = allign_str(token);
        token = token + pos;

        // printf("%s\n", token);
        
        for (int i = 0; i < 2; i++) {
            if (strcmp(token, check[i]) == 0) {
                flags[i] = 1;
                done = 0;
                break;
            }
        }

        if (done) {
            if (token[0] == '.')
                strcpy(path, token);
            else
                strcpy(file, token);
        }        
        token = strtok(NULL, " ");
    }

    // printf("%s, %s\n", path, file);
    discover_rec(path, file, flags[0], flags[1]);
    // printf("done\n");

    return;
}