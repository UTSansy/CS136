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

#include "cs136-trace.h"
#include <stdio.h>
#include <assert.h>

// read_integer(set, num) read input and put into stack
//  requires: set is valid pointer
//            num > 0;
//  effect: read input
void read_integer(int *set, int num){
  assert(set);
  assert(num > 0);
  for(int i = 0; i < num; i++){
    int input = 0;
    if(scanf(" %d", &input) == 1){
      set[i] = input;
    }
  }
}

int main(void) {
    int set1[1000] = {0};
    int set2[1000] = {0};
    int set3[1000] = {0};
    int num = 0;
    int sum = 0;
  
    if(scanf(" %d", &num) == 1){
      read_integer(set1, num);
      read_integer(set2, num);
      read_integer(set3, num);
    }

    for(int i = 0; i < num; i++){
      sum = set1[i] + set2[i] + set3[i];
      printf("%d\n", sum);
    }
}
