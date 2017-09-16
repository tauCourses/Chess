#include "AI.h"
#include "GameManager.h"
#include "GameState.h"

GameMove* applyAIMove(GameManager* game)
{
    MinMaxNode* bestNode = NULL;
    MIN_MAX_NODE_TYPE type = (game->state->currentPlayer == WHITE_PLAYER) ? MAX_NODE_TYPE : MIN_NODE_TYPE;
    if(game->difficulty < 5)
        bestNode = getBestNode(game->state, type, game->difficulty+1);
    else
    {
        printf("not supported yet");
        return NULL;
    }
    if(bestNode == NULL)
        return NULL;
    movePiece(game, duplicateLocation(bestNode->origin), duplicateLocation(bestNode->des));
    destroyMinMaxNode(bestNode);
    return seekFirstHistory(game->history);
}

void destroyChain(nodeChain* chain)
{
    nodeChain *current=chain, *next = NULL;;
    while(current != NULL)
    {
        if(current->node != NULL)
            destroyMinMaxNode(current->node);
        next = current->next;
        free(current);
        current = next;
    }
}

nodeChain* updateChainByDests(MinMaxNode* node, nodeChain *chain, Location *origin, Location **dests)
{
    int i=0;
    nodeChain* current = chain;
    while(dests[i] != NULL)
    {
        MinMaxNode* tempNode = createMinMaxNode(node->state,oppsiteType(node->type),node->depth+1,node->maxDepth);
        if(tempNode == NULL)
            return NULL;
        GameMove* move = applyMove(tempNode->state,origin,dests[i]);
        if(move == NULL)
            return NULL;
        destroyMove(move);
        tempNode->des = duplicateLocation(dests[i]);
        if(tempNode->des == NULL)
            return NULL;
        tempNode->origin = duplicateLocation(origin);
        if(tempNode->origin == NULL)
            return NULL;
        current->node = tempNode;
        current->next = (nodeChain*) calloc(1,sizeof(nodeChain));
        if(current->next == NULL)
            return NULL;
        i++;
        current = current->next;
    }
    return current;
}

nodeChain* getAllMinMaxNodes(MinMaxNode* node)
{
    nodeChain* root = (nodeChain*) calloc(1,sizeof(nodeChain));
    if(root == NULL)
        return NULL;
    Location loc;
    nodeChain* current = root;
    for(int x=0;x<CHESS_BOARD_SIZE;++x)
    {
        for(int y=0;y<CHESS_BOARD_SIZE;++y)
        {
            if(getPieceColor(node->state->board[x][y]) != node->state->currentPlayer)
                continue;
            loc = (Location){.x=x,.y=y};
            Location** dests = getAllAvailableMovesFromLocation(node->state, &loc);
            if(dests == NULL)
            {
                destroyChain(root);
                return NULL;
            }
            current = updateChainByDests(node, current, &loc, dests);
            destroyLocationsList(dests);
            if(current == NULL)
            {
                destroyChain(root);
                return NULL;
            }

        }
    }
    return root;
}

MinMaxNode* getBestNode(GameState* state, MIN_MAX_NODE_TYPE type, int maxDepth)
{
    MinMaxNode* node = createMinMaxNode(state, type, 0, maxDepth);
    nodeChain* nodesChain = getAllMinMaxNodes(node);
    if(nodesChain == NULL)
        return NULL;
    if(nodesChain->node == NULL) // no posible moves
    {
        free(nodesChain); //there are no nodes inside the nodesChain
        return NULL;
    }
    int currentPrunningScore = worstScore(node->type);
    nodeChain* currentNode = nodesChain;
    while(currentNode->node != NULL)
    {
        if(minMaxNodeScore(currentNode->node, currentPrunningScore) == GET_SCORE_FAILED)
        {
            destroyChain(nodesChain);
            return NULL;
        }
        if(isBetterScore(currentPrunningScore, currentNode->node->score, node->type))
            currentPrunningScore = currentNode->node->score;
        currentNode = currentNode->next;
    }
    MinMaxNode* tempNode = findBestNode(nodesChain, node->type);
    destroyMinMaxNode(node);
    node = (MinMaxNode*) malloc(sizeof(MinMaxNode));
    if(node == NULL)
        return NULL;
    node->origin = duplicateLocation(tempNode->origin);
    node->des = duplicateLocation(tempNode->des);
    node->state = NULL;

    destroyChain(nodesChain);

    return node;
}

MinMaxNode* createMinMaxNode(GameState* state, MIN_MAX_NODE_TYPE type, int depth, int maxDepth)
{
    MinMaxNode* node = (MinMaxNode*) malloc(sizeof(MinMaxNode));
    if(node == NULL)
        return NULL;
    node->state = duplicateGameState(state);
    if(node->state == NULL)
    {
        destroyMinMaxNode(node);
        return NULL;
    }
    node->des = NULL;
    node->origin = NULL;
    node->type = type;
    node->depth = depth;
    node->maxDepth = maxDepth;

    return node;
}

