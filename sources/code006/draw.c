/* Notice: here is path to my conio2.h which is in conio folder
 * so here it's full path declared.
 * If you use Borland Turbo C++ you probably must change this on:
 * #include <conio.h>
 */
#include <conio/conio2.h>
#include <ctype.h>
#include "draw.h"


void drawMenu(void)
{
  clrscr();

  textcolor(YELLOW);
  textbackground(BLUE);
  cprintf("%s", "***************************\n");
  cprintf("%s", "*      Tic Tac Toe!       *\n");
  cprintf("%s", "***************************\n");

  cprintf("%s", "***************************\n");
  cprintf("%s", "* 1. Player vs Computer   *\n");
  cprintf("%s", "* 2. Player vs Player     *\n");
  cprintf("%s", "* 3. Computer vs Computer *\n");
  cprintf("%s", "***************************\n");
  cprintf("%s", "* Q. Quit                 *\n");
  cprintf("%s", "***************************\n");
  textcolor(WHITE);
  textbackground(BLACK);
}


void drawOnceAgain(void)
{
  textcolor(WHITE);
  cprintf("%s", "\nDo you want play again? ");
  textcolor(LIGHTGREEN);
  cprintf("%s", "(y/n)\n");
  textcolor(LIGHTRED);
  cprintf("%s", "(q) - quit\n");
  textcolor(WHITE);
}


inline static void printCharacterOnBoard(int character)
{
  textbackground(BLACK);
  if ( isdigit(character) )
  {
    textcolor(DARKGRAY);
  }
  else
  {
    textcolor(WHITE);
  }
  cprintf(" %c ", character);
}


inline static void drawBoard(const int *board)
{
  textbackground(BLUE);
  textcolor(YELLOW);
  //gotoxy(30, 1);
  cprintf("%s", "Tic Tac Toe!\n");
  cprintf("%s", "************\n\n");

  textcolor(WHITE);
  textbackground(BLACK);

  printCharacterOnBoard(board[0]);
  textcolor(WHITE);
  cprintf("%s", "|");
  printCharacterOnBoard(board[1]);
  textcolor(WHITE);
  cprintf("%s", "|");
  printCharacterOnBoard(board[2]);
  textcolor(WHITE);
  cprintf("%s", "\n");
  cprintf("%s", "-----------\n");

  printCharacterOnBoard(board[3]);
  textcolor(WHITE);
  cprintf("%s", "|");
  printCharacterOnBoard(board[4]);
  textcolor(WHITE);
  cprintf("%s", "|");
  printCharacterOnBoard(board[5]);
  textcolor(WHITE);
  cprintf("%s", "\n");
  cprintf("%s", "-----------\n");

  printCharacterOnBoard(board[6]);
  textcolor(WHITE);
  cprintf("%s", "|");
  printCharacterOnBoard(board[7]);
  textcolor(WHITE);
  cprintf("%s", "|");
  printCharacterOnBoard(board[8]);
  textcolor(WHITE);
  cprintf("%s", "\n");
}


inline static void drawCurrentPlayer(const Player *currentPlayer)
{
  textcolor(LIGHTCYAN);
  textbackground(BLUE);
  cprintf("%s", "\n\nCurrent player ");// --->");
  textcolor(YELLOW);
  if(currentPlayer->type == PL_COMPUTER1)
  {
    cprintf("%s", "COMPUTER 1");
  }
  else if (currentPlayer->type == PL_COMPUTER2)
  {
    cprintf("%s", "COMPUTER 2");
  }
  else if (currentPlayer->type == PL_PLAYER1)
  {
    cprintf("%s", "PLAYER 1");
  }
  else if (currentPlayer->type == PL_PLAYER2)
  {
    cprintf("%s", "PLAYER 2");
  }

  textcolor(LIGHTCYAN);
  cprintf("%s", " --->");

  textbackground(BLACK);
  textcolor(LIGHTGREEN);
  cprintf(" %c\n", currentPlayer->character);
  textbackground(BLACK);
  textcolor(WHITE);
}


inline static void drawGameStatus(const GameStatus *status)
{
  if (*status == GS_DRAW)
  {
    textcolor(LIGHTGREEN);
    cprintf("%s", "     ###    ###    ###    #       #   #\n");
    cprintf("%s", "     #  #   #  #  #   #   #       #   #\n");
    cprintf("%s", "     #  #   #  #  #   #   #   #   #   #\n");
    cprintf("%s", "     #  #   ###   #####   #   #   #   #\n");
    cprintf("%s", "     #  #   # #   #   #    #  #  #     \n");
    cprintf("%s", "     ###    #  #  #   #     ## ##     #\n");
    textcolor(WHITE);
  }
  else if (*status == GS_X_WIN)
  {
    textcolor(LIGHTRED);
    cprintf("%s", "     X   X      #       #  #  #    #  #\n");
    cprintf("%s", "      X X       #       #  #  ##   #  #\n");
    cprintf("%s", "       X        #       #  #  # #  #  #\n");
    cprintf("%s", "       X        #   #   #  #  #  # #  #\n");
    cprintf("%s", "      X X        #  #  #   #  #   ##   \n");
    cprintf("%s", "     X   X        ## ##    #  #    #  #\n");
    textcolor(WHITE);
  }
  else if (*status == GS_O_WIN)
  {
    textcolor(LIGHTCYAN);
    cprintf("%s", "      OOO       #       #  #  #    #  #\n");
    cprintf("%s", "     O   O      #       #  #  ##   #  #\n");
    cprintf("%s", "    O     O     #       #  #  # #  #  #\n");
    cprintf("%s", "    O     O     #   #   #  #  #  # #  #\n");
    cprintf("%s", "     O   O       #  #  #   #  #   ##   \n");
    cprintf("%s", "      OOO         ## ##    #  #    #  #\n");
    textcolor(WHITE);
  }
}


void draw(const int *board, const Player *currentPlayer, const GameStatus *status)
{
  clrscr();
  drawBoard(board);
  drawCurrentPlayer(currentPlayer);
  drawGameStatus(status);
}
