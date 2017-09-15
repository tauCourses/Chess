#include "GameState.h"
#include "GameBoard.h"

GameState* createEmptyGameState()
{
    GameState* state = (GameState*) malloc(sizeof(GameState));
    if(state == NULL)
        return NULL;

    return state;
}

GameState* createInitialGameState()
{
    GameState* state = (GameState*) malloc(sizeof(GameState));
    if(state == NULL)
        return NULL;

    state->currentPlayer = WHITE_PLAYER;

    state->blackCastle = createCastleState(false, false, false);
    state->whiteCastle = createCastleState(false, false, false);
    if(state->blackCastle == NULL || state->whiteCastle == NULL)
    {
        destroyGameState(state);
        return NULL;
    }
    setInitialBoard(state->board);

    return state;
}

castleState* createCastleState(bool hasKingMoved,bool hasLeftRookMoved, bool hasRightRookMoved)
{
    castleState* castle = (castleState*) malloc(sizeof(castleState));
    if(castle == NULL)
        return NULL;
    castle->hasKingMoved = hasKingMoved;
    castle->hasRightRookMoved = hasRightRookMoved;
    castle->hasLeftRookMoved = hasLeftRookMoved;
    return castle;
}

castleState* duplicateCastleState(castleState* castle)
{
    castleState* newCastle = (castleState*) malloc(sizeof(castleState));
    if(castle == NULL)
        return NULL;
    newCastle->hasKingMoved = castle->hasKingMoved;
    newCastle->hasRightRookMoved = castle->hasRightRookMoved;
    newCastle->hasLeftRookMoved = castle->hasLeftRookMoved;
    return castle;
}

void destroyCastleState(castleState* castle)
{
    free(castle);
}



GameState* duplicateGameState(GameState* state)
{
    GameState* newState = createEmptyGameState();
    if(newState == NULL)
        return NULL;

    newState->blackCastle = createCastleState(false, false, false);
    newState->whiteCastle = createCastleState(false, false, false);

    return newState;
}

void destroyGameState(GameState* state)
{
    if(state == NULL)
        return;

    if(state->whiteCastle != NULL)
        destroyCastleState(state->whiteCastle);
    if(state->blackCastle != NULL)
        destroyCastleState(state->blackCastle);

    free(state);
}

bool isMoveLegal(GameState* state, Location* org, Location* des)
{
    if(getPieceColor(state->board[org->x][org->y]) != state->currentPlayer)
        return false;
    if(!isLegalDesPiece(state->board, state->board[org->x][org->y], state->board[des->x][des->y]))
        return false;
    if(checkCastleMove(state,org,des))
        return true;
    if(!isPieceMoveLegal(state->board,org,des))
        return false;

    bool result = true;
    char oldPiece = state->board[des->x][des->y];
    state->board[des->x][des->y] = state->board[org->x][org->y];
    state->board[org->x][org->y] = EMPTY_PLACE_SYMBOL;
    if(isKingThreatened(state))
        result = false;

    state->board[org->x][org->y] = state->board[des->x][des->y];
    state->board[des->x][des->y] = oldPiece;
    return result;
}

bool isKingThreatened(GameState* state)
{
    Location* kingLocation = findKingLocation(state, state->currentPlayer);
    if(kingLocation == NULL)
        return false;
    bool res = isThreatened(state, kingLocation, oppositeColor(state->currentPlayer));
    destroyLocation(kingLocation);
    return res;
}

Location* findKingLocation(GameState* state, PLAYER_COLOR kingColor)
{
    char kingChar = (char)((kingColor == WHITE_PLAYER) ? WHITE_KING_SYMBOL : BLACK_KING_SYMBOL);
    for(int x=0; x<CHESS_BOARD_SIZE; ++x)
        for (int y=0; y<CHESS_BOARD_SIZE; ++y)
            if(state->board[x][y] == kingChar)
                return createLocation(x,y);

    printf("BUG!!32141");
    return NULL;
}

bool isThreatened(GameState* state, Location* loc, PLAYER_COLOR byPlayer)
{
    for(int x=0; x<CHESS_BOARD_SIZE; ++x)
    {
        for (int y = 0; y < CHESS_BOARD_SIZE; ++y)
        {
            if(getPieceColor(state->board[x][y]) == byPlayer)
            {
                Location org = {.x=x,.y=y};
                if(state->board[x][y] != BLACK_PAWN_SYMBOL && state->board[x][y] != WHITE_PAWN_SYMBOL &&
                        isPieceMoveLegal(state->board,&org,loc) )
                        return true;
                else if(state->board[x][y] == BLACK_PAWN_SYMBOL &&
                            loc->x + 1 == x &&
                            (loc->y +1 == y || loc->y -1 == y))
                        return true;
                else if(state->board[x][y] == WHITE_PAWN_SYMBOL &&
                        loc->x - 1 == x &&
                        (loc->y +1 == y || loc->y -1 == y))
                    return true;

            }
        }
    }
    return false;
}

