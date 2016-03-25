#ifndef AI_H
#define AI_H

#if 0
/* return index of empty space in board if is possible to win
 * or return -1 when is not possible to win */
int isPossibleToWin(int *board, int character);
#endif


/* computer makes move on board,
 * if there isn't possible to put character on board
 * function just return, otherwise computer put character
 * on board
 */
void makeComputerMove(int *board, int character);

#endif // AI_H
