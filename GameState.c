#include "GameState.h"

GameState* createEmptyGameState()
{
    GameState* state = (GameState*) malloc(sizeof(GameState));
    if(state == NULL)
        return NULL;

    state->blackCastle = createCastleState(false,false,false);
    state->whiteCastle = createCastleState(false,false,false);
    if(state->blackCastle == NULL || state->whiteCastle == NULL)
    {
        destroyGameState(state);
        return NULL;
    }
    return state;
}

void setInitialGameState(GameState* state)
{
    state->currentPlayer = WHITE_PLAYER;
    setInitialBoard(state->board);
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
    return newCastle;
}

void destroyCastleState(castleState* castle)
{
    free(castle);
}

GameState* duplicateGameState(GameState* state)
{
    int x,y;
    GameState* newState = createEmptyGameState();
    if(newState == NULL)
        return NULL;

    newState->blackCastle = duplicateCastleState(state->blackCastle);
    if(newState->blackCastle == NULL)
    {
        destroyGameState(newState);
        return NULL;
    }
    newState->whiteCastle = duplicateCastleState(state->whiteCastle);
    if(newState->whiteCastle == NULL)
    {
        destroyGameState(newState);
        return NULL;
    }
    newState->currentPlayer = state->currentPlayer;
    for(x = 0;x<CHESS_BOARD_SIZE; ++x)
        for (y = 0; y < CHESS_BOARD_SIZE; ++y)
            newState->board[x][y] = state->board[x][y];

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

Location** getAllAvailableMovesFromLocation(GameState* state,Location* origin)
{
    size_t maxPossibleMoves = CHESS_BOARD_SIZE*CHESS_BOARD_SIZE;
    Location** possibleMoves = (Location**) calloc(sizeof(Location*),maxPossibleMoves);
    if(possibleMoves == NULL)
        return NULL;

    int numberOfElements = 0;
    int x,y;
    Location destination;
    for(x=0; x<CHESS_BOARD_SIZE; x++)
    {
        for(y=0;y<CHESS_BOARD_SIZE && numberOfElements < (int)maxPossibleMoves-1;y++)
        {
            destination = (Location){.x=x,.y=y};
            if (isMoveLegal(state,origin, &destination) == IS_LEGAL_VALID)
            {
                possibleMoves[numberOfElements] = duplicateLocation(&destination);
                if(possibleMoves[numberOfElements] == NULL)
                {
                    destroyLocationsList(possibleMoves);
                    return NULL;
                }
                numberOfElements++;
            }
        }
    }
    qsort(possibleMoves, (size_t)numberOfElements, sizeof(Location*), compareLocations);
    return possibleMoves;
}

GAME_IS_LEGAL_MESSAGE isMoveLegal(GameState* state, Location* org, Location* des)
{
	IS_KING_THREATENED isKingThreatenedMsg;
    if (isLocationOutOfBounds(org) || isLocationOutOfBounds(des))
		return IS_LEGAL_INVALID_POSITION;
	if(getPieceColor(state->board[org->x][org->y]) != state->currentPlayer)
        return IS_LEGAL_NOT_USER_PIECE;
    if(!isLegalDesPiece(state->board, state->board[org->x][org->y], state->board[des->x][des->y]))
        return IS_LEGAL_INVALID_DUE_TO_CHESS_RULES;
    if(checkCastleMove(state,org,des))
        return IS_LEGAL_VALID;
    if(!isPieceMoveLegal(state->board,org,des))
        return IS_LEGAL_INVALID_DUE_TO_CHESS_RULES;

    bool isChessAgainstUser = false;
    char oldPiece = state->board[des->x][des->y];
    state->board[des->x][des->y] = state->board[org->x][org->y];
    state->board[org->x][org->y] = EMPTY_PLACE_SYMBOL;
    isKingThreatenedMsg = isKingThreatened(state);
    if(isKingThreatenedMsg == IS_KING_THREATENED_TRUE)
        isChessAgainstUser = true;
    else
    {
        if(isKingThreatenedMsg == IS_KING_THREATENED_MALLOC_ERROR)
        {
            printf("ERROR: in allocating memory\n");
            return IS_LEGAL_INVALID_DUE_TO_CHESS_RULES;
        }
    }

    state->board[org->x][org->y] = state->board[des->x][des->y];
    state->board[des->x][des->y] = oldPiece;
    if (isChessAgainstUser)
    	return IS_LEGAL_INVALID_DUE_TO_CHESS_RULES;
    else
        return IS_LEGAL_VALID;
}

IS_KING_THREATENED isKingThreatened(GameState* state)
{
    Location* kingLocation = findKingLocation(state, state->currentPlayer);
    if(kingLocation == NULL)
        return IS_KING_THREATENED_MALLOC_ERROR;
	bool res = isThreatened(state, kingLocation, oppositeColor(state->currentPlayer));
    destroyLocation(kingLocation);
    if (res)
        return IS_KING_THREATENED_TRUE;
    else
        return IS_KING_THREATENED_FALSE;
}

Location* findKingLocation(GameState* state, PLAYER_COLOR kingColor)
{
    int x,y;
    char kingChar = (char)((kingColor == WHITE_PLAYER) ? WHITE_KING_SYMBOL : BLACK_KING_SYMBOL);
    for(x=0; x<CHESS_BOARD_SIZE; ++x)
        for (y=0; y<CHESS_BOARD_SIZE; ++y)
            if(state->board[x][y] == kingChar)
                return createLocation(x,y);

    printf("ERROR: - no king found!");
    return NULL;
}

bool isThreatened(GameState *state, Location *loc, PLAYER_COLOR byPlayer)
{
    int x,y;
    for(x=0; x<CHESS_BOARD_SIZE; ++x)
    {
        for (y = 0; y < CHESS_BOARD_SIZE; ++y)
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

bool isREALLYThreatened(GameState *state, Location *loc)
{
    int x,y;
    for(x=0; x<CHESS_BOARD_SIZE; ++x)
    {
        for (y = 0; y < CHESS_BOARD_SIZE; ++y)
        {
            Location org = {.x=x,.y=y};
            if(isMoveLegal(state,&org,loc) == IS_LEGAL_VALID)
                return true;
        }
    }
    return false;
}

void checkIfCastleChanged(GameState *state, Location *org)
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
        state->blackCastle->hasKingMoved = true;
}

void applyCastleChange(GameState *state, Location *org, Location *des)
{
    checkIfCastleChanged(state, org);
    if(state->board[des->x][des->y] == WHITE_KING_SYMBOL &&
            des->x == 0 && org->x == 0 && org->y == 4)
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
       des->x == 7 && org->x == 7 && org->y == 4)
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
    if(move->des != NULL)
        destroyLocation(move->des);
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
    if(move->blackCastle == NULL)
    {
        destroyMove(move);
        return NULL;
    }
    move->whiteCastle = duplicateCastleState(state->whiteCastle);
    if(move->whiteCastle == NULL)
    {
        destroyMove(move);
        return NULL;
    }
    move->origin = duplicateLocation(org);
    if(move->origin == NULL)
    {
        destroyMove(move);
        return NULL;
    }
    move->des = duplicateLocation(des);
    if(move->des == NULL)
    {
        destroyMove(move);
        return NULL;
    }
    move->beatedPiece = state->board[des->x][des->y];

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

bool isCastleUndo(GameState *state, GameMove *move)
{
    char castleKing = (char)((state->currentPlayer == WHITE_PLAYER) ? BLACK_KING_SYMBOL : WHITE_KING_SYMBOL);
    if(state->board[move->des->x][move->des->y] != castleKing)
        return false;
    if(abs(move->des->y - move->origin->y) > 1)
        return true;
    return false;
}

void applyCastleUndo(GameState *state, GameMove *move)
{
    char castleRook = (char)((state->currentPlayer == WHITE_PLAYER) ? BLACK_ROOK_SYMBOL : WHITE_ROOK_SYMBOL);
    if(move->des->y == 6)
    {
        state->board[move->des->x][7] = castleRook;
        state->board[move->des->x][5] = EMPTY_PLACE_SYMBOL;
    }
    if(move->des->y == 2)
    {
        state->board[move->des->x][0] = castleRook;
        state->board[move->des->x][3] = EMPTY_PLACE_SYMBOL;
    }
}

void applyUndoMove(GameState *state, GameMove *move)
{
    if(isCastleUndo(state, move))
        applyCastleUndo(state, move);

    if(move->pawnChanged)
    {
        char pawn = (char)(state->currentPlayer == WHITE_PLAYER ? 'M' : 'm');
        state->board[move->origin->x][move->origin->y] = pawn;
    }
    else
        state->board[move->origin->x][move->origin->y] = state->board[move->des->x][move->des->y];
    state->board[move->des->x][move->des->y] = move->beatedPiece;

    *state->whiteCastle = *move->whiteCastle; //copy the data, works because there are no pointers in this struct
    *state->blackCastle = *move->blackCastle;

    state->currentPlayer = oppositeColor(state->currentPlayer);
}

bool checkCastleMove(GameState* state, Location* org, Location* des)
{
    bool result;
    IS_KING_THREATENED  isKingThreatenedMsg;
    castleState* castleState = state->currentPlayer == WHITE_PLAYER ? state->whiteCastle : state->blackCastle;
    if(state->board[org->x][org->y] != (state->currentPlayer == WHITE_PLAYER ? WHITE_KING_SYMBOL : BLACK_KING_SYMBOL))
        return false;
    int rookY = (org->y < des->y) ? 7 : 0;
    if(state->board[org->x][rookY] != (state->currentPlayer == WHITE_PLAYER ? WHITE_ROOK_SYMBOL : BLACK_ROOK_SYMBOL))
        return false;

    if(org->y == 4 && des->y == 6 && org->x == des->x
       && castleState->hasKingMoved == false && castleState->hasRightRookMoved == false) //right castle
    {
        Location first = {.x = des->x, .y=5};
        Location second = {.x = des->x, .y=6};
        isKingThreatenedMsg = isKingThreatened(state);
        result = ((isKingThreatenedMsg == IS_KING_THREATENED_FALSE) &&
               !isThreatened(state, &first, oppositeColor(state->currentPlayer)) &&
               !isThreatened(state, &second, oppositeColor(state->currentPlayer)) &&
               state->board[des->x][5] == EMPTY_PLACE_SYMBOL &&
               state->board[des->x][6] == EMPTY_PLACE_SYMBOL);
        if (isKingThreatenedMsg == IS_KING_THREATENED_MALLOC_ERROR)
        {
            printf("ERROR: in allocating memory\n");
            return false;
        }
        else
            return result;
    }
    if(org->y == 4 && des->y == 2 && org->x == des->x
       && castleState->hasKingMoved == false && castleState->hasLeftRookMoved == false) //left castle
    {
        Location first = {.x = des->x, .y=3};
        Location second = {.x = des->x, .y=2};
        isKingThreatenedMsg = isKingThreatened(state);
        result = ((isKingThreatenedMsg == IS_KING_THREATENED_FALSE) &&
               !isThreatened(state, &first, oppositeColor(state->currentPlayer)) &&
               !isThreatened(state, &second, oppositeColor(state->currentPlayer)) &&
               state->board[des->x][3] == EMPTY_PLACE_SYMBOL &&
               state->board[des->x][2] == EMPTY_PLACE_SYMBOL &&
               state->board[des->x][1] == EMPTY_PLACE_SYMBOL);
        if (isKingThreatenedMsg == IS_KING_THREATENED_MALLOC_ERROR)
        {
            printf("ERROR: in allocating memory\n");
            return false;
        }
        else
            return result;
    }
    return false;
}
