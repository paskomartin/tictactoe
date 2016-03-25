#ifndef DRAW_H
#define DRAW_H

#include "gamedef.h"

/* draw menu */
void drawMenu(void);

/* draws question - Do you want to play once again? */
void drawOnceAgain(void);

/* draws game board and some information about game */
void draw(const int *board, const Player *currentPlayer, const GameStatus *status);

#endif // DRAW_H
