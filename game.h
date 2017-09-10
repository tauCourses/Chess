
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "SPArrayList.h"
#include "genericArrayList.h"
#include "math.h"
#include "Infrastructure.h"
#include "gameAux.h"
#include "console.h"

Game* createNewGame(int mode, int difficulty, bool userColor);

void destroyGame(Game* game);

bool isMoveLegal(Game* game, Location* org, Location* des, bool currentPlayerColor);

bool isLegalDesPiece(char** board, char orgPiece, char desPiece, bool currentPlayerColor);

bool isWhitePawnMoveLegal(char** board, Location* org, Location* des);

bool isBlackPawnMoveLegal(char** board, Location* org, Location* des);

bool isRookMoveLegal(char** board, Location* org, Location* des);

bool isKnightMoveLegal(Location* org, Location* des);

bool isBishopMoveLegal(char** board, Location* org, Location* des);

bool isKingMoveLegal(char** board, Location* org, Location* des);

bool isQueenMoveLegal(char** board, Location* org, Location* des);

bool isKingThreatened(Game* game, bool currentPlayerColor);

bool wouldKingBeThreatened(Game* game, Location* org, Location* des, bool currentPlayerColor);

bool isBishopLegalDirection(char** board, Location* org, Location* des, int (*addOrSubX)(int,int), int (*addOrSubY)(int,int));

bool movePiece(Game* game, Location* org, Location* des, bool currentPlayerColor);

bool isCheckmateOrTie(Game* game, bool currentPlayerColor);

genericArrayList* getMoves(Game* game,Location* currentLoc,bool currentUserColor);

genericArrayList* getMovesStates(Game* game,Location* currentLoc,bool currentUserColor);

bool undoMove(Game* game);

#endif //CHESS_GAME_H
