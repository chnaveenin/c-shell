#include "header.h"
#include "cd.h"
#include "discover.h"
#include "echo.h"
#include "exec.h"
#include "ls.h"
#include "pinfo.h"
#include "prompt.h"
#include "pwd.h"
#include "history.h"
#include "bg.h"
#include "fg.h"
#include "jobs.h"

void delay(int number_of_milli_seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + number_of_milli_seconds);
}

void commands(char *cmd, int flag) {
    if (strcmp(cmd, "exit") == 0) {
        if (*no_bg_process == 0) {
            check_print_process();
            exit(0);
        }
            
        else {
            printf("%d background processes are running, do you wish to terminate them? (y or n) ", *no_bg_process);
            char c = getchar();
            getchar();
            if (c == 'y') {
                kill(0, 0);
                exit(0);
            }
            else
                return;
        }
    }
    
    else if (strcmp(cmd, "cd") == 0 || strncmp(cmd, "cd ", sizeof("cd ")-1) == 0) {
        cd(cmd+2);
    }

    else if (strcmp(cmd, "pwd") == 0 || strncmp(cmd, "pwd ", sizeof("pwd ")-1) == 0) {
        pwd();
    }

    else if (strcmp(cmd, "echo") == 0 || strncmp(cmd, "echo ", sizeof("echo ")-1) == 0) {
        echo(cmd+4);
    }

    else if (strcmp(cmd, "ls") == 0 || strncmp(cmd, "ls ", sizeof("ls ")-1) == 0) {
        ls(cmd+2);
    }

    else if (strcmp(cmd, "pinfo") == 0 || strncmp(cmd, "pinfo ", sizeof("pinfo ")-1) == 0) {
        pinfo(cmd+5);
    }

    else if (strcmp(cmd, "discover") == 0 || strncmp(cmd, "discover ", sizeof("discover ")-1) == 0) {
        discover(cmd+8);
    }

    else if (strcmp(cmd, "history") == 0) {
        printHistory();
    }

    else if (strcmp(cmd, "jobs") == 0 || strncmp(cmd, "jobs ", sizeof("jobs ")-1) == 0) {
        jobs(cmd+4);
    }

    else if (strncmp(cmd, "fg ", sizeof("fg ")-1) == 0) {
        fg(cmd+2);
    }

    else if (strncmp(cmd, "bg ", sizeof("bg ")-1) == 0) {
        bg(cmd+2);
    }

    else if (strncmp(cmd, "sig ", sizeof("sig ")-1) == 0) {
        sig(cmd+3);
    }

    else {
        int i = 0;

        char *token[MAXLEN];
        token[i] = strtok(cmd, " ");

        while (token[i] != NULL) {
            int pos = allign_str(token[i]);
            token[i] = token[i] + pos;

            i++;
            token[i] = strtok(NULL, " ");
        }

        if (flag) {
            int pid = fork();
            if (pid == 0) {
                if (execvp(token[0], token) < 0)
                    printf("cmd: no such command\n");
                exit(0);
            }
            else {
                int status;
                proc = pid;
                proc_cmd = token[0];
                waitpid(pid, &status, WUNTRACED);
            }
        }

        else {
            if (execvp(token[0], token) < 0)
                printf("cmd: no such command\n");
            exit(0);
        }
    }
    return;
}

void sigint_handle();
void sigtstp_handle();

void shell() {
    while (1) {
        prompt(curr_sec-prev_sec);
        x_command();
        time(&curr_sec);
        check_print_process();
    }
}

void sigint_handle() {
    if (proc > 0) {
        kill(proc, SIGKILL);
        proc = -1;
    }
    printf("\n");
    return;
}

void sigtstp_handle() {
    if (proc > 0) {
        int retval = fork();
        if (retval == 0) {
            pid_t pgid = getpgid(getpid());
            setpgid(proc, pgid);
            kill(proc, SIGSTOP);
            exit(0);
        }
        else {
            store_bg_process(proc, proc_cmd);
            printf("\n[%d] %d\n", *no_bg_process, proc);
            proc = -1;
            return;
        }
    }
    return;
}

int main() {
    s_name = ALLOC(MAXLEN);
    root = ALLOC(MAXLEN);
    prev_dir = ALLOC(MAXLEN);
    
    u_name = getlogin();
    if (gethostname(s_name, MAXLEN) < 0)
        perror("hostname too large");
    getcwd(root, MAXLEN);

    proc = -1;
    int no_bg = 0;
    int max_no_count = 0;
    no_bg_process = &no_bg;

    bg_process_ids = mmap(NULL, sizeof *bg_process_ids, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    bg_processes = mmap(NULL, MAXLEN*MAXLEN, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    bg_process_times = mmap(NULL, sizeof *bg_process_times, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    bg_number = mmap(NULL, sizeof *bg_number, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    no_bg_process = mmap(NULL, sizeof *no_bg_process, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < MAXLEN; i++) {
        bg_process_times[i] = -11;
        strcpy(bg_processes[i], "process");
        bg_processes[i][0] = 'p';
        bg_processes[i][1] = '\0';
    }

    printf("welcome to naveen's custom c-shell\n");
    signal(SIGINT, sigint_handle);
    signal(SIGTSTP, sigtstp_handle);

    shell();

    return 0;
}