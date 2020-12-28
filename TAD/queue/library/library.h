#define N_USERS 20
#define N_BOOKS 20

typedef struct user user_t;
typedef struct book book_t;
typedef struct library lib_t;

lib_t* create_lib();
void free_lib(lib_t *lib);
void register_users(lib_t *lib);
void register_books(lib_t *lib);
int consult_user(lib_t *lib, int user_id);
int consult_book(lib_t *lib, int book_id);
int is_available(lib_t *lib, int book_id);
void borrow_book(lib_t *lib, int user_id, int book_id);
int insert_queue(lib_t *lib, int user_id, int book_id);
void return_book(lib_t *lib, int user_id, int book_id);