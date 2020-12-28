#include <stdio.h>

#include "priority_queue.h"

int main(int argc, char const *argv[])
{
  queue_t *q = create_queue();
  elem x;

  insert_elem(q, 4, 5);
  insert_elem(q, 7, 1);
  insert_elem(q, 0, 10);
  insert_elem(q, 2, 3);
  insert_elem(q, 8, 9);

  while (!queue_is_empty(q))
  {
    remove_elem(q, &x);
    printf("%d ", x);
  }
  
  free_queue(q);
  return 0;
}
