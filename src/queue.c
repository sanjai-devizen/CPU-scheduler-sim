#include <stdlib.h>
#include "../include/queue.h"

queue_t* queue_init(void) {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }
    q->frontIndex = -1;
    q->rearIndex = -1;
    return q;
}

int queue_is_empty(queue_t* q) {
    return (q->frontIndex == -1);
}

int queue_is_full(queue_t* q) {
    return ((q->rearIndex + 1) % MAX_QUEUE_SIZE == q->frontIndex);
}

int queue_enqueue(queue_t* q, process_t* process) {
    if (queue_is_full(q)) {
        return 0; 
    }
    
    if (queue_is_empty(q)) {
        q->frontIndex = 0;
        q->rearIndex = 0;
    } else {
        q->rearIndex = (q->rearIndex + 1) % MAX_QUEUE_SIZE;
    }

    q->dataList[q->rearIndex] = process;
    return 1; 
}

int queue_dequeue(queue_t* q, process_t** process) {
    if (queue_is_empty(q)) {
        return 0; 
    }
    
    *process = q->dataList[q->frontIndex];
    
    if (q->frontIndex == q->rearIndex) {
        q->frontIndex = -1;
        q->rearIndex = -1;
    } else {
        q->frontIndex = (q->frontIndex + 1) % MAX_QUEUE_SIZE;
    }
    
    return 1; 
}