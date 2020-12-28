#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

void free_list(node_t *list)
{
  node_t *current_node;

  while (list != NULL)
  {
    if (list->type == 1) free_list(list->info.sublist);
    
    current_node = list;
    list = list->next;
    free(current_node);   
  }  
}

node_t* create_atom(elem x)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  new_node->type = 0;
  new_node->info.atom = x;
  new_node->next = NULL;
  return new_node;
}

node_t* create_sublist(node_t *sublist)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  new_node->type = 1;
  new_node->info.sublist = sublist;
  new_node->next = NULL;
  return new_node;
}

node_t* concat(node_t *node1, node_t *node2)
{
  assert(node1 != NULL);
  node1->next = node2;
  return node1;
}

info_t get_head(node_t *list, int *type)
{
  assert(list != NULL);
  *type = list->type;
  return list->info;
}

node_t* get_tail(node_t *list)
{
  assert(list != NULL);
  return list->next;
}

void print(node_t *start)
{
  if (start == NULL) return;
  node_t *current_node = start;
  printf("(");
  while (current_node != NULL)
  {
    if (current_node->type == 0) printf("%d", current_node->info.atom);
    else print(current_node->info.sublist);

    if (current_node->next != NULL) printf(", ");
    current_node = current_node->next;
  }
  printf(")");  
}

void print_list(node_t *start){
  print(start);
  printf("\n");
}

int is_in_the_list(node_t *start, elem x)
{
  if (start == NULL) return 0;
  int result = 0;
  node_t *current_node = start;
  while (current_node != NULL)
  {
    if(current_node->type == 1) 
    {
      result = is_in_the_list(current_node->info.sublist, x);
      if (result) return result;      
    } else if (current_node->info.atom == x) return 1;
    current_node = current_node->next;
  }
  return 0;
}

int get_depth(node_t *start)
{
  if (start == NULL) return 0;
  int depth = 0;
  node_t *current_node = start;
  while (current_node != NULL)
  {
    if (current_node->type == 1) depth = get_depth(current_node->info.sublist);    
    current_node = current_node->next;
  }
  return depth+1;  
}

int are_the_same(node_t *list1, node_t *list2)
{
  if (list1 == NULL && list2 == NULL) return 1;
  if ((list1 != NULL && list2 == NULL) || (list1 == NULL && list2 != NULL)) return 0;
  node_t *current_node1 = list1;
  node_t *current_node2 = list2;

  int result = 0;

  while (current_node1 != NULL && current_node2 != NULL)
  {
    if (current_node1->type != current_node2->type) return 0;
    if (current_node1->type == 0 && current_node1->info.atom != current_node2->info.atom) return 0;
    if (current_node1->type == 1) 
    {
      result = are_the_same(current_node1->info.sublist, current_node2->info.sublist);
      if(!result) return 0; 
    }
    current_node1 = current_node1->next;
    current_node2 = current_node2->next;
  }
  if ((current_node1 != NULL && current_node2 == NULL) || (current_node1 == NULL && current_node2 != NULL)) return 0;
  return 1;
}