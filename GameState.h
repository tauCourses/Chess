#ifndef CHESS_STATE_H
#define CHESS_STATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "GameBoard.h"

/**
 * GameState summary:
 * contain all the function and structs for handling a game state
 * - the parameters of the game that changes during game play.
 */

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

typedef enum {
    IS_LEGAL_VALID, IS_LEGAL_INVALID_POSITION, IS_LEGAL_NOT_USER_PIECE, IS_LEGAL_INVALID_DUE_TO_CHESS_RULES
} GAME_IS_LEGAL_MESSAGE;

typedef enum {
    IS_KING_THREATENED_TRUE, IS_KING_THREATENED_FALSE, IS_KING_THREATENED_MALLOC_ERROR
} IS_KING_THREATENED;

/**
 *  create a new empty game state.
 *  @param none.
 *  @return the new game state
 */
GameState* createEmptyGameState();
/**
 *  reset a game state to initial parameters.
 *  @param state - state to reset.
 *  @return void
 */
void setInitialGameState(GameState* state);
/**
 *  create a new duplicated game state.
 *  @param state - state to duplicated.
 *  @return the new game state
 */
GameState* duplicateGameState(GameState* state);
/**
 *  destroys game state.
 *  @param state - the state to destroy.
 *  @return void
 */
void destroyGameState(GameState* state);

/**
 *  destroys move.
 *  @param move - the move to destroy.
 *  @return void
 */
void destroyMove(GameMove* move);
/**
 *  create a new castle state
 *  @param hasKingMoved boolean, hasLeftRookMoved boolean, hasRightRookMoved boolean.
 *  @return the new castle state.
 */
castleState* createCastleState(bool hasKingMoved,bool hasLeftRookMoved, bool hasRightRookMoved);
/**
 *  create a new duplicated castle state
 *  @param castle - castle state to duplicate
 *  @return the new duplicated castle state.
 */
castleState* duplicateCastleState(castleState* castle);
/**
 *  destroys castle state
 *  @param castle - castle state to destroy
 *  @return void
 */
void destroyCastleState(castleState* castle);

/**
 *  check if move is legal in current state
 *  @param state - current state
 *  org - original location of move
 *  des - destination location of move
 *  @return message if move is legal, and the reason why not otherwise.
 */
GAME_IS_LEGAL_MESSAGE isMoveLegal(GameState* state, Location* org, Location* des);

/**
 *  check if castle move is legal in current state
 *  @param state - current state
 *  org - original location of move
 *  des - destination location of move
 *  @return true if move is legal, false otherwise.
 */
bool checkCastleMove(GameState* state, Location* org, Location* des);

/**
 *  apply given move to the current game state, in case it is legal.
 *  @param state - current state
 *  org - original location of move
 *  des - destination location of move
 *  @return move that have been done.
 */
GameMove* applyMove(GameState* state, Location* org, Location* des);
/**
 *  apply undo for castle move.
 *  @param state - current state
 *  move - move to be undone
 *  @return void.
 */
void applyCastleUndo(GameState *state, GameMove *move);
/**
 *  apply undo move.
 *  @param state - current state
 *  move - move to be undone
 *  @return void.
 */
void applyUndoMove(GameState *state, GameMove *move);

/**
 *  get all available legal moves from location
 *  @param state - current state
 *  origin - location of origin piece
 *  @return array of possible legal locations.
 */
Location** getAllAvailableMovesFromLocation(GameState* state,Location* origin);

/**
 *  check if king is threatened
 *  @param state - current state
 *  @return message if king is threatened, not or error has occurred.
 */
IS_KING_THREATENED isKingThreatened(GameState* state);
/**
 *  finds king location
 *  @param state - current state
 *  kingColor - the color of the king we want find
 *  @return location of the king.
 */
Location* findKingLocation(GameState* state, PLAYER_COLOR kingColor);
/**
 *  check if location could be threatened
 *  @param state - current state
 *  loc - location to check
 *  byPlayer - color of the current player enemy
 *  @return true if location could be threatened, false otherwise.
 */
bool isThreatened(GameState *state, Location *loc, PLAYER_COLOR byPlayer);
/**
 *  check if location is really currently threatened
 *  @param state - current state
 *  loc - location to check
 *  byPlayer - color of the current player enemy
 *  @return true if location is threatened, false otherwise.
 */
bool isREALLYThreatened(GameState *state, Location *loc);





#endif //CHESS_STATE_H
