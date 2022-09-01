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
                command[j] = c;
                break;
            }
            command[j] = c;
        }
        command[j+1]='\0';

        int i;
        if (strcmp(command, "") != 0) {
            i = 0;
            char **token;
            token = (char **)malloc(MAXLEN * sizeof(char *));
            token[i] = strtok(command, ";");
            while( token[i] != NULL ) {
                i++;
                token[i] = strtok(NULL, ";");
            }

            int programs = 0;

            int j;
            while (programs < i) {
                j = 0;
                char **tok_token;
                tok_token = (char **)malloc(MAXLEN * sizeof(char *));

                tok_token[j] = strtok(token[programs], "&");
                while( tok_token[j] != NULL ) {
                    j++;
                    tok_token[j] = strtok(NULL, "&");
                }

                if (j == 1 && tok_token[0][get_size(tok_token[0]) - 1] == '&') {
                    int pid = fork();
                    if (pid == 0) {
                        pid = getpid();
                        printf("\n[%d] %d\n", 1, pid);

                        clock_t prev_seconds, curr_seconds;
                        prev_seconds = clock();
                        
                        int pos = allign_str(token[programs]);
                        commands(token[programs]+pos);

                        curr_seconds = clock();
                        printf("[%d] %s with pid = %d exited normally # After %lf seconds\n", 1, token[0]+pos, pid, ((float)(curr_seconds - prev_seconds))/CLOCKS_PER_SEC);

                        exit(0);
                    }
                }

                else if (j == 1) {
                    int pos = allign_str(tok_token[0]);
            
                    commands(tok_token[0]+pos);
                }

                else {

                    int prog_programs = 0;

                    while (prog_programs < j-1) {
                        int pid = fork();
                        if (pid == 0) {
                            pid = getpid();
                            printf("\n[%d] %d\n", prog_programs+1, pid);

                            clock_t prev_seconds, curr_seconds;
                            prev_seconds = clock();
                            
                            int pos = allign_str(token[programs]);
                            commands(token[programs]+pos);

                            curr_seconds = clock();
                            printf("[%d] %s with pid = %d exited normally # After %lf seconds\n", prog_programs+1,tok_token[prog_programs]+pos, pid, ((float)(curr_seconds - prev_seconds))/CLOCKS_PER_SEC);

                            exit(0);
                        }
                        prog_programs++;
                    }

                    int pos = allign_str(tok_token[j-1]);
            
                    commands(tok_token[j-1]+pos);
                }
                free(tok_token);

                programs++;
            }

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