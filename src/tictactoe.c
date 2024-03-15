#include <tictactoe.h>

game tic_tac_toe;

int to_play = 1;
int enter_username = 0;
int difficulty = 0;
int play_again = 0;

void initializeBoard(int *board) {
  for (int i = 0; i < N * N; ++i) {
    board[i] = EMPTY;
  }
}

void turnOffAll() {
  to_play = 0;
  enter_username = 0;
  difficulty = 0;
  play_again = 0;
  tic_tac_toe.gameOver = true;
}

void setGame(game *ticTacToe) {
  initializeBoard(ticTacToe->board);
  ticTacToe->gameOver = false;
  ticTacToe->side = CROSS;
}

void printBoard(const int *board) {
  monitor_write("\n");
  for (int i = 0; i < N * N; ++i) {
    if (i != 0 && !(i % 3)) {
      monitor_write("\n\n");
    }
    switch (board[i]) {
    case EMPTY:
      monitor_write("-  ");
      break;
    case CROSS:
      monitor_write("x  ");
      break;
    case NOUGHT:
      monitor_write("o  ");
      break;
    }
  }
  monitor_write("\n");
}

void computerMoveAndPrint(int *board, enum state st, enum levels lev) {
  int i = lev == EASY ? getComputerRandomMove(board)
                      : getComputerMoveAI(board, CROSS, NOUGHT);
  makeAMove(board, i, st);
  printBoard(board);
}

void makeMove(char *name) {
  monitor_write("\nEnter your move ");
  monitor_write(name);
  monitor_write(" (numbers from 1 to 9) >> ");
}

void toPlayOrNotToPlay() {
  monitor_write("Welcome to Tic Tac Toe game.\n");
  monitor_write("Do you want to play a game? (y\\n)\n");
}

void enterUsername() { monitor_write("\n\nPlease enter your username.\n"); }

void printRules() {
  monitor_clear();
  monitor_write("Place a cross/nought by entering appropriate number.\n1 2 "
                "3\n\n4 5 6\n\n7 8 9\n");
}

void chooseDifficulty() {
  monitor_write("\nWhat level do you want?\n1) EASY\n2) HARD\n(1 or 2)\n");
}

void askAgain() { monitor_write("\nDo you want to play again? (y\\n)\n"); }

bool hasFreeSquare(const int *board) {
  for (int i = 0; i < N * N; ++i) {
    if (board[i] == EMPTY) {
      return true;
    }
  }
  return false;
}

void makeAMove(int *board, const int position, const state) {
  board[position] = state;
}

int getComputerRandomMove(const int *board) {
  int availableMoves[N * N] = {-1}, numOfAvailableMoves = 0;
  for (int i = 0; i < N * N; ++i) {
    if (*(board + i) == EMPTY) {
      availableMoves[numOfAvailableMoves++] = i;
    }
  }

  return availableMoves[tick % numOfAvailableMoves];
}

