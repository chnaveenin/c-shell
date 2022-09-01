#include "header.h"
#include "cd.h"
#include "echo.h"
#include "exec.h"
#include "ls.h"
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
        ls();
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