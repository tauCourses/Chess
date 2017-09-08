#include "game.h"

typedef struct Game Game;
Game* createNewGame(int mode, int difficulty, bool userColor){
    Game* game = (Game*) malloc(sizeof(Game));
    if(game == NULL)
    {
        printf("ERROR: Failed to allocate memory for game.");
        return NULL;
    }

    game->state = createNewState();
    if (mode==1){
        game->historyStates = genericArrayListCreate(historySize,sizeof(State*),&destroyState);
        if(game->historyStates == NULL)
        {
            free(game);
            return NULL;
        }
        game->mode = 1;
    }
    else{
        game->mode = 2;
    }
    game->difficulty = difficulty;
    game->userColor = userColor;
    return game;
}


void destroyGame(Game* game){
    if (game == NULL)
        return;
    if (game->state != NULL)
        destroyState(game->state);
    if (game->historyStates != NULL)
        genericArrayListDestroy(game->historyStates);
    free(game);
}


bool isMoveLegal(Game* game, Location* org, Location* des, bool currentPlayerColor){
    if (isLocationOutOfBounds(org) || isLocationOutOfBounds(des))
        return 0;
    char orgPiece = getPiece(game->state->board,org);
    char desPiece = getPiece(game->state->board,des);
    //printf("isMoveLegal: move of '%c' from (%d,%d) to (%d,%d):\n",orgPiece,org->x,org->y,des->x,des->y);
    if (!(isLegalDesPiece(game->state->board, orgPiece, desPiece,currentPlayerColor)))
        return 0;
    switch(orgPiece) {
        case 'm':
            if (!isWhitePawnMoveLegal(game->state->board, org, des))
                return 0;
            break;
        case 'M':
            if (!isBlackPawnMoveLegal(game->state->board, org, des))
                return 0;
            break;
        case 'r':
        case 'R':
            if (!isRookMoveLegal(game->state->board, org, des))
                return 0;
            break;
        case 'n':
        case 'N':
            if (!isKnightMoveLegal(org, des))
                return 0;
            break;
        case 'b':
        case 'B':
            if (!isBishopMoveLegal(game->state->board, org, des))
                return 0;
            break;
        case 'k':
        case 'K':
            if (!isKingMoveLegal(game->state->board, org, des))
                return 0;
            break;
        case 'q':
        case 'Q':
            if (!isQueenMoveLegal(game->state->board, org, des))
                return 0;
            break;
    }
    return 1;
}


bool isLegalDesPiece(char** board, char orgPiece, char desPiece, bool currentPlayerColor){
    if (((getPieceColor(orgPiece) == WHITE) && (currentPlayerColor == BLACK)) || ((getPieceColor(orgPiece) == BLACK) && (currentPlayerColor == WHITE))) //if origion piece does not belong to user
        return 0;
    if (((getPieceColor(desPiece) == WHITE) && (currentPlayerColor == WHITE)) || ((getPieceColor(desPiece) == BLACK) && (currentPlayerColor == BLACK))) //if destenation piece belongs to user
        return 0;
    if (getPieceColor(orgPiece) == EMPTY_PIECE)//if origin piece is empty
        return 0;
    return 1;
}


bool isWhitePawnMoveLegal(char** board, Location* org, Location* des) {
    char desPiece = getPiece(board,des);
    if ((desPiece == EMPTY_PIECE) && (org->y == des->y)) { //move forward to an empty piece
        if ((org->x == 1) && (des->x == 3)) { //first move of pawn can be a double move
            return 1;
        }
        if (org->x+1 == des->x)
            return 1;
    }
    if ((desPiece != EMPTY_PIECE)&&((org->x+1 == des->x)&&((org->y+1 == des->y)||(org->y-1 == des->y))))//eating move, piece color was checked in isLegalDesPiece
        return 1;
    return 0;

}

