#include "queue.h"

typedef struct person
{
  int age, condition;
  char name[20];
}person_t;

int main(int argc, char const *argv[])
{
  int n, test;
  person_t p;
  queue_t *q1 = create(sizeof(person_t)); // first priority -- age >= 60 && has_condition
  queue_t *q2 = create(sizeof(person_t)); // second priority -- has_condition
  queue_t *q3 = create(sizeof(person_t)); // tird priority -- age >= 60
  queue_t *q4 = create(sizeof(person_t)); // last priority

  scanf("%d", &n);
  char action[5]; 

  for (int i = 0; i < n; i++)
  {
    scanf("%s", action);
    if (strcmp(action, "ENTRA") == 0)
    {
      char name[20];
      int age;
      int condition;
      scanf("%s %d %d", name, &age, &condition);
      p.age = age;
      p.condition = condition;
      strcpy(p.name, name);
      if (p.age >= 60 && p.condition == 1)
      {
        test = enqueue(q1, &p);
        if (test == 0) printf("FILA CHEIA\n");
      }else if (p.condition == 1)
      {
        test = enqueue(q2, &p);
        if (test == 0) printf("FILA CHEIA\n");
      }else if (p.age >= 60)
      {
        test = enqueue(q3, &p);
        if (test == 0) printf("FILA CHEIA\n");
      }else
      {
        test = enqueue(q4, &p);
        if (test == 0) printf("FILA CHEIA\n");
      }
    }else if (strcmp(action, "SAI") == 0)
    {
      if (!is_empty(q1))
      {
        test = dequeue(q1, &p);
        if (test == 0) printf("FILA VAZIA\n");
        else printf("%s %d %d\n", p.name, p.age, p.condition);        
      } else if (!is_empty(q2))
      {
        test = dequeue(q2, &p);
        if (test == 0) printf("FILA VAZIA\n");
        else printf("%s %d %d\n", p.name, p.age, p.condition);        
      } else if (!is_empty(q3))
      {
        test = dequeue(q3, &p);
        if (test == 0) printf("FILA VAZIA\n");
        else printf("%s %d %d\n", p.name, p.age, p.condition);        
      }else if (!is_empty(q4))
      {
        test = dequeue(q4, &p);
        if (test == 0) printf("FILA VAZIA\n");
        else printf("%s %d %d\n", p.name, p.age, p.condition);        
      }else
      {
        printf("FILA VAZIA\n");
      }      
    }
  }

  free_queue(q1);
  free_queue(q2);
  free_queue(q3);
  free_queue(q4);

  return 0;
}
