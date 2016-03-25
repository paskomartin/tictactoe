#include <conio/conio2.h> /* console i/o */
#include <time.h>         /* time */
#include <stdlib.h>       /* srand, exit */
#include <string.h>       /* malloc, free */
#include <stdio.h>        /* fprintf */

#include "game.h"
#include "gamecons.h"
#include "gamedef.h"
#include "random.h"
#include "board.h"
#include "input.h"
#include "draw.h"
#include "timer.h"

/* ================== Auxiliary functions ======================== */

/* showing main menu
 * returns MenuStatus depends on user choice */
inline static MenuStatus showMenu(void)
{
  MenuStatus menuStatus = MENU_RUN_GAME;
  int character = 0;

  while (menuStatus == MENU_RUN_GAME)
  {
    drawMenu();
    character = getch();

    switch( character )
    {
      case 'q':
      case 'Q':
      {
        menuStatus = MENU_QUIT;
        break;
      }

      case '1':
      {
        menuStatus = MENU_PLAYER_VS_COMPUTER;
        break;
      }

      case '2':
      {
        menuStatus = MENU_PLAYER_VS_PLAYER;
        break;
      }

      case '3':
      {
        menuStatus = MENU_COMPUTER_VS_COMPUTER;
        break;
      }
    }
  }

  return menuStatus;
}

/* initialize player1 and player2 depends on menuStatus */
inline static void preparePlayer(MenuStatus *status, Player *player1, Player *player2)
{
  int randomNum = random(0, 2);

  switch(*status)
  {
    case MENU_PLAYER_VS_PLAYER:
    {
      if (randomNum == 0)
      {
        player1->character = 'O';
        player1->type = PL_PLAYER1;

        player2->character = 'X';
        player2->type = PL_PLAYER2;
      }
      else
      {
        player1->character = 'X';
        player1->type = PL_PLAYER1;

        player2->character = 'O';
        player2->type = PL_PLAYER2;
      }
      break;
    }

    case MENU_PLAYER_VS_COMPUTER:
    {
      if (randomNum == 0)
      {
        player1->character = 'O';
        player1->type = PL_PLAYER1;

        player2->character = 'X';
        player2->type = PL_COMPUTER1;
      }
      else
      {
        player1->character = 'X';
        player1->type = PL_PLAYER1;

        player2->character = 'O';
        player2->type = PL_COMPUTER1;
      }
      break;
    }

    case MENU_COMPUTER_VS_COMPUTER:
    {
      if (randomNum == 0)
      {
        player1->character = 'O';
        player1->type = PL_COMPUTER1;

        player2->character = 'X';
        player2->type = PL_COMPUTER2;
      }
      else
      {
        player1->character = 'X';
        player1->type = PL_COMPUTER1;

        player2->character = 'O';
        player2->type = PL_COMPUTER2;
      }
      break;
    }
    default:
    {
      *status = MENU_ERROR;
      return;
      /* break; */
    }
  }
  *status = MENU_RUN_GAME;
}

/* checks is win situation for players */
inline static void isWin(const int currentChar, const int otherChar, const int currentCount, const int otherCount, GameStatus *status)
{
  if (currentCount == 3)
  {
    if (currentChar == 'X')
    {
      *status = GS_X_WIN;
    }
    else if (currentChar == 'O')
    {
      *status = GS_O_WIN;
    }
  }
  else if (otherCount == 3)
  {
    if (otherChar == 'X')
    {
      *status = GS_X_WIN;
    }
    else if (otherChar == 'O')
    {
      *status = GS_O_WIN;
    }
  }
}


