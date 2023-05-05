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
// Name: Junyi Gaoo
// login ID: j25gao
//////////////////////////////////////////////////////////////////////////////////////////

// This is the implementation of the generic hash table ADT with binary search 
//   trees.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "hashtable.h"
#include "cs136-trace.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THESE
// See hashtable.h for documentation
const int HT_SUCCESS        = 0;
const int HT_ALREADY_STORED = 1;
const int HT_NOT_STORED     = 2;
// -----------------------------------------------------------------------

struct bstnode {
  void *item;
  int hight;
  struct bstnode *left;
  struct bstnode *right;
};


// See hashtable.h for documentation
struct hashtable {
  struct bstnode **root;
  void *(*key_clone)(const void *);
  int (*hash_func)(const void *, int);
  int hash_length;
  int len;
  int (*key_compare)(const void *, const void *);
  void (*key_destroy)(void *);
  void (*key_print)(const void *);
};


// See hashtable.h for documentation
struct hashtable *ht_create(void *(*key_clone)(const void *),
                            int (*hash_func)(const void *, int), 
                            int hash_length,
                            int (*key_compare)(const void *, const void *),
                            void (*key_destroy)(void *),
                            void (*key_print)(const void *)) {
  
  int len = 1;
  for (int i = 0; i < hash_length; i++) {
    len *= 2;
  }

  struct hashtable *ht = malloc(sizeof(struct hashtable));
  struct bstnode **p = malloc(sizeof(struct bstnode*) * len);

  for (int i = 0; i < len; i++) {
    p[i] = NULL;
  }

  ht->root = p;

  ht->key_clone = key_clone;
  ht->hash_func = hash_func;
  ht->hash_length = hash_length;
  ht->key_compare = key_compare;
  ht->key_destroy = key_destroy;
  ht->key_print = key_print;
  ht->len = len;

  return ht;
}

void ht_print_helper(struct bstnode *node, void (*key_print)(const void *), bool *is_first) {
  if (node) {
    ht_print_helper(node->left, key_print, is_first);

    if (*is_first) {
      *is_first = false;
    } else {
      printf(",");
    }

    printf("%d-", node->hight);
    key_print(node->item);

    ht_print_helper(node->right, key_print, is_first);
  }
}

void free_node(struct bstnode *node, void (*key_destroy)(void *)) {
  if (!node) {
    return;
  }

  free_node(node->left, key_destroy);
  free_node(node->right, key_destroy);
  key_destroy(node->item);
  free(node);
}

struct bstnode* ht_remove_helper(struct hashtable *ht, 
                                 struct bstnode *node, 
                                 const void *key, 
                                 int *return_value) {

    if (node == NULL) {
      *return_value = HT_NOT_STORED;
      return node;
    }
    int compare = ht->key_compare(node->item, key);

    if (compare < 0) {
        node->right = ht_remove_helper(ht, node->right, key, return_value);
    } else if (compare > 0) {
        node->left = ht_remove_helper(ht, node->left, key, return_value);
    } else {
        if (!node->left && !node->right) {
            ht->key_destroy(node->item);
            free(node);
            *return_value = HT_SUCCESS;
            return NULL;
        }
        if (!node->right) {
            struct bstnode* temp = node->left;
            ht->key_destroy(node->item);
            free(node);
            *return_value = HT_SUCCESS;
            return temp;
        }
        if (!node->left) {
            struct bstnode* temp = node->right;
            ht->key_destroy(node->item);
            free(node);
            *return_value = HT_SUCCESS;
            return temp;
        }
        struct bstnode* prev = NULL;
        struct bstnode* curr = node->right;
        while (curr->left) {
            prev = curr;
            curr = curr->left;
        }
        node->item = curr->item;
        if (!prev) {
            node->right = curr->right;
        } else {
            prev->left = curr->right;
        }
        ht->key_destroy(node->item);
        free(curr);
    }
    *return_value = HT_SUCCESS;
    return node;
}

// See hashtable.h for documentation
void ht_destroy(struct hashtable *ht) {

  for (int i = 0; i < ht->len; i++) {
    if (!ht->root[i]) {
      free(ht->root[i]);
      continue;
    }
    free_node(ht->root[i], ht->key_destroy);
  }

  free(ht->root);
  free(ht);
}

// See hashtable.h for documentation
int ht_insert(struct hashtable *ht, const void *key){
  assert(ht);

  int get_hash = ht->hash_func(key, ht->hash_length);
  struct bstnode *p = malloc(sizeof(struct bstnode));
  p->item = ht->key_clone(key);
  p->hight = 0;
  p->left = NULL;
  p->right = NULL;

  
  if (!ht->root[get_hash]) {
    ht->root[get_hash] = p;
    return HT_SUCCESS;
  }

  struct bstnode *curr = ht->root[get_hash];
  int add_hight = 0;

  while (curr) {
    int result = ht->key_compare(curr->item, p->item);
    if (result == 0) {
      ht->key_destroy(p->item);
      free(p);
      return HT_ALREADY_STORED;
    } else if (result < 0) {
      if (curr->right) {
        curr = curr->right;
        add_hight += 1;
      } else {
        curr->right = p;
        p->hight += add_hight + 1;
        return HT_SUCCESS;
      }
    } else {
      if (curr->left) {
        curr = curr->left;
        add_hight += 1;
      } else {
        curr->left = p;
        p->hight += add_hight + 1;
        return HT_SUCCESS;
      }
    }
  }
  
  return HT_SUCCESS;
}

// See hashtable.h for documentation
int ht_remove(struct hashtable *ht, const void *key){
  assert(ht);
  int return_value = 0;

  int get_hash = ht->hash_func(key, ht->hash_length);
  ht->root[get_hash] = ht_remove_helper(ht, ht->root[get_hash], key, &return_value);
  return return_value;
}

// See hashtable.h for documentation
void ht_print(const struct hashtable *ht) {
  for (int i = 0; i < ht->len; i++) {
    printf("%d: [", i);
    bool is_first = true;
    ht_print_helper(ht->root[i], ht->key_print, &is_first);
    printf("]\n");
  }
}




