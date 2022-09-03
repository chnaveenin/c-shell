#include "ls.h"

int compare (const void * a, const void * b) {

  D_I_R *fileA = (D_I_R *)a;
  D_I_R *fileB = (D_I_R *)b;

  return ( strcmp(fileA->df_name, fileB->df_name) );
}

void printD_I_R(D_I_R *file, int flag_a, int flag_l, int count) {

    for (int i = 0; i < count; i++) {
        if (flag_l && flag_a) {
            printf("%s %3d %6d %s ", file[i].flags, file[i].no_links, file[i].no_bytes, file[i].mod_date);
            if (file[i].flags[0] == 'd') {
                printf("\033[1;36m");
                printf("%s\n", file[i].df_name);
                printf("\033[0;0m");
            }

            else if (file[i].flags[3] == 'x') {
                printf("\033[31m");
                printf("%s\n", file[i].df_name);
                printf("\033[0;0m");
            }
            
            else {
                printf("%s\n", file[i].df_name);
            }
        }

        else if (flag_l) {
            if (file[i].df_name[0] == '.')
                continue;
            printf("%s %3d %6d %s ", file[i].flags, file[i].no_links, file[i].no_bytes, file[i].mod_date);
            if (file[i].flags[0] == 'd') {
                printf("\033[1;36m");
                printf("%s\n", file[i].df_name);
                printf("\033[0;0m");
            }

            else if (file[i].flags[3] == 'x') {
                printf("\033[31m");
                printf("%s\n", file[i].df_name);
                printf("\033[0;0m");
            }
            
            else {
                printf("%s\n", file[i].df_name);
            }
        }
    
        else if (flag_a) {
            if (file[i].flags[0] == 'd') {
                printf("\033[1;36m");
                printf("%s\n", file[i].df_name);
                printf("\033[0;0m");
            }

            else if (file[i].flags[3] == 'x') {
                printf("\033[31m");
                printf("%s\n", file[i].df_name);
                printf("\033[0;0m");
            }
            
            else {
                printf("%s\n", file[i].df_name);
            }
        }

        else {
            if (file[i].df_name[0] == '.')
                continue;
            if (file[i].flags[0] == 'd') {
                printf("\033[1;36m");
                printf("%s\n", file[i].df_name);
                printf("\033[0;0m");
            }

            else if (file[i].flags[3] == 'x') {
                printf("\033[31m");
                printf("%s\n", file[i].df_name);
                printf("\033[0;0m");
            }
            
            else {
                printf("%s\n", file[i].df_name);
            }
        }
    }
}

void storeflags(D_I_R *file, struct stat buffer) {

    file->flags[0] = (S_ISDIR(buffer.st_mode))  ? 'd' : '-';
    file->flags[1] = (buffer.st_mode & S_IRUSR) ? 'r' : '-';
    file->flags[2] = (buffer.st_mode & S_IWUSR) ? 'w' : '-';
    file->flags[3] = (buffer.st_mode & S_IXUSR) ? 'x' : '-';
    file->flags[4] = (buffer.st_mode & S_IRGRP) ? 'r' : '-';
    file->flags[5] = (buffer.st_mode & S_IWGRP) ? 'w' : '-';
    file->flags[6] = (buffer.st_mode & S_IXGRP) ? 'x' : '-';
    file->flags[7] = (buffer.st_mode & S_IROTH) ? 'r' : '-';
    file->flags[8] = (buffer.st_mode & S_IWOTH) ? 'w' : '-';
    file->flags[9] = (buffer.st_mode & S_IXOTH) ? 'x' : '-';
    file->flags[10] = '\0';

    file->no_bytes = buffer.st_size;
    file->no_links = buffer.st_nlink;

    struct tm dt;
    char mon[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    dt = *(localtime(&buffer.st_mtime));

    strcpy(file->mod_date, mon[dt.tm_mon]);
    strcat(file->mod_date, " ");

    if (dt.tm_mday < 10) {
        strcat(file->mod_date, " ");
    }

    char temp[10];

    sprintf(temp, "%d", dt.tm_mday);
    strcat(file->mod_date, temp);
    strcat(file->mod_date, " ");

    if (dt.tm_hour < 10) {
        strcat(file->mod_date, "0");
    }

    sprintf(temp, "%d", dt.tm_hour);
    strcat(file->mod_date, temp);
    strcat(file->mod_date, ":");

    if (dt.tm_min < 10) {
        strcat(file->mod_date, "0");
    }

    sprintf(temp, "%d", dt.tm_min);
    strcat(file->mod_date, temp);

    file->mod_date[12] = '\0'; 

    return;
}

void ls_print(char *paths[], int flag_a, int flag_l, int no_paths) {
    if (no_paths == 0) {
        no_paths = 1;
        paths[0] = ".";
    }

    // printf("here1\n");
    int doing = 0;

    while(doing < no_paths) {
        if (doing > 0)
            printf("\n");
        
        DIR *curr_dir;
        struct dirent *dir_con;

        if (no_paths > 1)
            printf("%s:\n", paths[doing]);
        int total = 0;

        curr_dir = opendir(paths[doing]);

        int i = 0;
        D_I_R files[MAXLEN];

        // printf("here2\n");

        if (curr_dir) {
            dir_con = readdir(curr_dir);

            // printf("here3\n");
            while (dir_con != NULL) {

                strcpy(files[i].df_name, dir_con->d_name);
                // printf("%d: %s\n", i+1, files[i].df_name);

                struct stat buffer;

                char pathforfile[MAXLEN];
                strcpy(pathforfile, paths[doing]);
                strcat(pathforfile, "/");
                strcat(pathforfile, files[i].df_name);

                stat(pathforfile, &buffer);

                storeflags(&files[i], buffer);

                dir_con = readdir(curr_dir);
                i++;

                if (flag_a == 0) {
                    if (files[i].df_name[0] == '.') {
                        continue;
                    }
                }
                total += buffer.st_blocks;
            }
        }
        qsort(files, i, sizeof(D_I_R), compare);
        if (flag_l)
            printf("total: %d\n", total);
        printD_I_R(files, flag_a, flag_l, i);

        doing++;
    }
}

void ls(char *flags_paths) {
    char *check[4];
    check[0] = "-la";
    check[1] = "-a";
    check[2] = "-l";
    check[3] = "-al";

    char flags[4] = {0, 0, 0, 0};

    char *paths[MAXLEN];

    int no_paths = 0;

    char *token;
    token = strtok(flags_paths, " ");

    while (token != NULL) {
        int pos = allign_str(token);
        token = token + pos;

        int flagorpath = 1;
        
        for (int i = 0; i < 4; i++) {
            if (strcmp(token, check[i]) == 0) {
                flags[i] = 1;
                flagorpath = 0;
                break;
            }
        }

        if (flagorpath) {
            // strcpy(paths[no_paths], token);
            paths[no_paths] = token;
            no_paths++;
        }

        token = strtok(NULL, " ");
    }

    if (flags[0] == 1 || flags[3] == 1) {
        flags[1] = 1;
        flags[2] = 1;
    }

    // printf("%d\n", no_paths);
    // for (int i = 0; i < no_paths; i++)
    //     printf("%s\n", paths[i]);

    ls_print(paths, flags[1], flags[2], no_paths);

    return;
}