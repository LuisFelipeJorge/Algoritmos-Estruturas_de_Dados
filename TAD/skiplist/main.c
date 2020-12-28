#include <stdio.h>

#include "skip.h"

int main(void) 
{

  int input[6] = {4 , 6, 3, 3 , 5, 1};
  skiplist_t *sl = create_skiplist();
  for (int i = 0; i < 6; i++)
  {
    insert_elem(sl, input[i]);  
  }
  print_skiplist(sl);
  printf("\n");
  
  print_inorder(sl);
  printf("\n");
  
  remove_elem(sl, 3);
  print_skiplist(sl);
  printf("\n");
  print_inorder(sl);
  printf("\n");

  free_skiplist(sl);

  return 0;
}