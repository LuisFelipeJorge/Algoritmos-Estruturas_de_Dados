typedef struct node node_t;
typedef struct list list_t;

node_t* create_node(int value, int time);
list_t* create_list();
int is_empty(list_t *l);
void insert(list_t *l, int value, int back);
void print_list(list_t *l);
void free_list(list_t *l);
int remove_element(list_t *l, int value);
int is_on_the_list(list_t *l, int value);