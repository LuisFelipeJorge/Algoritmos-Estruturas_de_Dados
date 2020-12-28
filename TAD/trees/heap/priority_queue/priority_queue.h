#define MAX 100

typedef int elem;
typedef struct queue queue_t;
typedef struct node node_t;

queue_t *create_queue();
int insert_elem(queue_t *q, elem key, int prio);
int remove_elem(queue_t *q, elem *key);
int queue_is_empty(queue_t *q);
int queue_is_full(queue_t *q);
void free_queue(queue_t *q);