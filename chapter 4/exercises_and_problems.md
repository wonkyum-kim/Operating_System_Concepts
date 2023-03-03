# 4.2

(a) 1.4 (b) 1.8

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

void* average_worker(void* arg) {
    double sum = 0.0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += numbers[i];
    }
    average = sum / ARRAY_SIZE;
    pthread_exit(NULL);
}

void* max_worker(void* arg) {
    max = numbers[0];
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    pthread_exit(NULL);
}

void* min_worker(void* arg) {
    min = numbers[0];
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
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
# 4. 23

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_primes(void* args);

int main(int argc, char* argv[]) {

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

void Eratosthenes(int* sieve, int num) {
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

void* print_primes(void* args) {
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

void* calculate_pi(void* arg) {
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

int main() {
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
