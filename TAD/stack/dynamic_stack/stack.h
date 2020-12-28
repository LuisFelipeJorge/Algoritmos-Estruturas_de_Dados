typedef struct node node_t;
typedef struct stack stack_t;

node_t* create_node(void *info, int info_size);
stack_t* create_stack(int info_size);
void free_stack(stack_t*);
int is_empty(stack_t*);
void push(stack_t *s, void *info);
void pop(stack_t *s, void *info);
void top(stack_t* s, void* info);
node_t* get_top(stack_t *s);
void get_info(node_t *current_node, int info_size, void *info);
node_t* get_next(node_t *current_node);