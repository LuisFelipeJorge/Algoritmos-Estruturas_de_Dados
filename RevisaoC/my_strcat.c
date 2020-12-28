#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////
// functions declarations
int my_strlen(char* string);
char* my_strcpy(char* destination, char* source);
char* my_strcat(char* destination, char* source);

////////////////////////////////////////////////////


int main(int argc, char const *argv[])
{
  
  char str[80];
  my_strcpy (str,"these ");
  my_strcat (str,"strings ");
  my_strcat (str,"are ");
  my_strcat (str,"concatenated.");
  puts (str);
  return 0;
}

////////////////////////////////////////////////////
// functions definitions

int my_strlen(char* string){
  char *p = string;
  int length = 0;

  while (*p != '\0'){
    length += 1;
    p++;
  }
  return length;  
}

char* my_strcpy(char* destination, char* source){

  char* copy = source;
  int count = 0;
  do
  {
    count += 1;
    destination[count - 1] = *copy;
    copy++;
  } while (*copy != '\0');
  
  destination[count] = '\0';

  return destination;
}

char* my_strcat(char* destination, char* source){

  char* copy = source;
  int end_of_destination = my_strlen(destination);
  int count = end_of_destination;

  do
  {
    count += 1;
    destination[count - 1] = *copy;
    copy++;
  } while (*copy != '\0');
  
  destination[count] = '\0';

  return destination;
}
