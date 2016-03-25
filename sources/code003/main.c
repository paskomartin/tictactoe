#include <conio/conio2.h>
#include "draw.h"
#include "gamedef.h"
#include "gamecons.h"

int main()
{
  int board[BOARD_SIZE] = { '7', '8', '9', '4', '5', '6', '1', '2', '3' };
  Player player = { PL_COMPUTER2, 'X' };
  GameStatus status = GS_X_WIN;

  board[0] = 'X';
  board[4] = 'X';
  board[8] = 'X';
  board[1] = 'O';
  board[3] = 'O';

  drawMenu();
  drawOnceAgain();
  draw(board, &player, &status);

  getch();
  return 0;
}
