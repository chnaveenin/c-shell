#include "header.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "prompt.h"
#include "pwd.h"

void commands(char *cmd) {
    if (strcmp(cmd, "exit") == 0)
        exit(0);
    
    else if (strncmp(cmd, "cd", sizeof("cd")-1) == 0) {
        cd(cmd+2);
    }

    else if (strncmp(cmd, "pwd", sizeof("pwd")-1) == 0) {
        pwd();
    }

    else if (strncmp(cmd, "echo", sizeof("echo")-1) == 0) {
        printf("%s\n", cmd);
        echo(cmd+4);
    }

    else if (strncmp(cmd, "ls", sizeof("ls")-1) == 0) {
        ls();
    }

    return;
}

void shell() {
    while (1) {
        
        prompt();

        char command[MAXLEN];

        int j;
        for (j = 0; j < MAXLEN; j++) {
            char c = getchar();
            if (c == '\n') {
                break;
            }
            command[j] = c;
        }
        command[j]='\0';

        int i;
        if (strcmp(command, "") != 0) {
            i = 0;
            char **token;
            token = (char **)malloc(MAXLEN * sizeof(char *));
            token[i] = strtok(command, "&");
            while( token[i] != NULL ) {
                i++;
                token[i] = strtok(NULL, "&");
            }

            int programs = 0;

            while (programs < i-1) {
                int pid = fork();
                if (pid == 0) {
                    pid = getpid();
                    printf("\n[%d] %d\n", programs+1, pid);

                    clock_t prev_seconds, curr_seconds;
                    prev_seconds = clock();
                    
                    int pos = allign_str(token[programs]);
                    commands(token[programs]+pos);

                    curr_seconds = clock();
                    printf("%s with pid = %d exited normally # After %lf seconds\n", token[programs]+pos, pid, ((float)(curr_seconds - prev_seconds))/CLOCKS_PER_SEC);

                    exit(0);
                }
                programs++;
            }

            int pos = allign_str(token[i-1]);
            
            commands(token[i-1]+pos);

            free(token);
        }
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