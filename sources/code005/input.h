#ifndef INPUT_H
#define INPUT_H

#include "gamedef.h"

void input(const Player *player, int *board, GameStatus *status);

GameStatus inputOnceAgain(void);

#endif // INPUT_H
