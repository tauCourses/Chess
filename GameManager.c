#include "GameManager.h"

GameManager* createEmptyGame()
{
    GameManager* game = (GameManager*) malloc(sizeof(GameManager));
    if(game == NULL)
        return NULL;
    game->state = createEmptyGameState();
    if(game->state == NULL)
    {
        destroyGame(game);
        return NULL;
    }
    game->history = createHistory(HISTORY_SIZE*2);
    if(game->history == NULL)
    {
        destroyGame(game);
        return NULL;
    }
    return game;
}
GameManager* createTwoPlayersGame()
{
    GameManager* game = createEmptyGame();
    if(game == NULL)
        return NULL;

    setInitialGameState(game->state);

    game->mode = TWO_PLAYERS_GAME_MODE;
    return game;
}

GameManager* createOnePlayerGame(int difficulty,  PLAYER_COLOR userColor)
{
    GameManager* game = createEmptyGame();
    if(game == NULL)
        return NULL;

    setInitialGameState(game->state);

    game->mode = ONE_PLAYER_GAME_MODE;
    game->userColor = userColor;
    game->difficulty = difficulty;
    return game;
}


void destroyGame(GameManager* game)
{
    if (game == NULL)
        return;
    if (game->state != NULL)
        destroyGameState(game->state);
    if(game->history != NULL)
        destroyHistory(game->history);

    free(game);
}

GAME_MOVE_MESSAGE movePiece(GameManager* game, Location* org, Location* des)
{
	switch (isMoveLegal(game->state,org,des))
	{
		case IS_LEGAL_INVALID_POSITION:
			return MOVE_INVALID_POSITION;
		case IS_LEGAL_NOT_USER_PIECE:
			return MOVE_NOT_USER_PIECE;
		case IS_LEGAL_INVALID_DUE_TO_CHESS_RULES:
			return MOVE_INVALID_DUE_TO_CHESS_RULES;
		default:
			break;
	}

    GameMove* move = applyMove(game->state, org, des);
    if(move == NULL)
        return MOVE_ERROR;

    pushToHistory(game->history, move);

    if(move->pawnChanged)
        return MOVE_PAWN_REACH_END;

    return MOVE_VALID;
}

GAME_STATE getGameState(GameManager* game)
{
    for(int x=0; x<CHESS_BOARD_SIZE; x++)
    {
        for(int y=0;y<CHESS_BOARD_SIZE;y++) {
            Location location = {.x=x,.y=y};
            Location** dests = getAllAvailableMovesFromLocation(game->state, &location);
            if(dests == NULL)
                return GAME_ERROR;
            else if (dests[0] != NULL)
            {
                destroyLocationsList(dests);
                return VALID_GAME_STATE;
            }
            else
                destroyLocationsList(dests);
        }
    }
    if(isKingThreatened(game->state))
        return GAME_CHECKMATE;
    return GAME_TIE;
}


GAME_UNDO_MOVE_MESSAGE candoundo(GameManager* game)
{
    if (game->mode == TWO_PLAYERS_GAME_MODE)
    	return UNDO_REFUSED;
	if (game->history->numberOfMovesStored < 2)
		return UNDO_NO_HISTORY;
	return UNDO_POSSIBLE;
}


GameMove* undoMove(GameManager* game)
{
    GameMove* move = popFromHistory(game->history);
    applyUndoMove(game->state,move);
    return move;
}

