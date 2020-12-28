#include  <stdio.h>

int main(int argc, char const *argv[])
{
  int i;
  i = 100;
  printf("Int: %lu bytes\n", sizeof(i));
  printf("Char: %lu bytes\n", sizeof(char));

  char *p = (char *)&i;
  int k = 0;
  for (k = 0; k < sizeof(int); k++){
    printf("%.2x ", *p);
    p++;
  }  

  return 0;
}
