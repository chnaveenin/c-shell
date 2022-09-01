#include "ls.h"

void ls(char *flags) {
    DIR *curr_dir;
    struct dirent *dir_con;

    char files[MAXLEN][MAXLEN];
    char *path;

    path = ALLOC(MAXLEN);

    if (flags) {
        int pos = allign_str(flags);
        flags = flags + pos;

        if (strcmp(flags, "-l") == 0) {
            path = ".";
        }

        else if (strcmp(flags, "-a") == 0) {
            path = ".";
            curr_dir = opendir(path);

            int i = 0;

            if (curr_dir) {
                dir_con = readdir(curr_dir);
                while (dir_con != NULL) {
                    strcpy(files[i], dir_con->d_name);
                    dir_con = readdir(curr_dir);
                    i++;
                }
                closedir(curr_dir);
            }

            else {
                perror("directory:");
            }

            bubblesort(files, i);
            
            for (int j = 0; j < i; j++) {
                if (IsDir(files[j])) {
                    printf("\033[1;36m");
                    printf("%s ", files[j]);
                    printf("\033[0;0m");
                }

                else if (IsExe(files[j])) {
                    printf("\033[31m");
                    printf("%s ", files[j]);
                    printf("\033[0;0m");
                }
                
                else {
                    printf("%s ", files[j]);
                }
            }
            printf("\n");
        }
    }

    else {
        path = ".";
        curr_dir = opendir(path);

        int i = 0;

        if (curr_dir) {
            dir_con = readdir(curr_dir);
            while (dir_con != NULL) {
                if (dir_con->d_name[0] != '.') {
                    strcpy(files[i], dir_con->d_name);
                    dir_con = readdir(curr_dir);
                    i++;
                }
            }
            closedir(curr_dir);
        }

        else {
            perror("directory:");
        }

        bubblesort(files, i);
    
        for (int j = 0; j < i; j++) {
            if (IsDir(files[j])) {
                printf("\033[1;36m");
                printf("%s ", files[j]);
                printf("\033[0;0m");
            }

            else if (IsExe(files[j])) {
                printf("\033[31m");
                printf("%s ", files[j]);
                printf("\033[0;0m");
            }
            
            else {
                printf("%s ", files[j]);
            }
        }
        printf("\n");
    }
}