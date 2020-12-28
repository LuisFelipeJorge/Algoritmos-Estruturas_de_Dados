#include <stdio.h>

#include "list.h"

int main(int argc, char const *argv[])
{
  list_t *list = create_list();
  insert(list, 5);
  insert(list, 2);
  insert(list, 3);
  insert(list, 7);
  insert(list, 8);
  
  print_list(list);
  printf("Size: %d\n", get_size(list));

  remove_element(list, 5);
  remove_element(list, 8);
  remove_element(list, 3);
  print_list(list);   
  printf("Size: %d\n", get_size(list));
  
  if (is_on_the_list(list, 7)) printf("7 is on the list\n");
  if (is_on_the_list(list, 8)) printf(" is on the list");

  insert(list, 9);
  insert(list, 1);
  insert(list, 2);
  print_list(list);   
  printf("Size: %d\n", get_size(list));

  reverse_list(list);
  print_list(list);   
  printf("Size: %d\n", get_size(list));

  free_list(list);
  return 0;
}
