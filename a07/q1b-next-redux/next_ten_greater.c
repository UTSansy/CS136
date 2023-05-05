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

#include "next_ten_greater.h"
#include <assert.h>

// Assume this is the maximum array length (if you want/need it)
const int MAX_LEN = 10000;

// next_ten_greater(arr, len, value, result) finds the 10 or less
//  numbers from arr that is greater than value
// requires:
//  arr and result are valid pointers
//  len >= 0
// effects:
//  multates result
// time: O(n), n is length of arr
//   justification: 
//      Inner loop: Sum[i=j..i=count-1]:O(1) = O(n)
//      Outer loop: Sum[j=0..i=length-1]:O(n) = O(n) (sum of 10 or less O(n))
//      Overall: O(1) + Sum[i=0..i=n-1]:O(1) + O(1) + O(n) + O(1) 
//             = O(1) + O(n) + O(1) + O(n) + O(1)
//             = O(n)
int next_ten_greater(const int arr[], int len, int value, int result[]) {
  assert(arr);
  assert(len >= 0);
  assert(result);

  int count = 0;
  int length = 0;
  int temp[10000] = {0};

  for (int i = 0; i < len; i++) {
    if (arr[i] > value) {
      temp[count] = arr[i];
      count++;
    }
  }

  if (count < 10) {
    length = count;
  } else {
    length = 10;
  }

  for (int j = 0; j < length; j++) {
    int min_idx = j;
    int t = 0;

    for (int i = j; i < count; i++) {
      if (temp[i] < temp[min_idx]){
        min_idx = i;
      }
    }

    t = temp[min_idx];
    result[j] = t;
    temp[min_idx] = temp[j];
    temp[j] = t;
  }

  return length;
}

