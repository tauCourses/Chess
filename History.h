#ifndef CHESS_HISTORY_H
#define CHESS_HISTORY_H

#include "GameState.h"

typedef struct{
    GameMove** movesList;
    int numberOfMovesStored;
    int maxNumberOfMoves;
} GameHistory;

GameHistory* createHistory(int maxNumberOfMoves);
void destroyHistory(GameHistory* history);

GameMove* popFromHistory(GameHistory* history);
GameMove* pushToHistory(GameHistory* history, GameMove* move);
#endif //CHESS_HISTORY_H
