#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define StackSize 100000

typedef int element;
typedef struct stack
{
  int top;
  void **items;
  int element_size;
}stack_t;

stack_t* create(int);
void print_stack(stack_t *stack);
void free_stack(stack_t*);
int is_empty(stack_t*);
int is_full(stack_t*);  
int push(stack_t*, void*);
int pop(stack_t*, void*);
int top(stack_t*, void*);