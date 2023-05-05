/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// ERROR_NO_INTEGRITY_STATEMENT
//
// Name: ERROR_NO_NAME
// login ID: ERROR_NO_LOGIN
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <assert.h>
#include "cs136-trace.h"
#include "team.h"

//////////////////////////////////////////////////////////////////////////////////////////
// These definitions are used to control testing.
const int MAX_TEAMS = 4;

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE

// print_reason(r) prints information about the reason for a failure
//    as indicated in the structure r.
// requires: r is a valid pointer to a reason
//           The reason code is either FAIL_INSUFFICIENT_FUNDS or FAIL_ROSTER_FULL
// effects: produces output

void print_reason(const struct reason* const r) {
  assert(r);
  assert(r->code == FAIL_INSUFFICIENT_FUNDS || r->code == FAIL_ROSTER_FULL);
  if (r->code == FAIL_INSUFFICIENT_FUNDS) {
    printf("Team %d doesn't have enough money\n", r->team_num);
  } else if (r->code == FAIL_ROSTER_FULL) {
    printf("Team %d has a full roster\n", r->team_num);
  } 
}
// END OF DO NOT CHANGE REGION
//////////////////////////////////////////////////////////////////////////////////////////


void do_io_tests(void) {

  // Possible messages for team command (nothing is printed if successful)
  //   "Teams are all initialized\n"

  // Possible messages for is_on command
  //   "Player %d is on team %d\n"
  //   "Player %d is not on team %d\n"

  // Possible messages for add_player command (nothing is printed if successful)
  //   "add_player failed : " 
  //    followed by calling print_reason to print the reason for the failure

  // Possible messages for sell_player command (nothing is printed if successful)
  //   "sell_player failed : "
  //    followed by calling print_reason to print the reason for the failure

  // Possible messages for trade_players command (nothing is printed if successful)
  //   "trade_players failed : "
  //    followed by calling print_reason to print the reason for the failure

}

int main(void) {
  // DO NOT CHANGE THE CODE BELOW THIS LINE
  do_io_tests();
}
