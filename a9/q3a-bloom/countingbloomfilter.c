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

// This is the implementation of the counting Bloom filter ADT.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "countingbloomfilter.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THESE
// See countingbloomfilter.h for documentation
const int CBF_SUCCESS = 0;
const int CBF_FAILURE = 1;
// -----------------------------------------------------------------------

// See countingbloomfilter.h for documentation
struct countingbloomfilter {
    int (**hash_funcs)(const char *, int);
    int hash_len;
    int len;
    int nof_tables;
    int **tables;
};

// See countingbloomfilter.h for documentation
struct countingbloomfilter *cbf_create(int (**hash_funcs)(const char *, int),
                                       int hash_len, int nof_tables) { 

  struct countingbloomfilter *p = malloc(sizeof(struct countingbloomfilter));

  int len = 1;
  for (int i = 0; i < hash_len; i++) {
    len *= 2;
  }

  int **table = malloc(sizeof(int*) * nof_tables);

  for (int i = 0; i < nof_tables; i++) {
    table[i] = malloc(sizeof(int) * len);
    for (int j = 0; j < len; j++) {
      table[i][j] = 0;
    }
  }

  p->tables = table;
  p->hash_funcs = hash_funcs;
  p->hash_len = hash_len;
  p->len = len;
  p->nof_tables = nof_tables;

  return p;
}

// See countingbloomfilter.h for documentation
void cbf_destroy(struct countingbloomfilter *cbf) {
  assert(cbf);

  for (int i = 0; i < cbf->nof_tables; i++) {
      free(cbf->tables[i]);
  }

  free(cbf->tables);
  free(cbf);
}


// See countingbloomfilter.h for documentation
void cbf_insert(struct countingbloomfilter *cbf, const char *key) {
  assert(cbf);
  assert(key);

  for (int i = 0; i < cbf->nof_tables; i++) {
    int get_pos = cbf->hash_funcs[i](key, cbf->hash_len);
    cbf->tables[i][get_pos] += 1;
  }
}

// See countingbloomfilter.h for documentation
bool cbf_lookup(const struct countingbloomfilter *cbf, const char *key) {
  assert(cbf);
  assert(key);

  for (int i = 0; i < cbf->nof_tables; i++) {
    int get_pos = cbf->hash_funcs[i](key, cbf->hash_len);
    if (cbf->tables[i][get_pos] == 0) {
      return false;
    }
  }

  return true;
}

// See countingbloomfilter.h for documentation
int cbf_remove(struct countingbloomfilter *cbf, const char *key) {
  if (cbf_lookup(cbf, key) == true) {
    for (int i = 0; i < cbf->nof_tables; i++) {
      int get_pos = cbf->hash_funcs[i](key, cbf->hash_len);
      cbf->tables[i][get_pos] -= 1;
    }
    return CBF_SUCCESS;
  }
  return CBF_FAILURE;
}

// See countingbloomfilter.h for documentation
void cbf_print(const struct countingbloomfilter *cbf) {
  for (int i = 0; i < cbf->nof_tables; i++) {
    printf("table %d:\n", i);
    for (int j = 0; j < cbf->len; j++) {
       printf("%3d\n", cbf->tables[i][j]);
    }
  }
}