#ifndef GAMEDEF_H
#define GAMEDEF_H

typedef enum _PlayerType
{
    PL_PLAYER1,
    PL_PLAYER2,
    PL_COMPUTER1,
    PL_COMPUTER2
} PlayerType;


typedef struct _Player
{
    PlayerType type;
    int character;
} Player;


typedef enum _MenuStatus
{
  MENU_PLAYER_VS_PLAYER,
  MENU_PLAYER_VS_COMPUTER,
  MENU_COMPUTER_VS_COMPUTER,
  MENU_RUN_GAME,
  MENU_IDLE,
  MENU_ERROR,
  MENU_QUIT
} MenuStatus;


typedef enum _GameStatus
{
  GS_MENU,
  GS_RUN,
  GS_NO_MOVES,
  GS_X_WIN,
  GS_O_WIN,
  GS_DRAW,
  GS_IDLE,
  GS_END_GAME,
  GS_QUIT
} GameStatus;

#endif // GAMEDEF_H
