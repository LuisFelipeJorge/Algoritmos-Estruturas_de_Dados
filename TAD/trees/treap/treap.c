#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "treap.h"
#include "stack.h"
#include "queue.h"

struct  tnode
{
  elem info, priority;
  tnode_t *left,*right; 
};

tnode_t* create_tnode(elem x, int priority)
{
  tnode_t *new_node = (tnode_t*)malloc(sizeof(tnode_t));
  assert(new_node != NULL);
  
  new_node->info = x;
  new_node->priority = priority;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

treap_t* create_treap()
{
  treap_t *new_treap = (treap_t*)malloc(sizeof(treap_t));
  assert(new_treap != NULL);
  new_treap->root = NULL;
  return new_treap;
}

int treap_is_empty(treap_t *treap)
{
  assert(treap != NULL);
  if (treap->root == NULL) return 1;
  return 0;  
}

void free_treap(tnode_t *root)
{
  if (root != NULL)
  {
    free_treap(root->left);
    free_treap(root->right);
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

tnode_t* insert_node(tnode_t *root, elem x, int priority)
{
  if (root == NULL) return create_tnode(x, priority);
  
  if (root->info == x) 
  {
    printf("Elemento ja existente\n");
    return root;
  }
  if (x < root->info) 
  {
    root->left = insert_node(root->left, x, priority);
    if (root->left != NULL && root->left->priority > root->priority) root = rotation_RR(root);
  } else 
  {
    root->right = insert_node(root->right, x, priority);
    if (root->right != NULL && root->right->priority > root->priority) root = rotation_LL(root);
  }
  return root;
}

tnode_t* remove_node(tnode_t *root, elem x)
{
  if (root == NULL) 
  {
    printf("Chave nao localizada\n");
    return root;
  }

  if (x < root->info) root->left = remove_node(root->left, x);
  else if (x > root->info) root->right = remove_node(root->right, x);
  else
  {
    // remove a leaf node:
    if (root->left == NULL && root->right == NULL)
    {
      free(root);
      root = NULL;
      return root;
    }
    // One of the child nodes is not null
    if (root->left == NULL)
    { // right is not null
      tnode_t *aux = root;
      root = aux->right;
      free(aux);
      return root;
    }
    if (root->right == NULL)
    {// left is not null
      tnode_t *aux = root;
      root = aux->left;
      free(aux);
      return root;
    }
    // Both child nodes are not null
    root = rotation_LL(root);
    root->left = remove_node(root->left, x);    
  }
  return root;
}


void print_treap(tnode_t *root)
{
  if (root != NULL)
  {
    printf("[%d,%d](", root->info, root->priority);
    print_treap(root->left);
    printf(",");
    print_treap(root->right);
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
  if (root == NULL || root->info == x) return root;

  if(x < root->info) return search_elem(root->left, x);  

  return search_elem(root->right, x);
}

// Tree Traversal with recursion

void pre_order(tnode_t *root)
{
  if (root != NULL) 
  {
    printf("(%d, %d) ", root->info, root->priority);
    pre_order(root->left);
    pre_order(root->right);
  }  
}

void in_order(tnode_t *root)
{
  if (root != NULL) 
  {
    in_order(root->left);
    printf("(%d, %d) ", root->info, root->priority);
    in_order(root->right);
  }  
}

void post_order(tnode_t *root)
{
  if (root != NULL) 
  {
    post_order(root->left);
    post_order(root->right);
    printf("(%d, %d) ", root->info, root->priority);
  }  
}

// Tree Traversal without recursion

void in_order_i(treap_t *t)
{
  assert(t != NULL);
  tnode_t *current_node = t->root;
  stack_t *s = create_stack(sizeof(tnode_t));
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
void bfs(treap_t *t)
{
  assert(t != NULL);
  tnode_t *current_node = t->root;
  queue_t *q = create_queue(sizeof(tnode_t*));
  
  if(current_node != NULL) enqueue(q, &current_node);
  
  while (!queue_is_empty(q)) 
  {
    dequeue(q, &current_node);
    printf("(%d, %d) ", current_node->info, current_node->priority);
    if (current_node->left != NULL) enqueue(q, &current_node->left);
    if (current_node->right != NULL) enqueue(q, &current_node->right);
  }  
  free_queue(q);
}
