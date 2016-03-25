#include <ctype.h>
#include "ai.h"
#include "gamecons.h"
#include "random.h"

/* ================== Auxiliary functions ======================== */

/* return index if is possible to win for horizontal line
 * or return -1 if isn't posible */
inline static int checkHorizontalLines(int *board, int character)
{
  int filledCounter = 0;  /* how many fields are filled with character */
  int i;				  /* loop counter */
  int index = 0;		  /* index or -1 */

  /* check horizontal lines */
  for(i = 0; i < BOARD_SIZE; ++i)
  {
    /* check whether we found almost filled line */
    if (i != 0 && (i % 3 == 0) )
    {
      if(filledCounter == 2)
      {
        if (isdigit(board[index]))
        {
          return index;
        }
        index = filledCounter = 0;
      }
      else
      {
        index = filledCounter = 0;
      }
    }


    if(board[i] == character)
    {
      ++filledCounter;
    }
    else //if ( isdigit( board[i] ) )
    {
      index = i;
    }
  }

  /* check last */
  if(filledCounter == 2)
  {
    if (isdigit(board[index]))
    {
      return index;
    }
  }

  return -1;
}

/* return index if is possible to win for vertical line
 * or return -1 if isn't posible */
inline static int checkVerticalLines(int *board, int character)
{
  int filledCounter = 0;          /* how many characters are in
                                   * vertical line */
  int i;                          /* loop countee */
  int index = 0;                  /* array index */
  int internalLoopCounter = 0;    /* loop sentinel */
  int verticalLoopCounter = 0;    /* needs to indicate that
                                   * algorithm must check  if
                                   * vertical line is filled */


  /* check vertical lines */
  for (i = 0 ; i < BOARD_SIZE; i += 3)
  {
    if (board[i] == character)
    {
      ++filledCounter;
    }
    else //if ( isdigit( board[i] ) )
    {
      index = i;
    }

    ++verticalLoopCounter;

    /* check fill */
    if ( ( verticalLoopCounter != 0 )&& (verticalLoopCounter % 3 == 0) )
    {
      if(filledCounter == 2)
      {
        if (isdigit(board[index]))
        {
          return index;
        }
        index = filledCounter = 0;
      }
      else
      {
        index = filledCounter = 0;
        i -= 8;
      }
      ++internalLoopCounter;

      if (internalLoopCounter == 3)
      {
        break;
      }
    }
  }

  return -1;
}

/* return index if is possible to win for diagonal line
 * or return -1 if isn't posible */
inline static int checkDiagonalLines(int *board, int character)
{
  int filledCounter = 0;
  int i;
  int index = 0;

  /* check diagonal line
   *   #      index = 0
   *    #     index = 4
   *     #    index = 8
   */
  for(i = 0; i < BOARD_SIZE; i += 4)
  {
    if(board[i] == character )
    {
      ++filledCounter;
    }
    else //if ( isdigit(board[i]) )
    {
      index = i;
    }
  }

  /* check move */
  if(filledCounter == 2)
  {
    if (isdigit(board[index]))
    {
      return index;
    }
  }

  index = filledCounter = 0;

  /* check diagonal line
   *     #  index = 2
   *    #   index = 4
   *   #    index = 6
   */
  for (i = 2; i < BOARD_SIZE - 2; i += 2)
  {
    if(board[i] == character )
    {
      ++filledCounter;
    }
    else
    {
      index = i;
    }
  }

  /* check move */
  if(filledCounter == 2)
  {
    if (isdigit(board[index]))
    {
      return index;
    }
  }

  index = -1;
  return index;
}


/* return index of empty space in board if is possible to win
 * or return -1 when is not possible to win */
inline static int isPossibleToWin(int *board, int character)
{
  int result = -1;

  result = checkHorizontalLines(board, character);
  if (result > -1)
  {
    return result;
  }

  result = checkVerticalLines(board, character);
  if (result > -1)
  {
    return result;
  }

  result = checkDiagonalLines(board, character);
  return result;

}


/* =============================================================== */

/* checks if computer can win. Return index if computer can win
 * or return -1 if cannot
 */
inline static int isComputerWin(int *board, int character)
{
  int index;
  index = isPossibleToWin(board, character);
  return index;
}

/* checks if opponent can win. Return index if opponent can win
 * or return -1 if cannot
 */
inline static int isOpponentWin(int *board, int character)
{
  int secondCharacter;
  int index = -1;
  /* no - check whether opponent can win, but first
   * check the opponent character. */
  if (character == 'X')
  {
    secondCharacter = 'O';
  }
  else
  {
    secondCharacter = 'X';
  }


  /* check if opponent could win in next round */
  index = isPossibleToWin(board, secondCharacter);

  /* yes - so block this move */
  if (index != -1)
  {
    board[index] = character;
    return index;
  }
  return index;
}

/* trying making move. If is not possible to make move just
 * return -1. If computer made move, return index
 */
inline static int tryMakeMove(int *board, int character)
{
  int possibilities[BOARD_SIZE] = { -1 };
  int counter = 0;
  int index = -1;

  /* no - check if is space to put character */
  for (index = 0; index < BOARD_SIZE; ++index)
  {
    if (isdigit(board[index] ))
    {
      possibilities[counter] = index;
      ++counter;
    }
  }

  /* if there no space to make move, that means is draw situation - leave function */
  if (!counter)
  {
    return -1;
  }


  /* is space on board, check if middle is available */
  if (isdigit(board[4]))
  {
    /* random decision - sometimes put character on the middle
     * and sometimes don't put it
     */
    int r = random(0, 1024);
    r = r % 2;

    if (r == 1)
    {
      /* yes - just put character */
      board[4] = character;
      return 4;
    }

  }

  /* no - just get a random index from possibilities */
  index = 4;
  while (index == 4)
  {
    index = random(0, counter);
  }
  /* get proper index to board array */
  index = possibilities[index];
  board[index] = character;
  return index;
}


/* =============================================================== */

/* new refactored function */
void makeComputerMove(int *board, int character)
{
    int index = -1;

  index = isComputerWin(board, character);
  if (index > -1)
  {
    board[index] = character;
    return;
  }

  index = isOpponentWin(board, character);
  if (index > -1)
  {
    board[index] = character;
    return;
  }

  /* function return -1 if isn't possible to make move
   * you can react on this, but here is a last function
   * so it's just leave the makeComputerMove function.
   */
  tryMakeMove(board, character);
}
