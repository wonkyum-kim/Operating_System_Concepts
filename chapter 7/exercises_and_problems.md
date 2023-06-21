## 7.1

Spinlocks are useful for multiprocessor systems where a thread can run in a busy loop (for a short period of time) rather than incurring the overhead of being put in a sleep queue. 

Mutexes are useful for locking resources. 

Semaphores and condition variables are more appropriate tools for synchronization when a resource must be held for a long period of time, since spinning is inefficient for a long duration.

## 7.3 

Use `acuire(mutex)` and `release()` rather than `wait(mutex)` and `signal(mutex)`.

## 7.4

If all philosophers simultaneously pick up their left forks, when they turn to pick up their right forks they will realize they are unavailable, and will block while waiting for it to become available.

## 7.6

10 - 8 + 1 + 1 + 6 - 3 = 7

## 7.14

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
pthread_mutex_t mutex;

int allocate_map(void)
{
    pid_pool = (int*)malloc(sizeof(int) * (MAX_PID - MIN_PID));
    memset(pid_pool, 0, sizeof(int) * (MAX_PID - MIN_PID));
    pthread_mutex_init(&mutex, NULL);
    return pid_pool ? 1 : -1;
}

int allocate_pid(void)
{
    int flag = -1;
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_PID - MIN_PID; ++i) {
        if (pid_pool[i] & 1) {
            continue;
        }
        pid_pool[i] = 1;
        flag = i + MIN_PID;
        break;
    }
    pthread_mutex_unlock(&mutex);
    return flag;
}

void release_pid(int pid)
{
    pthread_mutex_lock(&mutex);
    pid_pool[pid - MIN_PID] = 0;
    pthread_mutex_unlock(&mutex);
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

    pthread_mutex_destroy(&mutex);
    free(pid_pool);
}
```

## 7.15

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SEQUENCE 30 // maximum size of Fibonacci sequence

int sequence[MAX_SEQUENCE]; // shared array for storing Fibonacci sequence
int sequence_size; // size of sequence to generate
int finish = 0;

void *generate_fibonacci(void *arg) 
{
    int i;
    sequence[0] = 0;
    sequence[1] = 1;
    for (i = 2; i < sequence_size; i++) {
        sequence[i] = sequence[i-1] + sequence[i-2];
    }
    finish = 1;
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

    while (!finish) ;

    printf("Fibonacci sequence:\n");
    for (int i = 0; i < sequence_size; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    pthread_join(fibonacci_thread, NULL);

    return 0;
}
```
## 7.17

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
