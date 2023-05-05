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

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "cs136-trace.h"

// at least 8 characters
// at least one upper case letter (e.g., 'T')
// at least one lower case letter (e.g., 'r')
// at least one digit (e.g., '1')
// at least one special character (e.g., '$') -- see below
// no whitespace or non-printable characters

const int MIN_LENGTH = 8;

// is_valid_password(s) determines whether or not the string s is a valid password
// requires:
//  s is a valid pointer
// time: O(n), n is the length of s
bool is_valid_password(const char *s){
  assert(s);

  int length = 0;
  int upper = 0;
  int lower = 0;
  int number = 0;
  int special = 0;

  length = strlen(s);

  for (int i = 0; i < length; i++) {
    if (s[i] >= '0' && s[i] <= '9') {
      number++;
    } else if (s[i] >= 'a' && s[i] <= 'z') {
      lower++;
    } else if (s[i] >= 'A' && s[i] <= 'Z') {
      upper++;
    } else if (s[i] > ' ' && s[i] <= '~') {
      special++;
    } else {
      return false;
    }
  }

  if (length >= MIN_LENGTH && upper > 0 && lower > 0 && number > 0 && special > 0) {
    return true;
  } else {
    return false;
  }
}

int main(void){
  assert(is_valid_password("Tru$tNo1"));
  assert(!is_valid_password("O1peach! "));
  assert(is_valid_password("Aa1@bcde")); 
  assert(!is_valid_password("abcde"));
  assert(!is_valid_password("Abc123"));
  assert(!is_valid_password("Abc123$"));
  assert(!is_valid_password("abc123$"));
  assert(!is_valid_password("Abcdef$"));
  assert(!is_valid_password("Abc12345"));
  assert(!is_valid_password("Abc123$ "));
  assert(is_valid_password("Abc123$~"));

  // add tests!
  trace_msg("ALL ASSERTIONS PASSED!")
}