#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "skip.h"

struct node
{
  elem value;
  int level;
  node_t *next;
  node_t *down; 
};

struct skiplist
{
  int level;
  int maxlevel;
  node_t *upleft;
};

node_t* create_node(elem x, int level)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  assert(new_node != NULL);
  new_node->value = x;
  new_node->level = level;
  new_node->next = NULL;
  new_node->down = NULL;
  return new_node;
}

skiplist_t* create_skiplist()
{
  skiplist_t *new_skiplist = (skiplist_t*)malloc(sizeof(skiplist_t));
  assert(new_skiplist != NULL);
  new_skiplist->level = 0;
  new_skiplist->maxlevel = MAX_LEVEL;
  new_skiplist->upleft = create_node(-1, 0);
  return new_skiplist;
}

void free_skiplist(skiplist_t *sl)
{
  while(sl->upleft != NULL)
  {
    node_t *current_node = sl->upleft;
    sl->upleft = current_node->down;
    while (current_node != NULL)
    {
      node_t *aux = current_node->next;
      free(current_node);
      current_node = aux;
    }
  }
  free(sl);
}

void print_skiplist(skiplist_t *sl)
{
  assert(sl != NULL);

  node_t **headers = (node_t**)malloc(sizeof(node_t*)*(sl->level+1));

  node_t *current_node = sl->upleft;
  // get all headers
  while(current_node->level != 0)
  {
    headers[current_node->level] = current_node;
    current_node = current_node->down;
  }
  headers[current_node->level] = current_node;

  for (int i = sl->level; i >= 0; i--)
  {
    current_node = headers[i]->next;
    while (current_node != NULL)
    {
      printf("%d", current_node->value);
      if(current_node->next != NULL) printf("->");
      current_node = current_node->next;
    }
    printf("\n");
  }

  free(headers);
}  

void print_inorder(skiplist_t *sl)
{ // Just print the level zero
  assert(sl != NULL);

  node_t *current_node = sl->upleft;
  // get all headers
  while(current_node->level != 0)
  {
    current_node = current_node->down;
  }
  // Level 0
  current_node = current_node->next;
  while (current_node != NULL)
  {
    printf("%d", current_node->value);
    if(current_node->next != NULL) printf("->");
    current_node = current_node->next;
  }
  printf("\n");
}

int search_elem(skiplist_t *sl, elem x)
{
  assert(sl != NULL);

  node_t *current_node = sl->upleft;

  // searching on levels above 0
  while(current_node->level != 0)
  {
    while(current_node->next != NULL && current_node->next->value < x)
    {
      current_node = current_node->next;
    }
    current_node = current_node->down;
  }
  // searching on level 0
  while(current_node->next != NULL && current_node->next->value <= x)
  {
    current_node = current_node->next;
  }

  if(current_node->value != x) return 0;
  return 1;
}

int generate_level()
{
  srand(time(NULL));
  int level = 0;
  while (rand()%2 != 0) level++;// 50% of chance to increase the level
  if (level <= MAX_LEVEL) return level;
  else return MAX_LEVEL;
}

node_t** get_updates(skiplist_t *sl, elem x)
{
  assert(sl != NULL);

  node_t *current_node = sl->upleft;
  node_t **updates = (node_t**)malloc((sl->level+1)*sizeof(node_t*));
  
  // Finding updates positions
  while(current_node->level != 0)
  {
    while(current_node->next != NULL && current_node->next->value < x)
    {
      current_node = current_node->next;
    }
    updates[current_node->level] = current_node;
    current_node = current_node->down;
  }
  
  while(current_node->next != NULL && current_node->next->value < x)
  {
    current_node = current_node->next;
  }
  updates[current_node->level] = current_node;

  return updates;
}

int insert_elem(skiplist_t *sl, elem x)
{
  assert(sl != NULL);
  if (search_elem(sl, x)) return 0;

  node_t **updates = get_updates(sl, x);

  int node_level = generate_level();
  int current_level = 0;
  while(current_level <= sl->level && current_level <= node_level)
  {
    node_t *new_node = create_node(x, current_level);
    new_node->next = updates[current_level]->next;
    
    if(current_level != 0) new_node->down = updates[current_level - 1]->next;
    
    updates[current_level]->next = new_node;
    current_level++;
  }

  // creating new levels
  for(int i = sl->level + 1; i <= node_level; i++)
  {
    node_t *new_node = create_node(x, i);
    new_node->down = updates[i-1]->next;

    node_t *new_upleft = create_node(-1, i);
    new_upleft->next = new_node;
    new_upleft->down = sl->upleft;
    sl->upleft = new_upleft;
    updates[i] = new_upleft;
  }

  if (node_level > sl->level) sl->level = node_level;
  free(updates);
  return 1;
}

int remove_elem(skiplist_t *sl, elem x)
{
  assert(sl != NULL);
  if (!search_elem(sl, x)) return 0;


  node_t** updates = get_updates(sl, x);
  
  node_t *current_node = NULL;
  int current_level = 0;
  while (current_level <= sl->level)
  {
    if (updates[current_level]->next->value == x)
    {
      current_node = updates[current_level]->next;
      updates[current_level]->next = current_node->next;
      free(current_node);
    }    
    current_level++;
  }

  // removes the level when there is no adjacent elements
  while (sl->upleft->next == NULL)
  {
    current_node = sl->upleft;
    sl->upleft = sl->upleft->down;
    sl->level--;
    free(current_node);
  }
  free(updates);
  return 1;  
}

