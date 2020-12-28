typedef int elem;
typedef struct node node_t;
typedef struct list list_t;

node_t* create_node(elem value);
list_t* create_list();
int is_empty(list_t *l);
void insert(list_t *l, elem value);
int get_size(list_t *l);
void print_list(list_t *l);
void free_list(list_t *l);
int remove_element(list_t *l, elem x);
elem josephus(int n, int k);
