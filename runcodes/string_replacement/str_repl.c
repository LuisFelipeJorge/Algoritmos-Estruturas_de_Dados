#include "str_repl.h"

void correct_end_of_string(char *string)
{
  int i = 0;
  while (string[i] != EOF)
  {
    if (string[i] == '\n')
    {
      string[i] = '\0';
    }
    i++;
  }
}

char* replace_string(char *to_be_corrected, char *error, char *correction){
    char *answer = NULL; 
    int i, count_error_occurance = 0; 
    int new_word_len = strlen(correction); 
    int old_word_len = strlen(error); 

    // counting the error occurrences within the original string  
    for (i = 0; to_be_corrected[i] != '\0'; i++) 
    { 
      if (strstr(to_be_corrected + i, error) == to_be_corrected + i) { 
          count_error_occurance++;
          i += old_word_len - 1; 
      } 
    } 
  
    // Allocating space for the final string
    answer = (char*)malloc(i + 1 + count_error_occurance*(new_word_len-old_word_len));
  
    i = 0; 
    while (*to_be_corrected) 
    { 
      // compare the substring with the result 
      if (strstr(to_be_corrected, error) == to_be_corrected) { 
          strcpy(answer + i, correction); 
          i += new_word_len; 
          to_be_corrected += old_word_len; 
      } 
      else
        answer[i++] = *to_be_corrected++; 
    } 
  
    answer[i] = '\0'; 
    return answer; 
}