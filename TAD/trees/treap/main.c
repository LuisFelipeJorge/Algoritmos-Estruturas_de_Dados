#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treap.h"

int main(int argc, char const *argv[])
{
  char command[10];
  int key, priority;
  int n;
  scanf("%d", &n);

  treap_t *tr = create_treap();

  for (int i = 0; i < n; i++)
  {
    scanf("%s", command);
    if (strcmp(command, "insercao")==0)
    {
      scanf("%d %d", &key, &priority);
      tr->root = insert_node(tr->root, key, priority);
    }else if (strcmp(command, "remocao")==0)
    {
      scanf("%d %d", &key, &priority);
      tr->root = remove_node(tr->root, key);      
    }else if (strcmp(command, "buscar")==0)
    {
      tnode_t *x = NULL;
      scanf("%d", &key);
      x = search_elem(tr->root, key);
      if (x == NULL) printf("0\n");
      else printf("1\n");
    }else if (strcmp(command, "impressao")==0)
    {
      char mode[10];
      scanf("%s", mode);
      if (strcmp(mode, "ordem") == 0)
      {
        in_order(tr->root);
        printf("\n");
      }else if (strcmp(mode, "posordem") == 0)
      {
        post_order(tr->root);
        printf("\n");
      }else if (strcmp(mode, "preordem") == 0)
      {
        pre_order(tr->root);
        printf("\n");
      }else if (strcmp(mode, "largura") == 0)
      {
        bfs(tr);
        printf("\n");
      }
    }
  }
  
  free_treap(tr->root);
  free(tr);
  return 0;
}
