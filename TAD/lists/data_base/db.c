#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "db.h"

typedef struct node 
{
  elem info;
  int next;
}node_t;

struct database
{
  node_t arr[SIZE];
  int start, end, empty_idx; 
};

int get_next_free_position(database_t *db)
{
  assert(db != NULL);
  if (is_full(db))
  {
    return -1;
  }else
  {
    int position = db->empty_idx;
    db->empty_idx = db->arr[position].next;
    db->arr[position].next = -1;
    return position;
  }  
}

void free_node(database_t *db, int position)
{
  assert(db != NULL);
  assert(position >= 0 && position < SIZE);
  db->arr[position].next = db->empty_idx;
  db->empty_idx = position;
}

database_t *create()
{
  database_t *db = (database_t*)malloc(sizeof(database_t));
  for (int i = 0; i < SIZE-1; i++)
  {
    db->arr[i].next = i+1;
  }

  db->arr[SIZE-1].next = -1;
  db->empty_idx = 0;
  db->start = -1;
  db->end = -1;

  return db;  
}

int is_empty(database_t *db)
{
  assert(db != NULL);
  return db->start == -1;
}

int is_full(database_t *db)
{
  assert(db != NULL);
  return db->empty_idx == -1;
}

int insert(database_t *db, elem x)
{
  int position = get_next_free_position(db);
  if(position == -1) return 0;
  db->arr[position].info = x;
  db->arr[position].next = -1;
  db->arr[db->end].next = position;
  db->end = position;
  if (db->start == -1) db->start = position;
  return 1;
}

int remove_elem(database_t *db, elem *x)
{
  assert(db != NULL);
  if(is_empty(db)) return 0;
  *x = db->arr[db->start].info;
  int position = db->start;
  db->start = db->arr[position].next;
  free_node(db, position);
  return 1;
}

void free_database(database_t *db)
{
  free(db);
}