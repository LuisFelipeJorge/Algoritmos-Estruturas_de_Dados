#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int main(int argc, char const *argv[])
{
  char vars[5];
  int exps[3];
  poly_t *poly = create_poly();

  strcpy(vars, "XYZ");
  exps[0] = 2; exps[1] = 3; exps[2] = 1;
  add_term(poly, 4, vars, exps);
  
  strcpy(vars, "XY");
  exps[0]=1; exps[1] = 1;
  add_term(poly, -3, vars, exps);

  strcpy(vars, "");
  add_term(poly, 5, vars, exps);

  print_polynomial(poly);
  printf("Result: %.3f\n", calculate_polynomial(poly, -1, 1, 1));

  free_poly(poly);

  return 0;
}
