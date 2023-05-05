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

// Implementation of a string stack (sstack) ADT

// This is a "wrapper" ADT that provides a stack ADT interface, but all of the data
// is actually stored inside of an SOS ADT

// IMPORTANT: Each of the functions should only be a few lines long

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "cs136-trace.h"
#include "sos.h"
#include "sstack.h"

//////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE FOLLOWING DEFINITIONS

struct sstack {
  struct sos *seq;
};

// we have provided sstack_is_empty() for you :)

// see sstack.h
bool sstack_is_empty(const struct sstack *ss) {
  assert(ss);
  return sos_length(ss->seq) == 0;
}

//////////////////////////////////////////////////////////////////////////////

struct sstack *sstack_create(void){
  struct sstack *p = malloc(sizeof(struct sstack));
  struct sos *s = sos_create();
  p->seq = s;

  return p;
}

const char *sstack_top(const struct sstack *ss){
  assert(ss);

  struct sos *s = ss->seq;
  return sos_item_at(s, sos_length(s) - 1);
}

char *sstack_pop(struct sstack *ss){
  assert(ss);

  struct sos *s = ss->seq;
  const char *str = sos_item_at(s, sos_length(s) - 1);

  int new_len = strlen(str) + 1;
  char *new = malloc(sizeof(char) * new_len);
  strcpy(new, str);
  sos_remove_end(s);

  return new;
}

void sstack_push(const char *str, struct sstack *ss){
  assert(ss);
  assert(str);

  sos_insert_end(ss->seq, str);
}

void sstack_destroy(struct sstack *ss) {
  assert(ss);
  
  sos_destroy(ss->seq);
  free(ss);
}