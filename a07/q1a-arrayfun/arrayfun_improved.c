/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// get original find_sorted from section example 6.3.5
//
// Name: Junyi Gao
// login ID: j25gao
//////////////////////////////////////////////////////////////////////////////////////////

#include "arrayfun_improved.h"
#include <assert.h>
#include <stdbool.h>


// see arrayfun_improved.h for documentation
int divides_followers(const int a[], int n) {
  assert(a);
  assert(n > 1);

  int total = 0;
  int count = 0;
  for(int i = 0; i < n; i++){
    total += a[i];
  }

  for(int i = 0; i < n; i++){
    if ((a[i] != 0) && (total % a[i] == 0)) {
      ++count;
    }
    total -= a[i];
  }

  return count;
}	

// find_sorted(item, b, len) find the iten from sorted array b
// requires: 
//  b is a valid and sorted array
//  len > 0
// time: O(logm), m is the length of b
static bool find_sorted(int item, const int b[], int len) {
  assert(b);
  assert(len > 0); 
  int low = 0;
  int high = len - 2;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (b[mid] == item) {
      return true;
    } else if (b[mid] < item) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return false;
}

// see arrayfun_improved.h for documentation
bool consec_sum(const int a[], int n, const int b[], int m) {
  assert(a);
  assert(n > 1);
  assert(b);
  assert(m > 1);

  for (int j = 1; j < n ; ++j) {
    if (find_sorted(a[j] + a[j - 1], b, m)) {
      return true;
    }
  }
  return false;
}

// see arrayfun_improved.h for documentation
void even_first(int a[], int n) {
  assert(a);
  assert(n > 1);
  
  int index = 0;
  int temp = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] % 2 == 0) {
      temp = a[i];
      a[i] = a[index];
      a[index] = temp;
      index++;
    }
  }
}
