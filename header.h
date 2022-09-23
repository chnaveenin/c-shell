#ifndef HEAD_H
#define HEAD_H

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/utsname.h>

#define MAXLEN 1024
#define ALLOC(x) (char *)malloc(x+1)

char *u_name, *s_name, *root, *curr;
char *prev_dir;

int *no_bg_process;
int *bg_process_ids;
char (*bg_processes)[MAXLEN];
int *bg_process_times;
int *bg_number;

int  proc;
char *proc_cmd;

time_t prev_sec, curr_sec;

int get_size(char *path);

int allign_str(char *message);

void commands(char *cmd, int flag);

int IsDir(char *filename);

int IsExe(char *filename);

#endif