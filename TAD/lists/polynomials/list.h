typedef char elem;
typedef struct node node_t;
typedef struct poly poly_t;
typedef union info info_t;

void free_poly(poly_t *poly);
poly_t *create_poly();
void print_polynomial(poly_t *list);
void add_term(poly_t *poly, int coefficient, char *variables, int *exponents);
float calculate_polynomial(poly_t *poly, float x, float y, float z);
