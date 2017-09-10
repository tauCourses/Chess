
#ifndef CHESS_GAMETESTS_H
#define CHESS_GAMETESTS_H
#include "game.h"
#include "console.h"

int runLegalMovesTests();

void runMoveTests();

void runArrayListTests();

void rungenericArrayListTests();

void runGamePlayTests();

void runUndoTest();

void runCompareLocationTest();

void runGetMovesStatesTest();

void runShitPointersTest();

void removePawns(Game* game);


#endif //CHESS_GAMETESTS_H
