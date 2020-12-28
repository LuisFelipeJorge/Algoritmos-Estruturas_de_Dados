#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "dictionary.h"

int main(void) 
{
  srand(time(NULL));

  char operation[10];
  char word[WORD_SIZE + 1]; // +1 for \0
  char definition[DEF_SIZE + 1];
  char ch[2];

  int evaluate; // get the result of operations

  dictionary_t *dict = create_dictionary();

  while(scanf("%s",operation)!=EOF)
	{
		if(strcmp(operation, "insercao") == 0)
		{
			scanf("%s", word);
			getchar();
			scanf("%[^\n]s", definition);

      evaluate = insert_word(dict, word, definition);
			if(evaluate == 0) printf("OPERACAO INVALIDA\n");
		}
    else if(strcmp(operation, "alteracao") == 0)
		{
			scanf("%s", word);
			getchar();
			scanf("%[^\n]s", definition);

			evaluate = change_word(dict, word, definition);
			if(evaluate == 0) printf("OPERACAO INVALIDA\n");
		}
    else if(strcmp(operation, "remocao") == 0)
		{
			scanf("%s", word);
			evaluate = remove_word(dict, word);
			if(evaluate == 0) printf("OPERACAO INVALIDA\n");
		}
    else if(strcmp(operation,"busca")==0)
		{
			scanf("%s",word);
		  evaluate = search_word(dict, word);
			if(evaluate == 0) printf("OPERACAO INVALIDA\n");
		}
    else if(strcmp(operation, "impressao") == 0)
		{
			scanf("%s", ch);
			evaluate = print_words(dict, ch[0]);
			if(evaluate == 0) printf("NAO HA PALAVRAS INICIADAS POR %c\n", ch[0]);
		}
	}
  free_dictionary(dict);
  return 0;
}