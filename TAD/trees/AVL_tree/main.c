#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int main(int argc, char const *argv[])
{
  tree_t *bt = create_tree();
  
  insert_node(bt, 5);
  insert_node(bt, 3);
  insert_node(bt, 7);
  insert_node(bt, 8);
  insert_node(bt, 2);
  insert_node(bt, 10);
  insert_node(bt, 15);

  print_tree(bt->root);
  printf("\n");
  
  pre_order(bt->root);
  printf("\n");

  in_order(bt->root);
  printf("\n");

  post_order(bt->root);
  printf("\n");

  remove_node(bt, 2);
  print_tree(bt->root);
  printf("\n");

  free_tree(bt->root);
  free(bt);

  return 0;
}
