#include <stdio.h>
#include <stdlib.h>

typedef struct stream_t{
  char** rows;
  int number_of_rows;
}stream_t;


////////////////////////////////////////////////////////////
// functions declarations
stream_t read_stream(FILE* stream);
void print_stream(stream_t strings);

////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]){
  stream_t strings;
  strings = read_stream(stdin);
  printf("\nNumber of Rows: %d\n", strings.number_of_rows);
  print_stream(strings);
  return 0;
}

////////////////////////////////////////////////////////////
// functions definitions 

stream_t read_stream(FILE* stream){

  stream_t strings;
  strings.rows = NULL;
  strings.number_of_rows = 0;


  int number_of_letters = 0;
  char input;

  do{
    strings.number_of_rows += 1;
    strings.rows = (char**)realloc(strings.rows, strings.number_of_rows*sizeof(char*));
    if (strings.rows != NULL){
      strings.rows[strings.number_of_rows - 1] = NULL;
      number_of_letters = 0;
      do{
        input = fgetc(stream);
        if (input != '\r'){
          number_of_letters += 1;
          strings.rows[strings.number_of_rows-1] = (char*)realloc(strings.rows[strings.number_of_rows-1], number_of_letters*sizeof(char));
          if (strings.rows[strings.number_of_rows-1] != NULL){
            strings.rows[strings.number_of_rows-1][number_of_letters-1] = input;
          }else{
            printf("Error in (re)allocating the memory");
            exit(EXIT_FAILURE);
          }          
        }        
      } while (input != '\0' && input != '\n' && input != '$');      

      strings.rows[strings.number_of_rows-1] = (char*)realloc(strings.rows[strings.number_of_rows-1], number_of_letters*sizeof(char));
        if (strings.rows[strings.number_of_rows-1] != NULL){
          strings.rows[strings.number_of_rows-1][number_of_letters-1] = '\0'; // overwrite the EOF over the last input
        }else{
          printf("Error in (re)allocating the memory");
          exit(EXIT_FAILURE);
        }       
    }else{
      printf("Error in (re)allocating the memory");
      exit(EXIT_FAILURE);
    }
  } while (input != '\0' && input != '$');

  return strings;
}

void print_stream(stream_t strings){
  int i;
  for ( i = 0; i < strings.number_of_rows; i++){
    printf("%s\n", strings.rows[i]);
  }  
}