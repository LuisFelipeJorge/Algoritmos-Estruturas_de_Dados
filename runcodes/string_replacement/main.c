#include "str_repl.h"

int main(int argc, char const *argv[])
{
  int input;
  char to_be_corrected[100];
  char error[20];
  char correction[20];
  char **answers = NULL;
  int count_inputs = 0;
  while (scanf("%d", &input) != EOF)
  {
    count_inputs++;
    fgets(to_be_corrected, 100, stdin);
    correct_end_of_string(to_be_corrected);
    fgets(error, 20, stdin);
    correct_end_of_string(error);
    fgets(correction, 20, stdin);
    correct_end_of_string(correction);
    char *answer = replace_string(to_be_corrected, error, correction);
    answers = (char**)realloc(answers, sizeof(char*)*count_inputs);
    if (answers != NULL)
    {
      int str_size = strlen(answer);
      answers[count_inputs - 1] = (char*)malloc(sizeof(char)*str_size);
      if (answers[count_inputs - 1] != NULL)
      {
        strcpy(answers[count_inputs - 1], answer);
      }      
    }
    free(answer);
  }
  int i;
  for ( i = 0; i < count_inputs; i++)
  {
    printf("%s\n", answers[i]);
  }
  for ( i = 0; i < count_inputs; i++)
  {
    free(answers[i]);
  }
  free(answers);
  
  return 0;
}