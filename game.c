#include "game.h"

typedef struct Game Game;
Game* createNewGame(int mode, int difficulty, bool userColor){
    Game* game = (Game*) malloc(sizeof(Game));
    if(game == NULL)
    {
        printf("ERROR: Failed to allocate memory for game.");
        return NULL;
    }

    game->board = createNewBoard();
    if (mode==1){
        game->history = spArrayListCreate(historySize);
        if(game->history == NULL)
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
    game->WKingLoc = newLocation(0,3);
    game->BKingLoc = newLocation(7,3);
    return game;
}

char** createNewBoard(){
    char** board = (char **)malloc(sizeof(char *) * 8);
    board[0] = (char *)malloc(sizeof(char) * 8 * 8);
    for(int i = 0; i < 8; i++)
        board[i] = (*board + 8 * i);

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if ((i < 2) | (i > 5)){ //non-empty pieces
                //white pieces
                if (i == 0){
                    if ((j==0) | (j==7))
                        board[i][j] = 'r';
                    if ((j==1) | (j==6))
                        board[i][j] = 'n';
                    if ((j==2) | (j==5))
                        board[i][j] = 'b';
                    if (j==3)
                        board[i][j] = 'k';
                    if (j==4)
                        board[i][j] = 'q';
                }
                if (i == 1)
                    board[i][j] = 'm';

                //black pieces
                if (i == 7){
                    if ((j==0) | (j==7))
                        board[i][j] = 'R';
                    if ((j==1) | (j==6))
                        board[i][j] = 'N';
                    if ((j==2) | (j==5))
                        board[i][j] = 'B';
                    if (j==3)
                        board[i][j] = 'K';
                    if (j==4)
                        board[i][j] = 'Q';
                }
                if (i == 6)
                    board[i][j] = 'M';
            }

            else {//blank pieces
                board[i][j] = EMPTY_PIECE;
            }
        }
    }
    return board;
}

void destroyBoard(char** board){
    free(board[0]);
    free(board);
}

void destroyGame(Game* game){
    if (game == NULL)
        return;
    if (game->board != NULL)
        destroyBoard(game->board);
    if (game->history != NULL)
        spArrayListDestroy(game->history);
    free(game);
}


bool isMoveLegal(Game* game, Location* org, Location* des, bool currentPlayerColor){
    if (isLocationOutOfBounds(org) || isLocationOutOfBounds(des))
        return 0;
    char orgPiece = getPiece(game->board,org);
    char desPiece = getPiece(game->board,des);
    printf("isMoveLegal: move of '%c' from (%d,%d) to (%d,%d): ",orgPiece,org->x,org->y,des->x,des->y);
    if (!(isLegalDesPiece(game->board, orgPiece, desPiece,currentPlayerColor)))
        return 0;
    switch(orgPiece) {
        case 'm':
            if (!isWhitePawnMoveLegal(game->board, org, des))
                return 0;
            break;
        case 'M':
            if (!isBlackPawnMoveLegal(game->board, org, des))
                return 0;
            break;
        case 'r':
        case 'R':
            if (!isRookMoveLegal(game->board, org, des))
                return 0;
            break;
        case 'n':
        case 'N':
            if (!isKnightMoveLegal(org, des))
                return 0;
            break;
        case 'b':
        case 'B':
            if (!isBishopMoveLegal(game->board, org, des))
                return 0;
            break;
        case 'k':
        case 'K':
            if (!isKingMoveLegal(game->board, org, des))
                return 0;
            break;
        case 'q':
        case 'Q':
            if (!isQueenMoveLegal(game->board, org, des))
                return 0;
            break;
    }
    return 1;
}

char getPiece(char** board, Location* loc){
    return (*(*(board +loc->x)+loc->y));
}

void setPiece(char** board, Location* loc, char newPiece){
    (*(*(board +loc->x)+loc->y)) = newPiece;
}

char getPieceInCoordinates(char** board, int x, int y){
    Location* newLoc = newLocation(x,y);
    char piece = (getPiece(board,newLoc));
    free(newLoc);
    return piece;
}


bool isLocationOutOfBounds(Location* des){
    return ((des->x > 7) || (des->x < 0) || (des->y > 7) || (des->y < 0));
}

