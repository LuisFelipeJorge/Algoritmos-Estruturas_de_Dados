typedef struct qnode qnode_t;
typedef struct queue queue_t;

qnode_t* create_qnode(void *info, int info_size);
queue_t* create_queue(int info_size);
void enqueue(queue_t *q, void* info);
void dequeue(queue_t *q, void* info);
int queue_is_empty(queue_t *q);
void free_queue(queue_t *q);
void get_info(qnode_t *current_node, void* info, int info_size);
void get_element(queue_t *q, int position, void *x);