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

// arrayfun.h [INTERFACE]

// This is a module that has some fun with arrays in C

#include <stdbool.h>

// divides_followers(a, n) determines how many items in a are divisors
//   of the sum of the sub-array starting at that item and ending at
//   the final item of the array.
// requires: a is a valid array with given len [not asserted]
//           n > 1
// time: O(n^2), n is len of a
//       Inner loop: Sum[j=i..j=n-1] O(1) = O(n)
//       Outer loop: Sum[i=0..i=n-1] O(n) = O(n^2)
int divides_followers(const int a[], int n);


// consec_sum(a, n, b, m) determines if an element of b is the sum
//   of any two consecutive elements in a.
// requires: a and b are arrays of length n and m, respectively
//           [not asserted]
//           n, m > 1
// 	     a is sorted in increasing order (b may not be sorted)
// time: O(mn), n is len of a and m is len of b
//       Inner loop: Sum[i=0..j=n-2] O(1) = O(n)
//       Outer loop: Sum[i=0..i=m-1] O(n) = O(mn)
bool consec_sum(const int a[], int n, const int b[], int m);

// even_first(a, n) puts all the even numbers before all of the odd numbers
//   in the array a.  The order of the even/odd items may be changed in some
//   unspecified way.
// requires: a is a valid array with given len [not asserted]
//           n > 1
// effects: may modify a
// time: O(n^2), n is len of a
//       Inner loop: Sum[j=i..j=1] O(1) = O(n)
//       Outer loop: Sum[i=0..i=n-1] O(n) = O(n^2)
void even_first(int a[], int n);
