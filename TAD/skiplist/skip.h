#define MAX_LEVEL 100
typedef int elem;
typedef struct node node_t;
typedef struct skiplist skiplist_t;

skiplist_t* create_skiplist();
void free_skiplist(skiplist_t *sl);
void print_skiplist(skiplist_t *sl);
void print_inorder(skiplist_t *sl);
int search_elem(skiplist_t *l, elem x);
int insert_elem(skiplist_t *sl, elem x);
int remove_elem(skiplist_t *sl, elem x);

