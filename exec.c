#include "exec.h"
#include "header.h"
#include "history.h"
#include "bg.h"

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
    time(&prev_sec);

    int i;
    if (strcmp(command, "") != 0) {
        i = 0;
        char **token;
        token = (char **)malloc(MAXLEN * sizeof(char *));
        int flag[MAXLEN];
        for (int i = 0; i < MAXLEN; i++)
            flag[i] = 0;
        token[i] = strtok(command, ";");
        while( token[i] != NULL ) {
            if (token[i][-1+get_size(token[i])] == '&')
            flag[i] = 1;
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

            if (j == 1 && flag[programs]) {
                int pid = fork();
                // child++;
                if (pid == 0) {
                    pid = getpid();

                    time_t prev_seconds, curr_seconds;
                    time(&prev_seconds);
                    
                    int pos = allign_str(tok_token[0]);
                    commands(tok_token[0]+pos);
                    // printf("here exec\n");

                    time(&curr_seconds);

                    time_t time = (curr_seconds - prev_seconds);
                    // printf("%d\n", time);

                    for (int i = 0; i < MAXLEN; i++) {
                        if (bg_process_ids[i] == pid) {
                            // printf("here in update\n");
                            bg_process_times[i] = time;
                            *no_bg_process = *no_bg_process - 1;
                            // printf("time: %d\n", bg_process_times[i]);
                            break;
                        }
                    }

                    exit(0);
                }
                else {
                    int pos = allign_str(tok_token[0]);
                    store_bg_process(pid, tok_token[0]+pos);
                    printf("[%d] %d\n", *no_bg_process, pid);
                }
            }

            else if (j == 1) {
                int pos = allign_str(tok_token[0]);
                commands(tok_token[0]+pos);
            }

            else {

                int prog_programs = 0;

                int temp = j;
                if (flag[programs] == 0)
                    temp--;

                while (prog_programs < temp) {
                    int pid = fork();
                    // child++;
                    if (pid == 0) {
                        pid = getpid();

                        time_t prev_seconds, curr_seconds;
                        time(&prev_seconds);
                        
                        int pos = allign_str(tok_token[prog_programs]);
                        commands(tok_token[prog_programs]+pos);

                        time(&curr_seconds);
                        time_t time = (curr_seconds - prev_seconds);

                        // printf("%d\n", time);
                        for (int i = 0; i < MAXLEN; i++) {
                            if (bg_process_ids[i] == pid) {
                                // printf("here in update\n");
                                bg_process_times[i] = time;
                                *no_bg_process = *no_bg_process - 1;
                                // printf("time: %d\n", bg_process_times[i]);
                                break;
                            }
                        }

                        exit(0);
                    }
                    else {
                        int pos = allign_str(tok_token[prog_programs]);
                        store_bg_process(pid, tok_token[prog_programs]+pos);
                        printf("[%d] %d\n", *no_bg_process, pid);
                    }
                    prog_programs++;
                }

                if (temp < j) {
                    int pos = allign_str(tok_token[j-1]);
                    commands(tok_token[j-1]+pos);
                }
            }
            free(tok_token);

            programs++;
        }

        free(token);
    }

    return;
}