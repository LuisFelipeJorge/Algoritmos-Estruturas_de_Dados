#include <stdio.h>

#include "list.h"

int main(int argc, char const *argv[])
{
  int x = 0;
  node_t *head = NULL;
  scanf("%d", &x);
  while (x != -1)
  {
    insert_node(&head, x);
    scanf("%d", &x);
  }
  print_list(&head);
  free_list(&head);
  return 0;
}
