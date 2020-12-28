#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define QueueSize 100

typedef struct queue queue_t;

queue_t* create(int element_size);
int enqueue(queue_t *q, void* x);
int dequeue(queue_t *q, void* x);
int is_empty(queue_t *q);
int is_full(queue_t *q);
void free_queue(queue_t *q);