# 2.1

The purpose of system calls is to provide an interface between a running program (user space) and the operating system (kernel space). 

# 2.2

It reads commands from the user or from a file of commands and executes them, usually by turning them into one or more system calls. 

It is usually not part of the kernel because the command interpreter is subject to changes.

# 2.3

Three system calls (fork(), exec(), and wait()) form the core sequence used by a command interpreter or shell to start a new process on a UNIX system. 

# 2.4

The purpose of system programs is to provide a convenient environment for program development and execution.

# 2.5

The main advantage of the layered approach is simplicity of construction and debugging. 

However, layered approach may introduce performance overhead, rigidity, duplication of functionality, and challenges in defining layer boundaries

# 2.6

See chapter 2.1 Operating-System Serveices.

# 2.7 

For certain devices, such as embedded systems, a disk with a file system may be not be available for the device. 

In this situation, the operating system must be stored in firmware.

# 2.8

Consider a system that would like to run both Windows and three different distributions of Linux.

Each operating system will be stored on disk. 

During system boot, a special program (which we will call the boot manager) will determine which operating system to boot into. 

This means that rather than initially booting to an operating system, the boot manager will first run during system startup. 

It is this boot manager that is responsible for determining which system to boot into. 

Typically, boot managers must be stored at certain locations on the hard disk to be recognized during system startup. 

Boot managers often provide the user with a selection of systems to boot into; boot managers are also typically designed to boot
into a default operating system if no choice is selected by the user.

After selecting an operating system to boot, the bootstrap program needs to do these things:

- Load the file containing the kernel program into memory.
- Run diagnostics to determine the state of the machine (inspecting memory and the CPU and discovering devices).
-  Initialize all aspects of the system, from CPU registers to device controllers and the contents of main memory.
- Start the operating system and mounts the root file system.

# 2.10

1. Register Passing:

In this method, parameters are passed to the operating system through registers. However, it limits the number and size of parameters that can be passed due to the limited number of registers available.

2. Memory Passing:

In some cases, there may be more parameters than registers. In these cases, the parameters are generally stored in a block, or table, in memory, and the address of the block is passed as a parameter in a register.

3. Stack Passing:

Parameters also can be placed, or pushed, onto a stack by the program and popped off the stack by the operating system.

# 2.16

APIs and ABIs serve different purposes in software development. 

APIs focus on the programming interface and provide a higher-level abstraction for developers to build applications, while ABIs define the low-level binary interface between modules and the system, ensuring interoperability at the binary level. 

APIs offer portability and compatibility, while ABIs are platform-specific and require adherence to specific binary-level conventions.

# 2.19

- Microkernel approach makes extending the operating system easier. All new services are added to user space and consequently do not require modification of the kernel. When the kernel does have to be modified, the changes tend to be fewer, because the microkernel is a smaller kernel.

- Communication is provided through message passing. For example, if the client program wishes to access a file, it must interact with the file server. The client program and service never interact directly. Rather, they communicate indirectly by exchanging messages with the microkernel.

- The performance of microkernels can suffer due to increased system-function overhead. When two user-level services must communicate, messages must be copied between the services, which reside in separate address spaces. In addition, the operating system may have to switch from one process to the next to exchange the messages.

# 2.20

Using LKM doesn't have to recompile the kernel every time a change was made.

# 2.24 

gcc FileCopy.c -std=c11 -o FileCopy

strace ./FileCopy

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main()
{
    char sourceFile[100], destFile[100];
    int sourceFd, destFd;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    // Prompt for source file
    printf("Enter the name of the source file: ");
    scanf("%s", sourceFile);

    // Open source file for reading
    sourceFd = open(sourceFile, O_RDONLY);
    if (sourceFd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Prompt for destination file
    printf("Enter the name of the destination file: ");
    scanf("%s", destFile);

    // Open destination file for writing (create if it doesn't exist, truncate if it does)
    destFd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (destFd == -1) {
        perror("Error opening destination file");
        exit(EXIT_FAILURE);
    }

    // Copy contents from source to destination
    while ((bytesRead = read(sourceFd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(destFd, buffer, bytesRead);
        if (bytesWritten == -1) {
            perror("Error writing to destination file");
            exit(EXIT_FAILURE);
        }
    }

    // Check for read error
    if (bytesRead == -1) {
        perror("Error reading from source file");
        exit(EXIT_FAILURE);
    }

    // Close file descriptors
    if (close(sourceFd) == -1) {
        perror("Error closing source file");
        exit(EXIT_FAILURE);
    }

    if (close(destFd) == -1) {
        perror("Error closing destination file");
        exit(EXIT_FAILURE);
    }

    printf("File copied successfully.\n");

    return 0;
}
```
