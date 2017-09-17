#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <limits.h>
#include "GameManager.h"


typedef enum {
    MAX_NODE_TYPE, MIN_NODE_TYPE
} MIN_MAX_NODE_TYPE;

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
} MinMaxNode;

typedef struct _nodeChain nodeChain;

struct _nodeChain {
    MinMaxNode* node;
    nodeChain* next;
};

void destroyChain(nodeChain* chain); //destory all the chain, not just the current node

GameMove* applyAIMove(GameManager* game);
MinMaxNode* getBestNode(GameState* state, MIN_MAX_NODE_TYPE type, int maxDepth);
MinMaxNode* findBestNode(nodeChain* nodesChain, MIN_MAX_NODE_TYPE type);

nodeChain* updateChainByDests(MinMaxNode* node, nodeChain *chain, Location *origin, Location **dests);
nodeChain* getAllMinMaxNodes(MinMaxNode* node);

bool isBetterScore(int oldScore, int newScore, MIN_MAX_NODE_TYPE type);
int worstScore(MIN_MAX_NODE_TYPE type);
MIN_MAX_NODE_TYPE oppsiteType(MIN_MAX_NODE_TYPE type);

MinMaxNode* createMinMaxNode(GameState* state, MIN_MAX_NODE_TYPE type,int depth, int maxDepth);
void destroyMinMaxNode(MinMaxNode *node);


int findBestScore(nodeChain* chain, MIN_MAX_NODE_TYPE type);

GET_SCORE_RESULT minMaxNodeScore(MinMaxNode* node, int prunningScore);
int boardScore(Board board);
int pieceScore(char piece);
#endif //CHESS_AI_H
