#include "queue.h"

typedef struct point
{
  int x, y;
}point_t;

void print_point(point_t p)
{
  printf("(%d, %d) ", p.x, p.y);
}

int main(int argc, char const *argv[])
{
  queue_t *q = create(sizeof(point_t));
  point_t p; 
  int i;
  for ( i = 0; i < 10; i++)
  {
    p.x = i;
    p.y = -i;
    enqueue(q, &p);
  }

  // print queue
  
  for ( i = get_start(q); i < get_end(q); i++)
  {
    get_element(q, i%QueueSize, &p);
    print_point(p);
  } 
  printf("\n");

  dequeue(q, &p);
  for ( i = get_start(q); i < get_end(q); i++)
  {
    get_element(q, i%QueueSize, &p);
    print_point(p);
  } 

  printf("\n");

  // print reverse
  for ( i = get_end(q)-1; i >= get_start(q); i--)
  {
    get_element(q, i, &p);
    print_point(p);
  } 
  printf("\n");


  while (!is_empty(q))
  {
    dequeue(q, &p);
    printf("(%d, %d) ", p.x, p.y);
  }
  printf("\n"); 
  free_queue(q);
  return 0;
}
