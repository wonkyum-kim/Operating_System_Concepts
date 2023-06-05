#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    int row;
    int column;
} parameters;

int sdoku[9][9] = {
    {6,2,4,5,3,9,1,8,7},
    {5,1,9,7,2,8,6,3,4},
    {8,3,7,6,1,4,2,9,5},
    {1,4,3,8,6,5,7,2,9},
    {9,5,8,2,4,7,3,6,1},
    {7,6,2,3,9,1,4,5,8},
    {3,7,1,9,5,6,8,4,2},
    {4,9,6,1,8,2,5,7,3},
    {2,8,5,4,7,3,9,1,6}
};

int check[11];

void *column_worker(void* param)
{
    int digits[9];
    for (int i = 0; i < 9; ++i) {
        memset(digits, 0, sizeof(digits));
        for (int j = 0; j < 9; ++j) {
            digits[sdoku[j][i] - 1] = 1;
        }
        for (int j = 0; j < 9; ++j) {
            if (!digits[j]) {
                pthread_exit(NULL);
            }
        }
    }

    check[0] = 1;
    pthread_exit(NULL);
}

void *row_worker(void* param)
{
    int digits[9];
    for (int i = 0; i < 9; ++i) {
        memset(digits, 0, sizeof(digits));
        for (int j = 0; j < 9; ++j) {
            digits[sdoku[i][j] - 1] = 1;
        }
        for (int j = 0; j < 9; ++j) {
            if (!digits[j]) {
                pthread_exit(NULL);
            }
        }
    }

    check[1] = 1;
    pthread_exit(NULL);
}

void *grid_worker(void *param)
{
    parameters *data = (parameters*)param;
    int row = data->row;
    int col = data->column;
    int digits[9];
    memset(digits, 0, sizeof(digits));
    for (int i = 3 * row; i < 3 * (row + 1); ++i) {
        for (int j = 3 * col; j < 3 * (col + 1); ++j) {
            digits[sdoku[i][j] - 1] = 1;
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (!digits[i]) {
            pthread_exit(NULL);
        }
    }
    check[row * 3 + col + 2] = 1;
    pthread_exit(NULL);
}


int main()
{
    pthread_t threads[11];

    pthread_create(&threads[0], NULL, column_worker, NULL);
    pthread_create(&threads[1], NULL, row_worker, NULL);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int num = i * 3 + j + 2;
            parameters *data = (parameters*)malloc(sizeof(parameters));
            data->row = i;
            data->column = j;
            pthread_create(&threads[num], NULL, grid_worker, (void*)data);
            free(data);
        }
    }

    for (int i = 0; i < 11; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < 11; ++i) {
        if (!check[i]) {
            printf("This solution is not valid.\n");
            return 0;
        }
    }
    printf("This solution is valid.\n");
    return 0;
}

