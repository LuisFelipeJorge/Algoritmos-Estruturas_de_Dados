#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char const *argv[])
{
  node_t *l1 = concat(create_atom(3), create_atom(4));
  node_t *l2 = create_sublist(l1);
  l2 = concat(l2, create_atom(2));
  node_t *l = concat(create_atom(1), l2);
  print_list(l);

  int type;
  info_t head = get_head(l, &type);
  if (type == 1) print_list(head.sublist);
  else printf("%d\n", head.atom);
  node_t *tail = get_tail(l);
  print_list(tail);

  if (is_in_the_list(l, 4)) printf("4 is in the list\n");
  if (!is_in_the_list(l, 5)) printf("5 is not in the list\n");
  if(is_in_the_list(l, 2)) printf("2 is in the list\n");
  
  printf("depth: %d\n", get_depth(l));
  
  if (are_the_same(l2, tail)) printf("Are the same\n");
  if (!are_the_same(l, l2)) printf("Are not the same\n");


  free_list(l);
  return 0;
}
