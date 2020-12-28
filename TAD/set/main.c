#include <stdio.h>
#include "set.h"

int main(int argc, char const *argv[]){
  int test1[] = {1, 2 , 3, 4};
  int test2[] = {1,4, 5, 8};
  set_t *a = create_set(test1, 4);
  set_t *b = create_set(test2, 4);

  printf("A :");
  print_set(a);
  printf("Min A: %d\n", set_min(a));
  printf("B :");
  print_set(b);
  printf("Max B: %d\n", set_max(b));

  set_t *c = set_union(a, b);
  printf("Union: ");
  print_set(c);
  printf("%d\n", c->number_of_elements);

  set_t *d = set_intersection(a, b);
  printf("Intersection: ");
  print_set(d);
  printf("%d\n", d->number_of_elements);

  set_t *e = set_difference(a, b);
  printf("Difference: ");
  print_set(e);
  printf("%d\n", e->number_of_elements);

  if (is_in_the_set(2,a))printf("2 is within a\n");
  if (is_in_the_set(2,b))printf("2 is not in b");   

  set_insert(9, a);
  set_remove(1, a);
  print_set(a);

  set_assign(b, a);
  print_set(b);

  if (are_equals(a,b))printf("A is equivalent to B\n");

  free_set(a);
  free_set(b);
  free_set(c);
  free_set(d);
  free_set(e);

  return 0;
}
