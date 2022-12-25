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

# 3.19

The first version

```c
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>

// complex command
// $ gcc -o time time.c
// $ ./time "ls | grep t | grep c"

int main(int argc, char* argv[])
{
    pid_t pid = fork();

    const int SIZE = 4096;
    const char* name = "starting time";
    
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    char* ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (pid == 0) {
        sprintf(ptr, "%d", (int)clock());
        system(argv[1]);
        exit(0);
    }
    else {
        wait(0);
        int end = (int)clock();
        int start = atoi(ptr);
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Elapsed time: %f\n", elapsed);
    }
    return 0;
}
```
