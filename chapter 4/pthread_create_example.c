#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum;

void* runner(void* param)
{
    int upper = atoi(param);
    sum = 0;
    for (int i = 1; i <= upper; ++i) {
        sum += i;
    }
    pthread_exit(0);
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);
    printf("sum = %d\n", sum);
}

/*
* gcc -pthread hello.c
* ./a.out 10
*/