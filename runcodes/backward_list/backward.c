#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "backward.h"

struct node
{
  node_t *next, *previous, *back;
  int key, time;
};

struct list
{
  node_t *start, *end;
  int size, time;
};

node_t* create_node(int value, int time)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  assert(new_node != NULL);
  new_node->key = value;
  new_node->time = time;
  new_node->back = NULL;
  new_node->previous = NULL;
  new_node->back = NULL;
  return new_node;
}

list_t* create_list()
{
  list_t *new_list = (list_t*)malloc(sizeof(list_t));
  new_list->end = NULL;
  new_list->start = NULL;
  new_list->time = 0;
  new_list->size = 0;
  return new_list;
}

int is_empty(list_t *l)
{
  return l->size == 0;
}

void insert(list_t *l, int value, int back)
{

  assert( l != NULL);

  node_t *new_node = create_node(value, l->time);
  if (is_empty(l))
  {
    l->start = new_node;
  }else
  {
    new_node->previous = l->end;
    l->end->next = new_node;
  }  
  l->end = new_node; 
  l->size++;
  
  l->end->time = l->time;
  l->time++;

  if ( back == 0) return;
  node_t *current_node = l->end;
  int i = 0;
  while (current_node != NULL && i < back)
  {
    current_node = current_node->previous; 
    i++;
  }
  if (current_node == NULL) l->end->back = NULL;
  else l->end->back = current_node;
}

int get_node_position(list_t *l, node_t *n)
{
  assert(n != NULL);
  node_t *current_node = l->start;
  int position = 0;
  
  while (current_node != n && current_node != NULL)
  {
    position++;
    current_node = current_node->next;
  }
  return position;
}

void print_list(list_t *l)
{
  if (is_empty(l)) 
  {
    printf("-1");
    return;
  }
  node_t *current_node = l->start;
  while (current_node != NULL)
  {
    printf("[%d,%d", current_node->key, current_node->time);
    if (current_node->back == NULL) printf("] ");
    else
    {
      printf(",%d] ", get_node_position(l, current_node->back));
    }    
    current_node = current_node->next;
  }
  printf("\n");
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

void update_back(list_t *l, node_t *removed_node)
{
  node_t *current_node = l->start;
  while (current_node != NULL)
  {
    if (current_node->back == removed_node) current_node->back = NULL;
    current_node = current_node->next;
  }  
}

int remove_element(list_t *l, int value)
{
  assert(l != NULL);  
  l->time++;

  node_t *previous = NULL;
  node_t *current_node = l->start;
  while (current_node != NULL)
  {
    if (current_node->key == value){
      if(current_node == l->start){ // remove the first element
        l->start = l->start->next;
        update_back(l, current_node);
        free(current_node);
      }else if (current_node == l->end) // remove the last element
      {
        l->end = previous;
        l->end->next = NULL;
        update_back(l, current_node);
        free(current_node);
      }else
      {
        previous->next = current_node->next;
        update_back(l, current_node);
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
