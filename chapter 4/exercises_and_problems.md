# 4.1

Image processing: When performing image processing tasks, such as applying filters or transformations, multithreading can greatly improve performance. By dividing the image into smaller sections and processing each section in parallel on different threads, the overall processing time can be reduced significantly.

Web server: Web servers often have to handle multiple requests simultaneously. By using multithreading, the server can handle multiple requests at the same time, without having to wait for each request to be processed before moving on to the next one.

Data processing: When dealing with large amounts of data, such as in data mining or analysis, multithreading can help speed up the process. By breaking up the data into smaller chunks and processing each chunk on a separate thread, the overall processing time can be reduced, allowing for faster analysis and insights.

# 4.2

(a) 1.43 (b) 1.82

# 4.3

The multithreaded web server described in Section 4.1 exhibit data parallelism.

# 4.4

User-level threads are unknown by the kernel, whereas the kernel is aware of kernel threads.

User threads are scheduled by the thread library, and kernel threads are scheduled by the kernel.

Kernel threads need not be associated with a process, whereas every user thread belongs to a process. 

Kernel threads are generally more expensive to maintain than user threads, as they must be represented with a kernel data structure.

# 4.5

1. Save the current thread context: The kernel saves the context of the current thread, including its CPU registers, program counter, and other relevant state information, to a data structure associated with the thread.

2. Select the next thread to run: The kernel selects the next thread to run, based on a scheduling algorithm that takes into account factors such as thread priority, time quantum, and other factors.

3. Restore the next thread context: The kernel restores the context of the next thread to run from the data structure associated with the thread, including its CPU registers, program counter, and other relevant state information.

4. Update kernel data structures: The kernel updates various data structures associated with the threads, such as the run queue and scheduling information.

5. Switch to user mode: The kernel switches the processor to user mode, allowing the next thread to resume execution from where it left off.

Context switching between kernel-level threads is a complex operation that involves significant overhead, due to the need to save and restore both the user-level and kernel-level contexts of the threads. As a result, kernel-level threads are generally less efficient than user-level threads, which are managed entirely in user space and involve only the saving and restoring of user-level context.

# 4.6

Because a `thread` is smaller than a `process`, thread creation typically uses fewer resources than process creation. 

Creating a process requires allocating a process control block (PCB), a rather large data structure.

The PCB includes a memory map, a list of open les, and environment variables. 

Allocating and managing the memory map is typically the most time-consuming activity. 

Creating either a user thread or a kernel thread involves allocating a small data structure to hold a register set, stack, and priority.

# 4.10

b. Heap memory

c. Global variables

# 4.14

- (a) 1 / (1 - 0.4 + (0.4 / 8)) = 1.54 (b) 1 / (1 - 0.4 + (0.4 / 16)) = 1.6
- (a) 1 / (1 - 0.67 + (0.67 / 2)) = 1.5 (b) 1 / (1 - 0.67 + (0.67 / 4)) = 2.01
- (a) 1 / (1 - 0.9 + (0.9 / 4)) = 3.08 (b) 1 / (1 - 0.9 + (0.9 / 8)) = 4.71

# 4.16

(a) For input and output operations, since there is only one file being read and written, it is not necessary to create multiple threads. Instead, a single thread can be used to perform the input and output operations.

(b) For the CPU-intensive portion of the application, since the system has four processors available for scheduling, it would be optimal to create four threads to fully utilize the available processing power. However, since the system has two dual-core processors, creating more than two threads may not result in a significant performance improvement due to the limitations of the hardware architecture. Therefore, it would be reasonable to create two threads for the CPU-intensive portion of the application.

# 4.17

(a) 5 (b) 2 

# 4.19

CHILD: value = 5

PARENT: value = 0

# 4.22

```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 3
#define ARRAY_SIZE 7

int numbers[ARRAY_SIZE];
double average;
int max;
int min;

void* average_worker(void* arg) 
{
    double sum = 0.0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += numbers[i];
    }
    average = sum / ARRAY_SIZE;
    pthread_exit(NULL);
}

void* max_worker(void* arg) 
{
    max = numbers[0];
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    pthread_exit(NULL);
}

void* min_worker(void* arg) 
{
    min = numbers[0];
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv) 
{
    pthread_t threads[NUM_THREADS];

    // Get the numbers from the command line arguments
    for (int i = 1; i <= ARRAY_SIZE; i++) {
        numbers[i - 1] = atoi(argv[i]);
    }

    // Create the threads
    pthread_create(&threads[0], NULL, average_worker, NULL);
    pthread_create(&threads[1], NULL, max_worker, NULL);
    pthread_create(&threads[2], NULL, min_worker, NULL);

    // Wait for the threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the results
    printf("The average value is %.2f\n", average);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);

    return 0;
}
```
# 4.23

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_primes(void* args);

