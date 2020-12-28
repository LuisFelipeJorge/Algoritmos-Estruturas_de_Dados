#include <stdio.h>

#include "queue.h"

int main(int argc, char const *argv[])
{
  queue_t *q;
  int i;
  elem x;
  q = create();
  for ( i = 0; i < 10; i++)
  {
    enqueue(q, i);
  }

  dequeue(q, &x);
  printf("%d ", x);
  printf("\n"); 
  
  enqueue(q, 11);

  while (!is_empty(q))
  {
    dequeue(q, &x);
    printf("%d ", x);
  }
  printf("\n"); 
  free_queue(q);
  return 0;
}
