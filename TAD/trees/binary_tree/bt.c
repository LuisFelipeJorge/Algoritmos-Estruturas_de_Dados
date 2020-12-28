#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "bt.h"
#include "stack.h"
#include "queue.h"

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

int remove_node(tree_t *t, elem x)
{
  assert(t != NULL);
  tnode_t *current_node, *parent;
  int is_left;

  // find the node and his parent
  if(!tree_is_empty(t) && t->root->info == x)
  {
    current_node = t->root;
    parent = NULL;
  }else
  {
    parent = search_parent(t->root, x);
    if(parent != NULL)
    {
      if( parent->left != NULL && parent->left->info == x) 
      {
        current_node = parent->left;
        is_left = 1;
      } else 
      {
        current_node = parent->right;
        is_left = 0;
      }
    }else 
    {// NULL parent -> element doesn't exist in the list
      current_node = NULL;
    }
  }

  // remotion
  if (current_node == NULL) return 0;

  if (current_node->left == NULL && current_node->right == NULL)
  {// leaf node
    if(parent == NULL) t->root = NULL; // remove root      
    else if (is_left) parent->left = NULL; // remove left child
    else parent->right = NULL; // remove right child
    free(current_node);  
    return 1;  
  } else
  {
    if (current_node->left != NULL)
    {
      current_node->info = current_node->left->info;
      current_node->left->info = x;
    }else
    {
      current_node->info = current_node->right->info;
      current_node->right->info = x;
    }
    return remove_node(t, x);
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
  if(root->info == x) return root;

  tnode_t *current_node = search_elem(root->left, x);
  if (current_node == NULL) current_node = search_elem(root->right, x);

  return current_node;
}

tnode_t* search_parent(tnode_t *root, elem x)
{
  if(root == NULL) return NULL;

  if(root->left != NULL && root->left->info == x) return root; 
  if(root->right != NULL && root->right->info == x) return root; 

  tnode_t *current_node = search_parent(root->left, x);
  if (current_node == NULL) current_node = search_parent(root->right, x);

  return current_node;
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

// Tree Traversal without recursion

void in_order_i(tree_t *t)
{
  assert(t != NULL);
  tnode_t *current_node = t->root;
  stack_t *s = create_stack(sizeof(tnode_t*));
  do
  {
    while (current_node != NULL)
    {
      push(s, &current_node);
      current_node = current_node->left;
    }
    if(!stack_is_empty(s))
    {
      pop(s, &current_node);
      printf("%d ", current_node->info);
      current_node = current_node->right;
    }
  } while ((!stack_is_empty(s)) || (current_node != NULL));
  free_stack(s);
}

// Breadth First Search
// queue
void bfs(tree_t *t)
{
  assert(t != NULL);
  tnode_t *current_node = t->root;
  queue_t *q = create_queue(sizeof(tnode_t*));
  
  if(current_node != NULL) enqueue(q, &current_node);
  
  while (!queue_is_empty(q)) 
  {
    dequeue(q, &current_node);
    printf("%d ", current_node->info);
    if (current_node->left != NULL) enqueue(q, &current_node->left);
    if (current_node->right != NULL) enqueue(q, &current_node->right);
  }  
  free_queue(q);
}

