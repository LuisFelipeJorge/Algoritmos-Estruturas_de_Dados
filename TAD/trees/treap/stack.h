typedef struct snode snode_t;
typedef struct stack stack_t;

snode_t* create_snode(void *info, int info_size);
stack_t* create_stack(int info_size);
void free_stack(stack_t*);
int stack_is_empty(stack_t*);
void push(stack_t *s, void *info);
void pop(stack_t *s, void *info);
void top(stack_t* s, void* info);
snode_t* get_top(stack_t *s);
void get_snode_info(snode_t *current_node, int info_size, void *info);
snode_t* get_next_snode(snode_t *current_node);