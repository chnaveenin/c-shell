#ifndef HEAD_H
#define HEAD_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>

#define MAXLEN 1024
#define ALLOC(x) (char *)malloc(x+1)

char *u_name, *s_name, *root, *curr;
char *prev_dir;

int get_size(char *path);

int allign_str(char *message);

void commands(char *cmd);

int IsDir(char *filename);

int IsExe(char *filename);

#endif