#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <limits.h>
#include "GameManager.h"

/**
 * AI summary:
 * Responsable for all the minmax algorithem.
 * Includes the scoring function, node creation and move making.
 */

#define END_GAME_SCORE 1000 //score set for prefering game ending moves. could be any high value int.


typedef enum {
    MAX_NODE_TYPE, MIN_NODE_TYPE
} MIN_MAX_NODE_TYPE;

//struct that is used for messages
typedef enum {
    GET_SCORE_SUCCEED, GET_SCORE_FAILED
} GET_SCORE_RESULT;

typedef struct {
    MIN_MAX_NODE_TYPE type;
    Location* des;
    Location* origin;
    GameState* state;
    int score;
    int depth;
    int maxDepth;
    char pawnPromotion;
} MinMaxNode;

typedef struct _nodeChain nodeChain;

struct _nodeChain {
    MinMaxNode* node;
    nodeChain* next;
};

/**
 *  Destroys entire chain. not just the current node.
 *  @param chain - the chain that needed to be destroyed.
 *  @return void
 */
void destroyChain(nodeChain* chain); //destory all the chain, not just the current node
/**
 *  Make a move by the computer. the move is done and applied in the game that
 *  is given as a parameter.
 *  @param game - the game upon the move is done.
 *  @return
 *  A description of the move that was done by the AI
 */
GameMove* applyAIMove(GameManager* game);

/**
 *  gets the best possible node according to current state of the game.
 *  @param state - the game current state.
 *  type - the type of node which is needed to be reached, max or min.
 *  maxDepth - the maximum depth the search should be done to.
 *  @return
 *  The best node possible for given game state.
 */
MinMaxNode* getBestNode(GameState* state, MIN_MAX_NODE_TYPE type, int maxDepth);

/**
 *  gets the best possible node inside a chain.
 *  @param nodesChain - the chain of nodes.
 *  type - the type of node which is needed to be reached, max or min.
 *  @return
 *  The best node in chain.
 */
MinMaxNode* findBestNode(nodeChain* nodesChain, MIN_MAX_NODE_TYPE type);

/**
 *  Updates a chain with another move.
 *  @param nodesChain - the chain of nodes.
 *  node - new node for the move.
 *  origin - Location of origin piece to move.
 *  dest - Location of destenation of move.
 *  @return
 *  updated chain.
 */
nodeChain* updateChainByRegularMove(MinMaxNode* node, nodeChain *chain, Location *origin, Location *dest);


/**
 *  Updates a chain with a list of moves from a origin location.
 *  @param nodesChain - the chain of nodes.
 *  node - new node for the move.
 *  origin - Location of origin piece to move.
 *  dests - List of location of possible destenations of moves.
 *  @return
 *  updated chain.
 */
nodeChain* updateChainByDests(MinMaxNode* node, nodeChain *chain, Location *origin, Location **dests);

/**
 *  Gets a chain of all the minMax nodes
 *  @param
 *  node - the node from where to get the chain of nodes.
 *  @return
 *  new chain from node.
 */
nodeChain* getAllMinMaxNodes(MinMaxNode* node);


/**
 *  Checks if a new score is better than an old one.
 *  @param oldScore - the old score.
 *  newScore - the new score.
 *  type - the type of node to check score for, min or max.
 *  @return
 *  true if new score is better, false otherwise.
 */
bool isBetterScore(int oldScore, int newScore, MIN_MAX_NODE_TYPE type);

/**
 *  Returns the worst score for a given type of node min or max.
 *  @param type - the type of node score, min or max.
 *  @return
 *  the worst score for given type.
 */
int worstScore(MIN_MAX_NODE_TYPE type);
/**
 *  Returns the oppsite type for given node type.
 *  @param type - the type of node.
 *  @return
 *  oppsite type of given type.
 */
MIN_MAX_NODE_TYPE oppsiteType(MIN_MAX_NODE_TYPE type);


/**
 *  create new minMax node.
 *  @param type - the type of node.
 *  state - current game state.
 *  depth - current depth of the node.
 *  maxDepth - maximum depth that nodes should be created for.
 *  @return
 *  the new node.
 */
MinMaxNode* createMinMaxNode(GameState* state, MIN_MAX_NODE_TYPE type,int depth, int maxDepth);

/**
 *  destroys new minMax node.
 *  @param node - node to be destroyed.
 *  @return
 *  void
 */
void destroyMinMaxNode(MinMaxNode *node);

/**
 *  finds best score in chain.
 *  @param type - the type of current node.
 *  chain - the chain that the best score is returned for.
 *  @return
 *  the best score value in chain.
 */
int findBestScore(nodeChain* chain, MIN_MAX_NODE_TYPE type);

/**
 *  the node score.
 *  @param node - the node for the scording
 *  prunningScore - the prunning score so far.
 *  @return
 *  if the get score was successful or not.
 */
GET_SCORE_RESULT minMaxNodeScore(MinMaxNode* node, int prunningScore);

/**
 *  the board score.
 *  @param board - the board for the score.
 *  @return
 *  the value of score.
 */
int boardScore(Board board);

/**
 *  the piece score.
 *  @param piece - the piece for scoring.
 *  @return
 *  the value of score.
 */
int pieceScore(char piece);

/**
 *  turns a char to lower case.
 *  @param piece - the char to turn to lower case.
 *  @return
 *  lower case version of input piece char.
 */
char toLower(char piece);

/**
 *  turns a char to upper case.
 *  @param piece - the char to turn to upper case.
 *  @return
 *  upper case version of input piece char.
 */
char toUpper(char piece);

#endif //CHESS_AI_H
