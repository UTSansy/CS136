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

// This is the implementation of the cuckoo filter ADT.

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cs136-trace.h"
#include "cuckoofilter.h"
#include "random.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THESE
// See cuckoofilter.h for documentation
const int CUCKOO_SUCCESS = 0;
const int CUCKOO_FAILURE = 1;
// -----------------------------------------------------------------------

// See cuckoofilter.h for documentation
struct cuckoofilter {
  int (*hash_func)(const char *, int);
  int hash_len;
  int hash_capacity;
  int nof_entries;
  int fp_len;
  int max_num_kicks;
  char ***buckets;
};

// See cuckoofilter.h for documentation
struct cuckoofilter *cuckoo_create(int (*hash_func)(const char *, int), 
                                  int hash_len, int nof_entries, int fp_len, 
                                  int max_num_kicks) {
  struct cuckoofilter *cf = malloc(sizeof(struct cuckoofilter));
  cf->hash_func = hash_func;
  cf->hash_len = hash_len;
  cf->hash_capacity = 1 << hash_len;
  cf->nof_entries = nof_entries;
  cf->fp_len = fp_len;
  cf->max_num_kicks = max_num_kicks;
  cf->buckets = malloc(cf->hash_capacity * sizeof(char **));
  for (int i = 0; i < cf->hash_capacity; i++) {
    cf->buckets[i] = malloc(nof_entries * sizeof(char *));
    for (int j = 0; j < nof_entries; j++) {
      cf->buckets[i][j] = NULL;
    }
  }
  return cf;
}

// See cuckoofilter.h for documentation
void cuckoo_destroy(struct cuckoofilter *cf) {
  assert(cf != NULL);
  for (int i = 0; i < cf->hash_capacity; i++) {
  for (int j = 0; j < cf->nof_entries; j++) {
  free(cf->buckets[i][j]);
  }
  free(cf->buckets[i]);
  }
  free(cf->buckets);
  free(cf);
}
 

// See cuckoofilter.h for documentation
bool cuckoo_lookup(const struct cuckoofilter *cf, const char *key) {
  char *fp = finger_print(key, cf->fp_len);
  bool result = false;
  int i1 = cf->hash_func(key, cf->hash_len);
  int i2 = i1 ^ cf->hash_func(fp, cf->hash_len);

  result = bucket_contains(cf, i1, fp) || bucket_contains(cf, i2, fp);

  free(fp);
  return result;
}

// See cuckoofilter.h for documentation
bool cuckoo_remove(struct cuckoofilter *cf, const char *key) {
  char *fp = finger_print(key, cf->fp_len);
  int i1 = cf->hash_func(key, cf->hash_len);
  int i2 = i1 ^ cf->hash_func(fp, cf->hash_len);

  for (int i = 0; i < cf->nof_entries; i++) {
    if (cf->buckets[i1][i] != NULL && strcmp(cf->buckets[i1][i], fp) == 0) {
      free(cf->buckets[i1][i]);
      cf->buckets[i1][i] = NULL;
      free(fp);
      return true;
    }
    if (cf->buckets[i2][i] != NULL && strcmp(cf->buckets[i2][i], fp) == 0) {
      free(cf->buckets[i2][i]);
      cf->buckets[i2][i] = NULL;
      free(fp);
      return true;
    }
  }

  free(fp);
  return false;
}

// See cuckoofilter.h for documentation
void cuckoo_print(const struct cuckoofilter *cf) {
assert(cf);

  for (int i = 0; i < cf->hash_capacity; i++) {
    printf("Bucket %3d: ", i);
    for (int j = 0; j < cf->nof_entries; j++) {
      if (cf->buckets[i][j] != NULL) {
        printf("%s ", cf->buckets[i][j]);
      } else {
      printf("- ");
    }
  }
    printf("\n");
  }
}