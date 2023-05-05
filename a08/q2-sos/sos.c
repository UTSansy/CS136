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

// This is the implementation of the sequence of strings (sos) ADT

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cs136-trace.h"
#include "string-io.h"
#include "sos.h"

//////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE FOLLOWING DEFINITIONS

struct sos {
  int len;
  int maxlen;
  char **data;
};

// we have provided sos_read() for you :)
// also, there is no need for you to test sos_read()

// see sos.h
struct sos *sos_read(void) {
  struct sos *seq = sos_create();
  while (1) {
    char *line = read_line();
    if (line == NULL) {
      break;
    }
    sos_insert_end(seq, line);
    free(line);
  }
  return seq;
}

//////////////////////////////////////////////////////////////////////////////

// The following are the functions you must implement

// We recommend that you complete them in the order below, as that may help
// facilitate your testing

// For example, we recommend you write the first few functions
// (create,destroy,length,insert_end,print)
// and then create your own simple tests (.in files) that sufficiently test
// those functions

// Once those functions are tested and debugged, write just one function
// at a time and test it before moving on to the next funciton

// Attempting to write all of the functions before you do any debugging or
// testing is an unwise strategy

//////////////////////////////////////////////////////////////////////////////


const int INITIAL_MAX_LEN = 4;


void space_for_string(struct sos *seq, const char *s, const int position){
  assert(seq);
  int length = strlen(s) + 1;
  seq->data[position] = malloc(sizeof(char) * length);
  strcpy(seq->data[position], s);
}


struct sos *sos_create(void) {
  struct sos *p = malloc(sizeof(struct sos));
  p->data = malloc(sizeof(char*) * INITIAL_MAX_LEN);
  for(int i = 0; i < INITIAL_MAX_LEN; i++){
    p->data[i] = NULL;
  }
  p->len = 0;
  p->maxlen = INITIAL_MAX_LEN;
  return p;
}


void sos_destroy(struct sos *seq) {
  assert(seq);
  int loop = seq->len;
  for (int i = loop - 1; i >= 0; i--) {
    free(seq->data[i]);
  }
  free(seq->data);
  free(seq);
}


int sos_length(const struct sos *seq) {
  assert(seq);
  int length = seq->len;
  return length;
}


void sos_insert_end(struct sos *seq, const char *s) {
  assert(seq);
  assert(s);
  if (seq->len + 1 >= seq->maxlen) {
    seq->maxlen *= 2;
    seq->data = realloc(seq->data, seq->maxlen * sizeof(char*));
  }

  space_for_string(seq, s, seq->len);
  seq->len++;
}


void sos_print(const struct sos *seq) {
  assert(seq);
  for(int i = 0; i < seq->len; i++){
    printf("%s\n", seq->data[i]);
  }
}


const char *sos_item_at(const struct sos *seq, int pos) {
  assert(seq);
  assert(pos >= 0);
  assert(pos <= sos_length(seq));
  return seq->data[pos];
}


void sos_remove_end(struct sos *seq) {
  assert(seq);
  int len = seq->len;
  free(seq->data[len - 1]);
  seq->data[len - 1] = NULL;
  seq->len--;
}


void sos_insert_at(struct sos *seq, int pos, const char *s) {
  assert(seq);
  assert(pos >= 0);
  assert(pos <= sos_length(seq));
  assert(s);
  seq->len++;
  if (seq->len >= seq->maxlen) {
    seq->maxlen *= 2;
    seq->data = realloc(seq->data, seq->maxlen * sizeof(char*));
  }

  for(int i = seq->len; i > pos; i--){
    seq->data[i] = seq->data[i - 1];
  }

  space_for_string(seq, s, pos);
}


void sos_remove_at(struct sos *seq, int pos) {
  assert(seq);
  assert(pos >= 0);
  assert(pos <= sos_length(seq));

  free(seq->data[pos]);
  for (int i = pos + 1; i < seq->len; i++) {
    seq->data[i - 1] = seq->data[i];
  }
  seq->len--; 
}


void sos_replace_at(struct sos *seq, int pos, const char *s) {
  assert(seq);
  assert(pos >= 0);
  assert(pos <= sos_length(seq));
  assert(s);

  free(seq->data[pos]);
  space_for_string(seq, s, pos);
}


void sos_swap(struct sos *seq, int pos1, int pos2) {
  assert(seq);
  assert(pos1 >= 0);
  assert(pos1 <= sos_length(seq));
  assert(pos2 >= 0);
  assert(pos2 <= sos_length(seq));

  char *temp = seq->data[pos1];
  seq->data[pos1] = seq->data[pos2];
  seq->data[pos2] = temp;
}


struct sos *sos_dup(const struct sos *seq) {
  assert(seq);
  
  struct sos *p = sos_create();
  p->maxlen = seq->maxlen;
  p->len = seq->len;
  p->data = realloc(p->data, p->maxlen * sizeof(char*));

  for(int i = 0; i < seq->len; i++){
    space_for_string(p, seq->data[i], i);
  }
  return p;
}
