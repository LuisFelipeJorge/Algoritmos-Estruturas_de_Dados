#include <stdio.h>

#include "stack.h"

int main(int argc, char const *argv[])
{  
  char expression[StackSize];
  fgets(expression, StackSize, stdin);
  correct_end_of_string(expression);

  int x = evaluate_reverse_polish_expression(expression);
  printf("Result: %d\n", x);
  
  return 0;
}
