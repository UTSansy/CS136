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

// This is the implementation of the suggest module.

#include "suggest.h"
#include "triple-s.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////// 
// do not modify this constant:
const int SUGGEST_MAX_STRLEN = 63;
/////////////////////////////////////////////////////////////////////////////

const int ALL_LETTERS = 26;


char *single_deletions(const char *keyword, const int pos, int len) {
  assert(pos >= 0);
  assert(len > 0);
  
  char *temp = malloc((len + 1) * sizeof(char));
  int curr_pos = 0;

  int i = 0;
  for (; i < len; i++) {
    if (i == pos) {
      continue;
    }
    temp[curr_pos] = keyword[i];
    curr_pos++;
  }
  temp[curr_pos] = 0;
  return temp;
}


char *single_insertions(const char *keyword, const int pos, const char c, const int len) {
  assert(pos >= 0);
  assert(len > 0);

  char *temp = malloc((len + 2) * sizeof(char));
  int curr_pos = 0;

  for (int i = 0; i <= len; i++) {
    if (i == pos) {
      temp[i] = c;
    } else {
      temp[i] = keyword[curr_pos];
      curr_pos++;
    }
  }
  temp[len + 1] = 0;

  return temp;
}


char *single_substitution(const char *keyword, const int pos, const char c, const int len) {
  assert(pos >= 0);
  assert(len > 0);

  char *temp = malloc((len + 1) * sizeof(char));

  for (int i = 0; i < len; i++) {
    if (i == pos) {
      temp[i] = c;
    } else {
      temp[i] = keyword[i];
    }
  }
  temp[len] = 0;

  return temp;
}


char *adjacent_swap(const char *keyword, const int pos, const int len) {
  assert(pos >= 0);
  assert(len > 0);

  char *temp = malloc((len + 1) * sizeof(char));

  for (int i = 0; i < len - 1; i++) {
    if (i == pos) {
      temp[i] = keyword[i + 1];
      temp[i + 1] = keyword[i];
      i++;
    } else {
      temp[i] = keyword[i];
    }
  }
  temp[len] = 0;

  return temp;
}


// suggest(dict, word) creates a new SSS that contains suggestions
//   from the provided dict[ionary] for possible misspellings of word
// note: the word itself should not appear in the returned SSS
//       the returned SSS will be empty if no suggestions can be found
//         (the returned SSS must still be destroyed)
//       see assignment text for more details regarding
//         which words should be suggested
// requires: dict must be a valid counting Bloom filter
//           word must be a non-empty null-terminated string [not asserted]
//           word only contains lowercase letters (or numbers) [not asserted]
//           length of word <= SUGGEST_MAX_STRLEN
// effects: allocates memory (an SSS) (you must call sss_destroy)
// time: O(n^2)
struct triple_s *suggest(const struct countingbloomfilter *dict, 
                         const char *word) {
  assert(dict);

  struct triple_s *p = sss_create();
  char *temp = NULL;

  int n = strlen(word);
  assert(n <= SUGGEST_MAX_STRLEN);

  for (int i = 0; i < n; i++) {
    temp = single_deletions(word, i, n);
    if (cbf_lookup(dict, temp)) {
      sss_add(p, temp);
    }

    free(temp);
  }

  for (int j = 0; j <= n; j++) {
    for (int i = 0; i < ALL_LETTERS; i++) {
      char c = 'a' + i;
      temp = single_insertions(word, j, c, n);
      if (cbf_lookup(dict, temp)) {
        sss_add(p, temp);
      }
      free(temp);
    }
  }

  for (int j = 0; j <= n; j++) {
    for (int i = 0; i < ALL_LETTERS; i++) {
      char c = 'a' + i;
      temp = single_substitution(word, j, c, n);
      if (cbf_lookup(dict, temp)) {
        sss_add(p, temp);
      }
      free(temp);
    }
  }

  for (int j = 0; j < n; j++) {
    temp = adjacent_swap(word, j, n);
    if (cbf_lookup(dict, temp)) {
      sss_add(p, temp);
    }
    free(temp);
  }

  return p;
}
