#include "History.h"

GameHistory* createHistory(int maxNumberOfMoves)
{
    GameHistory* history = (GameHistory*) malloc(sizeof(GameHistory));
    if(history == NULL)
        return NULL;
    history->movesList = (GameMove**) malloc(sizeof(GameMove*) * maxNumberOfMoves);
    if(history->movesList == NULL)
    {
        destroyHistory(history);
        return NULL;
    }
    history->numberOfMovesStored = 0;
    history->maxNumberOfMoves = maxNumberOfMoves;
    return history;
}

void destroyHistory(GameHistory* history)
{
    int i;
    if(history->movesList != 0)
    {
        for(i=0;i<history->numberOfMovesStored;i++)
        {
            GameMove* move = popFromHistory(history);
            destroyMove(move);
        }
        free(history->movesList);
    }
    free(history);
}

GameMove* popFromHistory(GameHistory* history)
{
    int i;
    GameMove* move = history->movesList[0];
    for(i=1; i<history->numberOfMovesStored;i++)
        history->movesList[i-1] = history->movesList[i];
    history->numberOfMovesStored--;
    return move;
}

GameMove* seekFirstHistory(GameHistory *history) {
    if(history->numberOfMovesStored == 0)
        return NULL;
    return history->movesList[0];
}

void pushToHistory(GameHistory* history, GameMove* move)
{
    int i;
    if(history->numberOfMovesStored == history->maxNumberOfMoves)
    {
        GameMove* lastMove = history->movesList[history->maxNumberOfMoves - 1];
        destroyMove(lastMove);
        history->numberOfMovesStored--;
    }
    for(i = history->numberOfMovesStored-1; i>=0; --i)
        history->movesList[i+1] = history->movesList[i];

    history->movesList[0] = move;
    history->numberOfMovesStored++;
}
