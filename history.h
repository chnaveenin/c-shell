#ifndef HIS_H
#define HIS_H

#include "header.h"

struct his {
    char *cmd;
    int no_cmds;
};

void storeCommand(char *cmd);
void printHistory();

#endif