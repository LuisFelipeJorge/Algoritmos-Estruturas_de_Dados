#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

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
  queue_t *queue = create_queue(sizeof(point_t));
  point_t p;
  for (int i = 0; i < 10; i++)
  {
    p.x = i;
    p.y = -i;
    enqueue(queue, &p);
  }

  node_t *current_node = get_start(queue);
  while (current_node != NULL)
  {
    get_info(current_node, &p, sizeof(point_t));
    print_point(&p);
    current_node = get_next(current_node);
  }
  printf("\n");
  printf("Size: %d\n", get_size(queue));
  printf("\n");
  
  dequeue(queue, &p);
  print_point(&p);
  dequeue(queue, &p);
  print_point(&p);
  dequeue(queue, &p);
  print_point(&p);
  enqueue(queue, &p);
  printf("\n");

  current_node = get_start(queue);
  while (current_node != NULL)
  {
    get_info(current_node, &p, sizeof(point_t));
    print_point(&p);
    current_node = get_next(current_node);
  }
  printf("\n");
  printf("Size: %d\n", get_size(queue));
  printf("\n");

  free_queue(queue);

  return 0;
}
