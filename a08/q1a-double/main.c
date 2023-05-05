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

// This program implements and tests a "ddoouubbllee" function

// For every word in the input, it calls ddoouubbllee function and then prints
// the "double" of the word on a separate line (see the ddoouubbllee function below)

// A "word" is a sequence of printable non-whitespace charcters (see modules/string-io.h)
// Note that the ddoouubbllee function works for any string, but this test
// client only tests ddoouubbllee with words, which should be sufficient

//////////////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string-io.h"

// ddoouubbllee(s) produces and returns a *new* string that is twice as long
//   as s, and contains each char from s repeated twice
// examples: "Hi there!!" => "HHii  tthheerree!!!!"
//           "" => ""
// requires: s is a valid string (not NULL)
// effects: allocates memory (caller must free)
// time: O(n)
char *ddoouubbllee(const char *s) {
  assert(s);
  int length = strlen(s);
  char *p = malloc(2 * length + 1);
  int i = 0;
  int next = 0;

  for (; i < length; ++i) {
    next = 2 * i;
    p[next] = s[i];
    p[next + 1] = s[i];
  }

  p[2 * i] = '\0';

  return p;
}


// you should not need to modify main()

int main(void) {
  while (1) {
    char *s = read_word();
    if (s == NULL) {
      break;
    }
    char *dd = ddoouubbllee(s);
    printf("%s\n", dd);
    free(s);
    free(dd);
  }
}
