#ifndef BG_H
#define BG_H

#include "header.h"

void store_bg_process(pid_t pid, char *cmd);
void check_print_process();
void bg(char *cmd);
int  get_pid_bg (int number);
void sig(char *cmd);

#endif