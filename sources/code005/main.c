#include <conio/conio2.h>
#include "draw.h"
#include "gamedef.h"
#include "gamecons.h"
#include "board.h"
#include "timer.h"
#include "random.h"

#include "input.h"

int main()
{
  int board[BOARD_SIZE] = { '7', '8', '9', '4', '5', '6', '1', '2', '3' };
  Player player = { PL_COMPUTER2, 'O' };
  GameStatus status = GS_O_WIN;
  int result = 0;
  int i;

  board[0] = 'X';
  /* board[4] = 'X'; */
  board[8] = 'X';
  board[1] = 'O';
  board[3] = 'O';
  board[7] = 'O';

  drawMenu();
  drawOnceAgain();

  input(&player, board, &status);

  draw(board, &player, &status);

  cprintf("%s\n", "random numbers between 10 to 20");
  for (i = 0; i < 60; ++i)
  {
    result = random(10, 21); /* max + 1 */
    cprintf("%i, ", result);
  }

  result = isBoardFull(board);
  if (result == 1)
  {
    cprintf("\n%s", "Board is full");
  }
  else
  {
    cprintf("\n%s", "Board isn't full");
  }

  result = isEmptySpace(board, 6);
  if (result == 1)
  {
    cprintf("\n%s %i", "There is empty space in array index", 6);
  }
  else
  {
    cprintf("\n%s %i", "There isn't empty space in array index", 6);
  }


  getch();
  return 0;
}
