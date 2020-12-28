#define StackSize 100

typedef int element;
typedef struct stack
{
  int top;
  void **items;
  int element_size;
}stack_t;

stack_t* create(int);
void free_stack(stack_t*);
int is_empty(stack_t*);
int is_full(stack_t*);  
int push(stack_t*, void*);
int pop(stack_t*, void*);
int top(stack_t*, void*);

void print_stack(stack_t *stack);
void correct_end_of_string(char *string);
int is_operator(char in);
void calculate(int value1, int value2,int input, int *result);
int evaluate_reverse_polish_expression(char *expression);