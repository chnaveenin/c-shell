#include "pinfo.h"

void pinfo(char *id) {
    int pos = allign_str(id);
    id = id+pos;

    char real_path[MAXLEN];

    int pid, pgrp, tpgid, memory;
    char status;

    char path[MAXLEN];
    char file[MAXLEN];

    char exe_path[MAXLEN];

    strcpy(path, "/proc/");

    if (id[0] != '\0') {
        strcat(path, id);
    }

    else {
        strcat(path, "self");
    }

    strcpy(file, path);
    strcat(file, "/stat");

    FILE *stat = fopen(file, "r");

    if (stat) {
        fscanf(stat,
           "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d",
            &pid, &status, &pgrp, &tpgid, &memory);

        char bf_flag = ' ';
        if (pgrp == tpgid)
            bf_flag = '+';
        
        printf("pid : %d\nstatus : %c%c\nmemory: %d\n", pid, status, bf_flag, memory);
    }

    else {
        perror("stat");
        return;
    }

    fclose(stat);

    strcpy(file, path);
    strcat(file, "/exe");

    printf("%s\n", file);

    int size = readlink(file, exe_path, 1023);
    exe_path[size] = '\0';

    char rel_exe_path[MAXLEN];

    if (strncmp(exe_path, root, get_size(root)-1) == 0) {
        rel_exe_path[0] = '~';
        int ptr = 1;

        for (int i = get_size(root); exe_path[i] != '\0'; i++, ptr++) {
            rel_exe_path[ptr] = exe_path[i];
        }

        rel_exe_path[ptr] = '\0';
        printf("executable path : %s\n", rel_exe_path);
    }

    else {
        printf("executable path : %s\n", exe_path);
    }

    return;
}