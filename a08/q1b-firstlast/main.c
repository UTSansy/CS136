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

// This program is an introduction to using dynamic memory

// A "word" is a sequence of printable non-whitespace charcters (see modules/string-io.h)

// all words in the input are read in and then two words are printed out,
// each on a separate line:
// * the lexicographically "first" word, and then
// * the lexicographially "last" word

// (comparing public.in and public.expect will help illustrate)

// If no words appear in the input then "INVALID INPUT\n" is printed
// If only one word appears, it is both the first and the last word and so it
// is printed twice

// Words should be compared lexicographically using strcmp()
// (you do not have to worry about about upper case, lower case, etc... just use strcmp)

// All input should be read using read_word() (see modules/string-io.h)
// All output should be printed as printf("%s\n", ...)

// Remember, this is an exercise in using dynamic memory, so endeavour to
// use malloc and free appropriately, and don't forget that the strings
// returned by read_word() must eventually be freed

//////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs136-trace.h"
#include "string-io.h"


int main(void) {

  char *min_word = read_word();
  char *max_word = read_word();

  while(min_word && max_word){
    char *temp = read_word();
    if (temp) {
      if(strcmp(temp, max_word) > 0){
        free(max_word);
        max_word = temp;
      } else if (strcmp(min_word, temp) > 0){
        free(min_word);
        min_word = temp;
      } else {
        free(temp);
      }
    } else {
      break;
    }
  }

  if (max_word == NULL) {
    max_word = min_word;
  }

  if (min_word == NULL) {
    printf("INVALID INPUT\n");
  } else {
    printf("%s\n%s\n", min_word, max_word);
  }

  free(min_word);
  free(max_word);
}
