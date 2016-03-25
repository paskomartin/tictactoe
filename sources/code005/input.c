#include <ctype.h>
#include <conio/conio2.h>
#include "input.h"
#include "board.h"
#include "gamecons.h"
#include "gamedef.h"
#include "random.h"
#include "ai.h"

/* ================== Auxiliary functions ======================== */


inline static void playerInput(const Player *player, int *board, GameStatus *status)
{
  int character;

  if (isBoardFull(board))
  {
    *status = GS_NO_MOVES;
    return;
  }

  /* get player input */
  for(;;)
  {
    int index = 0;

    character = getch();
    if (!isdigit(character) || character == '0')
    {
      continue;
    }

    /* mapped input key for array index */
    switch(character)
    {
      case '7': index = 0; break;
      case '8': index = 1; break;
      case '9': index = 2; break;
      case '4': index = 3; break;
      case '5': index = 4; break;
      case '6': index = 5; break;
      case '1': index = 6; break;
      case '2': index = 7; break;
      case '3': index = 8; break;
    }


    if (isEmptySpace(board, index))
    {

      board[index] = player->character;
      break;
    }
  }
}


inline static void computerInput(const Player *player, int *board, GameStatus *status)
{
  /* ---- find where put character ----
   *
   * first check is board empty
   */
  if (isBoardFull(board))
  {
    *status = GS_NO_MOVES;
    return;
  }

  makeComputerMove(board, player->character);
}

/* =============================================================== */


void input(const Player *player, int *board, GameStatus *status)
{
  if (player->type == PL_PLAYER1 || player->type == PL_PLAYER2)
  {
    playerInput(player, board, status);
  }
  else if (player->type == PL_COMPUTER1 || player->type == PL_COMPUTER2)
  {
    computerInput(player, board, status);
  }
}


GameStatus inputOnceAgain(void)
{
  int character;
  GameStatus status = GS_IDLE;

  while(status == GS_IDLE)
  {
    character = getch();
    if(character == 'y' || character == 'Y')
    {
      status = GS_RUN;
    }
    else if (character == 'n' || character == 'N')
    {
      status = GS_END_GAME;
    }
    else if (character == 'q' || character == 'Q')
    {
      status = GS_QUIT;
    }
  }

  return status;
}


