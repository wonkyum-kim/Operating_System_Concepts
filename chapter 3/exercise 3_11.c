#include <stdio.h>
#include <unistd.h>
#include <wait.h>

// How many processes are created?
// 1 parent process, 15 child processes

int main()
{
    pid_t pid;
    for (int i = 0; i < 4; ++i) {
        pid = fork();
    }
    return 0;
}
