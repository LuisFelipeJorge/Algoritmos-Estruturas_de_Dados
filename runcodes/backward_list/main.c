#include <stdio.h>
#include <stdlib.h>

#include "backward.h"

int main(int argc, char const *argv[])
{  
  list_t *l = create_list();
  char input_type; 
  int key, back_position;

  scanf("%c", &input_type);
  while (input_type != 'f')
  {
    if (input_type == 'i')
    {
      scanf("%d %d", &key, &back_position);
      insert(l, key, back_position);
    }else if (input_type == 'r')
    {
      scanf("%d", &key);
      remove_element(l, key);
    }
    scanf("%c", &input_type);
  }
  

  print_list(l);
  free_list(l);

  return 0;
}
