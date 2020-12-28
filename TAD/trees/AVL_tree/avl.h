typedef int elem;

typedef struct  tnode tnode_t;

typedef struct tree 
{
  tnode_t *root;
} tree_t;

tree_t* create_tree();
int tree_is_empty(tree_t *tree);
void free_tree(tnode_t *root);
void print_tree(tnode_t *root);
int get_height(tnode_t *root);
tnode_t* search_elem(tnode_t *root, elem x);
void pre_order(tnode_t *root);
void in_order(tnode_t *root);
void post_order(tnode_t *root);
void insert_node(tree_t *t, elem x);
void remove_node(tree_t *t, elem x);