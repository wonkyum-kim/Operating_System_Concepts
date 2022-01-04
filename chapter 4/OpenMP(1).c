#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    omp_set_num_threads(4);

    /* sequential code */
    #pragma omp parallel 
    {
        printf("OpenMP thread: %d\n", omp_get_thread_num());
    }

    /* sequential code */
    return 0;
}