inline static void checkRules(Player *currentPlayer, Player *otherPlayer, int *board, GameStatus *status)
{
  int currentChar = currentPlayer->character;
  int otherChar = otherPlayer->character;
  int currentCount = 0;
  int otherCount = 0;

  int verticalCounter = 0;
  int internalLoopCounter = 0;

  int character = 0;
  int i;

  /* --- check win --- */

  /* check horizontal lines */
  /* BOARD_SIZE + 1 becuase is easier to test win situation */
  for (i = 0; i < BOARD_SIZE + 1; ++i)
  {
    /* check win */
    if ( (i != 0) && (i % 3 == 0) )
    {
      isWin(currentChar, otherChar, currentCount, otherCount, status);

      if (*status == GS_X_WIN || *status == GS_O_WIN)
      {
        return; /* yes, is win situation */
      }
      else /* no, reset counters */
      {
        currentCount = otherCount = 0;
      }
    }

    /* prevent array out of range */
    if (i == BOARD_SIZE)
    {
      break;
    }

    character = board[i];
    if (character == currentChar)
    {
      ++currentCount;
    }
    else if (character == otherChar)
    {
      ++otherCount;
    }
  }



  /* check vertical lines */
  for (i = 0 ; i < BOARD_SIZE; i += 3)
  {
    character = board[i];
    if (character == currentChar)
    {
      ++currentCount;
    }
    else if (character == otherChar)
    {
      ++otherCount;
    }

    ++verticalCounter;

    /* check fill */
    if ( ( verticalCounter != 0 )&& (verticalCounter % 3 == 0) )
    {
      isWin(currentChar, otherChar, currentCount, otherCount, status);

      if (*status == GS_X_WIN || *status == GS_O_WIN)
      {
        return; /* yes, is win situation */
      }
      else /* no, reset counters */
      {
        currentCount = otherCount = 0;
      }
      ++internalLoopCounter;

      if (internalLoopCounter == 3)
      {
        break;
      }
      i -= 8;
    }
  }



  /* check diagonal line
   *   #      index = 0
   *    #     index = 4
   *     #    index = 8
   */
  for (i = 0; i < BOARD_SIZE; i += 4)
  {
    character = board[i];
    if (character == currentChar)
    {
      ++currentCount;
    }
    else if (character == otherChar)
    {
      ++otherCount;
    }
  }

  /* check win situation */
  isWin(currentChar, otherChar, currentCount, otherCount, status);
  if (*status == GS_X_WIN || *status == GS_O_WIN)
  {
    return; /* yes, is win situation */
  }
  else /* no, reset counters */
  {
    currentCount = otherCount = 0;
  }


  /* check diagonal line
   *     #  index = 2
   *    #   index = 4
   *   #    index = 6
   */
  for (i = 2; i < BOARD_SIZE - 2; i += 2)
  {
    character = board[i];
    if (character == currentChar)
    {
      ++currentCount;
    }
    else if (character == otherChar)
    {
      ++otherCount;
    }
  }

  /* check win situation */
  isWin(currentChar, otherChar, currentCount, otherCount, status);
  if (*status == GS_X_WIN || *status == GS_O_WIN)
  {
    return; /* yes, is win situation */
  }
  else /* no, reset counters */
  {
    currentCount = otherCount = 0;
  }

  /* -- there weren't win situation, so check is it a draw situation */
  if ( isBoardFull(board) == 1 )
  {
    *status = GS_DRAW;
  }
}


/* swap players */
inline static void swapPlayers(Player **player1, Player **player2)
{
  Player *tmp = *player1;
  *player1 = *player2;
  *player2 = tmp;
}


inline static GameStatus playGame(Player *player1, Player *player2)
{
  GameStatus status = GS_RUN;
  int randomNum = random(0, 2);
  Player *currentPlayer = NULL;
  Player *otherPlayer = NULL;
  int board[BOARD_SIZE] = { '7', '8', '9', '4', '5', '6', '1', '2', '3' };

  if (!randomNum)
  {
    currentPlayer = player1;
    otherPlayer = player2;
  }
  else
  {
    currentPlayer = player2;
    otherPlayer = player1;
  }

  /* ****************************** */

  draw(board, currentPlayer, &status);

  /* main loop */
  while(status == GS_RUN)
  {
    /* check player / computer input */
    input(currentPlayer, board, &status);
    /* is end of game? draw? */
    checkRules(currentPlayer, otherPlayer, board, &status);
    swapPlayers(&currentPlayer, &otherPlayer);
    draw(board, currentPlayer, &status);

    if (currentPlayer->type == PL_COMPUTER1 || currentPlayer->type == PL_COMPUTER2)
    {
      waitFor(COMPUTER_SPEED);
    }
  }

  status = GS_END_GAME;
  return status;
}



/* =============================================================== */
int gameRun(void)
{
  MenuStatus menuStatus = MENU_IDLE;
  GameStatus gameStatus = GS_IDLE;
  Player *player1 = NULL;
  Player *player2 = NULL;

  player1 = (Player*)malloc( sizeof(Player) );
  player2 = (Player*)malloc( sizeof(Player) );

  if (player1 == NULL || player2 == NULL)
  {
    fprintf(stderr, "%s\n", "Can't allocate memory for struct Player.");
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));

  while(gameStatus != GS_QUIT)
  {
    menuStatus = showMenu();
    if (menuStatus == MENU_QUIT)
    {
      break;
    }

    gameStatus = GS_RUN;
    while (gameStatus == GS_RUN)
    {
      //preparePlayer(&status, &player1, &player2);
      //gameStatus = playGame(&player1, &player2);

      preparePlayer(&menuStatus, player1, player2);
      gameStatus = playGame(player1, player2);

      /* once again? */
      if (gameStatus == GS_END_GAME)
      {
        drawOnceAgain();
        gameStatus = inputOnceAgain();
      }
    }

    if (gameStatus == GS_END_GAME)
      gameStatus = GS_RUN;
  }

  free( (void*) player1 );
  free( (void*) player2 );


  return 0;
}


// https://en.wikipedia.org/wiki/Category:Unix_file_system_technology

