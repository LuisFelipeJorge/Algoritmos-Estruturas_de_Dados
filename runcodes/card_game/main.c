#include "card_game.h"

stack_t *compra;
stack_t *descarte;
stack_t *morto;
stack_t *transition;

int main(int argc, char const *argv[])
{
  compra = create(sizeof(int));
  descarte = create(sizeof(int));
  morto = create(sizeof(int));

  int number_of_cards;
  scanf("%d", &number_of_cards);
  int *aux = (int*)malloc(sizeof(int)*number_of_cards);
  assert(aux);
  // the order to place the elements within the stack should be the reverse of the input
  for (int i = 0; i < number_of_cards; i++)
  {
    int temp;
    scanf("%d", &temp);
    aux[i] = temp;
  }
  for (int i = number_of_cards - 1; i >= 0; i--)
  {
    push(compra, (aux+i));
  }

  int count_turns = 0;
  int n = 1;
  int end_game = 0;
  int card;

  while (end_game == 0)
  {
    while (!is_empty(compra))
    {
      pop(compra, &card);
      if (card == n)
      {
        push(morto, &card);
        n++;
      }else
      {
        push(descarte, &card);      
      }    
    }
    count_turns++;
    if (n - 1 == number_of_cards)
    {
      end_game = 1;
    }else
    {
      while (!is_empty(descarte))
      {
        pop(descarte, &card);
        push(compra, &card);
      }
    }    
  }

  printf("%d\n", count_turns);

  free(aux);
  free_stack(compra);
  free_stack(descarte);
  free_stack(morto);

  return 0;
}
