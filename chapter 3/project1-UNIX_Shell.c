#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>

#define MAX_LINE 80 /* The maximum length command */
 
char* history = 0;

char* readcmd(char* buf) 
{
    printf("osh>");
    fflush(stdout);
    memset(buf, 0, MAX_LINE);
    char* cmd = fgets(buf, MAX_LINE, stdin);
    // Chop off the trailing '/n'.
    if (cmd) {
        cmd[strlen(cmd) - 1] = 0;
    }
    if (strcmp(cmd, "!!")) {
        history = strdup(cmd);
    }
    return cmd;
}

int runcmd(char* cmd)
{
    // Empty command.
    if (!*cmd) { return 1; }

    // history command
    if (!strcmp(cmd, "!!")) {
        if (*history) { cmd = strdup(history); }
        else {
            printf("No commands in history.\n");
            return 1;
        }
    }

    // Skip leading white space(s).
    while (*cmd == ' ') { cmd++; }

    // Remove trailing white space(s).
    for (char* c = cmd + strlen(cmd) - 1; *c == ' '; c--) { *c = 0; }

    // exit command
    if (!strcmp(cmd, "exit")) { return 0; }
    // cd command
    else if (!strncmp(cmd, "cd ", 3)) {
        if (chdir(cmd + 3) < 0) { printf("Cannot cd %s\n", cmd + 3); }
    }
    else {
        char* s = strchr(cmd, ';');
        char* p = strchr(cmd, '|');
        char* lt = strchr(cmd, '<');
        char* gt = strchr(cmd, '>');
        
        if (cmd[strlen(cmd) - 1] == '&') {
            printf("&\n");
            cmd[strlen(cmd) - 1] = 0;
            if (!fork()) {
                runcmd(cmd);
            }
            // do not wait
        }
        else if (s) {
            *s = 0;
            if (!fork()) {
                runcmd(cmd);
                exit(0);
            }
            wait(0);
            runcmd(s + 1);
        }
        else if (gt) {
            *gt = 0;
            if (!fork()) {
                int file = open(gt + 2, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                dup2(file, STDOUT_FILENO);
                runcmd(cmd);
                close(file);
                exit(0);
            }
            else {
                wait(0);
            }
        }
        else if (lt) {
            *lt = 0;
            if (!fork()) {
                int file = open(lt + 2, O_RDONLY, S_IRWXU);
                dup2(file, STDIN_FILENO);
                runcmd(cmd);
                close(file);
                exit(0);
            }
            else {
                wait(0);
            }
        }
        else if (p) {
            *p = 0;
            if (!fork()) {
                int fd[2];
                pipe(fd);
                if (!fork()) {
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                    runcmd(cmd);
                    exit(0);
                }
                else {
                    dup2(fd[0], STDIN_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                    runcmd(p + 1);
                    exit(0);
                }
                wait(0);
            }
        }
        else {
            char* args[MAX_LINE / 2 + 1];
            int count = 0;
            char* pp = strchr(cmd, ' ');

            while (pp) {
                *pp = 0;
                args[count] = cmd;
                count++;
                cmd = pp + 1;
                pp = strchr(cmd, ' ');
            }

            // Add the last one.
            args[count] = cmd;
            count++;
            args[count] = 0;

            if (!fork()) { execvp(args[0], args); }
            else wait(0);
        }
    }
    return 1;
}

int main(void)
{
	
	int should_run = 1; /* flag to determine when to exit program */

    char* cmd = 0;
    char buf[MAX_LINE];
	while (should_run) {
        if (!(cmd = readcmd(buf)) || !runcmd(cmd)) {
            should_run = 0;
        }


		/**
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) parent will invoke wait() unless command included &
		*/
	}
	return 0;
}
