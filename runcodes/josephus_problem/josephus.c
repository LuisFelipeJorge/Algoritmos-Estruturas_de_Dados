#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "josephus.h"

struct node 
{
  elem info;
  node_t *next;
};

struct list
{
  node_t *last;
  int size;
};

node_t* create_node(elem info)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  assert(new_node != NULL);
  new_node->next = NULL;
  new_node->info = info;
  return new_node;
}

list_t* create_list()
{
  list_t *l = (list_t*)malloc(sizeof(list_t));
  assert(l != NULL);
  l->last = NULL;
  l->size = 0;
  return l;
}

int is_empty(list_t *l)
{
  return (l->size == 0);
}

void insert(list_t *l, elem info)
{
  assert(l != NULL);
  node_t *new_node = create_node(info);
  if (is_empty(l))
  { 
    l->last = new_node;
    new_node->next = l->last;
  }else
  {
    new_node->next = l->last->next;
    l->last->next = new_node;
    l->last = new_node;
  }  
  l->size++;
}

void free_list(list_t *l)
{
  assert(l != NULL);
  if (is_empty(l)) return;
  node_t *current_node = l->last->next;
  while (current_node != l->last)
  {
    l->last->next = current_node->next;
    free(current_node);
    current_node = l->last->next;
  }
  free(current_node);
  free(l);     
}
int get_size(list_t *l)
{
  return l->size;
}

void print_list(list_t *l)
{
  assert(l != NULL);
  if(is_empty(l)) return;
  
  node_t *current_node = l->last->next;
  do
  {
    printf("%d ", current_node->info);
    current_node = current_node->next;
  } while (current_node != l->last->next);
  printf("\n");
}

int remove_element(list_t *l, elem x)
{
  assert(l != NULL);
  if (is_empty(l)) return 0;
  
  node_t *previous_node = l->last;
  node_t *current_node = l->last->next;
  do
  {
    if (current_node->info == x)
    {
      if (current_node == l->last)l->last = previous_node;
      previous_node->next = current_node->next;
      free(current_node);  
      l->size--;
      return 1;  
    }else
    {
      previous_node = current_node;
      current_node = current_node->next;
    }   
  }while (current_node != l->last->next);
  return 0;
}

elem josephus(int n, int k)
{
  list_t *l = create_list();
  int i;
  for ( i = 0; i < n; i++)
  {
    insert(l, i + 1);
  }
  
  node_t *current_node = l->last->next;
  node_t *previous_node = l->last;
  while (l->size > 1)
  {
    for ( i = 0; i < k; i++)
    {
      previous_node = current_node;
      current_node = current_node->next;
    }
    remove_element(l, previous_node->info);
  }  
  elem result = current_node->info;
  free_list(l);
  return result;
}