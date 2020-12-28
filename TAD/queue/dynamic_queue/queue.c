#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct node 
{
  void *info;
  node_t *next;
};

struct queue
{
  node_t *start, *end;
  int size;
  int info_size;
};


node_t* create_node(void *info, int info_size)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  assert(new_node != NULL);
  new_node->next = NULL;
  new_node->info = (void*)malloc(info_size);
  assert(new_node->info != NULL);
  memcpy(new_node->info, info, info_size);
  return new_node;
}

queue_t* create_queue(int info_size)
{
queue_t *q = (queue_t*)malloc(sizeof(queue_t));
  q->size = 0;
  q->info_size = info_size;
  q->start = NULL;
  q->end = NULL;
  return q;
}

int is_empty(queue_t* q)
{
  return (q->size == 0);
}

void free_queue(queue_t *q)
{
  if (q != NULL)
  {
    node_t *current_node = q->start;
    while (current_node != NULL)
    {
      q->start = current_node->next;
      free(current_node->info);
      free(current_node);
      current_node = q->start; 
    }
    free(q);
  }return;
}

void enqueue(queue_t *q, void* info)
{
  assert(q != NULL);
  node_t *new_node = create_node(info, q->info_size);
  if (is_empty(q))
  {
    q->start = new_node;
  }else
  {
    q->end->next = new_node;
  }
  q->end = new_node;
  q->size++;
}

void dequeue(queue_t *q, void* info)
{
  assert(q != NULL);
  if (is_empty(q)) return;
  node_t *current_node = q->start;
  memcpy(info, current_node->info, q->info_size);

  q->start = current_node->next;
  free(current_node->info);
  free(current_node);
  q->size--;
}

node_t* get_start(queue_t *q)
{
  return q->start;
} 

int get_size(queue_t *q)
{
  return q->size;
}

node_t* get_next(node_t *current_node)
{
  return current_node->next;
}

void get_info(node_t *current_node, void* info, int info_size)
{
  memcpy(info, current_node->info, info_size);
}