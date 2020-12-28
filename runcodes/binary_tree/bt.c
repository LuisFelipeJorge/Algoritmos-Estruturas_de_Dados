#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "bt.h"

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
  if (tree->root == NULL) return 1;
  return 0;  
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

int insert_left(tree_t *t, elem x, elem parent)
{
  tnode_t *new_node = create_tnode(x);
  if(parent == -1)
  {
    if (tree_is_empty(t)) t->root = new_node;
    else
    {
      free(new_node);
      return 0;
    }
  }else
  {
    tnode_t *parent_node = search_elem(t->root, parent);

    if (parent_node != NULL && parent_node->left == NULL)
    {
      parent_node->left =  new_node;
    }else
    {
      free(new_node);
      return 0;
    }    
  }

  return 1;
}

int insert_right(tree_t *t, elem x, elem parent)
{
  tnode_t *new_node = create_tnode(x);
  if(parent == -1)
  {
    if (tree_is_empty(t)) t->root = new_node;
    else
    {
      free(new_node);
      return 0;
    }
  }else
  {
    tnode_t *parent_node = search_elem(t->root, parent);

    if (parent_node != NULL && parent_node->right == NULL)
    {
      parent_node->right =  new_node;
    }else
    {
      free(new_node);
      return 0;
    }    
  }

  return 1;
}

tnode_t* search_elem(tnode_t *root, elem x)
{
  if (root == NULL) return NULL;
  if(root->info == x) return root;

  tnode_t *current_node = search_elem(root->left, x);
  if (current_node == NULL) current_node = search_elem(root->right, x);

  return current_node;
}

int get_height(tnode_t *root)
{
  if (root == NULL) return 0;

  int left_height = 1 + get_height(root->left);
  int right_height = 1 + get_height(root->right);

  return (left_height>right_height)?left_height:right_height;
}

int get_grade(tnode_t *root)
{
  int count = 0;
  if(root->left != NULL) count++;
  if(root->right != NULL) count++;
  return count;
}

char* get_type(tnode_t *root, int parent)
{
  char *type = (char*)malloc(sizeof(char)*10);

  if (parent == -1) strcpy(type, "raiz");
  else if (root->left == NULL && root->right == NULL) strcpy(type, "folha");
  else strcpy(type, "interno");
  return type;
}

void print_tree(tnode_t *root, int parent)
{
  if (root == NULL) return;

  char *t = get_type(root, parent);
  int left, right;
  left = right = -1;
  if (root->left != NULL) left = root->left->info;
  if (root->right != NULL) right = root->right->info;

  printf("no %d: ", root->info);
  printf("pai = %d, ", parent);
  printf("altura = %d, ", get_height(root));
  printf("grau = %d, ", get_grade(root));
  printf("filhos = (%d,%d), ", left, right);
  printf("tipo = %s\n", t);
  free(t);
  print_tree(root->left, root->info);
  print_tree(root->right, root->info);  
}