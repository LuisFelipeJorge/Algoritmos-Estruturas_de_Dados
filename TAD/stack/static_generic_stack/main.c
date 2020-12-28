#include <stdio.h>

#include "stack.h"

typedef struct point
{
  int x,y;  
}point_t;


int main(int argc, char const *argv[])
{

  stack_t *stack = create(sizeof(point_t));
  point_t p;
  for (int i = 0; i < 10; i++)
  {
    p.x = i;
    p.y = -i;
    push(stack, &p);
  }
  
  while (!is_empty(stack))
  {
    pop(stack, &p);
    printf("(%d, %d) ", p.x, p.y); 
  }
  
  free_stack(stack);
  return 0;
}
