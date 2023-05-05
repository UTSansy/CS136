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

// Implementation of a triple_s (SSS) ADT

// This is a "wrapper" ADT that provides a triple_s ADT interface, but all of the data
// is actually stored inside of an SOS ADT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs136-trace.h"
#include "sos.h"
#include "sss.h"

//////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE FOLLOWING DEFINITION

struct triple_s {
  struct sos *seq;
};

//////////////////////////////////////////////////////////////////////////////

struct triple_s *sss_create(void) {
  struct triple_s *s = malloc(sizeof(struct triple_s));
  struct sos *p = sos_create();
  s->seq = p;
  return s;
}


void sss_destroy(struct triple_s *sss) {
  assert(sss);

  struct sos *s = sss->seq;
  sos_destroy(s);
  free(sss);
}


int sss_count(const struct triple_s *sss) {
  assert(sss);
  
  struct sos *s = sss->seq;
  return sos_length(s);
}


int sss_search(const struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);

  struct sos *sos = sss->seq;
  int len = sos_length(sos);

  for (int i = 0; i < len; i++) {
    const char *c = sos_item_at(sos, i);
    if(strcmp(c, s) == 0) {
      return i;
    }
  }
  
  return -1;
}


const char *sss_get(const struct triple_s *sss, int idx) {
  assert(sss);
  assert(0 <= idx);
  assert(idx < sss_count(sss));

  struct sos *s = sss->seq;
  return sos_item_at(s, idx);
}


void sss_add(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);

  struct sos *seq = sss->seq;
  int len = sos_length(seq);

  if (len == 0) {
    sos_insert_end(seq, s);
    return;
  }
  
  for (int i = 0; i < len; i++) {
    const char *cur = sos_item_at(seq, i);
    int compare = strcmp(s, cur);
    if (compare < 0) {
      sos_insert_at(seq, i, s);
      return;
    } else if (compare == 0) {
      return;
    }
  }

  sos_insert_end(seq, s);
}


void sss_add_follows(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);

  struct sos *sos = sss->seq;
  sos_insert_end(sos, s);
}

void sss_remove(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);

  struct sos *sos = sss->seq;
  int len = sos_length(sos);
  for (int i = 0; i < len; i++) {
    const char *c = sos_item_at(sos, i);
    int compare = strcmp(c, s);
    if (compare == 0) {
      sos_remove_at(sos, i);
      break;
    }
  }
}