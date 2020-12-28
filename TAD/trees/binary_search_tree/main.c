#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main(int argc, char const *argv[])
{
  tree_t *bt = create_tree();
  
  insert_node(&bt->root, 5);
  insert_node(&bt->root, 3);
  insert_node(&bt->root, 7);
  insert_node(&bt->root, 9);
  insert_node(&bt->root, 8);
  insert_node(&bt->root, 2);

  print_tree(bt->root);
  printf("\n");
  
  pre_order(bt->root);
  printf("\n");

  in_order(bt->root);
  printf("\n");

  post_order(bt->root);
  printf("\n");

  remove_node(&bt->root, 5);
  print_tree(bt->root);
  printf("\n");

  free_tree(bt->root);
  free(bt);

  return 0;
}
