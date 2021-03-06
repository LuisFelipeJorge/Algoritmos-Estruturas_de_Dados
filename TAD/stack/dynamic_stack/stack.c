#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

struct node 
{
  void *info;
  node_t *next;
};

struct stack
{
  node_t *top;
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

stack_t* create_stack(int info_size)
{
  stack_t *s = (stack_t*)malloc(sizeof(stack_t));
  s->size = 0;
  s->info_size = info_size;
  s->top = NULL;
  return s;
}

int is_empty(stack_t* s)
{
  return (s->size == 0);
}

void free_stack(stack_t *s)
{
  if (s != NULL)
  {
    node_t *current_node = s->top;
    while (current_node != NULL)
    {
      s->top = current_node->next;
      free(current_node->info);
      free(current_node);
      current_node = s->top;
    }
    free(s);
  }return;
}

void push(stack_t *s, void *info)
{
  assert(s != NULL);
  node_t *new_node = create_node(info, s->info_size);
  if (!is_empty(s)) new_node->next = s->top;
  s->top = new_node;
  s->size++;
}

void top(stack_t* s, void* info)
{
  assert(s!=NULL);
  memcpy(info, s->top->info, s->info_size);  
}

node_t* get_top(stack_t *s)
{
  return s->top;
}

void get_info(node_t *current_node, int info_size, void *info)
{
  memcpy(info, current_node->info, info_size);
}

node_t* get_next(node_t *current_node)
{
  return current_node->next;
}

void pop(stack_t *s, void *info)
{
  top(s, info);
  node_t *current_node = s->top;
  memcpy(info, current_node->info, s->info_size);
  s->top = current_node->next;
  s->size--;
  free(current_node->info);
  free(current_node);
}