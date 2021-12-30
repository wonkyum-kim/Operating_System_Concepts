#include <stdio.h>
#include <unistd.h>
#include <wait.h>

// How many processes are created?

int main()
{
    pid_t pid;
    for (int i = 0; i < 4; ++i) {
        pid = fork();
    }
    return 0;
}
