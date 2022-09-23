#include "bg.h"

#define INF 11111

int get_pid_bg (int number) {
    for (int i = 0; i < MAXLEN; i++) {
        if (bg_number[i] == number && bg_process_times[i] == -1)
            return bg_process_ids[i];
    }
    return -1;
}

void store_bg_process(pid_t pid, char *cmd) {
    *no_bg_process = *no_bg_process + 1;
    for (int i = 0; i < MAXLEN; i++) {
        if (bg_process_times[i] < -1) {
            bg_process_ids[i] = pid;
            bg_number[i] = *no_bg_process;
            bg_process_times[i] = -1;
            char temp[MAXLEN];
            int j = 0;
            while (cmd[j] != ' ') {
                temp[j] = cmd[j];
                j++;
            }
            temp[j] = '\0';
            strcpy(bg_processes[i], cmd);

            break;
        }
    }
}

void check_print_process() {
    for (int i = 0; i < MAXLEN; i++) {
        int exit_status;
        if (((bg_process_ids[i] > 0) && (bg_process_times[i] >= 0)) || ((waitpid(bg_process_ids[i], &exit_status, WNOHANG) > 0) && bg_process_times[i] == -1)) {
            char status[MAXLEN];
            if (WIFEXITED(exit_status)) 
                strcpy(status, "normally");
            else
                strcpy(status, "abnormally");

            printf("[%d] %s process with pid: %d exited %s", bg_number[i],
                                                             bg_processes[i],
                                                             bg_process_ids[i],
                                                             status);

            if (bg_process_times[i] > 0)
                printf("\n");
                // printf(" # after %d seconds\n", bg_process_times[i]);
            else {
                bg_process_times[i] = INF;
                if (bg_number[i] == *no_bg_process) {
                    int max_num  = -1;
                    for (int j = 0; j < MAXLEN; j++)
                        if (bg_process_times[j] == -1)
                            if (max_num < bg_number[j])
                                max_num = bg_number[j];

                    if (max_num > 0)
                        *no_bg_process = max_num;
                    else
                        *no_bg_process = 0;
                }
                printf("\n");
            }

            bg_process_times[i] = -11;
        }
    }
}

void bg(char *cmd) {
    int pos = allign_str(cmd);
    cmd = cmd + pos;

    int number = atoi(cmd);

    int pid = get_pid_bg(number);
    if (pid > 0) {
        if (kill(pid, SIGCONT) < 0)
            perror("bg");
    }
    else
        printf("bg: no such process\n");
}

void sig(char *cmd) {
    int pos = allign_str(cmd);
    cmd = cmd + pos;

    char *num = strtok(cmd, " ");
    char *sig = strtok(NULL, " ");

    pos = allign_str(num);
    num = num + pos;

    pos = allign_str(sig);
    sig = sig + pos;

    if (num == NULL || sig == NULL) {
        printf("cmd: invalid usage");
        return;
    }

    int i_sig = atoi(sig);
    int i_num = atoi(num);
    int pid = get_pid_bg(i_num);

    if (pid > 0) {           
        if (kill(pid, i_sig) < 0) {
            perror("kill");
        }
    }

    else
        printf("bg: no such process\n");

    return;
}