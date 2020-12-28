#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "big.h"

///////////////////////////////////////////////////////////////////////////
// functions declarations
char** read_stream(FILE* stream);

///////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
  int iterations;
  scanf("%d\n", &iterations);
  char operator[3];
  char *operand1, *operand2;

  for (int i = 0; i < iterations; i++)
  {
    char **input = read_stream(stdin);
    int size1 = strlen(input[1]);
    int size2 = strlen(input[2]);
    operand1 = (char*)malloc(size1*sizeof(char));
    operand2 = (char*)malloc(size2*sizeof(char));

    strcpy(operator, input[0]);
    strcpy(operand1, input[1]);
    strcpy(operand2, input[2]);
    
    bignum_t *big1 = create_big(operand1);
    bignum_t *big2 = create_big(operand2);

    if (strcmp(operator, "sum") == 0)
    {
      printf("Resultado %d: ", i+1);
      bignum_t *result = sum(big1, big2);
      print_bignum(result);
      free_bignum(result);
    }else if (strcmp(operator, "big") == 0)
    {
      printf("Resultado %d: %d\n", i+1, is_greater(big1, big2));
    }else if (strcmp(operator, "sml") == 0)
    {
      printf("Resultado %d: %d\n", i+1, is_smaller(big1, big2));
    }else if (strcmp(operator, "eql") == 0)
    {
      printf("Resultado %d: %d\n", i+1, is_equal(big1, big2));
    }   

    for (int j = 0; j < 3; j++)
    {
      free(input[j]);
    }
    free(input);

    free_bignum(big1);
    free_bignum(big2);
    free(operand1);
    free(operand2);
  }
  
  return 0;
}

///////////////////////////////////////////////////////////////////

char** read_stream(FILE* stream)
{
  char **string = NULL;
  int number_of_words = 0;
  int number_of_letters = 0;
  char input;

  do
  {
    number_of_words++;
    string = (char**)realloc(string, number_of_words*sizeof(char*));
    assert(string != NULL);
    string[number_of_words-1] = NULL;
    number_of_letters = 0;
    do
    {
      input = fgetc(stream);
      if (input != '\r')
      {
        number_of_letters++;
        string[number_of_words-1] = (char*)realloc(string[number_of_words-1], number_of_letters*sizeof(char));
        assert(string[number_of_words-1] != NULL);
        string[number_of_words-1][number_of_letters-1] = input;
      }      
    } while (input != ' ' && input != '\n' && input != EOF);
    string[number_of_words-1][number_of_letters-1] = '\0';
  } while (input != '\n' && input != EOF);
  return string;
}

