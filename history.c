#include "history.h"

int read_last_line () {
    char line[MAXLEN], lastline[MAXLEN];
    int no_cmds = 0;

    FILE *fileptr = fopen("history.txt", "r");

    while (fscanf(fileptr, "%[^\n]s", line) > 0) {
        fgetc(fileptr);
        no_cmds++;
    }

    fclose(fileptr);

    return no_cmds;
}

void see_last_line(char lastline[]) {
    char line[MAXLEN];
    FILE *fileptr = fopen("history.txt", "r");

    while (fscanf(fileptr, "%[^\n]s", line) > 0) {
        fgetc(fileptr);
        strcpy(lastline, line);
    }

    fclose(fileptr);
}

void storeCommand (char *cmd) {
    FILE *fileptr = fopen("history.txt", "a");

    int no_cmds = read_last_line();

    char lastline[MAXLEN];
    see_last_line(lastline);

    int pos = allign_str(cmd);
    cmd = cmd + pos;

    // printf("in storeCommand: %s, %d cmd: %s\n", lastline, no_cmds, cmd);

    if (no_cmds > 0 && strcmp(lastline, cmd) == 0) {
        fclose(fileptr);
        return;
    }
    fprintf(fileptr, "%s\n", cmd);

    fclose(fileptr);

    return;
}

void printHistory () {
    FILE *fileptr = fopen("history.txt", "r");

    int no_cmds = read_last_line();

    fclose(fileptr);

    fileptr = fopen("history.txt", "r");

    // printf("noofcommands: %d\n", no_cmds);

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