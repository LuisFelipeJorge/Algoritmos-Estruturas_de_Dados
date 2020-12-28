#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

typedef struct stack
{
  int top;
  element items[StackSize];
}stack_t;

stack_t* create(){
  stack_t *s = (stack_t*)malloc(sizeof(stack_t));
  assert(s != NULL);
  s->top = -1;
  return s;
}

void print_stack(stack_t *stack){
  element x;
  while (!is_empty(stack)){
    pop(stack, &x);
    printf("%d ", x);
  }  
  printf("\n");
}

void free_stack(stack_t *stack){
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

int push(stack_t *stack, element x){
  assert(stack != NULL);
  if (is_full(stack)) return -1;
  stack->top++;
  stack->items[stack->top] = x;
  return 1;  
}

int pop(stack_t *stack, element *x){
  assert(stack != NULL);
  if (is_empty(stack)) return -1;
  *x = stack->items[stack->top];
  stack->top--;
  return 1;
}

int top(stack_t *stack, element *x){
  assert(stack != NULL);
  if (is_empty(stack)) return -1;
  *x = stack->items[stack->top];
  return 1;
}

