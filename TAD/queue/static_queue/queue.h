#define QueueSize 100

typedef int elem;
typedef struct queue queue_t;

queue_t* create();
int is_empty(queue_t *q);
int is_full(queue_t *q);
int enqueue(queue_t *q, elem x);
int dequeue(queue_t *q, elem *x);
void free_queue(queue_t *q);

