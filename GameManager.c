#include "GameManager.h"
#include "GameState.h"

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
    return game;
}
GameManager* createTwoPlayersGame()
{
    GameManager* game = (GameManager*) malloc(sizeof(GameManager));
    if(game == NULL)
        return NULL;

    game->state = createInitialGameState();
    if(game->state == NULL)
    {
        destroyGame(game);
        return NULL;
    }
    game->mode = TWO_PLAYERS_GAME_MODE;
    return game;
}

GameManager* createOnePlayerGame(int difficulty,  PLAYER_COLOR userColor)
{
    GameManager* game = (GameManager*) malloc(sizeof(GameManager));
    if(game == NULL)
        return NULL;

    game->state = createInitialGameState();
    if(game->state == NULL)
    {
        destroyGame(game);
        return NULL;
    }
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

    free(game);
}

GAME_MOVE_MESSAGE movePiece(GameManager* game, Location* org, Location* des)
{

    if(!isMoveLegal(game->state,org,des))
        return MOVE_INVALID_POSITION;
    GameMove* move = applyMove(game->state, org, des);

    //history - save move TODO!

    if(move->pawnChanged)
    {
        destroyMove(move);
        return MOVE_PAWN_REACH_END;
    }
    return MOVE_VALID;
}

GAME_STATE getGameState(GameManager* game)
{
    for(int i=0; i<7; i++) {
        if (game->state->board[0][i] == BLACK_PAWN_SYMBOL || game->state->board[7][i] == WHITE_PAWN_SYMBOL) {
            return PAWN_REACH_END;
        }
    }
    for(int x=0; x<CHESS_BOARD_SIZE; x++)
    {
        for(int y=0;y<CHESS_BOARD_SIZE;y++) {
            Location location = {.x=x,.y=y};
            if (getAllAvailableMovesFromLocation(game, &location) != NULL)
                return VALID_GAME_STATE;
        }
    }
    if(isKingThreatened(game->state))
        return GAME_CHECKMATE;
    return GAME_TIE;
}

Location* getAllAvailableMovesFromLocation(GameManager* game,Location* origin)
{
    Location* possibleMoves = (Location*) calloc(sizeof(Location),CHESS_BOARD_SIZE*CHESS_BOARD_SIZE-1);

    int numberOfElements = 0;
    for(int x=0; x<CHESS_BOARD_SIZE; x++)
    {
        for(int y=0;y<CHESS_BOARD_SIZE;y++) {
            Location destination = {.x=x,.y=y};
            if (isMoveLegal(game->state,origin, &destination))
            {
                possibleMoves[numberOfElements] = destination;
                numberOfElements++;
            }
        }
    }
    qsort(possibleMoves, (size_t)numberOfElements, sizeof(Location), &compareLocations);
    return possibleMoves;
}

GAME_UNDO_MOVE_MESSAGE undoMove(GameManager* game)
{
    printf("not supported yet");
    return UNDO_REFUSED;
}