void destroyMinMaxNode(MinMaxNode *node)
{
    if(node == NULL)
        return;
    if(node->state != NULL)
        destroyGameState(node->state);
    if(node->origin != NULL)
        destroyLocation(node->origin);
    if(node->des != NULL)
        destroyLocation(node->des);

    free(node);

}



GET_SCORE_RESULT endGameNodeScore(MinMaxNode* node)
{
    if(isKingThreatened(node->state))
        node->score = (node->state->currentPlayer == WHITE_PLAYER)? INT_MIN : INT_MAX;
    else
        node->score = 0;

    return GET_SCORE_SUCCEED;
}

GET_SCORE_RESULT minMaxNodeScore(MinMaxNode* node, int prunningScore)
{
    if(node->depth == node->maxDepth)
    {
        node->score = boardScore(node->state->board);
        return GET_SCORE_SUCCEED;
    }
    nodeChain* nodesChain = getAllMinMaxNodes(node);
    if(nodesChain == NULL)
        return GET_SCORE_FAILED;
    if(nodesChain->node == NULL) // no posible moves
    {
        free(nodesChain); //there are no nodes inside the nodesChain
        return endGameNodeScore(node);
    }
    int currentPrunningScore = worstScore(node->type);
    nodeChain* currentNode = nodesChain;
    while(currentNode->node != NULL)
    {
        if(minMaxNodeScore(currentNode->node, currentPrunningScore) == GET_SCORE_FAILED)
        {
            destroyChain(nodesChain);
            return GET_SCORE_FAILED;
        }
        if(isBetterScore(currentNode->node->score,prunningScore,oppsiteType(node->type)))
        {
            node->score = currentNode->node->score;
            destroyChain(nodesChain);
            return GET_SCORE_SUCCEED;
        }
        if(isBetterScore(currentPrunningScore, currentNode->node->score, node->type))
            currentPrunningScore = currentNode->node->score;
        currentNode = currentNode->next;
    }

    node->score = findBestScore(nodesChain, node->type);
    destroyChain(nodesChain);
    return GET_SCORE_SUCCEED;
}

int findBestScore(nodeChain* nodesChain, MIN_MAX_NODE_TYPE type)
{
    int score = worstScore(type);
    nodeChain* currentNode = nodesChain;
    while(currentNode->node != NULL)
    {
        if(isBetterScore(score,currentNode->node->score,type))
            score = currentNode->node->score;
        currentNode = currentNode->next;
    }
    return score;
}

MinMaxNode* findBestNode(nodeChain* nodesChain, MIN_MAX_NODE_TYPE type)
{
    int score = worstScore(type);
    MinMaxNode* node = NULL;
    nodeChain* currentNode = nodesChain;
    while(currentNode->node != NULL)
    {
        if(isBetterScore(score,currentNode->node->score,type))
        {
            score = currentNode->node->score;
            node = currentNode->node;
        }
        currentNode = currentNode->next;
    }
    return node;
}

int worstScore(MIN_MAX_NODE_TYPE type)
{
    if(type == MAX_NODE_TYPE)
        return INT_MIN;
    return INT_MAX;
}

bool isBetterScore(int oldScore, int newScore, MIN_MAX_NODE_TYPE type)
{
    if(type == MAX_NODE_TYPE)
        return newScore > oldScore;
    return newScore<oldScore;
}

MIN_MAX_NODE_TYPE oppsiteType(MIN_MAX_NODE_TYPE type)
{
    if(type == MAX_NODE_TYPE)
        return MIN_NODE_TYPE;
    return MAX_NODE_TYPE;
}

int boardScore(Board board)
{
    int score = 0;
    for(int x=0; x<CHESS_BOARD_SIZE; ++x)
        for (int y = 0; y < CHESS_BOARD_SIZE; ++y)
            score += pieceScore(board[x][y]);

    return score;
}

int pieceScore(char piece)
{
    int playerFactor = (getPieceColor(piece) == WHITE_PLAYER) ? 1 : -1;
    int pieceValue = 0;
    switch (piece)
    {
        case WHITE_PAWN_SYMBOL:
        case BLACK_PAWN_SYMBOL:
            pieceValue = 1;
            break;
        case WHITE_KNIGHT_SYMBOL:
        case BLACK_KNIGHT_SYMBOL:
        case WHITE_BISHOP_SYMBOL:
        case BLACK_BISHOP_SYMBOL:
            pieceValue = 3;
            break;
        case WHITE_ROOK_SYMBOL:
        case BLACK_ROOK_SYMBOL:
            pieceValue = 5;
            break;
        case WHITE_QUEEN_SYMBOL:
        case BLACK_QUEEN_SYMBOL:
            pieceValue = 9;
            break;
        case WHITE_KING_SYMBOL:
        case BLACK_KING_SYMBOL:
            pieceValue = 100;
            break;
        default:
            break;
    }
    return pieceValue * playerFactor;
}