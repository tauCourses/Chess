
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <stdlib.h>
#include <stdbool.h>
#include "GameState.h"

#define historySize 3

typedef enum  {
    ONE_PLAYER_GAME_MODE, TWO_PLAYERS_GAME_MODE
} GAME_MODE;

typedef enum {
    MOVE_VALID, MOVE_PAWN_REACH_END, MOVE_INVALID_POSITION, MOVE_NOT_USER_PIECE, MOVE_INVALID_DUE_TO_CHESS
} GAME_MOVE_MESSAGE;

typedef enum {
    VALID_GAME_STATE, PAWN_REACH_END, GAME_CHECKMATE, GAME_TIE,
} GAME_STATE;

typedef enum{
    UNDO_SUCCEEDED, UNDO_NO_HISTORY, UNDO_REFUSED
}GAME_UNDO_MOVE_MESSAGE;

typedef struct{
    GameState* state;
    GAME_MODE mode;
    int difficulty;
    PLAYER_COLOR userColor;
} GameManager;

GameManager* createEmptyGame();
GameManager* createTwoPlayersGame();
GameManager* createOnePlayerGame(int difficulty,  PLAYER_COLOR userColor);

void destroyGame(GameManager* game);

GAME_MOVE_MESSAGE movePiece(GameManager* game, Location* org, Location* des);

GAME_STATE getGameState(GameManager* game);

Location* getAllAvailableMovesFromLocation(GameManager* game,Location* location);

bool candoundo(GameManager* game); //just kidding, should be canDoUndo or isUndoAvailable
GAME_UNDO_MOVE_MESSAGE undoMove(GameManager* game);

#endif //CHESS_GAME_H
