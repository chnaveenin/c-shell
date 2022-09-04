#include "pinfo.h"

void pinfo(char *id) {
    int pos = allign_str(id);
    id = id+pos;

    char real_path[MAXLEN];

    int pid, pgrp, tpgid, memory;
    char status;

    char path[MAXLEN];
    strcpy(path, "/proc/");

    if (id[0] != '\0') {
        // printf("here");
        strcat(path, id);
    }

    else {
        // printf("here");
        strcat(path, "self");
    }

    strcat(path, "/stat");

    FILE *stat = fopen(path, "r");

    if (stat) {
        fscanf(stat,
           "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s "
           "%*s %*s %*s %*s %*s %d",
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

    return;
}