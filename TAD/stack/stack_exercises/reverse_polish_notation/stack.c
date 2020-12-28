#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ctype.h"

#include "stack.h"

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

void print_stack(stack_t *stack)
{
  for (int i = stack->top; i >= 0; i--)
  {
    printf("%d\n", *(int *)stack->items[i]);
  }  
}

void correct_end_of_string(char *string)
{
  int i = 0;
  while (string[i] != '\0')
  {
    if (string[i] == '\n')
    {
      string[i] = '\0';
    }
    i++;
  }
}

int is_operator(char in)
{
  return((in == '+')||(in == '-')||(in == '*')||(in == '/'));
}

void calculate(int value1, int value2,int input, int *result)
{
  switch (input)
  {
  case ('+'):
    *result = value1+value2;
    break;
  case ('-'):
    *result = value1-value2;
    break;
  case ('*'):
    *result = value1*value2;
    break;
  case ('/'):
    *result = value1/value2;
    break;
  
  default:
    break;
  }
}

// https://en.wikipedia.org/wiki/Reverse_Polish_notation

int evaluate_reverse_polish_expression(char *expression)
{
  stack_t *stack = create(sizeof(int));
  
  int i = 0;
  int result;
  while (expression[i] != '\0')
  {
    if (isdigit(expression[i]))
    {
      int aux = (int)expression[i] - '0';
      push(stack, &aux);
    }else
    {
      int value1, value2;
      pop(stack, &value1);
      pop(stack, &value2);
      calculate(value2, value1, expression[i], &result);
      push(stack, &result);
    }   
    i++;   
  }

  pop(stack, &result);
  free_stack(stack);
  return(result);
}