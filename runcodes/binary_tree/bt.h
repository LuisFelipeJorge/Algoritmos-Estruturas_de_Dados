typedef int elem;

typedef struct  tnode tnode_t;
typedef struct tree 
{
  tnode_t *root;
} tree_t;

tree_t* create_tree();
int tree_is_empty(tree_t *tree);
void free_tree(tnode_t *root);;
int insert_left(tree_t *t, elem x, elem parent);
int insert_right(tree_t *t, elem x, elem parent);
int remove_node(tree_t *t, elem x);
void print_tree(tnode_t *root, int parent);
int get_height(tnode_t *root);
tnode_t* search_elem(tnode_t *root, elem x);
tnode_t *search_parent(tnode_t *root, elem x);