int main(int argc, char* argv[]) 
{

    pthread_t tid;

    if (argc < 2) {
        printf("Please provide a number as command line argument.\n");
        return 1;
    }

    int num = atoi(argv[1]);

    if (num < 2) {
        printf("Please enter a number greater than or equal to 2.\n");
        return 1;
    }

    pthread_create(&tid, NULL, print_primes, (void*)&num);
    pthread_join(tid, NULL);

    return 0;
}

void Eratosthenes(int* sieve, int num) 
{
    for (int i = 1; i < num + 1; ++i) {
        sieve[i] = 1;
    }
    sieve[1] = 0;
    
    for (int i = 2; i <= num; ++i) {
        if (!sieve[i]) {
            continue;
        }
        for (int j = 2 * i; j <= num; j += i) {
            sieve[j] = 0;
        }
    }
    return;
}

void* print_primes(void* args) 
{
    int num = *((int*)args);
    int* sieve = malloc(sizeof(int) * (num + 1));

    if (sieve == NULL) {
        printf("Memory allocation error.\n");
        pthread_exit(NULL);
    }

    // Eratosthenes's sieve
    Eratosthenes(sieve, num);

    for (int i = 1; i <= num; ++i) {
        if (sieve[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    free(sieve);
    pthread_exit(NULL);
}
```
# 4.24

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 4
#define TOTAL_POINTS 10000000

double points_in_circle = 0;
pthread_mutex_t lock;

void* calculate_pi(void* arg) 
{
    int num_points = *(int*)arg;
    double x, y, distance;

    for (int i = 0; i < num_points; ++i) {
        x = -1.0 + 2.0 * (double)rand() / RAND_MAX;  
        y = -1.0 + 2.0 * (double)rand() / RAND_MAX;  
        distance = sqrt(x * x + y * y);
        if (distance <= 1) {
            pthread_mutex_lock(&lock);
            points_in_circle++;
            pthread_mutex_unlock(&lock);
        }
    }
    pthread_exit(NULL);
}

int main() 
{
    int num_points = TOTAL_POINTS / NUM_THREADS;
    double pi_estimate;
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, calculate_pi, (void*)&num_points);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    pi_estimate = 4 * points_in_circle / TOTAL_POINTS;
    printf("Estimated value of pi: %f\n", pi_estimate);

    pthread_mutex_destroy(&lock);

    return 0;
}
```
# 4.27

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SEQUENCE 30 // maximum size of Fibonacci sequence

int sequence[MAX_SEQUENCE]; // shared array for storing Fibonacci sequence
int sequence_size; // size of sequence to generate

void *generate_fibonacci(void *arg) 
{
    int i;
    sequence[0] = 0;
    sequence[1] = 1;
    for (i = 2; i < sequence_size; i++) {
        sequence[i] = sequence[i-1] + sequence[i-2];
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <sequence size>\n", argv[0]);
        return -1;
    }
    sequence_size = atoi(argv[1]);
    if (sequence_size <= 0 || sequence_size > MAX_SEQUENCE) {
        fprintf(stderr, "Sequence size must be between 1 and %d\n", MAX_SEQUENCE);
        return -1;
    }

    pthread_t fibonacci_thread;
    int rc = pthread_create(&fibonacci_thread, NULL, generate_fibonacci, NULL);

    pthread_join(fibonacci_thread, NULL);

    printf("Fibonacci sequence:\n");
    for (int i = 0; i < sequence_size; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}
```
# 4.28

```c
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

#define MIN_PID 300
#define MAX_PID 5000
#define NUM_THREADS 100

int* pid_pool;

int allocate_map(void)
{
    pid_pool = (int*)malloc(sizeof(int) * (MAX_PID - MIN_PID));
    memset(pid_pool, 0, sizeof(int) * (MAX_PID - MIN_PID));
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

void* pid_manager()
{
    int pid = allocate_pid();
    if (pid == -1) {
        printf("Error: Unable to allocate PID. Exiting thread \n");
        pthread_exit(NULL);
    }
    printf("Allocated PID %d.\n", pid);

    srand(time(NULL));
    int sleep_time = rand() % 10;
    sleep(sleep_time);

    release_pid(pid);
    printf("Released PID %d.\n", pid);

    pthread_exit(NULL);
}

int main()
{
    if (allocate_map() == -1) {
        printf("Error: Unable to allocate PID map.\n");
        return 0;
    }

    pthread_t threads[NUM_THREADS];
    int rc;

    for (int i = 0; i < NUM_THREADS; ++i) {
        rc = pthread_create(&threads[i], NULL, pid_manager, NULL);
        if (rc) {
            printf("Error: Unable to create thread\n");
            return 0;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(pid_pool);
}
```
