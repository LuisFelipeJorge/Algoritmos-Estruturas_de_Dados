#define StackSize 100

typedef int element;
typedef struct stack stack_t;

stack_t* create();
void print_stack(stack_t *stack);
void free_stack(stack_t*);
int is_empty(stack_t*);
int is_full(stack_t*);  
int push(stack_t*, element );
int pop(stack_t*, element*);
int top(stack_t*, element*);