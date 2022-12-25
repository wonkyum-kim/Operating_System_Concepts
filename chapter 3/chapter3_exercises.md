# 3.1 

The result is 5.

# 3.2

8 processes are created including the initial parent process.

# 3.5

c. shared memory segments

# 3.11

16 processes are creeated including the initial parent process.

# 3.12

Because of `execlp()`, LINE J will not be reached.

# 3.13

```
A : 0
B : 2603
C : 2603
D : 2600
```

# 3.18

```c
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) {
        exit(0);
    }
    else {
        sleep(10);
        char kill[100] = "kill -9 ";
        char process[100];
        sprintf(process, "%d", getpid());
        strcat(kill, process);
        system(kill);
    }
    return 0;
}
```
