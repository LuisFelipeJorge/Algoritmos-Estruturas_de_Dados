#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"
#include "queue.h"

struct user
{
  int id;
  char name[100];
};

struct book
{
  int id;
  char title[100];
  int availability;
  queue_t *q;
  int user_id;
};

struct library
{
  user_t users[N_USERS];
  book_t books[N_BOOKS];
};

lib_t* create_lib()
{
  lib_t *lib = (lib_t*)malloc(sizeof(lib_t));
  assert(lib != NULL);

  register_users(lib);
  register_books(lib);  
  return lib;
}

void free_lib(lib_t *lib)
{
  assert(lib != NULL);
  for(int i = 0; i < N_BOOKS; i++ )
  {
    free_queue(lib->books[i].q);
  }
  free(lib);
}

void register_users(lib_t *lib)
{
  assert(lib != NULL);
  for (int i = 0; i < N_USERS; i++)
  {
    lib->users[i].id = i;
    strcpy(lib->users[i].name, "User Name");
  }
}

void register_books(lib_t *lib)
{
  assert(lib != NULL);
  for (int i = 0; i < N_BOOKS; i++)
  {
    lib->books[i].id = i;
    strcpy(lib->books[i].title, "Book title");
    lib->books[i].availability = 1;
    lib->books[i].q = create_queue(sizeof(user_t));
    lib->books[i].user_id = -1;
  }
}

int consult_user(lib_t *lib, int user_id)
{
  assert(lib != NULL);
  return (user_id < 0 || user_id >= N_USERS);
}

int consult_book(lib_t *lib, int book_id)
{
  assert(lib != NULL);
  return (book_id < 0 || book_id >= N_USERS);
}

int is_available(lib_t *lib, int book_id)
{
  assert(lib != NULL);
  return lib->books[book_id].availability;
}

void borrow_book(lib_t *lib, int user_id, int book_id)
{
  assert(lib != NULL);
  lib->books[book_id].availability = 0;
  lib->books[book_id].user_id = user_id;
}

int insert_queue(lib_t *lib, int user_id, int book_id)
{
  assert(lib != NULL);
  return enqueue(lib->books[book_id].q, (void*)&lib->users[user_id]);
}

void return_book(lib_t *lib, int user_id, int book_id)
{
  if(is_empty(lib->books[book_id].q))
  {
    lib->books[book_id].availability = 1;
    lib->books[book_id].user_id = -1;
  }else{
    user_t new_user;
    dequeue(lib->books[book_id].q, (void*)&new_user);
    borrow_book(lib, new_user.id, book_id);
    printf("Borrowed to a new user on the queue: %d\n", new_user.id);
  }
}