#include "unity.h"

#include <tictactoe.h>

static void fill_board(int *board, int value) {
  for (int i = 0; i < N * N; ++i) {
    board[i] = value;
  }
}

void test_initializeBoard_sets_all_cells_empty(void) {
  int board[N * N];
  fill_board(board, CROSS);

  initializeBoard(board);

  for (int i = 0; i < N * N; ++i) {
    TEST_ASSERT_EQUAL_INT(EMPTY, board[i]);
  }
}

void test_setGame_resets_board_sets_default_turn_state(void) {
  game g;
  fill_board(g.board, NOUGHT);
  g.gameOver = true;
  g.side = NOUGHT;

  setGame(&g);

  for (int i = 0; i < N * N; ++i) {
    TEST_ASSERT_EQUAL_INT(EMPTY, g.board[i]);
  }
  TEST_ASSERT_FALSE(g.gameOver);
  TEST_ASSERT_EQUAL_INT(CROSS, g.side);
}

void test_hasFreeSquare_reports_true_if_any_empty(void) {
  int board[N * N] = {CROSS, NOUGHT, CROSS, NOUGHT, EMPTY,
                      CROSS, NOUGHT, CROSS,  NOUGHT};

  TEST_ASSERT_TRUE(hasFreeSquare(board));
}

void test_hasFreeSquare_reports_false_if_board_full(void) {
  int board[N * N] = {CROSS, NOUGHT, CROSS, NOUGHT, CROSS,
                      NOUGHT, CROSS, NOUGHT, CROSS};

  TEST_ASSERT_FALSE(hasFreeSquare(board));
}

void test_isThereAWinner_detects_row_win(void) {
  int board[N * N] = {CROSS, CROSS, CROSS, EMPTY, EMPTY,
                      EMPTY, EMPTY, EMPTY, EMPTY};

  TEST_ASSERT_TRUE(isThereAWinner(board, CROSS));
  TEST_ASSERT_FALSE(isThereAWinner(board, NOUGHT));
}

void test_isThereAWinner_reports_no_win(void) {
  int board[N * N] = {CROSS, NOUGHT, CROSS, CROSS, NOUGHT,
                      NOUGHT, NOUGHT, CROSS, NOUGHT};

  TEST_ASSERT_FALSE(isThereAWinner(board, CROSS));
  TEST_ASSERT_FALSE(isThereAWinner(board, NOUGHT));
}

void test_win_returns_winner_side_value(void) {
  int board[N * N] = {NOUGHT, NOUGHT, NOUGHT, CROSS, CROSS,
                      EMPTY,  EMPTY,  EMPTY,  EMPTY};

  TEST_ASSERT_EQUAL_INT(NOUGHT, win(board));
}

void test_getComputerMoveAI_takes_winning_move(void) {
  int board[N * N] = {NOUGHT, NOUGHT, EMPTY, CROSS, CROSS,
                      EMPTY,  EMPTY,  EMPTY, EMPTY};

  int move = getComputerMoveAI(board, CROSS, NOUGHT);

  TEST_ASSERT_EQUAL_INT(2, move);
}

void test_getComputerMoveAI_blocks_immediate_player_win(void) {
  int board[N * N] = {CROSS, CROSS, EMPTY, NOUGHT, EMPTY,
                      EMPTY,  EMPTY, NOUGHT, EMPTY};

  int move = getComputerMoveAI(board, CROSS, NOUGHT);

  TEST_ASSERT_EQUAL_INT(2, move);
}

void test_resetScoreboard_resets_only_score_fields(void) {
  game g = {0};
  g.level = HARD;
  g.user[0].name = "aleksa";
  g.user[1].name = "Computer";
  g.totalGamesPlayed = 9;
  g.totalDraws = 3;
  g.user[0].numbereOfWins = 2;
  g.user[1].numbereOfWins = 4;

  resetScoreboard(&g);

  TEST_ASSERT_EQUAL_INT(0, g.totalGamesPlayed);
  TEST_ASSERT_EQUAL_INT(0, g.totalDraws);
  TEST_ASSERT_EQUAL_INT(0, g.user[0].numbereOfWins);
  TEST_ASSERT_EQUAL_INT(0, g.user[1].numbereOfWins);
  TEST_ASSERT_EQUAL_STRING("aleksa", g.user[0].name);
  TEST_ASSERT_EQUAL_INT(HARD, g.level);
}
