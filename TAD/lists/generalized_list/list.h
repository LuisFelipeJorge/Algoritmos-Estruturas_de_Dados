typedef int elem;
typedef struct node node_t;

typedef union 
{
  elem atom;
  node_t *sublist;
}info_t;

struct node 
{
  int type;
  info_t info;
  node_t *next;
};

void free_list(node_t *list);
node_t* create_atom(elem x);
node_t* create_sublist(node_t *sublist);
node_t* concat(node_t *node1, node_t *node2);
info_t get_head(node_t *list, int *type);
node_t* get_tail(node_t *list);
void print_list(node_t *list);
int is_in_the_list(node_t *start, elem x);
int get_depth(node_t *start);
int are_the_same(node_t *list1, node_t *list2);