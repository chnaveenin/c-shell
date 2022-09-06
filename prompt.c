#include "prompt.h"

int IsDir(char *filename) {
    struct stat check;
    stat(filename, &check);

    return S_ISDIR(check.st_mode);
}

int IsExe(char *filename) {
    struct stat check;
    stat(filename, &check);

    return S_IXUSR & (check.st_mode);
}

int get_size(char *path) {
    int size = 0;
    for (; path[size] != '\0'; size++);
    return size;
}

int allign_str(char *message) {
    int i = 0;
    while(message[i] == ' ' || message[i] == '\t') {
        i++;
    }

    if (message[i] == 34 || message[i] == 39) {
        i++;
        message[get_size(message)-1] = '\0';
    }

    while(message[get_size(message)-1] == ' ' | message[get_size(message)-1] == '\n') {
        message[get_size(message)-1] = '\0';
    }

    return i;
}

void prompt(time_t time_gap) {

    pr_path = ALLOC(MAXLEN);
    getcwd(pr_path, MAXLEN);

    new_path = ALLOC(MAXLEN);

    if (strcmp(pr_path, root) == 0) {
        new_path = "~";
    }

    else {
        char temp[MAXLEN];
        strcpy(temp, root);
        strcat(temp, "/");
        if (strncmp(pr_path, temp, get_size(temp)) == 0) {
            new_path[0] = '~';
            int ptr = 1;

            for (int i = get_size(temp)-1; pr_path[i] != '\0'; i++, ptr++) {
                new_path[ptr] = pr_path[i];
            }

            new_path[ptr] = '\0';
        }

        else {
            getcwd(new_path, MAXLEN);
        }
    }
    
    char time_str[MAXLEN];

    if (time_gap > 0) {
        sprintf(time_str, "took%lds", time_gap);
    }
    else
        strcpy(time_str, "");

    printf("\033[1;36m");
    printf("<%s@%s:", u_name, s_name);
    printf("\033[0;0m");
    printf("\033[1;31m");
    printf("%s%s>", new_path, time_str);
    printf("\033[0;0m");
    printf(" ");

    return;
}