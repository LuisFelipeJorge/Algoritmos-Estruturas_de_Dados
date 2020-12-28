#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

typedef struct stack
{
  int top;
  void **items;
  int element_size;
}stack_t;

stack_t* create(int element_size){
  stack_t *s = (stack_t*)malloc(sizeof(stack_t));
  assert(s != NULL);
  s->items = (void**)malloc(sizeof(void*)*StackSize);
  assert(s->items != NULL);
  s->top = -1;
  s->element_size = element_size;
  return s;
}

void free_stack(stack_t *stack){
  while (stack->top >= 0)
  {
    free(stack->items[stack->top]);
    stack->top -= 1;
  }  
  assert(stack->items != NULL);
  free(stack->items);
  assert(stack != NULL);    
  free(stack);
  stack = NULL;  
}

int is_full(stack_t *stack){
  assert(stack != NULL);
  return (stack->top == StackSize - 1);
}

int is_empty(stack_t *stack){
  assert(stack != NULL);
  return (stack->top == -1);
}

int push(stack_t *stack, void *x){
  assert(stack != NULL);
  if (is_full(stack)) return -1;

  stack->top++;
  stack->items[stack->top] = (void*)malloc(stack->element_size);
  assert(stack->items[stack->top] != NULL);

  memcpy(stack->items[stack->top], x, stack->element_size);
  return 1;  
}

int pop(stack_t *stack, void *x){
  assert(stack != NULL);

  if (is_empty(stack)) return -1;
  memcpy(x, stack->items[stack->top], stack->element_size);
  free(stack->items[stack->top]);
  stack->top--;

  return 1;
}

int top(stack_t *stack, void *x){
  assert(stack != NULL);

  if (is_empty(stack)) return -1;
  memcpy(x, stack->items[stack->top], stack->element_size);

  return 1;
}

int is_palindrome(char *string)
{
  stack_t *s=create(sizeof(char));
  int len = strlen(string);
  int midle = len/2;
  int i;
  for (i = 0; i < midle; i++)
  {
    push(s, &string[i]);
  }
  if (len % 2 == 0) i = 0;
  else i = 1;
  
  
  while (s->top>=0)
  {
    char top;
    pop(s, &top);
    if (top != string[i+midle])
    {
      free_stack(s);
      return 0;
    }
    i++;
  }
  free_stack(s);
  return 1;
}


void correct_end_of_string(char *string)
{
  int i = 0;
  while (string[i] != EOF)
  {
    if (string[i] == '\n')
    {
      string[i] = '\0';
    }
    i++;
  }
}