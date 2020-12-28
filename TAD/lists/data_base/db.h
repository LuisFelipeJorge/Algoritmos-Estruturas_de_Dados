#define SIZE 100

typedef int elem;
typedef struct database database_t;

database_t *create();
int is_empty(database_t *db);
int is_full(database_t *db);
int insert(database_t *db, elem x);
int remove_elem(database_t *db, elem *x);
void free_database(database_t *db);