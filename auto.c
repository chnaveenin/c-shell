#include "auto.h"
#include "prompt.h"

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

void autocomplete(char *command, int *pt) {
    char temp[MAXLEN];
    strcpy(temp, "");
    int j = 0;
    for (j = *pt-1; j > 0; j--) {
        if (command[j] == ' ') {
            strcpy(temp, command+j+1);
            command[j+1] = 0;
            break;
        }
    }
    
    DIR *curr_dir;
    struct dirent *dir_con;
    char files[100][MAXLEN];

    curr_dir = opendir(".");

    int i = 0;

    if (curr_dir) {
        dir_con = readdir(curr_dir);
        while (dir_con != NULL) {
            if ((dir_con->d_name[0] == '.' && temp[0] != '.'))
                ;

            else if (strncmp(temp, dir_con->d_name, strlen(temp)) == 0) {
                strcpy(files[i], dir_con->d_name);
                i++;
            }
            dir_con = readdir(curr_dir);
        }

        if (i > 1) {
            bubblesort(files, i);
            printf("\n");
            for (int run = 0; run < i; run++) {
                printf("%s\n", files[run]);
            }
        }

        char result[MAXLEN];
        if (i == 0)
            ;
 
        else if (i == 1) {
            for (int iptr = 0; iptr < strlen(files[0]); iptr++) {
                command[j+1+iptr] = files[0][iptr];
            }
            printf("%s ", command+*pt);
        }

        else {
            int en = strlen(files[0]) < strlen(files[i - 1]) ? strlen(files[0]) : strlen(files[i - 1]);
        
            char* front = files[0];
            char* rear = files[i - 1];
            int c = 0;
            while (c < en && front[c] == rear[c]) {
                command[j+1+c] = front[c];
                c++;
            }
            command[j+1+c] = 0;
            *pt = j+1+c;

            prompt(0);
            printf("%s", command);
        }
    }
}