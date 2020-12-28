#include <stdio.h>
  
#include "stack.h"

int main(int argc, char const *argv[]){
  stack_t *stack = create();
  
  // decimal to binary conversion
  
  int x;
  scanf("%d", &x);
  while (x > 0){
    push(stack, (x%2));
    x = x/2;
  }
  print_stack(stack);
  free_stack(stack);
  return 0;
}
