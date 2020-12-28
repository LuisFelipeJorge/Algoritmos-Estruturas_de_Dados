typedef int elem;
typedef struct  tnode tnode_t;
typedef struct treap 
{
  tnode_t *root;
} treap_t;

treap_t* create_treap();
int treap_is_empty(treap_t *treap);
void free_treap(tnode_t *root);
tnode_t* insert_node(tnode_t *root, elem x, int priority);
tnode_t* remove_node(tnode_t *root, elem x);
void print_treap(tnode_t *root);
int get_height(tnode_t *root);
tnode_t* search_elem(tnode_t *root, elem x);
void pre_order(tnode_t *root);
void in_order(tnode_t *root);
void post_order(tnode_t *root);
void in_order_i(treap_t *t);
void bfs(treap_t *t);