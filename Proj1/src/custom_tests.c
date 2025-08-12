#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in game.c
#include "game.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char *vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
  // TODO: Implement this function.
  if (!assert_true("w is tail",is_tail('w')))
  {
    return false;
  }

  if (!assert_true("a is tail",is_tail('a')))
  { 
    return false;
  }

  if (!assert_true("s is tail",is_tail('s')))
  {
    return false;
  }

  if (!assert_true("d is tail",is_tail('d')))
  {
    return false;
  }

  if (!assert_false("W is not tail",is_tail('W')))
  {
    return false;
  }

  if (!assert_false("A is not tail",is_tail('A')))
  {
    return false;
  }

  return true;
}

bool test_is_head() {
  // TODO: Implement this function.
  if (!assert_true("W is head",is_head('W')))
  {
    return false;
  }

  if (!assert_true("A is head",is_head('A')))
  {
    return false;
  }

  if (!assert_true("S is head",is_head('S')))
  {
    return false;
  }

  if (!assert_true("D is head",is_head('D')))
  {
    return false;
  }

  if (!assert_true("x is head",is_head('x')))
  {
    return false;
  }

  if (!assert_false("w is not head",is_head('w')))
  {
    return false;
  }

  if (!assert_false("a is not head",is_head('a')))
  {
    return false;
  }

  if (!assert_false("s is not head",is_head('s')))
  {
    return false;
  }

  if (!assert_false("d is not head",is_head('d')))
  {
    return false;
  }

  return true;
}

bool test_is_snake() {
  // TODO: Implement this function.
  if (!assert_true("'w' is snake", is_snake('w'))) return false;
  if (!assert_true("'a' is snake", is_snake('a'))) return false;
  if (!assert_true("'s' is snake", is_snake('s'))) return false;
  if (!assert_true("'d' is snake", is_snake('d'))) return false;
  
  // 测试蛇身字符
  if (!assert_true("'^' is snake", is_snake('^'))) return false;
  if (!assert_true("'<' is snake", is_snake('<'))) return false;
  if (!assert_true("'v' is snake", is_snake('v'))) return false;
  if (!assert_true("'>' is snake", is_snake('>'))) return false;
  
  // 测试蛇头字符
  if (!assert_true("'W' is snake", is_snake('W'))) return false;
  if (!assert_true("'A' is snake", is_snake('A'))) return false;
  if (!assert_true("'S' is snake", is_snake('S'))) return false;
  if (!assert_true("'D' is snake", is_snake('D'))) return false;
  if (!assert_true("'x' is snake", is_snake('x'))) return false;
  
  // 测试非蛇字符
  if (!assert_false("'#' is not snake", is_snake('#'))) return false;
  if (!assert_false("' ' is not snake", is_snake(' '))) return false;
  if (!assert_false("'*' is not snake", is_snake('*'))) return false;
  
  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  if (!assert_equals_char("^ to w",'w',body_to_tail('^')))
  {
    return false;
  }

  if (!assert_equals_char("< to a",'a',body_to_tail('<')))
  {
    return false;
  }

  if (!assert_equals_char("> to d",'d',body_to_tail('>')))
  {
    return false;
  }

  if (!assert_equals_char("v to s",'s',body_to_tail('v')))
  {
    return false;
  }

  if (!assert_equals_char("'w' returns '?'", '?', body_to_tail('w'))) 
  {
    return false;
  }

  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  if (!assert_equals_char("W to ^",'^',head_to_body('W')))
  {
    return false;
  }

  if (!assert_equals_char("A to <",'<',head_to_body('A')))
  {
    return false;
  }

  if (!assert_equals_char("S to v",'v',head_to_body('S')))
  {
    return false;
  }

  if (!assert_equals_char("D to >",'>',head_to_body('D')))
  {
    return false;
  }

  if (!assert_equals_char("'?' returns '?'", '?', head_to_body('?'))) {
    return false;
  }

  return true;
}

bool test_get_next_row() {
  // TODO: Implement this function.
  if (!assert_equals_unsigned_int("'v' returns 1",1,get_next_row(0,'v')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("'s' returns 1",1,get_next_row(0,'s')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("'S' returns 1",1,get_next_row(0,'S')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("'^' returns 0",0,get_next_row(1,'^')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("'w' returns 0",0,get_next_row(1,'w')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("'W' returns 0",0,get_next_row(1,'W')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("'x' returns 1",1,get_next_row(1,'x')))
  {
    return false;
  }


  return true;
}

bool test_get_next_col() {
  // TODO: Implement this function.
  if (!assert_equals_unsigned_int("> returns 1",1,get_next_col(0,'>')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("d returns 1",1,get_next_col(0,'d')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("D returns 1",1,get_next_col(0,'D')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("< returns 0",0,get_next_col(1,'<')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("a returns 1",0,get_next_col(1,'a')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("A returns 1",0,get_next_col(1,'A')))
  {
    return false;
  }

  if (!assert_equals_unsigned_int("x returns 0",0,get_next_col(0,'x')))
  {
    return false;
  }
  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
