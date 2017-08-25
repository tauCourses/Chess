
#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include <stdbool.h>
#include <stdlib.h>
#include <rpcndr.h>
#include "SPArrayList.h"
#include "math.h"
#define historySize 3;
#define EMPTY_PIECE '_';

typedef struct Location{
    int x,y;
} Location;

typedef struct Piece{
    char type;
    boolean color;
    Location location;
} Piece;


typedef struct Game{
    char** board;
    int mode;
    int difficulty;
    char userColor;
    SPArrayList *history;
} Game;

Game* createNewGame(int mode, int difficulty, char userColor);

#endif //CHESS_GAME_H