// Tic-tac-toe playing AI. Exhaustive tree-search. WTFPL
// Matthew Steel 2009, www.repsilat.com
int win(const int *board) {
  // Determines if a player has won, returns 0 otherwise.
  unsigned wins[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                         {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
  for (int i = 0; i < 8; ++i) {
    if (board[wins[i][0]] != 0 && board[wins[i][0]] == board[wins[i][1]] &&
        board[wins[i][0]] == board[wins[i][2]]) {
      return board[wins[i][2]];
    }
  }
  return 0;
}

int minimax(int *board, int player) {
  // How is the position like for player (their turn) on board?
  int winner = win(board);
  if (winner != 0) {
    return winner * player;
  }

  int move = -1;
  int score = -2; // Losing moves are preferred to no move

  for (int i = 0; i < N * N; ++i) { // For all moves,
    if (board[i] == EMPTY) {        // If legal,
      board[i] = player;            // Try the move
      int thisScore = -minimax(board, player * -1);
      if (thisScore > score) {
        score = thisScore;
        move = i;
      }                 // Pick the one that's worst for the opponent
      board[i] = EMPTY; // Reset board after try
    }
  }

  if (move == -1) {
    return 0;
  }

  return score;
}

int getComputerMoveAI(int *board, int playerSide, int computerSide) {
  int move = -1;
  int score = -2;
  for (int i = 0; i < N * N; ++i) {
    if (board[i] == EMPTY) {
      board[i] = computerSide;
      int tempScore = -minimax(board, playerSide);
      board[i] = EMPTY;

      if (tempScore > score) {
        score = tempScore;
        move = i;
      }
    }
  }

  // Returns a score based on minimax tree at a given node.
  return move;
}

bool isThereAWinner(const int *board, int side) {
  /* 8 winning combinations */
  int winningCombos[8 * 3] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 3, 6,
                              1, 4, 7, 2, 5, 8, 0, 4, 8, 2, 4, 6};

  for (int i = 0; i <= 24 - 3; i += 3) {
    if (board[winningCombos[i]] == side &&
        board[winningCombos[i + 1]] == side &&
        board[winningCombos[i + 2]] == side) {
      return true;
    }
  }

  return false;
}

void drawHelpFunct(game *ticTacToe) {
  monitor_write("\nGame over! It's a draw.\n");
  ticTacToe->gameOver = true;
  ticTacToe->winner = DRAW;
  ticTacToe->totalDraws++;
  ticTacToe->totalGamesPlayed++;
}

void winHelpFunct(game *ticTacToe, int index) {
  ticTacToe->user[index].numbereOfWins++;
  ticTacToe->winner = PLAYER1WIN;
  ticTacToe->gameOver = true;
  monitor_put('\n');
  monitor_write(ticTacToe->user[index].name);
  monitor_write(" has won a game!\n");
  ticTacToe->totalGamesPlayed++;
}

void gameInterrupt() {
  char answer = get_last_char();
  if (to_play) {
    if (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N') {
      monitor_write("\nDo you want to play a game? (y\\n)\n");
    } else {
      if (answer == 'n' || answer == 'N') {
        // TODO: IMPLEMENT SHUTTING DOWN
        turnOffAll();
      } else {
        setGame(&tic_tac_toe);
        player pl = {"Computer", EMPTY, 0};
        tic_tac_toe.user[0] = tic_tac_toe.user[1] = pl;
        tic_tac_toe.totalGamesPlayed = 0;
        tic_tac_toe.user[0].numbereOfWins = tic_tac_toe.user[1].numbereOfWins =
            tic_tac_toe.totalDraws = 0;
        enter_username = 1;
        to_play = 0;
        enterUsername();
      }
    }
  } else if (enter_username) {
    tic_tac_toe.user[0].name = get_current_line();
    monitor_clear();
    enter_username = 0;
    difficulty = 1;
    chooseDifficulty();
  } else if (difficulty) {
    tic_tac_toe.level = get_last_char() - '0';
    if (tic_tac_toe.level != EASY && tic_tac_toe.level != HARD) {
      chooseDifficulty();
    } else {
      tic_tac_toe.user[0].side = CROSS;
      tic_tac_toe.user[1].side = NOUGHT;
      printRules();
      difficulty = 0;
      makeMove(tic_tac_toe.user[0].name);
    }
  } else if (!tic_tac_toe.gameOver) {
    int input = get_last_char() - '0';
    if (input <= 0 || input >= 10) {
      makeMove(tic_tac_toe.user[0].name);
    } else if (input >= 1 && input <= 9 && tic_tac_toe.board[input - 1]) {
      monitor_write("\nThat square is not available!\n");
      makeMove(tic_tac_toe.user[0].name);
    } else {
      tic_tac_toe.board[input - 1] = tic_tac_toe.user[0].side;

      if (isThereAWinner(tic_tac_toe.board, tic_tac_toe.user[0].side)) {
        winHelpFunct(&tic_tac_toe, 0);
        play_again = 1;
        askAgain();
      } else if (!hasFreeSquare(tic_tac_toe.board)) {
        drawHelpFunct(&tic_tac_toe);
        play_again = 1;
        askAgain();
      }
      if (!tic_tac_toe.gameOver) {
        printBoard(tic_tac_toe.board);
        monitor_write("\nComputer is making a move...\n");
        computerMoveAndPrint(tic_tac_toe.board, tic_tac_toe.user[1].side,
                             tic_tac_toe.level);

        if (isThereAWinner(tic_tac_toe.board, tic_tac_toe.user[1].side)) {
          winHelpFunct(&tic_tac_toe, 1);
          play_again = 1;
          askAgain();
        } else if (!hasFreeSquare(tic_tac_toe.board)) {
          drawHelpFunct(&tic_tac_toe);
          play_again = 1;
          askAgain();
        } else {
          makeMove(tic_tac_toe.user[0].name);
        }
      }
    }
  } else if (play_again) {
    if (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N') {
      askAgain();
    } else {
      if (answer == 'n' || answer == 'N') {
        monitor_write("\n\n\nNumber of games played: ");
        monitor_write_dec(tic_tac_toe.totalGamesPlayed);
        monitor_write("\nNumber of wins for ");
        monitor_write(tic_tac_toe.user[0].name);
        monitor_write(": ");
        monitor_write_dec(tic_tac_toe.user[0].numbereOfWins);
        monitor_write("\nNumber of wins for ");
        monitor_write(tic_tac_toe.user[1].name);
        monitor_write(": ");
        monitor_write_dec(tic_tac_toe.user[1].numbereOfWins);
        monitor_write("\nNumber of draws: ");
        monitor_write_dec(tic_tac_toe.totalDraws);
        monitor_write("\n");
        // TODO: IMPLEMENT SHUTTING DOWN
        turnOffAll();
      } else {
        setGame(&tic_tac_toe);
        monitor_clear();
        tic_tac_toe.winner = DRAW;
        makeMove(tic_tac_toe.user[0].name);
      }
    }
  }
}
