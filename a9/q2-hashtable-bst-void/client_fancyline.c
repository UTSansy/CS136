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

// This is the implementation of the fancy client module and client.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cs136-trace.h"
#include "read.h"
#include "hash.h"
#include "hashtable.h"
#include "client_fancyline.h"

// === FANCY LINE MODULE ======================================================

// fancyline represents a fancy line consisting of a printable symbol and a
//   length.
struct fancyline {
  int len;
  char sym;
};

// requires: all functions require valid (non-NULL) parameters

// fl_create(sym, len) creates a new fancy line consisting of symbol sym 
//   and of length len.
// requires: sym must be printable and non-whitespace and len must be > 0
// effects: allocate heap memory, client must call destroy
// time: O(1)
static struct fancyline *fl_create(char sym, int len) {
  assert(len > 0);
  assert(sym >= 32);
  assert(sym <= 126);

  struct fancyline *p = malloc(sizeof(struct fancyline));
  p->len = len;
  p->sym = sym;
  return p;
}

// fl_destroy(fl) releases all resources used by fl.
// effects: fl becomes invalid
// time: O(1)
static void fl_destroy(struct fancyline *fl) {
  assert(fl);

  free(fl);
}

// fl_print(fl) prints the fancy line's symbol length times
// effects: creates output
// time: O(n) where n is the length of the fancy line
static void fl_print(const struct fancyline *fl) {
  assert(fl);

  for (int i = 0; i < fl->len; i++) {
    printf("%c", fl->sym);
  }
}

// fl_clone(fl) creates a duplicate of fl.
// effects: allocate heap memory, client must call fl_destroy
// time: O(1)
static struct fancyline* fl_clone(const struct fancyline *fl) {
  assert(fl);

  struct fancyline *copy = malloc(sizeof(struct fancyline));
  copy->len = fl->len;
  copy->sym = fl->sym;
  return copy;
}

// fl_hash(fl, hash_len) calculates the hash value of fl with a length
//   of hash_len bits.
// requires: hash_len must be between 2 and 16 (both inclusive)
// time: O(1)
static int fl_hash(const struct fancyline *fl, int hash_len) {
  assert(fl);
  assert(hash_len >= 2);
  assert(hash_len <= 16);
  
  int hash_return = hash_char(fl->sym, hash_len);
  return hash_return;
}

// fl_compare(fl1, fl2) compares fl1 and fl2 and returns the following
//   values:
//   * < 0: fl1 comes before fl2,
//   * = 0: fl1 and fl2 are equal, and
//   * > 0: fl1 comes after fl2.
// time: O(1)
static int fl_compare(const struct fancyline *fl1, 
  const struct fancyline *fl2) {

  assert(fl1);
  assert(fl2);
  
  int len_diff = fl1->len - fl2->len;
  if (len_diff != 0) {
    return len_diff;
  }
  return fl1->sym - fl2->sym;
}

// === CONNECTORS =============================================================

// There is no need to add additional documentation to the connectors

// fl_adt_clone(ptr) connects to fl_clone.
static void *fl_adt_clone(const void *ptr) {
  const struct fancyline *temp = ptr;
   
  return fl_clone(temp);
}

// fl_adt_hash(ptr, hash_len) connects to fl_hash.
static int fl_adt_hash(const void *ptr, int hash_len) {
  const struct fancyline *temp = ptr;

  return fl_hash(temp, hash_len);;
}

// fl_adt_compare(ptr1, ptr2) connects to fl_compare.
static int fl_adt_compare(const void *ptr1, const void *ptr2) {
  const struct fancyline *temp1 = ptr1;
  const struct fancyline *temp2 = ptr2;

  return fl_compare(temp1, temp2);
}

// fl_adt_destory(ptr) connects to fl_destroy.
static void fl_adt_destroy(void *ptr) {
  struct fancyline *temp = ptr;

  fl_destroy(temp);
}

// fl_adt_print(ptr) connects to fl_print.
static void fl_adt_print(const void *ptr) {
  const struct fancyline *temp = ptr;
  fl_print(temp);
}

/// === CLIENT FUNCTION =======================================================

// See client_fancyline.h for documentation.
void client_fancyline(void) {

  // Enable the return statement below when you have not implemented the
  // fancy line module but want to test your hash table implementation with the 
  // string client only.
  //return;

  const int CREATE = lookup_symbol("HASHTABLE");
  const int INSERT = lookup_symbol("INSERT");
  const int REMOVE = lookup_symbol("REMOVE");
  const int PRINT = lookup_symbol("PRINT");

  int cmd = read_symbol();
  assert(cmd == CREATE);
  int hash_length = -1;
  assert(scanf("%d", &hash_length) == 1);
  assert(2 <= hash_length && hash_length <= 16);

  struct hashtable *ht = ht_create(fl_adt_clone, 
                                   fl_adt_hash, hash_length, 
                                   fl_adt_compare,
                                   fl_adt_destroy,
                                   fl_adt_print);

  while ((cmd = read_symbol()) != INVALID_SYMBOL) {
    if (cmd == INSERT) {
      char symbol;
      assert(scanf(" %c", &symbol) == 1);
      int length;
      assert(scanf("%d", &length) == 1);
      struct fancyline *fl = fl_create(symbol, length);
      int status = ht_insert(ht, fl);
      if (status == HT_SUCCESS) {
        fl_print(fl);
        printf(" inserted into the hash table.\n");
      } else {
        fl_print(fl);
        printf(" is already stored in the hash table.\n");
      }
      fl_destroy(fl);
    } else if (cmd == REMOVE) {
      char symbol;
      assert(scanf("%c", &symbol) == 1);
      int length;
      assert(scanf("%d", &length) == 1);
      struct fancyline *fl = fl_create(symbol, length);
      int status = ht_remove(ht, fl);
      if (status == HT_SUCCESS) {
        printf("SUCCESS: ");
        fl_print(fl);
        printf(" removed from the hash table.\n");
      } else {
        printf("WARNING: ");
        fl_print(fl);
        printf(" not removed from the hash table.\n");
      }
      free(fl);
    } else if (cmd == PRINT) {
      ht_print(ht);
    } else {
      printf("ERROR: unknown command\n");
      break;
    }
  }

  ht_destroy(ht);
}
