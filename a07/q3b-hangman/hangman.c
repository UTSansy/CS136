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

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "words.h"
#include "hangman-io.h"
#include "string.h"

// change_input(intput_num, cap_word) changes input_num to corresponding array index, 
//  and let cap_word store the cap version of the char
// requires: 
//  input_num and cap_word are valid pointers
// effects: 
//  multates input_num, cap_word
// time: O(1)
void change_input(int *input_num, char *cap_word) {
  assert(input_num);
  assert(cap_word);

  if (*input_num >= 'a' && *input_num <= 'z') {
    *input_num -= 'a';
    *cap_word = *input_num + 'A';
  } else {
    *cap_word = *input_num;
    *input_num -= 'A';
  }
}

// print_word(p, len, all_latters) prints the word with actual latter or * 
// requires: 
//  p and all_latters are valid pointers
//  len >= 0
// effects: 
//  produce output
// time: O(n), n is the length of p
void print_word(const char *p, int len, int const all_latters[]){
  assert(p);
  assert(all_latters);

  int star_printed = 0;
  for (int i = 0; i < len; i++) {
    int num = p[i] - 'A';

    if (p[i] == ' ') {
      printf(" ");
    } else if (all_latters[num] > 0) {
      printf("%c", p[i]);
    } else {
      printf("*");
      star_printed++;
    }
  }
  printf("\n");
}

// star_printed(*p, len, all_latters) return true if all p's latters are revealed
// requires: 
//  p and all_latters are valid pointers
//  len >= 0
// time: O(n), n is the length of p
bool star_printed(const char *p, int len, const int all_latters[]) {
  assert(p);
  assert(all_latters);

  int star = 0;
  for (int i = 0; i < len; i++) {
    int num = p[i] - 'A';
    if (p[i] != ' ' && all_latters[num] == 0) {
      star++;
    }
  }

  if (star == 0) {
    return true;
  } else {
    return false;
  }
}

// is_on(p, len, c) returns true if c is in p
// requires: 
//  p is a valid pointer
//  len >= 0
// time: O(n), n is the length of p
bool is_on(const char *p, int len, char c) {
  assert(p);

  for (int i = 0; i < len; i++) {
    if (p[i] == c || p[i] == (c - 'a' + 'A')) {
      return true;
    } 
  }

  return false;
}

// already_guessed(all_latters, num) check if num is been guessed
// requires: 
//  all_latters is a valid pointer
//  num >= 0
// time: O(1)
bool already_guessed(int all_latters[], int num) {
  assert(num >= 0);
  assert(all_latters);

  if (all_latters[num] != 0) {
    return true;
  } else {
    return false;
  }
}

// start_game() plays the game
// time: O(mn), m is the number of things read, n is the length of the word
void start_game(void){
  int attempts = 0;
  int all_latters[26] = {0};
  char cap_word = '\0';

  printf(enter_game_number, max_words);
  int word = 0;
  
  while(scanf(" %d", &word) == 1){
    if (word > max_words || word < 0) {
      printf("%s", invalid_game_number);
      printf(enter_game_number, max_words);
    } else {
      break;
    }
  }

  const char *p = get_word(word);
  int length = strlen(p);
  char input = '\0';
  print_hangman(attempts);
  printf("%s", letter_prompt);
  print_word(p, length, all_latters);
  
  while(scanf(" %c", &input) == 1){

    int input_num = input;
    change_input(&input_num, &cap_word);

    if (input < 'A' || (input > 'Z' && input < 'a') || input > 'z') {
      printf(not_a_letter, input);
    } else if (is_on(p, length, input)) {
      if (already_guessed(all_latters, input_num)){
        printf(already_guessed_letter, cap_word);
        print_hangman(attempts);
        printf("%s", letter_prompt);
        print_word(p, length, all_latters);
        continue;
      }

      all_latters[input_num] += 1;

      if (star_printed(p, length, all_latters) == 1) {
        printf(congratulations, p);
        break;
      }

    } else {
      if (already_guessed(all_latters, input_num)){
        printf(already_guessed_letter, cap_word);
        print_hangman(attempts);
        printf("%s", letter_prompt);
        print_word(p, length, all_latters);
        continue;
      }

      all_latters[input_num] += 1;

      printf(not_in_word, cap_word);
      attempts++;
      if (attempts == max_strikes) {
        print_hangman(attempts);
        printf(game_over, p);
        break;
      }
      printf(not_last_guess, max_strikes - attempts);
    }

    print_hangman(attempts);
    printf("%s", letter_prompt);
    print_word(p, length, all_latters);
  }
}

int main(void) {
  char again = '\0';
  start_game();

  printf("%s", play_again);
  while (scanf (" %c", &again) == 1) {
    if (again == 'Y' || again == 'y'){
      start_game();
      printf("%s", play_again);
    } else if (again == 'N' || again == 'n') {
      break;
    } else {
      printf("%s", invalid_play_again_response);
      printf("%s", play_again);
    }
  }
}
