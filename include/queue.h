#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 50

#include "process.h"

typedef struct {
    process_t* dataList[MAX_QUEUE_SIZE];
    int frontIndex;
    int rearIndex;
} queue_t;

queue_t* queue_init(void);
int queue_is_empty(queue_t* q);
int queue_is_full(queue_t* q);
int queue_enqueue(queue_t* q, process_t* process);
int queue_dequeue(queue_t* q, process_t** process);

#endif