#include <stdbool.h>

#define N 100
typedef struct set_t{
  int *elements;
  int number_of_elements;
}set_t;

set_t* create_set(int* arr, int size);
void free_set(set_t *set);
void print_set(set_t *set);
set_t* set_union(set_t *a, set_t *b);
set_t* set_intersection(set_t *a, set_t *b);
set_t* set_difference(set_t *a, set_t *b);
bool is_in_the_set(int x, set_t* a);
void set_insert(int x, set_t* a);
void set_remove(int x, set_t* a);
void set_assign(set_t *a, set_t *b);
int set_min(set_t *a);
int set_max(set_t *a);
bool are_equals(set_t *a, set_t *b);