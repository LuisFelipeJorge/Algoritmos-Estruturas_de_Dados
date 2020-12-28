#include "registration.h"

int main(int argc, char const *argv[])
{
  record_t *records = create_record();
  int number_of_persons = 3;

  int i;
  for ( i = 0; i < number_of_persons; i++){
    char *name = read_string(stdin);
    char *address =read_string(stdin);
    person_t *p = create_person(name, address);
    insert_person(records, p);
  }

  print_record(records);
  free_records(records);
  return 0;
}
