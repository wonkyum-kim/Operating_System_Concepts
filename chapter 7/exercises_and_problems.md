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
