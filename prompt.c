#include "prompt.h"

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

void prompt() {

    char *path = ALLOC(MAXLEN);
    getcwd(path, MAXLEN);

    new_path = ALLOC(MAXLEN);

    if (strcmp(path, root) == 0) {
        new_path = "~";
    }

    else {
        if (strcmp(path, root) > 0) {
            new_path[0] = '~';
            int ptr = 1;

            for (int i = get_size(root); path[i] != '\0'; i++, ptr++) {
                new_path[ptr] = path[i];
            }

            new_path[ptr] = '\0';
        }

        else {
            getcwd(new_path, MAXLEN);
        }
    }

    printf("\033[1;36m");
    printf("<%s@%s:%s>", u_name, s_name, new_path);
    printf("\033[0;0m");
    printf(" ");

    return;
}