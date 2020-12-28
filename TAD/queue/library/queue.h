#define QueueSize 100

typedef struct queue queue_t;

queue_t* create_queue(int element_size);
int enqueue(queue_t *q, void *x);
int dequeue(queue_t *q, void *x);
int is_empty(queue_t *q);
int is_full(queue_t *q);
void free_queue(queue_t *q);
int get_start(queue_t *q);
int get_end(queue_t *q);
void get_element(queue_t *q, int position, void *x);