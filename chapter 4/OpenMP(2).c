#include <stdio.h>
#include <omp.h>

#define SIZE 100000000

int a[SIZE], b[SIZE], c[SIZE];

int main(int argc, char* argv[])
{
    for (int i = 0; i < SIZE; ++i) {
        a[i] = i;
        b[i] = i;
    }

    #pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
        c[i] = a[i] + b[i];
    }

    return 0;
}

