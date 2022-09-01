#include "pinfo.h"

void pinfo(char *id) {
    int pos = allign_str(id);
    id = id+pos;

    if (id) {
        int pid = atoi(id);
        printf("%d\n", pid);
    }

    else {
        printf("%d\n", getpid());
    }
    return;
}