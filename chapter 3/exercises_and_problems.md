# 3.1 

The result is 5.

# 3.2

8 processes are created including the initial parent process.

# 3.4

The CPU current-register-set pointer is changed to point to the set containing the new context. 

If the context is in memory, one of the contexts in a register set must be chosen and be moved to memory, and the new context must be loaded from memory into the set.

# 3.5

c. shared memory segments

# 3.8

1. Save the current process state: The kernel saves the state of the currently running process by storing its register values, program counter, and other necessary data in memory. This allows the kernel to later restore the process to its previous state when it is ready to resume execution.

2. Choose a new process to run: The kernel selects a new process to run by selecting it from the list of ready processes. The kernel may use a scheduling algorithm to determine which process to run next, based on factors such as priority, time slice, or resource availability.

3. Load the new process state: The kernel loads the state of the new process by retrieving its register values, program counter, and other necessary data from memory. This restores the new process to the state it was in when it was last running.

4. Update the kernel data structures: The kernel updates its data structures to reflect the change in the running process. For example, it may update the process state, scheduling queues, or other relevant data structures.

5. Update the CPU: The kernel updates the CPU's registers to reflect the new process state. This includes updating the program counter to point to the next instruction in the new process's code.

6. Resume execution: The kernel transfers control to the new process and allows it to resume execution. The new process will continue running until it either completes its work or is preempted by the kernel.

# 3.10

1. Reaping zombie processes: When a process terminates, its exit status and other information is stored in the process table until the parent process can read it. If the parent process does not read this information, the terminated process becomes a "zombie" process, which can consume system resources and cause problems. The init process is responsible for periodically checking for and reaping any zombie processes that have not been properly cleaned up.

2. Stopping dependent processes: Some processes may have other processes that depend on them, either directly or indirectly. When a process is terminated, the init process is responsible for identifying any dependent processes and ensuring that they are also terminated, if necessary. For example, if a web server process is terminated, the init process may need to terminate any running CGI scripts or database processes that were being used by the server.

3. Cleaning up resources: When a process is terminated, it may be holding system resources such as memory, file handles, or network sockets. The init process is responsible for ensuring that any resources held by the terminated process are released, so that they can be used by other processes.

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

# 3.14

Example 1: Ordinary Pipes
Suppose you have two related processes, and one process needs to send a large amount of data to the other process. In this case, an ordinary pipe would be more suitable because it is a unidirectional communication channel that can efficiently transfer data between related processes. Since the two processes are related, there is no need for a named pipe to establish communication between them.

Example 2: Named Pipes
Suppose you have a client-server architecture where multiple clients need to send requests to the server, and the server needs to respond to each request individually. In this case, a named pipe would be more suitable because it is a bidirectional communication channel that can be used by any process with appropriate permissions. Each client could establish a connection to the named pipe, send their request, and wait for the server to respond. The server could then read the request from the named pipe and send the response back to the appropriate client.

# 3.16

CHILD: 0 CHILD: -1 CHILD: -4 CHILD: -9 CHILD: -16

PARENT: 0 PARENT: 1 PARENT: 2 PARENT: 3 PARENT: 4

# 3.18

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
    pid_t pid;

    // fork a child process
    pid = fork();

    if (pid == 0) {        // child process
        exit(0);
    } else if (pid > 0) {. // parent process
        sleep(10);         // wait for the child to become a zombie
    }

    return 0;
}
```

```bash
gcc zombie.c -o zombie
./zombie &
ps -l
kill -9 <parent_pid>
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