bool isBlackPawnMoveLegal(char** board, Location* org, Location* des){
    char desPiece = getPiece(board,des);
    if (desPiece == EMPTY_PIECE && org->y == des->y) { //move forward to an empty piece
        if ((org->x == 6) && (des->x == 5)) { //first move of pawn can be a double move
            return 1;
        }
        if (org->x-1 == des->x)
            return 1;
    }
    if ((desPiece != EMPTY_PIECE)&&(org->x-1 == des->x)&&((org->y+1 == des->y)||(org->y-1 == des->y)))//eating move, color wise legal has been checked already
        return 1;
    return 0;

}
bool isRookMoveLegal(char** board, Location* org, Location* des){
    if (org->x == des->x){
        for (int j = fmin(org->y,des->y)+1; j< fmax(org->y,des->y); j++) {
            if (!isCoordinatesEmpty(board, org->x, j))
                return 0;
        }
        return 1;
    }
    if (org->y == des->y) {
        for (int i = fmin(org->x, des->x) + 1; i < fmax(org->x, des->x); i++) {
            if (!isCoordinatesEmpty(board, i, org->y))
                return 0;
        }
        return 1;
    }
    return 0;

}
bool isKnightMoveLegal(Location* org, Location* des){
    if ((org->x + 2 == des->x) && (org->y + 1 == des->y))
        return 1;
    if ((org->x + 1 == des->x) && (org->y + 2 == des->y))
        return 1;
    if ((org->x - 1 == des->x) && (org->y + 2 == des->y))
        return 1;
    if ((org->x - 2 == des->x) && (org->y + 1 == des->y))
        return 1;
    if ((org->x - 2 == des->x) && (org->y - 1 == des->y))
        return 1;
    if ((org->x - 1 == des->x) && (org->y - 2 == des->y))
        return 1;
    if ((org->x + 1 == des->x) && (org->y - 2 == des->y))
        return 1;
    if ((org->x + 2 == des->x) && (org->y - 1 == des->y))
        return 1;
    return 0;
}
bool isBishopMoveLegal(char** board, Location* org, Location* des){
    if ((org->x < des->x)&&(org->y < des->y)) {
        return (isBishopLegalDirection(board, org, des, &addInt, &addInt));
    }
    if ((org->x < des->x)&&(org->y > des->y)){
        return (isBishopLegalDirection(board, org, des, &addInt, &subInt));
    }
    if ((org->x > des->x)&&(org->y > des->y)){
        return (isBishopLegalDirection(board, org, des, &subInt, &subInt));
    }
    if ((org->x > des->x)&&(org->y < des->y)){
        return (isBishopLegalDirection(board, org, des, &subInt, &addInt));
    }
    return 0;
}

bool isBishopLegalDirection(char** board, Location* org, Location* des, int (*addOrSubX)(int,int), int (*addOrSubY)(int,int)){
    int i = 1;
    while (!isCoordinatesOutOfBounds(addOrSubX(org->x,i), addOrSubY(org->y,i)) && (addOrSubX(org->x,i) != des->x) && (addOrSubY(org->y,i) != des->y)) {//while in bounds and not in destination row or column
        if (!isCoordinatesEmpty(board, addOrSubX(org->x, i), addOrSubY(org->y, i))) //if there is another piece in the way
            return 0;
        i++;
    }
    if ((addOrSubX(org->x,i) == des->x)&&(addOrSubY(org->y,i) == des->y))//if we reached destination piece
        return 1;
    else
        return 0;
}

bool isKingMoveLegal(char** board, Location* org, Location* des){
    if ((org->x != des->x) ||(org->y != des->y))
        return ((org->y == des->y)||(org->y+1 == des->y)||(org->y-1 == des->y)) && ((org->x == des->x)||(org->x+1 == des->x) || (org->x-1 == des->x));
    return 0;
}


bool isQueenMoveLegal(char** board, Location* org, Location* des){
    return (isBishopMoveLegal(board,org,des) || isRookMoveLegal(board,org,des));
}

