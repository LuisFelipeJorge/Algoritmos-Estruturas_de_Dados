#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "dictionary.h"


// RELATED TO THE DICTIONARY

struct dnode
{
  elem_t *element;
  int level;
  dnode_t *next;
  dnode_t *down; 
};

struct dictionary
{
  int level;
  int maxlevel;
  dnode_t *upleft;
};

dnode_t* create_dnode(elem_t *e, int level)
{
  dnode_t *new_node = (dnode_t*)malloc(sizeof(dnode_t));
  assert(new_node != NULL);
  new_node->level = level;
  new_node->next = NULL;
  new_node->down = NULL;

  new_node->element = (elem_t*)malloc(sizeof(elem_t));
  assert(new_node->element != NULL);
  memcpy(new_node->element, e, sizeof(elem_t));

  return new_node;
}

dnode_t* create_header(int level)
{
  elem_t aux;
  strcpy(aux.word, "");
  strcpy(aux.definition, "");
  return create_dnode(&aux, level);
}

dictionary_t* create_dictionary()
{
  dictionary_t *new_dictionary = (dictionary_t*)malloc(sizeof(dictionary_t));
  assert(new_dictionary != NULL);

  new_dictionary->level = 0;
  new_dictionary->maxlevel = MAX_LEVEL;
  new_dictionary->upleft = create_header(0);
  return new_dictionary;
}

void free_dictionary(dictionary_t *dict)
{
  while(dict->upleft != NULL)
  {
    dnode_t *current_node = dict->upleft;
    dict->upleft = current_node->down;
    while (current_node != NULL)
    {
      dnode_t *aux = current_node->next;
      free(current_node->element);
      free(current_node);
      current_node = aux;
    }
  }
  free(dict);
}

void print_dictionary(dictionary_t *dict)
{
  assert(dict != NULL);

  dnode_t **headers = (dnode_t**)malloc(sizeof(dnode_t*)*(dict->level+1));

  dnode_t *current_node = dict->upleft;
  // get all headers
  while(current_node->level != 0)
  {
    headers[current_node->level] = current_node;
    current_node = current_node->down;
  }
  headers[current_node->level] = current_node;

  for (int i = dict->level; i >= 0; i--)
  {
    current_node = headers[i]->next;
    while (current_node != NULL)
    {
      printf("{ Word: %s, ", current_node->element->word);
      printf("Def: %s}", current_node->element->definition);
      if(current_node->next != NULL) printf("->");
      current_node = current_node->next;
    }
    printf("\n");
  }

  free(headers);
}  

void print_inorder(dictionary_t *dict)
{ // Just print the level zero
  assert(dict != NULL);

  dnode_t *current_node = dict->upleft;
  // get all headers
  while(current_node->level != 0)
  {
    current_node = current_node->down;
  }
  // Level 0
  current_node = current_node->next;
  while (current_node != NULL)
  {
    printf("{ Word: %s, ", current_node->element->word);
    printf("Def: %s}", current_node->element->definition);
    if(current_node->next != NULL) printf("->");
    current_node = current_node->next;
  }
  printf("\n");
}

int search_elem(dictionary_t *dict, elem_t *e)
{
  assert(dict != NULL);

  dnode_t *current_node = dict->upleft;

  // searching on levels above 0
  while(current_node->level != 0)
  {
    // while(current_node->next != NULL && current_node->next->value < x)
    while (current_node->next != NULL && strcmp(current_node->next->element->word, e->word) < 0)
    {
      current_node = current_node->next;
    }
    current_node = current_node->down;
  }
  // searching on level 0
  // while(current_node->next != NULL && current_node->next->value <= x)
  while (current_node->next != NULL && strcmp(current_node->next->element->word, e->word) < 0)
  {
    current_node = current_node->next;
  }

  // if(current_node->value != x) return 0;
  if(current_node->next != NULL && strcmp(current_node->next->element->word, e->word) == 0) return 1;
  return 0;
}

int generate_level()
{
  int level = 0;
  while (rand()%2 != 0) level++;// 50% of chance to increase the level
  if (level <= MAX_LEVEL) return level;
  else return MAX_LEVEL;
}

dnode_t** get_updates(dictionary_t *dict, elem_t *e)
{
  assert(dict != NULL);

  dnode_t *current_node = dict->upleft;
  dnode_t **updates = (dnode_t**)malloc((dict->maxlevel)*sizeof(dnode_t*));
  
  // Finding updates positions
  while(current_node->level != 0)
  {
    // while(current_node->next != NULL && current_node->next->value < x)
    while (current_node->next != NULL && strcmp(current_node->next->element->word, e->word) < 0)
    {
      current_node = current_node->next;
    }
    updates[current_node->level] = current_node;
    current_node = current_node->down;
  }
  
  // while(current_node->next != NULL && current_node->next->value < x)
  while (current_node->next != NULL && strcmp(current_node->next->element->word, e->word) < 0)
  {
    current_node = current_node->next;
  }
  updates[current_node->level] = current_node;

  return updates;
}

