#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "list.h"
#include "schedulers.h"

static int tid = 1;
struct node *head = NULL;
struct node *tail = NULL;

void add(char* name, int priority, int burst) 
{
    Task *task = (Task*)malloc(sizeof(Task));
    task->name = name;
    task->tid = __sync_fetch_and_add(&tid, 1);
    task->priority = priority;
    task->burst = burst;

    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->task = task;
    newNode->next = NULL;

    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = tail->next;
    }
}

void schedule()
{
    int now = 0;
    int turnaround_time = 0;
    int waiting_time = 0;
    int response_time = 0;

    while (head) {
        struct node *curr_node = head;
        Task *curr_task = curr_node->task;
        printf("Running task = [%s] [%d]\n",curr_task->name, curr_task->burst);
        __sync_fetch_and_add(&turnaround_time, curr_task->burst + now);
        __sync_fetch_and_add(&waiting_time, now);
        __sync_fetch_and_add(&now, curr_task->burst);
        head = head->next;
        free(curr_task);
        free(curr_node);
    }

    response_time = waiting_time;

    printf("Average turnaround time = [%.1f]\n", 1.0 * turnaround_time / 8);
    printf("Average waiting time = [%.1f]\n", 1.0 * waiting_time / 8);
    printf("Average response time = [%.1f]\n", 1.0 * response_time / 8);
}

