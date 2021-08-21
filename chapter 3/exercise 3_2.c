#include <stdio.h>
#include <unistd.h>
#include <wait.h>

// How many processes are created?
// 1 parent process, 7 child processes

int main()
{
    fork(); // fork a chidl process
    fork(); // fork another child process
    fork(); // and fork another
    return 0;
}
