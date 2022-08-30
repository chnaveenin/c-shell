#include "pwd.h"

void pwd() {
    char *path = ALLOC(MAXLEN);
    getcwd(path, MAXLEN);

    printf("%s\n", path);
    return;
}