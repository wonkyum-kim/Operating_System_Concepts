#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    int *A;
    int *T;
    int p1;
    int r1;
    int p2;
    int r2;
    int p3;
} p_merge_data;

typedef struct {
    int *A;
    int *B;
    int p;
    int r;
    int s;
} p_merge_sort_data;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int binary_search(int x, int *T, int p, int r)
{
    int low = p;
    int high = p > r + 1 ? p : r + 1;
    while (low < high) {
        int mid = (low + high) / 2;
        if (x <= T[mid]) {
            high = mid;
        } 
        else {
            low = mid + 1;
        }
    }
    return high;
}

void *p_merge(void *data)
{
    p_merge_data *args = (p_merge_data*)data;

    int p1 = args->p1;
    int p2 = args->p2;
    int p3 = args->p3;

    int r1 = args->r1;
    int r2 = args->r2;

    int *A = args->A;
    int *T = args->T;

    int n1 = r1 - p1 + 1;
    int n2 = r2 - p2 + 1;

    if (n1 < n2) {
        swap(&p1, &p2);
        swap(&r1, &r2);
        swap(&n1, &n2);
    }

    if (n1 == 0) {
        pthread_exit(NULL);
    }
    else {
        int q1 = (p1 + r1) / 2;
        int q2 = binary_search(T[q1], T, p2, r2);
        int q3 = p3 + (q1 - p1) + (q2 - p2);
        A[q3] = T[q1];

        pthread_t threads[2];

        p_merge_data *data1 = (p_merge_data*)malloc(sizeof(p_merge_data));
        p_merge_data *data2 = (p_merge_data*)malloc(sizeof(p_merge_data));

        data1->T = T;
        data1->p1 = p1;
        data1->r1 = q1 - 1;
        data1->p2 = p2;
        data1->r2 = q2 - 1;
        data1->A = A;
        data1->p3 = p3;

        data2->T = T;
        data2->p1 = q1 + 1;
        data2->r1 = r1;
        data2->p2 = q2;
        data2->r2 = r2;
        data2->A = A;
        data2->p3 = q3 + 1;

        pthread_create(&threads[0], NULL, p_merge, (void*)data1);
        pthread_create(&threads[1], NULL, p_merge, (void*)data2);

        for (int i = 0; i < 2; ++i) {
            pthread_join(threads[i], NULL);
        }
      
        free(data1);
        free(data2);
    }
}

void *p_merge_sort(void *data)
{
    p_merge_sort_data *args = (p_merge_sort_data*)data;
    int *A = args->A;
    int *B = args->B;
    int p = args->p;
    int r = args->r;
    int s = args->s;

    int n = r - p + 1;
    if (n == 1) {
        B[s] = A[p];
    }
    else {
        int *T = (int*)malloc(sizeof(int) * (n + 1));
        int q = (p + r) / 2;
        int qp = q - p + 1;

        pthread_t threads[3];

        p_merge_sort_data *data1 = (p_merge_sort_data*)malloc(sizeof(p_merge_sort_data));
        p_merge_sort_data *data2 = (p_merge_sort_data*)malloc(sizeof(p_merge_sort_data));

        data1->A = A;
        data1->p = p;
        data1->r = q;
        data1->B = T;
        data1->s = 1;

        data2->A = A;
        data2->p = q + 1;
        data2->r = r;
        data2->B = T;
        data2->s = qp + 1;

        pthread_create(&threads[0], NULL, p_merge_sort, (void*)data1);
        pthread_create(&threads[1], NULL, p_merge_sort, (void*)data2);

        for (int i = 0; i < 2; ++i) {
            pthread_join(threads[i], NULL);
        }

        p_merge_data *data3 = (p_merge_data*)malloc(sizeof(p_merge_data));

        data3->T = T;
        data3->p1 = 1;
        data3->r1 = qp;
        data3->p2 = qp + 1; 
        data3->r2 = n;
        data3->A = B;
        data3->p3 = s;

        pthread_create(&threads[2], NULL, p_merge, (void*)data3);
        pthread_join(threads[2], NULL);
        
        free(T);
        free(data1);
        free(data2);
    }
}

int main()
{
    p_merge_sort_data *data = (p_merge_sort_data*)malloc(sizeof(p_merge_sort_data));
    int *A = (int*)malloc(sizeof(int) * 11);
    int *B = (int*)malloc(sizeof(int) * 11);

    int values[] = {0, 10, 8, 6, 4, 3, 2, 1, 5, 7, 9};
    for (int i = 0; i < 11; i++) {
        A[i] = values[i];
    }

    data->A = A;
    data->p = 1;
    data->r = 10;
    data->B = B;
    data->s = 1;
  
    pthread_t thread;
    pthread_create(&thread, NULL, p_merge_sort, (void*)data);
    pthread_join(thread, NULL);

    printf("Before:\t");
    for (int i = 1; i <= 10; ++i) {
        printf("%d ", A[i]);
    }

    printf("\nAfter:\t");
    for (int i = 1; i <= 10; ++i) {
        printf("%d ", B[i]);
    }
    printf("\n");

    free(A);
    free(B);
    free(data);
}
