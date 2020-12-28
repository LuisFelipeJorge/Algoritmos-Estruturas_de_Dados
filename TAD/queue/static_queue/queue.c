#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "queue.h"

struct queue
{
  int start, end, total;
  elem itens[QueueSize];
};

queue_t* create()
{
  queue_t *q = (queue_t*)malloc(sizeof(queue_t));
  assert(q != NULL);
  q->total = 0;
  q->start = 0;
  q->end = 0;
  return q;
}

int is_empty(queue_t *q)
{
  assert(q != NULL);
  return (q->total == 0);  
}

int is_full(queue_t *q)
{
  assert(q != NULL);
  return (q->total == QueueSize);  
}

int enqueue(queue_t *q, elem x)
{
  if (is_full(q)) return 0;
  q->total++;
  q->itens[q->end] = x;  
  q->end = (q->end + 1)%QueueSize;// circular array
  return 1;
}

int dequeue(queue_t *q, elem *x)
{
  if (is_empty(q)) return 0;
  q->total--;
  *x = q->itens[q->start];
  q->start = (q->start + 1) % QueueSize;
  return 1;  
}

void free_queue(queue_t *q)
{
  if (q != NULL) free(q);  
}