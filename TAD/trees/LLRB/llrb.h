#define RED 1
#define BLACK 0
typedef int elem;

typedef struct  tnode tnode_t;
// Leaft Leaning Red Black Tree
typedef struct llrbtree 
{
  tnode_t *root;
} llrbtree_t;

llrbtree_t* create_llrbtree();
int llrbtree_is_empty(llrbtree_t *llrbtree);
void free_llrbtree(tnode_t *root);
tnode_t* insert_elem(tnode_t *root, elem x);
void turn_black(tnode_t *root);
void print_tree(tnode_t *root);
void pre_order(tnode_t *root);
void in_order(tnode_t *root);
void post_order(tnode_t *root);
void find_pre_suc(tnode_t* root, tnode_t** pre, tnode_t** suc, int key);
elem get_info(tnode_t *root);
elem get_max(tnode_t *root);
elem get_min(tnode_t *root);
tnode_t* get_successor(tnode_t *root, elem x);
tnode_t* get_predeccessor(tnode_t *root, elem x);