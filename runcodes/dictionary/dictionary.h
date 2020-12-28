#define MAX_LEVEL 15
#define WORD_SIZE 50
#define DEF_SIZE 140

typedef struct elem
{
  char word[WORD_SIZE];  
  char definition[DEF_SIZE];
}elem_t;


typedef struct dnode dnode_t;
typedef struct dictionary dictionary_t;
// The dictionaries will be implemented as skiplists, to guarantee 
// O(log n) in operations such as insertion, removal and search.

dictionary_t* create_dictionary();
void free_dictionary(dictionary_t *dict);
void print_dictionary(dictionary_t *dict);
void print_inorder(dictionary_t *dict);
int insert_elem(dictionary_t *dict, elem_t *e);
int remove_elem(dictionary_t *dict, elem_t *e);
int change_word(dictionary_t *dict, char* word, char* definition);
int search_word(dictionary_t *dict, char* word);
int print_words(dictionary_t *dict, char c);
int insert_word(dictionary_t *dict, char *word, char *definition);
int remove_word(dictionary_t *dict, char *word);