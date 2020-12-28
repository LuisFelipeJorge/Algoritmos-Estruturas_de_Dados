#include <stdio.h>
#include <stdlib.h>


////////////////////////////////////////////////////
// functions declarations
char* readStream(FILE* stream);
char* my_strcpy(char* destination, char* source);

////////////////////////////////////////////////////

int main(int argc, char const *argv[]){

  char* str1 = NULL;
  str1 = readStream(stdin);
  char str2[40];
  char str3[40];
  my_strcpy (str2,str1);
  my_strcpy (str3,"copy successful");
  printf ("str1: %s\nstr2: %s\nstr3: %s\n",str1,str2,str3);
  return 0;
}

////////////////////////////////////////////////////
// functions definitions

char* readStream(FILE* stream){
    char *str1 = NULL; 
    char *str2 = NULL;      // pointers to save the reference for the beginning of the stream

    char input;             // auxiliary variable to get the input stream
    int count = 0;          //variable to indicate the reading position and also the size of the space to be (re)allocated

    do{   
        input = fgetc(stream);  
        if (input != '\r'){  // check if a char other than \r was entered
            count += 1;
            str2 = (char*)realloc(str1,count*sizeof(char));

            if (str2 != NULL ){ // this checks if the allocation process went wrong 
                str1 = str2;                    // pass the reference to the new memory block
                str1[count - 1] = input;        // stores the input char within the array
            }else {
                free(str1);
                printf("Error (re)allocating memory !!");
                exit(EXIT_FAILURE);
            }
        }        
    } while (str1[count-1] != '\n' && !feof(stream));

    str2 = (char*)realloc(str1,(count+1)*sizeof(char));
    if (str2 != NULL){
        str1 = str2;
        str1[count - 1] = '\0';     // overwriting the \n at the end of the stream
    }else {
        free(str1);
        printf("Error (re)allocating memory !!");
        exit(EXIT_FAILURE);
    }    
    
    return str1; 
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