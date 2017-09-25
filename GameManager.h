
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <stdlib.h>
#include <stdbool.h>
#include "GameState.h"
#include "History.h"

/**
 * GameManager summary:
 * contain all the function and structs for handling a game logicly.
 */

#define HISTORY_SIZE 3

typedef enum  {
    ONE_PLAYER_GAME_MODE, TWO_PLAYERS_GAME_MODE
} GAME_MODE;

typedef enum {
    MOVE_VALID, MOVE_PAWN_REACH_END, MOVE_INVALID_POSITION, MOVE_NOT_USER_PIECE, MOVE_INVALID_DUE_TO_CHESS_RULES, MOVE_ERROR
} GAME_MOVE_MESSAGE;

typedef enum {
    VALID_GAME_STATE, GAME_CHECKMATE, GAME_TIE, GAME_ERROR
} GAME_STATE;

typedef enum{
    UNDO_POSSIBLE, UNDO_NO_HISTORY, UNDO_REFUSED, UNDO_SUCCEEDED
}GAME_UNDO_MOVE_MESSAGE;



typedef struct{
    GameState* state;
    GAME_MODE mode;
    int difficulty;
    PLAYER_COLOR userColor;
    GameHistory* history;
} GameManager;

/**
 *  create a new empty game.
 *  @param none.
 *  @return the new game
 */
GameManager* createEmptyGame();
/**
 *  create a new game with game mode for two players.
 *  @param none.
 *  @return the new game
 */
GameManager* createTwoPlayersGame();
/**
 *  create a new game with game mode for one player.
 *  @param difficulty - the difficulty for the game.
 *  userColor - the color for the user.
 *  @return the new game
 */
GameManager* createOnePlayerGame(int difficulty,  PLAYER_COLOR userColor);

/**
 *  destroys the game.
 *  @param game - the game to destroy.
 *  @return void
 */
void destroyGame(GameManager* game);
/**
 *  try to move a piece in the given game.
 *  @param game - the game.
 *  org - original location of piece.
 *  des - destination location.
 *  @return message if move is valid, and if not the reason why
 */
GAME_MOVE_MESSAGE movePiece(GameManager* game, Location* org, Location* des);
/**
 *  get the game state to know if it's over
 *  @param game - the game.
 *  @return message if game is over and why or not
 */
GAME_STATE getGameState(GameManager* game);
/**
 *  can an undo command be done
 *  @param game - the game.
 *  @return message if undo is possible or why not
 */
GAME_UNDO_MOVE_MESSAGE candoundo(GameManager* game); //just kidding, should be canDoUndo or isUndoAvailable
/**
 *  undo one last move
 *  @param game - the game.
 *  @return the move that was undone
 */
GameMove* undoMove(GameManager* game);

#endif //CHESS_GAME_H
