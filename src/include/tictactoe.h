#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include <common.h>
#include <monitor.h>
#include <timer.h>
#define N 3

enum levels { GAME_WITH_A_FRIEND, EASY, HARD };
enum state { EMPTY, NOUGHT, CROSS = -1 };
enum win { PLAYER1WIN, PLAYER2WIN, DRAW }; /* PLAYER2 can be a computer */
typedef enum { false, true } bool;

typedef struct {
  char *name;
  int side;
  int numbereOfWins;
} player;

typedef struct {
  int board[N * N];
  int level;
  player user[2];
  bool gameOver;
  int side;
  int winner; /* array index */
  int totalGamesPlayed;
  int totalDraws;
} game;

void initializeBoard(int *board);
void setGame(game *ticTacToe);
void printBoard(const int *board);
int welcome(game *ticTacToe);
void toPlayOrNotToPlay();
void enterUsername();
void printRules();
void chooseDifficulty();
void askAgain();
bool hasFreeSquare(const int *board);
void makeAMove(int *board, const int position, const state);
int getHumanMove(const int *board, const char *name);
int getComputerRandomMove(const int *board);
/* -minmax- */
int win(const int *board);
int minimax(int *board, int player);
int getComputerMoveAI(int *board, int playerSide, int computerSide);
/* -------- */
bool isThereAWinner(const int *board, int side);
void computerMoveAndPrint(int *board, enum state st, enum levels lev);
void makeMove(char *name);
void drawHelpFunct(game *ticTacToe);
void winHelpFunct(game *ticTacToe, int index);
void gameInterrupt();

#endif // ! TICTACTOE_H_
