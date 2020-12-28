#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

struct node
{
  elem info;
  node_t *next;
};

struct list
{
  node_t *start, *end;
  int size;
};

node_t* create_node(elem value)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  assert(new_node != NULL);
  new_node->next = NULL;
  new_node->info = value;
  return new_node;
}

list_t* create_list()
{
  list_t *l = (list_t*)malloc(sizeof(list_t));
  assert(l != NULL);
  l->start = NULL;
  l->end = NULL;
  l->size = 0;
  return l;
}

int is_empty(list_t *l)
{
  return (l->size == 0);
}

void free_list(list_t *l)
{
  if (l != NULL)
  {
    node_t *current_node = l->start;
    while (current_node != NULL)
    {
      l->start = current_node->next;
      free(current_node);
      current_node = l->start;
    }
    free(l);
  }return;  
}

void insert(list_t *l, elem value)
{
  assert( l != NULL);

  if (is_on_the_list(l, value)) return; // does not allow repeated elements

  node_t *new_node = create_node(value);
  if (is_empty(l))
  {
    l->start = new_node;
  }else
  {
    l->end->next = new_node;
  }  
  l->end = new_node; 
  l->size++;
}

int get_size(list_t *l)
{
  assert(l != NULL);
  return l->size;
}

void print_list(list_t *l)
{
  assert(l != NULL);
  node_t *current_node = l->start;
  while (current_node != NULL)
  {
    printf("%d ", current_node->info);
    current_node = current_node->next;
  }
  printf("\n");  
}

int is_on_the_list(list_t *l, elem x)
{
  assert(l!=NULL);
  node_t *current_node = l->start;
  while (current_node != NULL)
  {
    if (current_node->info == x) return 1;
    current_node = current_node->next;
  }
  return 0;
}

int remove_element(list_t *l, elem x)
{ 
  assert(l != NULL);
  node_t *previous = NULL;
  node_t *current_node = l->start;
  while (current_node != NULL)
  {
    if (current_node->info == x){
      if(current_node == l->start){ // remove the first element
        l->start = l->start->next;
        free(current_node);
      }else if (current_node == l->end) // remove the last element
      {
        l->end = previous;
        l->end->next = NULL;
        free(current_node);
      }else
      {
        previous->next = current_node->next;
        free(current_node);
      }     
      l->size--;
      return 1;
    }else
    {
      previous = current_node;
      current_node = current_node->next;
    }    
  }
  return 0; 
}

void reverse_list(list_t *list)
{
  assert(list != NULL);
  node_t *previous_node = NULL;
  node_t *next_node = NULL;
  node_t *current_node = list->start;
  list->end = current_node;

  while (current_node != NULL)
  {
    next_node = current_node->next;
    current_node->next = previous_node;
    previous_node = current_node;
    current_node = next_node;
  }
  list->start = previous_node;
}