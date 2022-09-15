#ifndef JOB_H
#define JOB_H

#include "header.h"

struct t_jobs {
    int pid;
    int number;
    char process[MAXLEN];
    char status;
};

typedef struct t_jobs JOB;

void jobs(char *cmd);

#endif