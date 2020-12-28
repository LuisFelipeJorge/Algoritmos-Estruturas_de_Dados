#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

struct node
{
  int value;
  node_t *next;
};

node_t* create_node(int value)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  assert(new_node != NULL);
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

void insert_node(node_t **head, int value)
{ 
  node_t *new_node = create_node(value);
  if (*head == NULL)
  {
    *head = new_node;
    return;
  }
  node_t *last_node_reference = *head;
  while (last_node_reference->next != NULL)
  {
    last_node_reference = last_node_reference->next;
  }
  last_node_reference->next = new_node;
  return;  
}


void print_list(node_t **head)
{
  if (*head == NULL) return;
  node_t *current_node = *head;
  while (current_node->next != NULL)
  {
    printf("%d ", current_node->value);
    current_node = current_node->next;
  }
  printf("%d ", current_node->value);
  return;
}

void free_list(node_t **head)
{
  node_t *current, *next;
  current = *head;
  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }  
  return;
}
