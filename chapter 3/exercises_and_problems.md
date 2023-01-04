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
#include <sys/time.h>

// Complex command
// $ gcc -o time time.c
// $ ./time "ls | grep t | grep c"

struct timeval current;

int main(int argc, char* argv[])
{
    pid_t pid = fork();

    const int SIZE = 4096;
    const char* name = "starting time";
    
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    char* ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (pid == 0) {
        gettimeofday(&current, NULL);
        double start = current.tv_sec + (double)current.tv_usec / 1000000;
        sprintf(ptr, "%f", start);
        ptr += sizeof(double);
        system(argv[1]);
        exit(0);
    }
    else {
        wait(0);
        gettimeofday(&current, NULL);
        double end = current.tv_sec + (double)current.tv_usec / 1000000;
        double start = atof(ptr);
        double diff = end - start;
        printf("Elapsed time: %f\n", diff);
        shm_unlink(name);
    }
    return 0;
}
```

The second version

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
#include <sys/time.h>

// Complex command
// $ gcc -o time time.c
// $ ./time "ls | grep t | grep c"

struct timeval current;

int main(int argc, char* argv[])
{

    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        gettimeofday(&current, NULL);
        double start = current.tv_sec + (double)current.tv_usec / 1000000;
        char message[30];
        sprintf(message, "%f", start);

        // Close the read end of the pipe
        close(fd[0]);
        // Write to the pipe
        write(fd[1], message, strlen(message) + 1);
        // Close the write end of the pipe
        close(fd[1]);

        system(argv[1]);
        exit(0);
    }
    else {
        wait(0);
        gettimeofday(&current, NULL);
        double end = current.tv_sec + (double)current.tv_usec / 1000000;
        char message[30];

        // Close the write end of the pipe
        close(fd[1]);
        // Read from the pipe
        read(fd[0], message, 30);
        // Close the read end of the pipe
        close(fd[0]);

        double start = atof(message);
        double diff = end - start;
        printf("Elapsed time: %f\n", diff);
    }
    return 0;
}
```

# 3.20

```c
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define MIN_PID 300
#define MAX_PID 5000

int* pid_pool;

int allocate_map(void)
{
    pid_pool = (int*)malloc(sizeof(int) * (MAX_PID - MAX_PID));
    memset(pid_pool, 0, sizeof(int) * (MAX_PID - MAX_PID));
    return pid_pool ? 1 : -1;
}

int allocate_pid(void)
{
    int flag = -1;
    for (int i = 0; i < MAX_PID - MIN_PID; ++i) {
        if (pid_pool[i] & 1) {
            continue;
        }
        pid_pool[i] = 1;
        flag = i + MIN_PID;
        break;
    }
    return flag;
}

void release_pid(int pid)
{
    pid_pool[pid - MIN_PID] = 0;
}

int main()
{
    if(allocate_map() == -1) {
        printf("Error\n");
        return 0;
    }
    
    printf("%d\n", allocate_pid());
    printf("%d\n", allocate_pid());
    release_pid(300);
    printf("%d\n", allocate_pid());
    printf("%d\n", allocate_pid());
    free(pid_pool);
}
```

# 3.21

```c
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

// gcc -o Collatz ./Collatz.c
// ./Collatz 35

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Enter a positive integer\n");
        return 0;
    } 
    pid_t pid = fork();
    if (pid == 0) {
        while (n != 1) {
            printf("%d, ", n);
            if (n % 2 == 0) {
                n >>= 1;
            }
            else {
                n = 3 * n + 1;
            }
        } 
        printf("%d\n", n);
    }
    else {
        wait(0);
    }
}
```

# 3.22

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
#include <sys/time.h>

// gcc -o Collatz ./Collatz.c
// ./Collatz 35

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Enter a positive integer\n");
        return 0;
    } 

    const int SIZE = 4096;
    const char* name = "Collatz conjecture";
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    char* ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


    pid_t pid = fork();

    if (pid == 0) {
        while (n != 1) {
            // Find a null character
            char* p = strchr(ptr, 0);
            sprintf(p, "%d, ", n);
            if (n % 2 == 0) {
                n /= 2;
            }
            else {
                n = 3 * n + 1;
            }
        } 
        char* p = strchr(ptr, 0);
        sprintf(p, "%d", n);
    }
    else {
        wait(0);
        printf("%s\n", ptr);
        shm_unlink(name);
    }
}
```

# 3.26

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
#include <sys/time.h>

// gcc -o pipe ./pipe.c
// ./pipe

int main(int argc, char* argv[])
{
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        close(fd[0]);
        char write_msg[30] = "Hi There";
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
    }
    else {
        close(fd[1]);
        char read_msg[30];
        read(fd[0], read_msg, sizeof(char) * 30);
        char* c = read_msg;
        while (*c) {
            if ('a' <= *c && *c <= 'z') {
                *c -= 32;
            }
            else if ('A' <= *c && *c <= 'Z') {
                *c += 32;
            }
            printf("%c", *c);
            c++;
        }
        printf("\n");
        close(fd[0]);
    }
}
```

# 3.27

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
#include <sys/time.h>

// gcc -o filecopy ./filecopy.c
// ./filecopy input.txt copy.txt

// input.txt
/*
Hi!
Nice to meet you.
See you next time.
*/

int main(int argc, char* argv[])
{
    int fd[2];
    pipe(fd);

    FILE* src = fopen(argv[1], "r");
    FILE* des = fopen(argv[2], "w");
    
    if (!fork()) {
        close(fd[0]);
        char write_msg[100];
        char* p = write_msg;
        while (fgets(p, sizeof(write_msg), src)) {
            p = strchr(write_msg, 0);
        }
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
    }
    else {
        close(fd[1]);
        char read_msg[100];
        read(fd[0], read_msg, sizeof(read_msg));
        fprintf(des, "%s", read_msg);
        close(fd[0]);
    }
    fclose(src);
    fclose(des);
    
}
```