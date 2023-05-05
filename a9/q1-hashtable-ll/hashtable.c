/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// none
//
// Name: Junyi Gao
// login ID: j25gao
//////////////////////////////////////////////////////////////////////////////////////////

// This is the implementation of the hash tree ADT with linked lists.

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "cs136-trace.h"

typedef int (*hash_f) (const char *, int);

// -----------------------------------------------------------------------
// DO NOT CHANGE THESE
// See hashtable.h for documentation
const int HT_SUCCESS        = 0;
const int HT_ALREADY_STORED = 1;
const int HT_NOT_STORED     = 2;
// -----------------------------------------------------------------------

struct llnode {
  char *item;
  struct llnode *next;
};

struct llist {
  struct llnode *front;
};

// See hashtable.h for documentation
struct hashtable {
  int hash_len;
  int len;
  hash_f hf;
  struct llist **list;
};


void free_linked_list(struct llist *list) {
  if (!list) {
    return;
  }

  struct llnode *curr = list->front;

  while (curr) {
    struct llnode *prev = curr;
    curr = curr->next;
    free(prev->item); 
    free(prev);
    prev = NULL;
  }

  free(list);
}

// See hashtable.h for documentation
struct hashtable *ht_create(int (*hash_func)(const char *, int),
                            int hash_length) {
  assert(hash_length > 0);

  int len = 1;
  for (int i = 0; i < hash_length; i++) {
    len *= 2;
  }

  struct hashtable *hash = malloc(sizeof(struct hashtable));
  struct llist **list = malloc(len * sizeof(struct llist *));

  for (int i = 0; i < len; i++) {
    list[i] = NULL;
  }

  hash->list = list;
  hash->hf = hash_func;
  hash->hash_len = hash_length;
  hash->len = len;

  return hash;
}

// See hashtable.h for documentation
void ht_destroy(struct hashtable *ht) {
  int len = ht->len;
  for (int i = 0; i < len; i++) {
    free_linked_list(ht->list[i]);
  }
  free(ht->list);

  free(ht);
}

// See hashtable.h for documentation
int ht_insert(struct hashtable *ht, const char *str) {
  int get_hash = ht->hf(str, ht->hash_len);
  int len = strlen(str) + 1;

  struct llnode *new = malloc(sizeof(struct llnode));
  char *new_string = malloc(sizeof(char) * len);
  strcpy(new_string, str);
  new->item = new_string;

  if (!ht->list[get_hash]) {
    ht->list[get_hash] = malloc(sizeof(struct llist));
    ht->list[get_hash]->front = new;
    new->next = NULL;
    return HT_SUCCESS;
  }

  
  struct llnode *temp = ht->list[get_hash]->front;

  while (temp) {
    if (strcmp (temp->item, str) == 0) {
      free(new_string);
      free(new);
      return HT_ALREADY_STORED;
    }
    temp = temp->next;
  }
  
  temp = ht->list[get_hash]->front;
  ht->list[get_hash]->front = new;
  new->next = temp;
  temp = NULL;
  return HT_SUCCESS;
}

// See hashtable.h for documentation
int ht_remove(struct hashtable *ht, const char *str) {
  int get_hash = ht->hf(str, ht->hash_len);
  if (!ht->list[get_hash]) {
    return HT_NOT_STORED;
  }

  struct llnode *curr = ht->list[get_hash]->front;
  if (strcmp (curr->item, str) == 0) {
    ht->list[get_hash]->front = curr->next;
    free(curr->item);
    free(curr);
    return HT_SUCCESS;
  }

  while (curr) {
    struct llnode *prev = curr;
    curr = curr->next;
    if (strcmp(curr->item, str) == 0) {
      prev->next = curr->next;
      free(curr->item);
      free(curr);
      return HT_SUCCESS;
    }
  }
  
  return HT_NOT_STORED;
}

// See hashtable.h for documentation
void ht_print(const struct hashtable *ht) {
  int len = ht->len;
  for (int i = 0; i < len; i++) {
    printf("%d: ", i);

    if (!ht->list[i]) {
      printf("\n");
      continue;
    }

    struct llnode *temp = ht->list[i]->front;
    while (temp) {
      printf("%s", temp->item);
      if (temp->next) {
        printf(" -> ");
      }
      temp = temp->next;
    }
    printf("\n");
  }
}