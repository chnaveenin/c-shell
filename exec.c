#include "exec.h"
#include "header.h"
#include "history.h"

void x_command() {
    char command[MAXLEN];

    int child = 0;

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

    // printf("%s\n", command);
    storeCommand(command);

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
                child++;
                if (pid == 0) {
                    pid = getpid();
                    printf("\n[%d] %d\n", child, pid);

                    clock_t prev_seconds, curr_seconds;
                    prev_seconds = clock();
                    
                    int pos = allign_str(tok_token[programs]);
                    commands(tok_token[programs]+pos);

                    curr_seconds = clock();
                    printf("%s with pid = %d exited normally # After %lf seconds\n",
                            tok_token[0]+pos,
                            pid,
                            ((float)(curr_seconds - prev_seconds))/CLOCKS_PER_SEC);

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
                    child++;
                    if (pid == 0) {
                        pid = getpid();
                        printf("\n[%d] %d\n", child, pid);

                        clock_t prev_seconds, curr_seconds;
                        prev_seconds = clock();
                        
                        int pos = allign_str(tok_token[prog_programs]);
                        commands(tok_token[prog_programs]+pos);

                        curr_seconds = clock();
                        printf("%s with pid = %d exited normally # After %lf seconds\n",
                                tok_token[prog_programs]+pos,
                                pid,
                                ((float)(curr_seconds - prev_seconds))/CLOCKS_PER_SEC);

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

    return;
}