void applyCastleChange(GameState *state, Location *org, Location *des)
{
    if(org->x == 0 && org->y == 0)
        state->whiteCastle->hasLeftRookMoved = true;
    if(org->x == 0 && org->y == 7)
        state->whiteCastle->hasRightRookMoved = true;
    if(org->x == 0 && org->y == 4)
        state->whiteCastle->hasKingMoved = true;
    if(org->x == 7 && org->y == 0)
        state->blackCastle->hasLeftRookMoved = true;
    if(org->x == 7 && org->y == 7)
        state->blackCastle->hasRightRookMoved = true;
    if(org->x == 7 && org->y == 4)
        state->whiteCastle->hasKingMoved = true;


    if(state->board[des->x][des->y] == WHITE_KING_SYMBOL &&
            des->x == 0 && org->x == 0 &&
            org->y == 4)
    {
        if(des->y == 6)
        {
            state->board[0][5] = WHITE_ROOK_SYMBOL;
            state->board[0][7] = EMPTY_PLACE_SYMBOL;
        }
        if(des->y == 2)
        {
            state->board[0][3] = WHITE_ROOK_SYMBOL;
            state->board[0][0] = EMPTY_PLACE_SYMBOL;
        }
    }

    if(state->board[des->x][des->y] == BLACK_KING_SYMBOL &&
       des->x == 7 && org->x == 7 &&
       org->y == 4)
    {
        if(des->y == 6)
        {
            state->board[7][5] = BLACK_ROOK_SYMBOL;
            state->board[7][7] = EMPTY_PLACE_SYMBOL;
        }
        if(des->y == 2)
        {
            state->board[7][3] = BLACK_ROOK_SYMBOL;
            state->board[7][0] = EMPTY_PLACE_SYMBOL;
        }
    }
}

void destroyMove(GameMove* move)
{
    if(move == NULL)
        return;

    if(move->origin != NULL)
        destroyLocation(move->origin);
    if(move->destination != NULL)
        destroyLocation(move->destination);
    if(move->whiteCastle != NULL)
        destroyCastleState(move->whiteCastle);
    if(move->blackCastle != NULL)
        destroyCastleState(move->blackCastle);

    free(move);
}

GameMove* applyMove(GameState* state, Location* org, Location* des)
{
    GameMove* move = (GameMove*) malloc(sizeof(GameMove));
    if(move == NULL)
        return NULL;
    move->blackCastle = duplicateCastleState(state->blackCastle);
    move->whiteCastle = duplicateCastleState(state->whiteCastle);
    move->origin = duplicateLocation(org);
    move->destination = duplicateLocation(des);
    move->piece = state->board[des->x][des->y];

    if(state->board[org->x][org->y] == WHITE_PAWN_SYMBOL && org->x == 6)
        move->pawnChanged = true;
    else if(state->board[org->x][org->y] == BLACK_PAWN_SYMBOL && org->x == 1)
        move->pawnChanged = true;
    else
        move->pawnChanged = false;

    state->board[des->x][des->y] = state->board[org->x][org->y];
    state->board[org->x][org->y] = EMPTY_PLACE_SYMBOL;
    applyCastleChange(state, org, des);

    state->currentPlayer = oppositeColor(state->currentPlayer);
    return move;
}

bool checkCastleMove(GameState* state, Location* org, Location* des)
{
    castleState* castleState = state->currentPlayer == WHITE_PLAYER ? state->whiteCastle : state->blackCastle;
    if(org->y == 4 && des->y == 6 && org->x == des->x
       && castleState->hasKingMoved == false && castleState->hasLeftRookMoved == false) //right castle
    {
        Location first = {.x = des->x, .y=5};
        Location second = {.x = des->x, .y=6};
        return !isKingThreatened(state) &&
               !isThreatened(state, &first , oppositeColor(state->currentPlayer)) &&
               !isThreatened(state, &second , oppositeColor(state->currentPlayer)) &&
               state->board[des->x][5] == EMPTY_PLACE_SYMBOL &&
               state->board[des->x][6] == EMPTY_PLACE_SYMBOL;
    }
    if(org->y == 4 && des->y == 2 && org->x == des->x
       && castleState->hasKingMoved == false && castleState->hasRightRookMoved == false) //left castle
    {
        Location first = {.x = des->x, .y=3};
        Location second = {.x = des->x, .y=2};
        return !isKingThreatened(state) &&
               !isThreatened(state, &first , oppositeColor(state->currentPlayer)) &&
               !isThreatened(state, &second , oppositeColor(state->currentPlayer)) &&
               state->board[des->x][3] == EMPTY_PLACE_SYMBOL &&
               state->board[des->x][2] == EMPTY_PLACE_SYMBOL &&
               state->board[des->x][1] == EMPTY_PLACE_SYMBOL;
    }
    return false;
}
