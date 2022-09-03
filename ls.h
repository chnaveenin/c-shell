#ifndef LS_H
#define LS_H

#include "header.h"

struct ls_directory {
    char df_name[MAXLEN];
    char flags[11];
    char usr_name[MAXLEN];
    char grp_name[MAXLEN];
    int  no_links;
    int  no_bytes;
    char mod_date[13];
};

typedef struct ls_directory D_I_R;

void ls(char *flags);

#endif