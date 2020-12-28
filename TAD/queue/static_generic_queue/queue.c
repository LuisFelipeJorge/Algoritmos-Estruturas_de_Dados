#include "queue.h"

struct queue
{
  int start, end, total;
  int element_size;
  void **items;
};

queue_t* create(int element_size)
{
  queue_t *q = (queue_t*)malloc(sizeof(queue_t));
  assert(q != NULL);
  q->items = (void**)malloc(sizeof(void*)*QueueSize);
  assert(q->items != NULL);
  q->total = 0;
  q->start = 0;
  q->end = 0;
  q->element_size = element_size;
  return q;
}

int is_empty(queue_t *q)
{
  assert(q != NULL);
  return(q->total == 0);
}

int is_full(queue_t *q)
{
  assert(q != NULL);
  return(q->total == QueueSize);
}

int enqueue(queue_t *q, void *x)
{
  assert(q != NULL);
  if (is_full(q)) return 0;
  q->total++;
  q->items[q->end] = (void*)malloc(q->element_size);
  assert(q->items[q->end] != NULL);
  memcpy(q->items[q->end], x, q->element_size);
  q->end = (q->end + 1) % QueueSize;
  return 1;  
}

int dequeue(queue_t *q, void *x)
{
  assert(q != NULL);
  if (is_empty(q)) return 0;
  q->total--;
  memcpy(x, q->items[q->start], q->element_size);
  free(q->items[q->start]);
  q->start = (q->start + 1)%QueueSize;
  return 1;
}

void free_queue(queue_t *q)
{
  for (int i = q->start; i < q->end; i++)
  {
    free(q->items[i%QueueSize]);
  }
  assert(q->items != NULL);
  free(q->items);
  assert(q != NULL);
  free(q);
  q = NULL;
}

int get_start(queue_t *q)
{
  return q->start;
}

int get_end(queue_t *q)
{
  return q->end;
}

void get_element(queue_t *q, int position, void *x)
{
  memcpy(x, q->items[position], q->element_size);// copy bytes**
}