#define K 4 // number of digits stored in each node

typedef struct bignum bignum_t;
typedef struct node node_t;

bignum_t* create_big(char *string);
void print_bignum(bignum_t *big);
void free_bignum(bignum_t *big);
bignum_t* sum(bignum_t *b1, bignum_t *b2);
int is_equal(bignum_t *b1, bignum_t *b2);
int is_greater(bignum_t *b1, bignum_t *b2);
int is_smaller(bignum_t *b1, bignum_t *b2);