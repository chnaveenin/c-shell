#include "history.h"

int read_last_line () {
    char line[MAXLEN], lastline[MAXLEN];
    int no_cmds = 0;

    char fpath[MAXLEN];
    strcpy(fpath, root);
    strcat(fpath, "/history.txt");

    FILE *fileptr = fopen(fpath, "r");

    while (fscanf(fileptr, "%[^\n]s", line) > 0) {
        fgetc(fileptr);
        no_cmds++;
    }

    fclose(fileptr);

    return no_cmds;
}

void see_last_line(char lastline[]) {
    char line[MAXLEN];

    char fpath[MAXLEN];
    strcpy(fpath, root);
    strcat(fpath, "/history.txt");

    FILE *fileptr = fopen(fpath, "r");

    while (fscanf(fileptr, "%[^\n]s", line) > 0) {
        fgetc(fileptr);
        strcpy(lastline, line);
    }

    fclose(fileptr);
}

void storeCommand (char *cmd) {
    if (cmd[0] == '\n')
        return;

    char fpath[MAXLEN];
    strcpy(fpath, root);
    strcat(fpath, "/history.txt");

    FILE *fileptr = fopen(fpath, "a");

    int no_cmds = read_last_line();

    char lastline[MAXLEN];
    see_last_line(lastline);

    int pos = allign_str(cmd);
    cmd = cmd + pos;

    if (no_cmds > 0 && strcmp(lastline, cmd) == 0) {
        fclose(fileptr);
        return;
    }

    else if (no_cmds == 20) {
        char hist_arr[20][MAXLEN];
        strcpy(hist_arr[19], cmd);

        char temp[MAXLEN];
        fclose(fileptr);
        
        fileptr = fopen(fpath, "r");
        fscanf(fileptr, "%[^\n]s", temp);
        fgetc(fileptr);
        for (int i = 0; i < 19; i++) {
            fscanf(fileptr, "%[^\n]s", hist_arr[i]);
            fgetc(fileptr);
        }
        fclose(fileptr);

        fileptr = fopen(fpath, "w");
        for (int i = 0; i < 20; i++) {
            fprintf(fileptr, "%s\n", hist_arr[i]);
        }

        fclose(fileptr);
    }

    else {
        fprintf(fileptr, "%s\n", cmd);
        fclose(fileptr);
    }

    return;
}

void printHistory () {
    char fpath[MAXLEN];
    strcpy(fpath, root);
    strcat(fpath, "/history.txt");

    FILE *fileptr = fopen(fpath, "r");

    int no_cmds = read_last_line();

    fclose(fileptr);

    strcpy(fpath, root);
    strcat(fpath, "/history.txt");

    fileptr = fopen(fpath, "r");

    char line[MAXLEN];

    if (no_cmds > 10) {
        for(int i = 0; i < no_cmds-10; i++) {
            fscanf(fileptr, "%[^\n]s", line);
            fgetc(fileptr);
        }
        while (fscanf(fileptr, "%[^\n]s", line) > 0) {
            fgetc(fileptr);
            printf("%s\n", line);
        }
    }

    else {
        for (int i = 0; i < no_cmds; i++) {
            fscanf(fileptr, "%[^\n]s", line);
            fgetc(fileptr);
            printf("%s\n", line);
        }
    }

    fclose(fileptr);

    return;
}