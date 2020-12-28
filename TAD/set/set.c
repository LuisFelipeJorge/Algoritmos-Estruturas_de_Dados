#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

set_t* create_set(int* arr, int size){
  if (size >= N){
    return NULL;
  }
  set_t *set = (set_t*)malloc(sizeof(set_t));
  if (set != NULL){
    set->number_of_elements = size;
    set->elements = (int*)calloc(N, sizeof(int));
    if (set->elements != NULL){
      int i;
      for ( i = 0; i < size; i++){
        set->elements[arr[i]] = 1;    
      }
      return set;        
    }else{
      return NULL;
    }    
  }else{
    return NULL;
  } 
}

void print_set(set_t *set){
  if (set != NULL){
    int count = 0;
    printf("{ ");
    int i;
    for ( i = 0; i < N; i++){
      if (set->elements[i] == 1 && count < set->number_of_elements - 1){
        printf("%d, ", i);
        count++;
      }else if (set->elements[i] == 1){
        printf("%d ", i);
      }
    }
    printf("}\n");     
  }else{
    printf("Empty set\n");
  }  
}

void free_set(set_t *set){
  if (set != NULL){
    free(set->elements);
    free(set);    
  }  
}

set_t* set_union(set_t *a, set_t *b){
  set_t *result = NULL;
  int* elements = NULL;
  int i;
  int count = 0;
  for ( i = 0; i < N; i++){
    if (a->elements[i] == 1 || b->elements[i] == 1){
      count++;
      elements = (int*)realloc(elements, count*sizeof(int));
      if (elements != NULL){
        elements[count - 1] = i;
      }else{
        return NULL;
      }       
    }    
  }
  result = create_set(elements, count);
  free(elements);
  return result;
}

set_t* set_intersection(set_t *a, set_t *b){
  set_t *result = NULL;
  int* elements = NULL;
  int i;
  int count = 0;
  for ( i = 0; i < N; i++){
    if (a->elements[i] == 1 && b->elements[i] == 1){
      count++;
      elements = (int*)realloc(elements, count*sizeof(int));
      if (elements != NULL){
        elements[count - 1] = i;
      }else{
        return NULL;
      }       
    }    
  }
  result = create_set(elements, count);
  free(elements);
  return result;
}

set_t* set_difference(set_t *a, set_t *b){
  set_t *result = NULL;
  int* elements = NULL;
  int i;
  int count = 0;
  for ( i = 0; i < N; i++){
    if (a->elements[i] == 1 && b->elements[i] == 0){
      count++;
      elements = (int*)realloc(elements, count*sizeof(int));
      if (elements != NULL){
        elements[count - 1] = i;
      }else{
        return NULL;
      }       
    }    
  }
  result = create_set(elements, count);
  free(elements);
  return result;
}

bool is_in_the_set(int x, set_t* a){
  if (a->elements[x] == 1) return true;
  return false;
}

void set_insert(int x, set_t* a){
  if (x < N){
    a->elements[x] = 1;
    a->number_of_elements += 1;
  }  
}

void set_remove(int x, set_t* a){
  if (x < N){
    a->elements[x] = 0;    
    a->number_of_elements -= 1;
  }  
}

void set_assign(set_t *a, set_t *b){
  a->number_of_elements = b->number_of_elements;
  int i;
  for ( i = 0; i < N; i++){
    a->elements[i] = b->elements[i];
  }    
}

int set_min(set_t *a){
  int i;
  for ( i = 0; i < N; i++){
    if (a->elements[i] == 1){
      return i;
    }    
  }
  return -1; 
}

int set_max(set_t *a){
  int i;
  int max_index = 0;
  for ( i = 0; i < N; i++){
    if (a->elements[i] == 1){
      max_index = i;
    }    
  }
  return max_index; 
}

bool are_equals(set_t *a, set_t *b){
  if (a->number_of_elements != b->number_of_elements) return false;
  int i;
  for ( i = 0; i < N; i++){
    if (a->elements[i] != b->elements[i]){
      return false;
    }    
  }
  return true;    
}
