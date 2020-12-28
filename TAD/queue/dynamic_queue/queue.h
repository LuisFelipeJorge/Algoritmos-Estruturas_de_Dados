typedef struct node node_t;
typedef struct queue queue_t;

node_t* create_node(void *info, int info_size);
queue_t* create_queue(int info_size);
void enqueue(queue_t *q, void* info);
void dequeue(queue_t *q, void* info);
int is_empty(queue_t *q);
void free_queue(queue_t *q);
node_t* get_start(queue_t *q);
int get_size(queue_t *q);
node_t* get_next(node_t *current_node);
void get_info(node_t *current_node, void* info, int info_size);
void get_element(queue_t *q, int position, void *x);