#include <stdio.h> // basic input outpu streams 
#include <stdlib.h> // memory alloction

////////////////////////////////////////////////////
// functions declarations
char* readStream(FILE* stream);
int my_strlen(char* string);

////////////////////////////////////////////////////

int main(int argc, char const *argv[]){
  char* stream = NULL;
  int length = 0;

  stream = readStream(stdin);
  length = my_strlen(stream);

  printf("String Lenght: %d\n", length);

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

int my_strlen(char* string){
  char *p = string;
  int length = 0;

  while (*p != '\0'){
    length += 1;
    p++;
  }
  return length;  
}