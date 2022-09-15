#include "fg.h"
#include "bg.h"

#define INF 11111

void fg(char *cmd) {
    pid_t pid;
    cmd = strtok(cmd, " ");
    char *temp = strtok(NULL, " ");
    if (temp != NULL) {
        printf("cmd: invalid usage\n");
        return;
    }

    int num = atoi(cmd);
    pid = get_pid_bg(num);

    if (pid == -1) {
        perror("fg");
        return;
    }

    setpgid(pid, getpgid(0));

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(0, pid);

    if (kill(pid, SIGCONT) < 0)
        perror("kill");

    for (int i = 0; i < MAXLEN; i++) {
        if (bg_process_ids[i] == pid) {
            bg_process_ids[i] = -1;
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
        }
    }

    waitpid(pid, NULL, WUNTRACED);

    tcsetpgrp(0, getpgid(0));

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    return;
}