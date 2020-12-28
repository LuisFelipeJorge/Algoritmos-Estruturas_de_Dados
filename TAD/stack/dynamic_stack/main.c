#include <stdio.h>

#include "stack.h"

typedef struct point
{
  int x,y;
}point_t;

void print_point(point_t *p)
{
  printf("(%d, %d) ", p->x, p->y);
}

int main(int argc, char const *argv[])
{
  stack_t *stack = create_stack(sizeof(point_t));
  point_t p;
  for (size_t i = 0; i < 10; i++)
  {
    p.x = i;
    p.y = -i;
    push(stack, &p);
  }
  node_t *current_node = get_top(stack);
  while (current_node != NULL)
  {
    get_info(current_node, sizeof(point_t), &p);
    print_point(&p);
    current_node = get_next(current_node);
  }
  printf("\n");  

  pop(stack, &p);
  print_point(&p);
  printf("\n");

  current_node = get_top(stack);
  while (current_node != NULL)
  {
    get_info(current_node, sizeof(point_t), &p);
    print_point(&p);
    current_node = get_next(current_node);
  }
  printf("\n");

  free_stack(stack);

  return 0;
}
