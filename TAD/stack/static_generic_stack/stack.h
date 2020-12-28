#define StackSize 100

typedef struct stack stack_t;

stack_t* create(int);
void free_stack(stack_t*);
int is_empty(stack_t*);
int is_full(stack_t*);  
int push(stack_t*, void*);
int pop(stack_t*, void*);
int top(stack_t*, void*);