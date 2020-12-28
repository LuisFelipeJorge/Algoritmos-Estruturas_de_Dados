#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

typedef struct person_t{
  char *name;
  char* address;
}person_t;

typedef struct record_t{
  int top;
  person_t* record[N];
}record_t;


char* read_string(FILE* stream);
person_t* create_person(char* name, char* address);
record_t* create_record();
void print_person(person_t *person);
void print_record(record_t *records);
void free_person(person_t* person);
void free_records(record_t *records);
void insert_person(record_t *records,person_t *person);
int search_person(record_t *records, char* name);
void delete_person(record_t *records, char* name);
// int search_person(char* name);
