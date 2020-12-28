#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "avl.h"

struct  tnode
{
  elem info;
  int balance_factor;
  tnode_t *left,*right; 
};

tnode_t* create_tnode(elem x)
{
  tnode_t *new_node = (tnode_t*)malloc(sizeof(tnode_t));
  assert(new_node != NULL);
  new_node->info = x;
  new_node->balance_factor = 0;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

tree_t* create_tree()
{
  tree_t *new_tree = (tree_t*)malloc(sizeof(tree_t));
  assert(new_tree != NULL);
  new_tree->root = NULL;
  return new_tree;
}

int tree_is_empty(tree_t *tree)
{
  assert(tree != NULL);
  return (tree->root == NULL);
}

void free_tree(tnode_t *root)
{
  if (root != NULL)
  {
    free_tree(root->left);
    free_tree(root->right);
    free(root);
  }
}

// ROTATIONS

// Simple rotation LeftLeft
tnode_t* rotation_LL(tnode_t *target)
{
  tnode_t *aux = target->right;
  target->right = aux->left;
  aux->left = target;
  return aux;  
}

// Simple rotation RightRight
tnode_t* rotation_RR(tnode_t *target)
{
  tnode_t *aux = target->left;
  target->left = aux->right;
  aux->right = target;
  return aux;
}

// Double rotation RightLeft
tnode_t* rotation_RL(tnode_t *target)
{
  target->right = rotation_RR(target->right);
  return rotation_LL(target);
}

// Double rotation LeftRight
tnode_t* rotation_LR(tnode_t *target)
{
  target->left = rotation_LL(target->left);
  return rotation_RR(target);
}

tnode_t* insert_avl(tnode_t *root, elem x, int *must_rotate)
{
  if (root == NULL)
  { // base: empty tree
    root = create_tnode(x);
    *must_rotate = 1;
  }else
  {
    if (x < root->info)
    {
      root->left = insert_avl(root->left, x, must_rotate);
      if (*must_rotate == 1)
      {// Discovering the type of rotation
        switch (root->balance_factor)
        {
          case -1:
          // originally the balancing factor was -1 
          // (right subtree larger than the left subtree). With the insertion on the left it was corrected.
            root->balance_factor = 0;
            *must_rotate = 0;
            break;
          case 0:
          // originally, the equilibrium factor was 0 
          // (the right subtree was the same height as the left subtree). With the insertion on the left, it should be checked on the previous nodes.
            root->balance_factor = 1;
            *must_rotate = 1;
            break;
          case 1:
            if (root->left->balance_factor == 1)
            { // simple rotation RightRight
              // root balance factor > 0  && root.left balance factor > 0
              root = rotation_RR(root);
              root->right->balance_factor = 0;
              root->balance_factor = 0; 
            }else
            {// double rotation LeftRight
              // root balance factor > 0  && root.left balance factor < 0
              root = rotation_LR(root);
              if (root->balance_factor == -1)
              {
                root->left->balance_factor = 1;
                root->right->balance_factor = 0;
                root->balance_factor = 0;
              }else if (root->balance_factor == 1)
              {
                root->left->balance_factor = 0;
                root->right->balance_factor = -1;
                root->balance_factor = 0;
              }else
              {// root.bf == 0
                root->left->balance_factor = 0;
                root->right->balance_factor = 0;
                root->balance_factor = 0;
              }
            } 
          *must_rotate = 0;           
          break;
        }
      }  
    }else if (x > root->info)
    {
      root->right = insert_avl(root->right, x, must_rotate);
      if (*must_rotate == 1)
      {// Discovering the type of rotation
        switch (root->balance_factor)
        {
          case 1:
          // originally the balancing factor was -1 
          // (left subtree larger than the right subtree). With the insertion on the right it was corrected.
            root->balance_factor = 0;
            *must_rotate = 0;
            break;
          case 0:
          // originally, the equilibrium factor was 0 
          // (the left subtree was the same height as the right subtree). With the insertion on the right, it should be checked on the previous nodes.
            root->balance_factor = -1;
            *must_rotate = 1;
            break;
          case -1:
            if (root->right->balance_factor == -1)
            { // simple rotation LeftLeft
              // root balance factor > 0  && root.right balance factor > 0
              root = rotation_LL(root);
              root->right->balance_factor = 0;
              root->balance_factor = 0; 
            }else
            {// double rotation RightLeft
              // root balance factor > 0  && root.right balance factor < 0
              root = rotation_RL(root);
              if (root->balance_factor == -1)
              {
                root->left->balance_factor = 1;
                root->right->balance_factor = 0;
                root->balance_factor = 0;
              }else if (root->balance_factor == 1)
              {
                root->left->balance_factor = 0;
                root->right->balance_factor = -1;
                root->balance_factor = 0;
              }else
              {// root.bf == 0
                root->left->balance_factor = 0;
                root->right->balance_factor = 0;
                root->balance_factor = 0;
              }
            } 
          *must_rotate = 0;           
          break;
        }
      }

    }else
    {// x is already inside the tree
      return root;
    }
  }
  return root;
}

void insert_node(tree_t *t, elem x)
{
  int must_rotate = 0;
  t->root = insert_avl(t->root, x, &must_rotate);

}

tnode_t* left_balancing(tnode_t *root, int *height)
{
  switch (root->balance_factor)
  {
    case 1: // left sub-tree greater than right sub-tree
      // remove one node, so now balance factor is equal to 0
      // bf: 1 -> 0
      // height changed but there is no unbalancing
      root->balance_factor = 0;
      break;
    case 0:
      // the left sub-tree height did not changed
      // no unbalicing
      root->balance_factor = -1;
      *height = 0;
      break;
    case -1:
      // We do have change and unbalancing together
      if (root->right->balance_factor <= 0)
      {
        root = rotation_LL(root);
        if (root->balance_factor == 0)
        { // make a draw to visualize teh rotation
          root->left->balance_factor = -1;
          root->balance_factor = 1;
          *height = 0;
        }else
        {
          root->left->balance_factor = 0;
          root->balance_factor = 0;
        }
      }else
      {
        root = rotation_RL(root);
        if (root->balance_factor == 1)
        {
          root->left->balance_factor = 0;
          root->right->balance_factor = -1;
        }else if (root->balance_factor == -1)
        {
          root->left->balance_factor = 1;
          root->right->balance_factor = 0;
        }else
        {
          root->left->balance_factor = 0;
          root->right->balance_factor = 0;
        }
        root->balance_factor = 0;
      }      
      break;   
    default:
      break;
  }
  return root;
}

tnode_t* right_balancing(tnode_t *root, int *height)
{
  switch (root->balance_factor)
  {
    case -1: // right sub-tree greater than left sub-tree
      // remove one node, so now balance factor is equal to 0
      // bf: -1 -> 0
      // height changed but there is no unbalancing
      root->balance_factor = 0;
      break;
    case 0:
      // the left sub-tree height did not changed
      // no unbalicing
      root->balance_factor = 1;
      *height = 0;
      break;
    case 1:
      // We do have change and unbalancing together
      if (root->left->balance_factor >= 0)
      {
        root = rotation_RR(root);
        if (root->balance_factor == 0)
        { // make a draw to visualize teh rotation
          root->right->balance_factor = 1;
          root->balance_factor = -1;
          *height = 0;
        }else
        {
          root->right->balance_factor = 0;
          root->balance_factor = 0;
        }
      }else
      {
        root = rotation_LR(root);
        if (root->balance_factor == 1)
        {
          root->left->balance_factor = 0;
          root->right->balance_factor = -1;
        }else if (root->balance_factor == -1)
        {
          root->left->balance_factor = 1;
          root->right->balance_factor = 0;
        }else
        {
          root->left->balance_factor = 0;
          root->right->balance_factor = 0;
        }
        root->balance_factor = 0;
      }      
      break;   
    default:
      break;
  }
  return root;
}

tnode_t* search_remove(tnode_t *root, tnode_t *key_node, int *height)
{
  if (root->right != NULL)
  { 
    root->right = search_remove(root->right, key_node, height);
    if (*height == 1) root = right_balancing(root, height);
  }else
  {
    tnode_t *aux;
    key_node->info = root->info;
    aux = root;
    root = root->left;
    free(aux);
    *height = 1;
  }
  return root;
}


tnode_t* remove_avl(tnode_t *root, elem x, int *height)
{
  if (root == NULL)
  {
    printf("Element not found!!");  
    *height = 0;
  } else if (x < root->info)
  {
    root->left = remove_avl(root->left, x, height);
    if(*height == 1)
    {
      root = left_balancing(root, height);
    }
  } else if (x > root->info)
  {
    root->left = remove_avl(root->right, x, height);
    if(*height == 1)
    {
      root = right_balancing(root, height);
    }
  } else
  { // did find the element
    // nodes with only one child:
    if (root->right == NULL)
    {
      tnode_t *aux = root->left;
      root = root->left;
      free(aux);
      *height = 1;
    }else if (root->left == NULL)
    {
      tnode_t *aux = root->right;
      root = root->left;
      free(aux);
      *height = 1;
    } else
    { // node that have both children left and right
      root->left = search_remove(root->left, root, height);
      if (*height == 1) root = left_balancing(root, height);
    }
  }
  return root;
}

void remove_node(tree_t *t, elem x)
{
  int height = 0;
  t->root = remove_avl(t->root, x, &height);
}

void print_tree(tnode_t *root)
{
  if (root != NULL)
  {
    printf("%d(", root->info);
    print_tree(root->left);
    printf(",");
    print_tree(root->right);
    printf(")");
  } else  printf("null");
}

int get_height(tnode_t *root)
{
  if (root == NULL) return 0;

  int left_height = 1 + get_height(root->left);
  int right_height = 1 + get_height(root->right);

  return (left_height>right_height)?left_height:right_height;
}

tnode_t* search_elem(tnode_t *root, elem x)
{
  if (root == NULL) return NULL;
  else if (root->info == x) return root;
  else if (x < root->info) return search_elem(root->left, x);
  else return search_elem(root->right, x);
}

// Tree Traversal with recursion

void pre_order(tnode_t *root)
{
  if (root != NULL) 
  {
    printf("%d ", root->info);
    pre_order(root->left);
    pre_order(root->right);
  }  
}

void in_order(tnode_t *root)
{
  if (root != NULL) 
  {
    in_order(root->left);
    printf("%d ", root->info);
    in_order(root->right);
  }  
}

void post_order(tnode_t *root)
{
  if (root != NULL) 
  {
    post_order(root->left);
    post_order(root->right);
    printf("%d ", root->info);
  }  
}