#include <stdio.h>
#include <stdlib.h>

#include "db.h"

int main(int argc, char const *argv[])
{
  database_t *db = create();
  elem x;
  insert(db, 1);
  insert(db, 2);
  insert(db, 3);
  insert(db, 4);
  insert(db, 5);
  while (!is_empty(db))
  {
    remove_elem(db, &x);
    printf("%d ", x);
  }
  printf("\n");
  free_database(db);
  return 0;
}
