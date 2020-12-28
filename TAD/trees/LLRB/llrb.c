#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "llrb.h"

/*
References: 
  https://www.ime.usp.br/~yoshi/Sedgewick/Algs4th/Slides/33BalancedSearchTrees.pdf
  https://www.geeksforgeeks.org/left-leaning-red-black-tree-insertion/
  https://en.wikipedia.org/wiki/Left-leaning_red%E2%80%93black_tree
  https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/
  https://www.geeksforgeeks.org/inorder-predecessor-successor-given-key-bst/
  https://www.youtube.com/watch?v=5cPbNCrdotA
*/

struct  tnode
{
  elem info;
  int color; // 1 := RED and 0 := black
  tnode_t *left,*right; 
};

tnode_t* create_tnode(elem x)
{
  tnode_t *new_node = (tnode_t*)malloc(sizeof(tnode_t));
  assert(new_node != NULL);
  new_node->info = x;
  new_node->color = RED; // always insert a red node
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

llrbtree_t* create_llrbtree()
{
  llrbtree_t *new_tree = (llrbtree_t*)malloc(sizeof(llrbtree_t));
  assert(new_tree != NULL);
  new_tree->root = NULL;
  return new_tree;
}

int tree_is_empty(llrbtree_t *tree)
{
  assert(tree != NULL);
  return (tree->root == NULL);
}

void free_llrbtree(tnode_t *root)
{
  if (root != NULL)
  {
    free_llrbtree(root->left);
    free_llrbtree(root->right);
    free(root);
  }
}

// ROTATIONS

// Simple rotation to left
tnode_t* left_rotation(tnode_t *target)
{
  tnode_t *aux = target->right;
  target->right = aux->left;
  aux->left = target;
  aux->color = target->color;
  target->color = RED;
  return aux;  
}

// Simple rotation to right
tnode_t* right_rotation(tnode_t *target)
{
  tnode_t *aux = target->left;
  target->left = aux->right;
  aux->right = target;
  aux->color = target->color;
  target->color = RED;
  return aux;
}

int is_red(tnode_t *root)
{
  if(root != NULL) return (root->color);
  return 0;
}

void flip_colors(tnode_t *root)
{
  root->color = RED;
  root->right->color = BLACK;
  root->left->color = BLACK;
}

void turn_black(tnode_t *root)
{
  root->color = BLACK;
}

tnode_t* insert_elem(tnode_t *root, elem x)
{
  // Recursive Aproach

  // Basic Cases:
  if (root == NULL) root = create_tnode(x);
  else if(x < root->info) root->left = insert_elem(root->left, x);
  else if(x > root->info) root->right = insert_elem(root->right, x);
  else return root; // x == root->info, repeated elements are not allowed

  // Insertion:
  if (is_red(root->right) && !is_red(root->left)) 
  {
    root = left_rotation(root);
  } else if (is_red(root->left) && is_red(root->left->left)) 
  {
    root = right_rotation(root);
     flip_colors(root);
  } else if (is_red(root->left) && is_red(root->right)) 
  {
    flip_colors(root);
  }
  return root;
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

tnode_t* search_elem(tnode_t *root, elem x)
{
  if (root == NULL || root->info == x) return root;
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

// find in orde predecessor and in order successor 

tnode_t* find_min(tnode_t* root)
{
  assert(root != NULL);
  tnode_t *current_node = root;
  while(current_node->left != NULL) current_node = current_node->left;
  return current_node; 
}

tnode_t* get_successor(tnode_t *root, elem x)
{
  // first case:  node has R sub-tree:
  //  find the min in the right sub-tree
  // case 2: node has no right sub-tree 
  //  go to the nearest ancestor for wich 
  //  given node would be in the left sub-tree

  tnode_t *current_node = search_elem(root, x);
  if (current_node == NULL) return current_node;
  if(current_node->right != NULL) return find_min(current_node->right);
  else
  {
    tnode_t *successor = NULL;
    tnode_t *ancestor = root;
    while (ancestor != current_node)
    {
      if (current_node->info < ancestor->info)
      {
        successor = ancestor;
        ancestor = ancestor->left;
      }else
      {
        ancestor = ancestor->right;
      }
    }
    return successor;
  }
}

tnode_t* find_max(tnode_t* root)
{
  assert(root != NULL);
  tnode_t *current_node = root;
  while(current_node->right != NULL) current_node = current_node->right;
  return current_node; 
}

tnode_t* get_predeccessor(tnode_t *root, elem x)
{
  // first case:  node has L sub-tree:
  //  find the max in the left sub-tree
  // case 2: node has no right sub-tree 
  //  go to the nearest ancestor for wich 
  //  given node would be in the right sub-tree

  tnode_t *current_node = search_elem(root, x);
  if (current_node == NULL) return current_node;
  if(current_node->left != NULL) return find_max(current_node->left);
  else
  {
    tnode_t *predecessor = NULL;
    tnode_t *ancestor = root;
    while (ancestor != current_node)
    {
      if (current_node->info > ancestor->info)
      {
        predecessor = ancestor;
        ancestor = ancestor->right;
      }else
      {
        ancestor = ancestor->left;
      }
    }
    return predecessor;
  }
}

elem get_info(tnode_t *root)
{
  return root->info;
}

elem get_max(tnode_t *root)
{
  assert(root != NULL);
  tnode_t *current_node;
  current_node = root;
  // go all the way to the right
  while (current_node->right != NULL)
  {
    current_node = current_node->right;
  }
  return current_node->info;
}

elem get_min(tnode_t *root)
{
    assert(root != NULL);
  tnode_t *current_node;
  current_node = root;
  // go all the way to the left
  while (current_node->left != NULL)
  {
    current_node = current_node->left;
  }
  return current_node->info;
}