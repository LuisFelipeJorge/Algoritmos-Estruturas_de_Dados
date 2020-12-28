typedef struct node node_t;

node_t* create_node(int value);
void insert_node(node_t **head, int value);
void print_list(node_t **head);
void free_list(node_t **head);