#include <game.h>
#include "game.h"

typedef struct Game Game;
Game* createNewGame(int mode, int difficulty, char userColor){
    Game* game = (Game*) calloc(1,sizeof(Game));
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

    return game;
}

char** createNewBoard(){
    char board[8][8];
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (i < 2 | i > 5){ //non-empty pieces
                //white pieces
                if (i == 0){
                    if (j==0 | j==7)
                        board[i][j] = 'r';
                    if (j==1 | j==6)
                        board[i][j] = 'n';
                    if (j==2 | j==5)
                        board[i][j] = 'b';
                    if (j==3)
                        board[i][j] = 'k';
                    if (j==4)
                        board[i][j] = 'q';
                }
                if (i == 1)
                    board[i][j] = 'm';

                //black pieces
                if (i == 0){
                    if (j==0 | j==7)
                        board[i][j] = 'R';
                    if (j==1 | j==6)
                        board[i][j] = 'N';
                    if (j==2 | j==5)
                        board[i][j] = 'B';
                    if (j==3)
                        board[i][j] = 'K';
                    if (j==4)
                        board[i][j] = 'Q';
                }
                if (i == 1)
                    board[i][j] = 'M';
            }
            else {//blank pieces
                board[i][j] = '_';
            }
        }
    }
    return board;
}

boolean isMoveLegal(char** board, Location* org, Location* des, boolean userColor){
    char orgPiece = getPiece(board,org);
    if (isLocationOutOfBounds(org) || isLocationOutOfBounds(des))
        return 0;
    if (!(isLegalDesPiece(board, orgPiece, des,userColor)))
        return 0;

    switch(orgPiece) {
        case 'm':
            if (!isWhitePawnMoveLegal(board, org, des))
                return 0;
            break;
        case 'M':
            if (!isBlackPawnMoveLegal(board, org, des))
                return 0;
            break;
        case 'r':
        case 'R':
            if (!isRookMoveLegal(board, org, des))
                return 0;
            break;
        case 'n':
        case 'N':
            if (!isKnightMoveLegal(board, org, des))
                return 0;
            break;
        case 'b':
        case 'B':
            if (!isBishopMoveLegal(board, org, des))
                return 0;
            break;
        case 'k':
        case 'K':
            if (!isKingMoveLegal(board, org, des))
                return 0;
            break;
        case 'q':
        case 'Q':
            if (!isQueenMoveLegal(board, org, des))
                return 0;
            break;
    }
    if (isKingThreatened(board, org, des, userColor))
        return 0;
    return 1;
}

char getPiece(char** board, Location* loc){
    return *((*(board + (loc->x))) + loc->y);
}

boolean isLocationOutOfBounds(Location* des){
    return ((des->x < 8) && (des->x > -1) && (des->y < 8) && (des->y > -1) );
}

boolean isCoordinatesOutOfBounds(int x, int y){
    return isLocationOutOfBounds(createNewLocation(x,y));
}

boolean isLegalDesPiece(char** board, char orgPiece, Location* des, boolean userColor){
    char desPiece = getPiece(board,des);
    if (((getPieceColor(orgPiece) == 0) && (userColor == 1)) || ((getPieceColor(orgPiece) == 1) && (userColor == 0))) //if origion piece does not belong to user
        return 0;
    if (((getPieceColor(desPiece) == 0) && (userColor == 0)) || ((getPieceColor(desPiece) == 1) && (userColor == 1))) //if destenation piece belongs to user
        return 0;
    if (getPieceColor(orgPiece) == '_')//if origin piece is empty
        return 0;
    return 1;
}

int getPieceColor(char piece){
    if ((piece == 'm')||(piece == 'r')||(piece == 'n')||(piece == 'b')||(piece == 'k')||(piece == 'q'))
        return 0;
    if ((piece == 'M')||(piece == 'R')||(piece == 'N')||(piece == 'B')||(piece == 'K')||(piece == 'Q'))
        return 1;
    return EMPTY_PIECE;
}

boolean isWhitePawnMoveLegal(char** board, Location* org, Location* des) {
    char desPiece = getPiece(board,des);
    if (desPiece == '_' && org->y == des->y) { //move forward to an empty piece
        if ((org->x == 1) && (des->x == 3)) { //first move of pawn can be a double move
            return 1;
        }
        if (org->x+1 == des->x)
            return 1;
    }
    if ((org->x+1 == des->x)&&((org->y+1 == des->y)||(org->y-1 == des->y)))//eating move, color wise legal has been checked already
        return 1;
    return 0;

}

boolean isBlackPawnMoveLegal(char** board, Location* org, Location* des){
    char desPiece = getPiece(board,des);
    if (desPiece == '_' && org->y == des->y) { //move forward to an empty piece
        if ((org->x == 6) && (des->x == 5)) { //first move of pawn can be a double move
            return 1;
        }
        if (org->x-1 == des->x)
            return 1;
    }
    if ((org->x-1 == des->x)&&((org->y+1 == des->y)||(org->y-1 == des->y)))//eating move, color wise legal has been checked already
        return 1;
    return 0;

}
boolean isRookMoveLegal(char** board, Location* org, Location* des){
    if (org->x == des->x){
        for (int j = fmin(org->y,des->y)+1; j< fmax(org->y,des->y)-1; j++)
            if (!isCoordinatesEmpty(board, org->x, j))
             return -1;
    }
    if (org->y == des->y){
        for (int i = fmin(org->x,des->x)+1; i< fmax(org->x,des->x)-1; i++)
            if (!isCoordinatesEmpty(board, i, org->y))
                return -1;
    }
    return 0;

}
boolean isKnightMoveLegal(char** board, Location* org, Location* des){
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
boolean isBishopMoveLegal(char** board, Location* org, Location* des){
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
boolean isKingMoveLegal(char** board, Location* org, Location* des){
    if ((org->x != des->x) ||(org->y != des->y))
        return ((org->y == des->y)||(org->y+1 == des->y)||(org->y-1 == des->y)) && ((org->x == des->x)||(org->x+1 == des->x) || (org->x-1 == des->x));
    return 0;
}


boolean isQueenMoveLegal(char** board, Location* org, Location* des){
    return (isBishopMoveLegal(board,org,des) || isRookMoveLegal(board,org,des));
}

boolean isKingThreatened(char** board, Location* org, Location* des, boolean userColor){

}

Location* createNewLocation(int x, int y){
    Location* newLocation = (Location*) malloc(sizeof(Location));
    return newLocation;
}

boolean isCoordinatesEmpty(char** board, int x, int y){
    return ((getPiece(board,createNewLocation(x,y) == '_')));
}

int addInt(int a, int b) {
    return a+b;
}
int subInt(int a, int b) {
    return a-b;
}
boolean isBishopLegalDirection(char** board, Location* org, Location* des, int (*addOrSubX)(int,int), int (*addOrSubY)(int,int)){
    int i = 1;
    while (!isCoordinatesOutOfBounds(addOrSubX(org->x,i), addOrSubY(org->y,i)) && (addOrSubX(org->x,i) < des->x) && (addOrSubY(org->y,i) < des->y)) {//while ib bounds and not in destination row or column
        if (!isCoordinatesEmpty(board, addOrSubX(org->x, i), addOrSubY(org->y, i))) //if there is another piece in the way
            return 0;
        i++;
    }
    if ((addOrSubX(org->x,i) == des->x)&&(addOrSubY(org->y,i) == des->y))//if we reached destination piece
        return 1;
    else
        return 0;
}

boolean movePiece(char** board, Location org, Location des){

}