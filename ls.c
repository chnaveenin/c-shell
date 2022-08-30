#include "ls.h"

int IsDir(char *filename) {
    struct stat check;
    stat(filename, &check);

    return S_ISDIR(check.st_mode);
}

int IsExe(char *filename) {
    struct stat check;
    stat(filename, &check);

    return S_IXUSR & (check.st_mode);
}

void bubblesort(char A[MAXLEN][MAXLEN], int size){
    int swap_count = 0;
    char temp[MAXLEN];
    if(size == 1)
        return;
    for(int i = 0; i < size-1; i++){
        if(strcmp(A[i], A[i+1]) > 0){
            strcpy(temp, A[i]);
            strcpy(A[i], A[i+1]);
            strcpy(A[i+1], temp);
            swap_count += 1;
        }
    }
    if(swap_count == 0)
        return;
    else
        bubblesort(A, size-1);
}

void ls() {
    DIR *curr_dir;
    struct dirent *dir_con;

    char files[MAXLEN][MAXLEN];

    char path[] = ".";

    curr_dir = opendir(path);

    int i = 0;

    if (curr_dir) {
        dir_con = readdir(curr_dir);
        while (dir_con != NULL) {
            strcpy(files[i], dir_con->d_name);
            dir_con = readdir(curr_dir);
            i++;
        }
        closedir(curr_dir);
    }

    else {
        perror("directory:");
    }

    bubblesort(files, i);
    
    for (int j = 0; j < i; j++) {
        if (IsDir(files[j])) {
            printf("\033[1;36m");
            printf("%s ", files[j]);
            printf("\033[0;0m");
        }

        else if (IsExe(files[j])) {
            printf("\033[31m");
            printf("%s ", files[j]);
            printf("\033[0;0m");
        }
        
        else {
            printf("%s ", files[j]);
        }
    }
    printf("\n");

    return;
}