int insert_elem(dictionary_t *dict, elem_t *e)
{
  assert(dict != NULL);
  if (search_elem(dict, e)) 
  {
    return 0;
  }

  dnode_t **updates = get_updates(dict, e);

  int node_level = generate_level();
  int current_level = 0;
  while(current_level <= dict->level && current_level <= node_level)
  {
    dnode_t *new_node = create_dnode(e, current_level);
    new_node->next = updates[current_level]->next;
    
    if(current_level != 0) new_node->down = updates[current_level - 1]->next;
    
    updates[current_level]->next = new_node;
    current_level++;
  }

  // creating new levels
  for(int i = dict->level + 1; i <= node_level; i++)
  {
    dnode_t *new_node = create_dnode(e, i);
    new_node->down = updates[i-1]->next;

    dnode_t *new_upleft = create_header(i);
    new_upleft->next = new_node;
    new_upleft->down = dict->upleft;
    dict->upleft = new_upleft;
    updates[i] = new_upleft;
  }

  if (node_level > dict->level) dict->level = node_level;
  free(updates);
  return 1;
}

int remove_elem(dictionary_t *dict, elem_t *e)
{
  assert(dict != NULL);
  if (!search_elem(dict, e)) 
  {
    return 0;
  }


  dnode_t** updates = get_updates(dict, e);
  
  dnode_t *current_node = NULL;
  int current_level = 0;
  while (current_level <= dict->level)
  {
    // if (updates[current_level]->next->value == x)
    if( updates[current_level]->next != NULL && strcmp(updates[current_level]->next->element->word, e->word) == 0)
    {
      current_node = updates[current_level]->next;
      updates[current_level]->next = current_node->next;
      free(current_node->element);
      free(current_node);
    }    
    current_level++;
  }

  // removes the level when there is no adjacent elements
  while (dict->upleft->next == NULL)
  {
    current_node = dict->upleft;
    dict->upleft = dict->upleft->down;
    dict->level--;
    free(current_node->element);
    free(current_node);
  }
  free(updates);
  return 1;  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// USER FUNCTIONS

dnode_t* search(dictionary_t *dict, char* word)
{
  dnode_t *current_node = dict->upleft;

  // searching on levels above 0
  while(current_node->level != 0)
  {
    // while(current_node->next != NULL && current_node->next->value < x)
    while (current_node->next != NULL && strcmp(current_node->next->element->word, word) < 0)
    {
      current_node = current_node->next;
    }
    current_node = current_node->down;
  }
  // searching on level 0
  // while(current_node->next != NULL && current_node->next->value <= x)
  while (current_node->next != NULL && strcmp(current_node->next->element->word, word) <= 0)
  {
    current_node = current_node->next;
  }

  return current_node;
}

int search_word(dictionary_t *dict, char* word)
{
  assert(dict != NULL);

  dnode_t *current_node = search(dict, word);
  if(strcmp(current_node->element->word, word) != 0) return 0;

  printf("%s %s\n", current_node->element->word, current_node->element->definition);
  return 1;
}

int change_word(dictionary_t *dict, char* word, char* definition)
{
  assert(dict != NULL);
  dnode_t *current_node = search(dict, word);
  if(strcmp(current_node->element->word, word) == 0)
  {
    strcpy(current_node->element->definition, definition);
    return 1;
  }
  return 0;
}

int print_words(dictionary_t *dict, char c)
{
  // Just print the level zero
  assert(dict != NULL);

  int found_the_word = 0;

  dnode_t *current_node = dict->upleft;
  // pass through headers
  while(current_node->level != 0)
  {
    current_node = current_node->down;
  }
  // Level 0
  current_node = current_node->next;
  while (current_node != NULL)
  {
    if (current_node->element->word[0] == c)
    { 
      found_the_word = 1;
      printf("%s %s\n", current_node->element->word, current_node->element->definition);
    }
    current_node = current_node->next;  
  }
  return found_the_word;
}

int insert_word(dictionary_t *dict, char *word, char *definition)
{
  assert(dict != NULL);
  elem_t input;
  strcpy(input.word, word);
  strcpy(input.definition, definition);

  return insert_elem(dict, &input);
}

int remove_word(dictionary_t *dict, char *word)
{
  assert(dict != NULL);
  elem_t input;
  strcpy(input.word, word);
  strcpy(input.definition, "");

  return remove_elem(dict, &input);
}