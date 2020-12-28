#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "list.h"

union info
{
  elem atom;
  node_t *sublist;
};

struct node 
{
  int type;
  info_t info;
  float value;
  node_t *next;
};

struct poly
{
  node_t *start,*end;
};


void free_list(node_t *list)
{
  node_t *current_node;

  while (list != NULL)
  {
    if (list->type == 1) free_list(list->info.sublist);
    
    current_node = list;
    list = list->next;
    free(current_node);   
  }  
}

void free_poly(poly_t *poly)
{
  free_list(poly->start);
  free(poly);
}


node_t* create_atom(elem x, float value)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  new_node->type = 0;
  new_node->info.atom = x;
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

node_t* create_sublist(node_t *sublist, float value)
{
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  new_node->type = 1;
  new_node->info.sublist = sublist;
  new_node->value = value;  
  new_node->next = NULL;
  return new_node;
}

poly_t *create_poly()
{
  poly_t *new_poly = (poly_t*)malloc(sizeof(poly_t));
  new_poly->end = NULL;
  new_poly->start = NULL;
  return new_poly;
}

node_t* concat(node_t *node1, node_t *node2)
{
  assert(node1 != NULL);
  node1->next = node2;
  return node1;
}

info_t get_head(node_t *list, int *type)
{
  assert(list != NULL);
  *type = list->type;
  return list->info;
}

node_t* get_tail(node_t *list)
{
  assert(list != NULL);
  return list->next;
}

void print(node_t *start)
{
  if (start == NULL) return;
  node_t *current_node = start;
  while (current_node != NULL)
  {
    if (current_node->type == 0)
    {
      printf("%c^(%.1f)", current_node->info.atom, current_node->value);
      if (current_node->next != NULL)printf("*");
    }
    else 
    {
      printf("%.1f", current_node->value);
      if (current_node->info.sublist != NULL) printf("*");
      print(current_node->info.sublist);
      if (current_node->next != NULL) 
      {
        if(current_node->next->value > 0)printf(" + ");
        else printf(" ");
      }
    }
    current_node = current_node->next;
  } 
}

void print_polynomial(poly_t *poly)
{
  print(poly->start);
  printf("\n");
}

void add_term(poly_t *poly, int coefficient, char *variables, int *exponents)
{
  node_t *new_term = NULL;
  node_t *end = NULL;
  for (int i = 0; i < strlen(variables); i++)
  {
    node_t *new_atom = create_atom(variables[i], exponents[i]);
    if (i == 0)  new_term = create_sublist(new_atom, coefficient);
    else end->next = new_atom;
    end = new_atom;
  }

  if (poly->start == NULL)
  {
    poly->start = new_term; 
  }else
  {
    poly->end->next = new_term;
  }
  poly->end = new_term;
}

float calculate_poly(node_t *p, float x, float y, float z)
{
  if (p == NULL) return 0;
  
  float result = 0.0;
  float product;
  node_t* current_node = p;
  while (current_node != NULL)
  {
    if (current_node->type == 0)
    {
      product = 1.0;

      switch (current_node->info.atom)
      {
      case 'X':
        product *= pow(x, current_node->value);
        break;
      case 'Y':
        product *= pow(y, current_node->value);
        break;
      case 'Z':
        product *= pow(z, current_node->value);
        break;
      default:
        break;
      }

      // if (current_node->info.atom == 'X')
      // {
      //   product *= pow(x, current_node->value);
      // }else if (current_node->info.atom == 'Y')
      // {
      //   product *= pow(y, current_node->value);
      // }else
      // {
      //   product *= pow(z, current_node->value);
      // }      
      result += product;
    } else
    {
      product = 1.0;
      product *= current_node->value;
      product *= calculate_poly(current_node->info.sublist, x, y, z);
      result += product;
    }
    current_node = current_node->next;
  }
  return result;
}

float calculate_polynomial(poly_t *poly, float x, float y, float z)
{
  return calculate_poly(poly->start, x, y, z);
}