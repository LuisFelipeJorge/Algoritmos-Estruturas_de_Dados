#include <stdio.h>
#include <stdlib.h>

#include "bt.h"

int main(int argc, char const *argv[])
{
  tree_t *bt = create_tree();
  insert_left(bt, 1, -1);
  insert_left(bt, 2, 1);
  insert_right(bt, 3, 1);
  insert_left(bt, 4, 3);
  insert_right(bt, 5, 3);
  insert_left(bt, 6, 4);

  print_tree(bt->root);
  printf("\n");
  
  pre_order(bt->root);
  printf("\n");

  in_order(bt->root);
  printf("\n");

  post_order(bt->root);
  printf("\n");

  in_order_i(bt);
  printf("\n");

  print_tree(bt->root);
  printf("\n");

  bfs(bt);
  printf("\n");

  print_tree(bt->root);
  printf("\n");

  free_tree(bt->root);
  free(bt);

  return 0;
}
