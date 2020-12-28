#include <stdio.h>

#include "josephus.h"

int main(int argc, char const *argv[])
{
  int number_of_tests;
  int n, k;

  scanf("%d", &number_of_tests);

  for (int i = 0; i < number_of_tests; i++)
  {
    scanf("%d %d", &n, &k);
    printf("Caso %d: %d\n", i+1, josephus(n,k));  
  }

  return 0;
}
