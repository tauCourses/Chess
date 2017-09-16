
#ifndef CHESS_GAMETESTS_H
#define CHESS_GAMETESTS_H
#include "GameManager.h"
#include "ConsoleManager.h"

int runLegalMovesTests();

void runMoveTests();

void runArrayListTests();

void rungenericArrayListTests();

void runGamePlayTests();

void runUndoTest();


void runCompareLocationTest();

void runGetMovesStatesTest();

void runShitPointersTest();

void removePawns(GameManager* game);



#endif //CHESS_GAMETESTS_H
