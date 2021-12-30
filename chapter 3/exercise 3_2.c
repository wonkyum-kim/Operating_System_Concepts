#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    fork(); // fork a child process
    fork(); // fork another child process
    fork(); // and fork another
    return 0;
}
