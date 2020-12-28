#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "big.h"

struct node
{
  node_t *previous, *next;
  int value;
};


struct bignum
{
  node_t *start,*end;
  int size;
};

node_t* create_node(int value)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  assert(new_node);
  new_node->next = NULL;
  new_node->previous = NULL;
  new_node->value = value;
  return new_node;
}

int is_empty(bignum_t *b)
{
  return b->size == 0;
}

void insert(bignum_t *b, int value)
{
  assert( b != NULL);

  node_t *new_node = create_node(value);
  if (is_empty(b))
  {
    b->start = new_node;
  }else
  {
    new_node->previous = b->end;
    b->end->next = new_node;
  }  
  b->end = new_node; 
  b->size++;
}

bignum_t* new_big()
{
  bignum_t *new_number = (bignum_t*)malloc(sizeof(bignum_t));
  assert(new_number != NULL);
  new_number->end = NULL;
  new_number->start = NULL;
  new_number->size = 0;
  return new_number;
}

void clean_bignum(bignum_t *big)
{
  //removes the extra zeros from the left of the list
  assert(big != NULL);
  if (big->end->value != 0) return;

  node_t *current_node = big->end;
  while (current_node != NULL && current_node->value == 0)
  {
    big->end = current_node->previous;
    free(current_node);
    big->end->next = NULL;
    current_node = big->end;
  }
}

bignum_t* create_big(char *string)
{
  bignum_t *new_number = new_big();

  int size = strlen(string);
  for (int i = size-1; i >= 0; i -= 4)
  {
    int is_positive = 1;
    char number[K];

    for (int j = K - 1; j >= 0; j--)
    {
      if (i-j<0) number[K-1-j] = '0';
      else number[K-1-j] = string[i-j];        
    }      

    for (int j = 0; j < K; j++)
    {
      if (number[j] == '-')//**
      {
        is_positive = 0;
        char copy[K-j];
        for (int w = 0; w < K-j; w++)
        {
          copy[w] = number[j+w];
        }
        insert(new_number, atoi(copy));
      }
    }
    if(is_positive)insert(new_number, atoi(number));
  }
  clean_bignum(new_number);
  return new_number;
}
//**  atoi function returns 0 when it receives as input "0-10", therefore for negative numbers
//    we must change the input, "-10".

void print_bignum(bignum_t *big)
{
  assert(big != NULL);
  if (is_empty(big)) return;  
  
  clean_bignum(big);

  node_t *current_node = big->end;
  while (current_node != NULL)
  {
    if (current_node == big->end ) printf("%d", current_node->value);
    else printf("%.4d", current_node->value);
    current_node = current_node->previous;
  }
  printf("\n");
}

void free_bignum(bignum_t *big)
{
  if (big != NULL)
  {
    node_t *current_node = big->start;
    while (big->start != NULL)
    {
      big->start = current_node->next;
      free(current_node);
      current_node = big->start;
    }
    free(big);
  }  
  return;
}

bignum_t* sum(bignum_t *b1, bignum_t *b2)
{
  assert(b1 != NULL && b2 != NULL);
  
  node_t *current_node1 = b1->start;
  node_t *current_node2 = b2->start;
  bignum_t *result = new_big();

  int quocient = 1;
  for (int i = 0; i < K; i++)
  {// k = 4 => 10^4
    quocient *= 10;
  }
  

  int sum = 0;
  int add_one = 0;
  while (current_node1 != NULL && current_node2 != NULL)
  {
    if(add_one) sum = current_node1->value + current_node2->value + 1;
    else sum = current_node1->value + current_node2->value;
    insert(result, sum % quocient); // k = 4 => 10^4
    current_node1 = current_node1->next;
    current_node2 = current_node2->next;
    if (sum/quocient >= 1) add_one = 1;
    else add_one = 0;
  }
  while (current_node1 != NULL)
  {
    if (add_one == 1) 
    {
      insert(result, current_node1->value + 1);
      add_one = 0; 
    }else insert(result, current_node1->value);
    current_node1 = current_node1->next;
  }
  while (current_node2 != NULL)
  {
    if (add_one == 1) 
    {
      insert(result, current_node1->value + 1);
      add_one = 0; 
    } else insert(result, current_node2->value);
    current_node2 = current_node2->next;
  }
  if (add_one == 1) insert(result, add_one); 

  return result;
}

int is_equal(bignum_t *b1, bignum_t *b2)
{
  assert(b1 != NULL && b2 != NULL);
  
  node_t *current_node1 = b1->start;
  node_t *current_node2 = b2->start;
  if (b1->size != b2->size) return 0;
  while (current_node1 != NULL && current_node2 != NULL)
  {
    if (current_node1->value != current_node2->value) return 0;
    current_node1 = current_node1->next;
    current_node2 = current_node2->next;
  }
  return 1;
}

int is_greater(bignum_t *b1, bignum_t *b2)
{
  assert(b1 != NULL && b2 != NULL);
  
  if (b1->size < b2->size) return 0;
  if (b1->size > b2->size) return 1;

  node_t *current_node1 = b1->end;
  node_t *current_node2 = b2->end;


  while (current_node1 != NULL && current_node2 != NULL)
  {
    if (current_node1->value > current_node2->value) return 1;
    current_node1 = current_node1->previous;
    current_node2 = current_node2->previous;
  }

  return 0;
}

int is_smaller(bignum_t *b1, bignum_t *b2)
{
  assert(b1 != NULL && b2 != NULL);
  
  if (b1->size < b2->size) return 1;
  if (b1->size > b2->size) return 0;
  
  node_t *current_node1 = b1->end;
  node_t *current_node2 = b2->end;


  while (current_node1 != NULL && current_node2 != NULL)
  {
    if (current_node1->value < current_node2->value) return 1;
    current_node1 = current_node1->previous;
    current_node2 = current_node2->previous;
  }
  return 0;
}