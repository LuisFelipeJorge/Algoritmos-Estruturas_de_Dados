#include <stdio.h>

#include "stack.h"

int main(int argc, char const *argv[])
{
  char input[StackSize];
  fgets(input, StackSize, stdin);
  correct_end_of_string(input);
  if (is_palindrome(input)) printf("Is a Palindrome !\n");
  else printf("Is Not a Palindrome !\n"); 
  
  return 0;
}
