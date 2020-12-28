#include <stdio.h>
#include <stdlib.h>

#include "llrb.h"

int main(int argc, char const *argv[])
{
  llrbtree_t *rb = create_llrbtree();

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    int op; // operation
    scanf("%d", &op);
    elem input;
    tnode_t *pre, *suc;
    switch (op)
    {
      case 1: // insertion 
        scanf("%d", &input);
        rb->root = insert_elem(rb->root, input);
        turn_black(rb->root); // to ensure that root will aways remains as a black node
        break;
      case 2: // inorder succcessor
        scanf("%d", &input);
        suc = get_successor(rb->root, input);
        if (suc != NULL) printf("%d\n", get_info(suc));
        else printf("erro\n");
        break;
      case 3: // inorder predecessor
        scanf("%d", &input);
        pre = get_predeccessor(rb->root, input);
        if (pre != NULL )printf("%d\n", get_info(pre));
        else printf("erro\n");
        break;
      case 4: // maximum
        printf("%d\n", get_max(rb->root));
        break;
      case 5: // minimum
        printf("%d\n", get_min(rb->root));
        break;
      case 6: // pre order
        pre_order(rb->root);
        printf("\n");
        break;
      case 7: // in order
        in_order(rb->root);
        printf("\n");
        break;
      case 8: // pos order
        post_order(rb->root);
        printf("\n");
        break;
      
      default:
        break;
    }
  }
  free_llrbtree(rb->root);
  free(rb);

  return 0;
}
