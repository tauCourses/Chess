#ifndef CHESS_STATE_H
#define CHESS_STATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "GameBoard.h"

typedef struct {
    bool hasKingMoved;
    bool hasLeftRookMoved;
    bool hasRightRookMoved;
}castleState;

typedef struct{
    Board board;
    PLAYER_COLOR currentPlayer;
    castleState *whiteCastle, *blackCastle;
} GameState;

typedef struct{
    Location *des, *origin;
    char beatedPiece; //the beatedPiece in origin location before move
    bool pawnChanged;
    castleState *whiteCastle, *blackCastle;
}GameMove;

GameState* createEmptyGameState();
void setInitialGameState(GameState* state);
GameState* duplicateGameState(GameState* state);
void destroyGameState(GameState* state);

void destroyMove(GameMove* move);
castleState* createCastleState(bool hasKingMoved,bool hasLeftRookMoved, bool hasRightRookMoved);
castleState* duplicateCastleState(castleState* castle);
void destroyCastleState(castleState* castle);

bool isCastleMove(Location* org, Location* des); //return true if is valid castle move, false if not and unknown result for invalid move!
bool isMoveLegal(GameState* state, Location* org, Location* des);
bool checkCastleMove(GameState* state, Location* org, Location* des);

GameMove* applyMove(GameState* state, Location* org, Location* des);
void applyUndoMove(GameState *state, GameMove *move);

bool isKingThreatened(GameState* state);
Location* findKingLocation(GameState* state, PLAYER_COLOR kingColor);
bool isThreatened(GameState* state, Location* loc, PLAYER_COLOR byPlayer);


#endif //CHESS_STATE_H
