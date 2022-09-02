#include "ls.h"

// void ls_print(char *paths[], int flag_a, int flag_l, int no_paths) {
//     if (no_paths == 0) {
//         no_paths = 1;
//         paths[0] = ".";
//     }

//     while(no_paths--) {
//         D_I_R files[MAXLEN];
//         paths[no_paths];
//     }
// }

void ls(char *flags_paths) {
    char *check[3];
    check[0] = "-la";
    check[1] = "-a";
    check[2] = "-l";

    char flags[3] = {0, 0, 0};

    char *paths[MAXLEN];

    int no_paths = 0;

    char *token;
    token = strtok(flags_paths, " ");

    while (token != NULL) {
        int pos = allign_str(token);
        token = token + pos;
        
        for (int i = 0; i < 3; i++) {
            if (strcmp(token, check[i]) == 0) {
                flags[i] = 1;
                break;
            }
        }

        if (!flags[0] && !flags[1] && !flags[2]) {
            paths[no_paths] = token;
            no_paths++;
        }

        token = strtok(NULL, " ");
    }

    if (flags[0] || (flags[1] && flags[2])) {
        // implement ls -al paths
    }

    else if (flags[1]) {
        // implement ls -a paths
    }

    else if (flags[2]) {
        // implement ls -l paths
    }

    return;
}