bool isKingThreatened(Game* game, bool currentPlayerColor){
    Location* kingLoc = currentPlayerColor ? game->state->BKingLoc : game->state->WKingLoc;
    char currentPieceColor;
    Location* currentLoc;
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            currentPieceColor = getPieceColorInCoordinates(game->state->board,i,j);
            currentLoc = newLocation(i,j);
            if ((currentPieceColor == enemysColor(currentPlayerColor)) && (isMoveLegal(game,currentLoc,kingLoc,currentPieceColor))) //current piece is enemy's piece
                    return 1;
            free(currentLoc);
        }
    }
    return 0;
}

bool wouldKingBeThreatened(Game* game, Location* org, Location* des, bool currentPlayerColor){
    char orgPiece = getPiece(game->state->board,org);
    char desPiece = getPiece(game->state->board,des);

    setPiece(game->state->board, org, EMPTY_PIECE);
    setPiece(game->state->board, des, orgPiece);
    if (isKingThreatened(game, currentPlayerColor)){
        setPiece(game->state->board, org, orgPiece);
        setPiece(game->state->board, des, desPiece);
        return 1;
    }
    setPiece(game->state->board, org, orgPiece);
    setPiece(game->state->board, des, desPiece);
    return 0;
}

bool movePiece(Game* game, Location* org, Location* des, bool currentPlayerColor){
    char orgPiece = getPiece(game->state->board,org);
    char desPiece = getPiece(game->state->board,des);
    if (isMoveLegal(game, org, des, currentPlayerColor)&& !wouldKingBeThreatened(game,org,des,currentPlayerColor)){
        //make move and update history and king's location if needed
        printf("\nmovePiece: moving now '%c' from (%d,%d) to (%d,%d):\n",orgPiece,org->x,org->y,des->x,des->y);
        updateHistory(game);
        setPiece(game->state->board, org, EMPTY_PIECE);
        setPiece(game->state->board, des, orgPiece);
        updateKingLocation(game,orgPiece,des);
        return 1;
    }
    else{
        printf("\nmovePiece: NOT moving '%c' from (%d,%d) to (%d,%d) for user color:%d\n",orgPiece,org->x,org->y,des->x,des->y,currentPlayerColor);
        printf("movePiece: isMoveLegal:%d\n",isMoveLegal(game, org, des, currentPlayerColor));
        return 0;
    }

}

bool isCheckmateOrTie(Game* game, bool currentPlayerColor){
    char currentPiece;
    Location* currentLoc;
    Location* optionalLoc;
    SPArrayList* optionalMoves;
    bool isCheckmate = 1;
    bool isTie = 1;

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            currentLoc = newLocation(i,j);
            currentPiece = getPiece(game->state->board,currentLoc);
            if ((currentPiece != EMPTY_PIECE)&&(getPieceColor(currentPiece) != currentPlayerColor)){ //current piece is enemy's piece
                optionalMoves = getMoves(game,currentLoc,getPieceColor(currentPiece));
                while (!spArrayListIsEmpty(optionalMoves)){ //for all optional moves for current piece
                    isTie = 0;
                    optionalLoc = spArrayListPop(optionalMoves);
                    if (!wouldKingBeThreatened(game,currentLoc,optionalLoc,getPieceColor(currentPiece))) //if there exists a move that does not threats king-
                        isCheckmate = 0;
                }
                spArrayListDestroy(optionalMoves);
            }
            free(currentLoc);
        }
    }
    return (isCheckmate|isTie);
}

SPArrayList* getMoves(Game* game,Location* currentLoc,bool currentUserColor){
    SPArrayList* possibleMoves = spArrayListCreate(63); //maximum number of moves for single piece is 63, for getMoves list
    Location* des;

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            des = newLocation(i,j);
            if (isMoveLegal(game,currentLoc, des, currentUserColor))
                spArrayListPush(possibleMoves,des);
        }
    }
    return possibleMoves;
}

bool undoMove(Game* game) {
    if (game->mode == 2) {
        printf("Undo command not available in 2 players mode\n");
        return 0;
    }
    if (genericArrayListIsEmpty(game->historyStates)) {
        printf("Empty history, move cannot be undone\n");
        return 0;
    }
    destroyState(game->state);
    game->state = genericArrayListPop(game->historyStates);
    return 1;
}