#include "jobs.h"
#include "bg.h"

int compare_jobs (const void * a, const void * b) {

  JOB *fileA = (JOB *)a;
  JOB *fileB = (JOB *)b;

  return ( strcmp(fileA->process, fileB->process) );
}

char get_status(int pid) {
    char status;
    char path[MAXLEN];

    strcpy(path, "/proc/");
    
    char id[12];

    sprintf(id, "%d", pid);
    strcat(path, id);
    strcat(path, "/stat");

    FILE *stat = fopen(path, "r");

    if (stat) {
        fscanf(stat, "%*d %*s %c", &status);
    }

    else {
        perror("stat");
    }

    return status;
}

void jobs(char *cmd) {
    check_print_process();
    int pos = allign_str(cmd);
    cmd = cmd + pos;

    int flag[3] = {0, 0, 0};

    if (cmd[0] == '\0') {
        flag[0] = 1;
    }

    else if (strcmp(cmd, "-r") == 0) {
        flag[1] = 1;
    }

    else if (strcmp(cmd, "-s") == 0) {
        flag[2] = 1;
    }

    JOB arr[MAXLEN];
    JOB temp;
    int ptr = 0;

    for (int i = 0; i < MAXLEN; i++) {
        if (bg_process_times[i] == -1) {
            temp.number  = bg_number[i];
            temp.pid     = bg_process_ids[i];
            strcpy(temp.process, bg_processes[i]);
            temp.status  = get_status(temp.pid);

            if (flag[0] == 1) {
                arr[ptr] = temp;
                ptr++;
            }

            else if (flag[1] && temp.status != 'T') {
                arr[ptr] = temp;
                ptr++;
            }

            else if (flag[2] && temp.status == 'T') {
                arr[ptr] = temp;
                ptr++;
            }
        }
    }

    qsort(arr, ptr, sizeof(JOB), compare_jobs);

    for (int i = 0; i < ptr; i++) {
        char *st;
        st = (arr[i].status == 'T') ? "Stopped" : "Running";
        printf("[%d] %s %s [%d]\n", arr[i].number, st, arr[i].process, arr[i].pid);
    }

    return;
}