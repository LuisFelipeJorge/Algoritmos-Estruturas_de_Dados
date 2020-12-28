#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "bst.h"

struct  tnode
{
  elem info;
  tnode_t *left,*right; 
};

tnode_t* create_tnode(elem x)
{
  tnode_t *new_node = (tnode_t*)malloc(sizeof(tnode_t));
  assert(new_node != NULL);
  new_node->info = x;
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

int insert_node(tnode_t **root, elem x)
{
  if (*root == NULL)
  {
    *root = create_tnode(x);
    return 1;
  }else if ((*root)->info == x) return 0;
  else if (x < (*root)->info) return insert_node(&(*root)->left, x);
  else return insert_node(&(*root)->right, x);
}

int remove_node(tnode_t **root, elem x)
{
  if (*root == NULL) return 0;
  else if (x < (*root)->info) return remove_node(&(*root)->left, x);
  else if (x > (*root)->info) return remove_node(&(*root)->right, x);
  else
  {
    // remove a leaf node:
    if ((*root)->left == NULL && (*root)->right == NULL)
    {
      free(*root);
      *root = NULL;
      return 1;
    }
    // One of the child nodes is not null
    if ((*root)->left == NULL)
    {
      tnode_t *aux = *root;
      *root = aux->right;
      free(aux);
      return 1;
    }
    if ((*root)->right == NULL)
    {
      tnode_t *aux = *root;
      *root = aux->left;
      free(aux);
      return 1;
    }
    // Both child nodes are not null
    // Finding the largest among the smallest
    tnode_t *current_node = (*root)->left;
    while (current_node->right != NULL)
    {
      current_node = current_node->right;
    }
    (*root)->info = current_node->info;
    return remove_node(&(*root)->left, current_node->info);
  }
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