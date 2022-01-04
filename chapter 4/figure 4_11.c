#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sum = 0;    /* this data is shared by the thread(s) */

void* runner(void* param)   /* threads call this funtion */
{
    int upper = atoi(param);

    for (int i = 1; i <= upper; ++i) {
        sum += i;
    }

    pthread_exit(0);
}

int main(int argc, char* argv[]) 
{
    pthread_t tid;  /* the thread identifier */
    pthread_attr_t attr;    /* set of thread attributes */

    /* set the default attributes of the thread */
    pthread_attr_init(&attr);
    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);
    /* wait for the thread to exit */
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
}
