#ifndef CHESS_HISTORY_H
#define CHESS_HISTORY_H

#include "GameState.h"

/**
 * History summary:
 * a module that handle the history of moves of the game for undo move feature.
 */

typedef struct{
    GameMove** movesList;
    int numberOfMovesStored;
    int maxNumberOfMoves;
} GameHistory;

/**
 *  create a new empty History.
 *  @param maxNumberOfMoves - number of maximum moves that can be undone.
 *  @return the new History
 */
GameHistory* createHistory(int maxNumberOfMoves);
/**
 *  destroy History.
 *  @param history - the history to destroy.
 *  @return void
 */
void destroyHistory(GameHistory* history);

/**
 *  return the latest move that was entered to history.
 *  @param history - the current history.
 *  @return the latest move
 */
GameMove* popFromHistory(GameHistory* history);
/**
 *  return the oldest move that was entered to history.
 *  @param history - the current history.
 *  @return the oldest move
 */
GameMove* seekFirstHistory(GameHistory* history);
/**
 *  add a move to the current history
 *  @param history - the current history.
 *  move - the move to enter
 *  @return void
 */
void pushToHistory(GameHistory* history, GameMove* move);

#endif //CHESS_HISTORY_H
