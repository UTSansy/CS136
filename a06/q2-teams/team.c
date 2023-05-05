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
#include <stdbool.h>
#include "team.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE
const int MAX_PLAYERS = 5;
const int TEAM_INVALID_ID = -1;
const struct team team_empty = {TEAM_INVALID_ID, 0}; // Doesn't set players to empty_player
                                                     // Must be done by team_init_empty

// DO NOT CHANGE THESE
// Reasons for failures
const int FAIL_INSUFFICIENT_FUNDS = -1;
const int FAIL_ROSTER_FULL = -2;
// END OF DO NOT CHANGE REGION

// YOU MUST COMPLETE THIS FUNCTION
void team_print(const struct team* const t) {
  assert(t);
  assert(team_player_value(t) + team_cash(t) == team_value(t));
  printf("Team %d : ", team_get_id(t));

  // INSERT CODE HERE FOR PRINTING PLAYERS
  // Players must be printed from the lowest player_id to highest player_id.
  // You must NOT print players with player_id == PLAYER_INVALID_ID
  // The function you use to print the player is 
  //    player_print(player_ptr);  See player.h
  // player_print will take care of proper spacing.
  // See team_print in team.c of A5 if you need a better idea of what to do.

  printf("player value = %d cash = %d", team_player_value(t), team_cash(t));
  printf("\n");
}
// -----------------------------------------------------------------------

int team_player_value(const struct team* const t) {
  // Replace this with your code
  return 0;
}

int team_value(const struct team* const t) {
  // Replace this with your code
  return 0;
}

int team_cash(const struct team* const t) {
  // Replace this with your code
  return 0;
}

void team_init_empty(struct team* const t) {
  // Replace this with your code
}

void team_setup(struct team* const t, const int id, const int cash) {
  // Replace this with your code
}

int team_get_id(const struct team* const t) {
  // Replace this with your code
  return 1;
}

bool team_is_player_on(const struct team* const t, const int id) {
  // Replace this with your code
  return true;
}

bool team_add_player(struct team* const t, const int id, const int val,
   struct reason *r) {
  // Replace this with your code
  return true;
}

bool team_sell_player(struct team* const t1, const int id,
     struct team* const t2, struct reason *r) {
  // Replace this with your code
  return true;
}

bool team_trade_players(struct team* const t1, const int id1,
     struct team* const t2, const int id2, struct reason *r) {
  // Replace this with your code
  return true;
}

