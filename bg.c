#include "bg.h"

void store_bg_process(pid_t pid, char *cmd) {
    // bg_process_ids[no_bg_process] = pid;
    *no_bg_process = *no_bg_process + 1;
    // printf("here store %d %d %s\n", *no_bg_process, pid, cmd);
    for (int i = 0; i < MAXLEN; i++) {
        // printf("here for loop\n");
        if (bg_process_times[i] < -1) {
            bg_process_ids[i] = pid;
            bg_number[i] = *no_bg_process;
            bg_process_times[i] = -1;
            strcpy(bg_processes[i], cmd);
            // printf("stored: %d %d %s\n", bg_number[i], bg_process_ids[i], bg_processes[i]);

            break;
        }
    }
}

void check_print_process() {
    // printf("here in check\n");
    for (int i = 0; i < MAXLEN; i++) {
        if (bg_process_times[i] >= 0) {
            int exit_status;
            char status[MAXLEN];
            if (waitpid(bg_process_ids[i], &exit_status, WNOHANG) > 0) {
                if (WIFEXITED(exit_status)) 
                    strcpy(status, "normally");
                else
                    strcpy(status, "abnormally");
            }

            printf("[%d] %s process with pid: %d exited %s", bg_number[i],
                                                             bg_processes[i],
                                                             bg_process_ids[i],
                                                             status);

            if (bg_process_times[i] > 0)
                printf(" # after %d seconds\n", bg_process_times[i]);
            else
                printf("\n");
            bg_process_times[i] = -11;
        }
    }
}