#include <ctype.h>
#include "board.h"
#include "gamecons.h"

/* is empty space in the board ? */
int isEmptySpace(int *board, int index)
{
  int character = board[index];

  if (isdigit(character))
    return 1;
  else
    return 0;
}

/* no more moves? */
int isBoardFull(int *board)
{
  int character;
  int index;

  for (index = 0; index < BOARD_SIZE; ++index)
  {
    character = board[index];
    if (isdigit(character))
      return 0;
  }
  return 1;
}

