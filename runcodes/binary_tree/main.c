#include <stdio.h>
#include <stdlib.h>

#include "bt.h"

int main(int argc, char const *argv[])
{
  tree_t *bt = create_tree();
  
  int n;
  scanf("%d", &n);
  
  for (int i = 0; i < n; i++)
  {
    int id, left_child, right_child;
    scanf("%d %d %d", &id, &left_child, &right_child);
    if (i == 0) insert_left(bt, id, -1);
    
    if (left_child != -1) insert_left(bt, left_child, id);
    if (right_child != -1) insert_right(bt, right_child, id);      
     
  }
  
  print_tree(bt->root, -1);

  free_tree(bt->root);
  free(bt);

  return 0;
}