bool isCoordinatesOutOfBounds(int x, int y){
    Location* newLoc = newLocation(x,y);
    char piece =  isLocationOutOfBounds(newLoc);
    free(newLoc);
    return piece;
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

int getPieceColor(char piece){
    if ((piece == 'm')||(piece == 'r')||(piece == 'n')||(piece == 'b')||(piece == 'k')||(piece == 'q'))
        return WHITE;
    if ((piece == 'M')||(piece == 'R')||(piece == 'N')||(piece == 'B')||(piece == 'K')||(piece == 'Q'))
        return BLACK;
    return EMPTY_PIECE;
}

int getPieceColorInCoordinates(char** board, int x, int y){
    Location* newLoc = newLocation(x,y);
    char piece = getPieceColor(getPiece(board, newLoc));
    free(newLoc);
    return piece;
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


Location* newLocation(int x, int y){
    Location* newLocation = (Location*) malloc(2*sizeof(int));
    newLocation->x = x;
    newLocation->y = y;
    return newLocation;
}

bool isCoordinatesEmpty(char** board, int x, int y){
    Location* newLoc = newLocation(x,y);
    bool ans = ((getPiece(board,newLoc) == EMPTY_PIECE));
    free(newLoc);
    return ans;
}

int addInt(int a, int b) {
    return a+b;
}
int subInt(int a, int b) {
    return a-b;
}

bool isKingThreatened(Game* game, bool currentPlayerColor){
    Location* kingLoc = currentPlayerColor ? game->BKingLoc : game->WKingLoc;
    char currentPieceColor;
    Location* currentLoc;
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            currentPieceColor = getPieceColorInCoordinates(game->board,i,j);
            currentLoc = newLocation(i,j);
            if ((currentPieceColor != EMPTY_PIECE)&&(currentPieceColor != currentPlayerColor)){ //current piece is enemy's piece
                if (isMoveLegal(game,currentLoc,kingLoc,currentPieceColor))
                    return 1;
            }
            free(currentLoc);
        }
    }
    return 0;
}

bool wouldKingBeThreatened(Game* game, Location* org, Location* des, bool currentPlayerColor){
    char orgPiece = getPiece(game->board,org);
    char desPiece = getPiece(game->board,des);

    setPiece(game->board, org, EMPTY_PIECE);
    setPiece(game->board, des, orgPiece);
    if (isKingThreatened(game, currentPlayerColor)){
        setPiece(game->board, org, orgPiece);
        setPiece(game->board, des, desPiece);
        return 1;
    }
    setPiece(game->board, org, orgPiece);
    setPiece(game->board, des, desPiece);
    return 0;
}

bool movePiece(Game* game, Location* org, Location* des, bool currentPlayerColor){
    char orgPiece = getPiece(game->board,org);
    char desPiece = getPiece(game->board,des);
    if (isMoveLegal(game, org, des, currentPlayerColor)&& !wouldKingBeThreatened(game,org,des,currentPlayerColor)){
        //make move and update king's location if needed
        if (orgPiece == 'k')
            game->WKingLoc = des;
        if (orgPiece == 'K')
            game->BKingLoc = des;
        return 1;
    }
    else
        return 0;
}

bool isCheckmateOrTie(Game* game, bool currentPlayerColor){
    char currentPiece;
    Location* currentLoc;
    Location optionalLoc;
    SPArrayList* optionalMoves;
    bool isCheckmate = 1;
    bool isTie = 1;

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            currentLoc = newLocation(i,j);
            currentPiece = getPiece(game->board,currentLoc);
            if ((currentPiece != EMPTY_PIECE)&&(getPieceColor(currentPiece) != currentPlayerColor)){ //current piece is enemy's piece

                optionalMoves = getMoves(game->board,currentPiece,currentLoc,getPieceColor(currentPiece));
                while (!spArrayListIsEmpty(optionalMoves)){ //for all optional moves for current piece
                    isTie = 0;
                    optionalLoc = spArrayListPop(optionalMoves);
                    if (!wouldKingBeThreatened(game,currentLoc,&optionalLoc,getPieceColor(currentPiece))) //if there exists a move that does not threats king
                        isCheckmate = 0;
                }
                spArrayListDestroy(optionalMoves);
            }
            free(currentLoc);
        }
    }
    return (isCheckmate|isTie);
}

SPArrayList* getMoves(char** board,char currentPiece,Location* currentLoc,bool currentUserColor){

}
