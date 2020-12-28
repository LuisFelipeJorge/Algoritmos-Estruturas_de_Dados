#include <stdio.h>
#include <string.h>

#include "stack.h"

int main(int argc, char const *argv[])
{
  char expression[StackSize];
  fgets(expression, StackSize, stdin);
  int len = strlen(expression);
  if (is_balanced(expression, len)) printf("Is Balanced!\n");
  else printf("Not Balanced!\n");  
  
  return 0;
}
