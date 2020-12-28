#include "registration.h"

char* read_string(FILE* stream){
  char* string = NULL;
  int number_of_letters = 0;
  char input;

  do{
    input = fgetc(stream);
    if (input != '\r'){
      number_of_letters += 1;
      string = (char*)realloc(string, number_of_letters*sizeof(char));
      if (string != NULL){
        string[number_of_letters - 1] = input;
      }      
    }  
  } while (input != '\0' && input != '\n');

  string = (char*)realloc(string, number_of_letters*sizeof(char));
  if (string != NULL){
    string[number_of_letters - 1] = '\0';
  }  

  return string;
}

person_t* create_person(char* name, char* address){
  person_t *person = NULL;
  person = (person_t*)malloc(sizeof(person_t));
  if (person != NULL){
    size_t name_size = strlen(name);
    size_t address_size = strlen(address);
    person->name = (char*)malloc(name_size*sizeof(char));
    person->address = (char*)malloc(address_size*sizeof(char)); 
    if (person->name != NULL && person->address != NULL){
      strcpy(person->name, name);
      strcpy(person->address, address);
    }         
  }  
  return person;
}

record_t* create_record(){
  record_t* records = (record_t*)malloc(sizeof(record_t));
  records->top = -1;
  return records;
}


void free_person(person_t *person){
  if (person != NULL){
    free(person->name);
    free(person->address);
    free(person);
    person = NULL;    
  }
}

void free_records(record_t *records){
  int i;
  for ( i = 0; i <= records->top; i++){
    free_person(records->record[i]);
  }
  free(records);
}

void print_person(person_t *person){
  printf("Name: %s\nAddres: %s\n", person->name, person->address);
}

void print_record(record_t *records){
  int i;
  for ( i = 0; i <= records->top; i++){
    print_person(records->record[i]);
  }  
}

void insert_person(record_t *records,person_t *person){
  if (person != NULL && records->top < N)
  { 
    records->top++;
    records->record[records->top] = person;
  }  
}

int search_person(record_t *records, char* name){
  int i;
  for ( i = 0; i < N; i++){
    if (records->record[i]->name == name){
      return i;
    }    
  }
  return -1;
}

void delete_person(record_t *records, char* name){
  int index = search_person(records, name);
  if (index != -1){
    free_person(records->record[index]);
    records->record[index] = NULL;
    records->top--;
  }  
}