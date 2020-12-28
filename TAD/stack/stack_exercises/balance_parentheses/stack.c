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

int is_pair(char c1, char c2)
{
  return ((c1 == '(' && c2 == ')')||(c1 == '{' && c2 == '}')||(c1 == '[' && c2 == ']'));  
}

void print_stack(stack_t *stack)
{
  for (int i = stack->top; i >= 0; i--)
  {
    printf("%c\n", *(int *)stack->items[i]);
  }  
}

int is_balanced(char *expression, int length)
{
  stack_t *s = create(sizeof(char));  
  for (int i = 0; i < length; i++)
  {
    if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
    {
      push(s, &expression[i]);
    }else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
    {
      char last_opened;
      top(s, &last_opened);
      if (is_empty(s) || !is_pair(last_opened, expression[i]))
      {
        return 0;
      }else
      {
        pop(s, &last_opened);
      }           
    }    
  }
  if (is_empty(s))
  {
    free_stack(s);
    return 1;
  }else
  {
    free_stack(s);
    return 0;
  }
}