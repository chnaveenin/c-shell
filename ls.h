#ifndef LS_H
#define LS_H

#include "header.h"

struct ls_directory {
    char *df_name;
    char flags[9];
    char *usr_name;
    char *grp_name;
    int  no_links;
    int  no_bytes;
    char *modifed_date;
};

typedef struct ls_directory D_I_R;

void ls(char *flags);

#endif