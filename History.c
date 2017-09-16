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
    if(history->movesList != 0)
    {
        for(int i=0;i<history->numberOfMovesStored;i++)
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
    GameMove* move = history->movesList[0];
    for(int i=1; i<history->numberOfMovesStored;i++)
        history->movesList[i-1] = history->movesList[i];
    history->numberOfMovesStored--;
    return move;
}

GameMove* pushToHistory(GameHistory* history, GameMove* move)
{
    if(history->numberOfMovesStored == history->maxNumberOfMoves)
    {
        GameMove* lastMove = history->movesList[history->maxNumberOfMoves - 1];
        destroyMove(lastMove);
        history->numberOfMovesStored--;
    }
    for(int i=history->numberOfMovesStored-1; i>=0; --i)
        history->movesList[i+1] = history->movesList[i];

    history->movesList[0] = move;
    history->numberOfMovesStored++;
}
