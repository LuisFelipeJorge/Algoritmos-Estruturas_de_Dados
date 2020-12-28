#include <stdio.h>
#include "library.h"

int main(int argc, char const *argv[])
{
  int option, user_id, book_id;
  lib_t *lib  = create_lib();
  do
  {
    printf("Type the chosen option:\n");
    printf("1-Borrow a book\n");
    printf("2-Return a book\n");
    printf("0-Skip the Program\n");
    scanf("%d", &option);
    switch(option)
    {
      case 1:
        printf("Type the user id: ");
        scanf("%d", &user_id);
        if(consult_user(lib, user_id))
        {
          printf("Unregistered user!\n");
          continue;
        } 
        printf("Type the book id: ");
        scanf("%d", &book_id);
        if(consult_book(lib, book_id))
        {
          printf("Unregistered book!\n");
          continue;
        }
        if(is_available(lib, book_id))
        {
          borrow_book(lib, user_id, book_id);
          printf("Borrowed with success!\n");
        } else 
        {
          insert_queue(lib, user_id, book_id);
          printf("Book already borrowed, added to the queue...\n");
        }
        break;
      case 2:
        printf("Type the book id: ");
        scanf("%d", &book_id);
        if(consult_book(lib, book_id))
        {
          printf("unregistered book!\n");
          continue;
        }
        if(is_available(lib, book_id))
        {
          printf("Book has already been returned!\n");
          continue;
        }else 
        {
          printf("The book was successfully returned!\n");
          return_book(lib, user_id, book_id);
        }
        break;
    }
  }while(option != 0);
  free_lib(lib);
  return 0;
}
