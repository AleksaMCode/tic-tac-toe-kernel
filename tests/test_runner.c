#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_unity_framework_is_wired(void);
void test_initializeBoard_sets_all_cells_empty(void);
void test_setGame_resets_board_sets_default_turn_state(void);
void test_hasFreeSquare_reports_true_if_any_empty(void);
void test_hasFreeSquare_reports_false_if_board_full(void);
void test_isThereAWinner_detects_row_win(void);
void test_isThereAWinner_reports_no_win(void);
void test_win_returns_winner_side_value(void);
void test_getComputerMoveAI_takes_winning_move(void);
void test_getComputerMoveAI_blocks_immediate_player_win(void);
void test_resetScoreboard_resets_only_score_fields(void);
void test_strcmp_returns_zero_for_equal_strings(void);
void test_strcmp_returns_nonzero_for_different_strings(void);
void test_strcpy_copies_source_into_destination(void);
void test_strcat_appends_source_to_destination(void);
void test_malloc_forwards_size_to_allocate(void);

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_unity_framework_is_wired);
  RUN_TEST(test_initializeBoard_sets_all_cells_empty);
  RUN_TEST(test_setGame_resets_board_sets_default_turn_state);
  RUN_TEST(test_hasFreeSquare_reports_true_if_any_empty);
  RUN_TEST(test_hasFreeSquare_reports_false_if_board_full);
  RUN_TEST(test_isThereAWinner_detects_row_win);
  RUN_TEST(test_isThereAWinner_reports_no_win);
  RUN_TEST(test_win_returns_winner_side_value);
  RUN_TEST(test_getComputerMoveAI_takes_winning_move);
  RUN_TEST(test_getComputerMoveAI_blocks_immediate_player_win);
  RUN_TEST(test_resetScoreboard_resets_only_score_fields);
  RUN_TEST(test_strcmp_returns_zero_for_equal_strings);
  RUN_TEST(test_strcmp_returns_nonzero_for_different_strings);
  RUN_TEST(test_strcpy_copies_source_into_destination);
  RUN_TEST(test_strcat_appends_source_to_destination);
  RUN_TEST(test_malloc_forwards_size_to_allocate);
  return UNITY_END();
}
