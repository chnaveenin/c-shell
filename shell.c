#include "header.h"
#include "cd.h"
#include "discover.h"
#include "echo.h"
#include "exec.h"
#include "ls.h"
#include "pinfo.h"
#include "prompt.h"
#include "pwd.h"

void commands(char *cmd) {
    if (strcmp(cmd, "exit") == 0)
        exit(0);
    
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

        int pid = fork();
            if (pid == 0)
                execvp(token[0], token);
            else
                wait(0);
    }

    return;
}

void shell() {
    while (1) {
        prompt();
        x_command();
    }
}

int main() {
    s_name = ALLOC(MAXLEN);
    root = ALLOC(MAXLEN);
    prev_dir = ALLOC(MAXLEN);
    
    u_name = getlogin();
    if (gethostname(s_name, MAXLEN) < 0)
        perror("hostname too large");
    getcwd(root, MAXLEN);

    shell();

    return 0;
}