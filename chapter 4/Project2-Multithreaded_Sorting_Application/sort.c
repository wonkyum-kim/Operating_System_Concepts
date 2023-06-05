#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int arr[10] = {
    7,12,19,3,18,4,2,6,15,8
};

int left[5], right[5], result[10];

void *left_sorting_worker(void *param)
{
    for (int j = 1; j < 5; j++) {
        int key = left[j];
        int i = j - 1;
        while (i >= 0 && left[i] > key) {
            left[i + 1] = left[i];
            i--;
        }
        left[i + 1] = key;
    }
    pthread_exit(NULL);
}

void *right_sorting_worker(void *param)
{
    for (int j = 1; j < 5; j++) {
        int key = right[j];
        int i = j - 1;
        while (i >= 0 && right[i] > key) {
            right[i + 1] = right[i];
            i--;
        }
        right[i + 1] = key;
    }
    pthread_exit(NULL);
}

void *merging_worker(void *param)
{
    int k = 0, l = 0, r = 0;
    while (l != 5 && r != 5) {
        if (left[l] <= right[r]) {
            result[k++] = left[l];
            l++;
        } else {
            result[k++] = right[r];
            r++;
        }
    }

    while (l == 5 && r != 5) {
        result[k++] = right[r];
        r++;
    }

    while (r == 5 && l != 5) {
        result[k++] = left[l];
        l++;
    }
    pthread_exit(NULL);
}

int main()
{
    for (int i = 0; i < 5; ++i) {
        left[i] = arr[i];
        right[i] = arr[i + 5];
    }

    pthread_t threads[3];
    pthread_create(&threads[0], NULL, left_sorting_worker, NULL);
    pthread_create(&threads[1], NULL, right_sorting_worker, NULL);

    for (int i = 0; i < 2; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_create(&threads[2], NULL, merging_worker, NULL);
    pthread_join(threads[2], NULL);

    for (int i = 0; i < 10; ++i) {
        printf("%d ", result[i]);
    }
    
    return 0;
}

