#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "priority_queue.h"

struct node
{
  elem info;
  int priority;
};

struct queue
{
  int heap_size;
  node_t *heap[MAX];    
};

void up(int i, queue_t *q)
{
  int p_idx; // parent index
  p_idx = (int)((i-1)/2);
  if(p_idx >= 0 && q->heap[i]->priority > q->heap[p_idx]->priority)
  {
    node_t *temp;
    temp = q->heap[i];
    q->heap[i] = q->heap[p_idx];
    q->heap[p_idx] = temp;
    up(p_idx, q);
  }
}

void down(int i, queue_t *q)
{
  int c_idx; // child index
  c_idx = 2*i+1;
  if(c_idx < q->heap_size) // i has children
  {
    if(c_idx < q->heap_size - 1) // i has a right child
    { // choose the greatest
      if(q->heap[c_idx]->priority < q->heap[c_idx+1]->priority) c_idx++;
    }
    if(q->heap[c_idx]->priority > q->heap[i]->priority)
    {
      node_t *temp;
      temp = q->heap[i];
      q->heap[i] = q->heap[c_idx];
      q->heap[c_idx] = temp;
      down(c_idx, q);
    }
  }
}

queue_t *create_queue()
{
  queue_t *q = (queue_t*)malloc(sizeof(queue_t));
  assert(q != NULL);
  q->heap_size = 0;
  return q;
}

node_t* create_node(elem key, int prio) 
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  assert(new_node != NULL);
  new_node->info = key;
  new_node->priority = prio;
  return new_node;
}

int insert_elem(queue_t *q, elem key, int prio)
{
  if (queue_is_full(q)) return 0;
  
  node_t *new_node = create_node(key, prio);
  q->heap[q->heap_size] = new_node;
  up(q->heap_size, q);
  q->heap_size++;
  return 1;
}

int remove_elem(queue_t *q, elem *key)
{
  if(queue_is_empty(q)) return 0;

  *key = q->heap[0]->info;
  free(q->heap[0]);
  q->heap[0] = q->heap[q->heap_size-1];
  q->heap_size--;
  down(0, q);
  return 1;
}

int queue_is_empty(queue_t *q)
{
  assert(q != NULL);
  return q->heap_size == 0;
}

int queue_is_full(queue_t *q)
{
  assert(q != NULL);
  return q->heap_size == MAX;
}

void free_queue(queue_t *q)
{
  for (int i = 0; i < q->heap_size; i++)
  {
    free(q->heap[i]);
  }
  free(q);
}