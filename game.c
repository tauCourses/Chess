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
                    board[i][j] = 'p';

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
                    board[i][j] = 'P';
            }
            else {//blank pieces
                board[i][j] = '_';
            }
        }
    }
    return board;
}

boolean isMoveLegal(char** board, Location* org, Location* des, boolean userColor){
    char orgPiece = *((*(board+(org->x)))+org->y);
    char desPiece = *((*(board+(des->x)))+des->y);

    if (!(isMoveLegalColorWise(orgPiece,desPiece,userColor)))
        return 0;

    switch(orgPiece) {
        case 'p':
        case 'P':
            return isPawnMoveLegal(org, des);
        case 'r':
        case 'R':
            return isRookMoveLegal(org, des);
        case 'n':
        case 'N':
            return isKnightMoveLegal(org, des);
        case 'b':
        case 'B':
            return isBishopMoveLegal(org, des);
        case 'k':
        case 'K':
            return isKingMoveLegal(org, des);
        case 'q':
        case 'Q':
            return isQueenMoveLegal(org, des);
    }
}

boolean isMoveLegalColorWise(char orgPiece, char desPiece, boolean userColor){
    if (((getPieceColor(orgPiece) == 0) && (userColor == 1)) || ((getPieceColor(orgPiece) == 1) && (userColor == 0))) //if origion piece does not belong to user
        return 0;
    if (((getPieceColor(desPiece) == 0) && (userColor == 0)) || ((getPieceColor(desPiece) == 1) && (userColor == 1))) //if destenation piece belongs to user
        return 0;
    if (getPieceColor(orgPiece) == -1)//if origin piece is empty
        return 0;
    return 1;
}

int getPieceColor(char piece){
    if ((piece == 'p')||(piece == 'r')||(piece == 'n')||(piece == 'b')||(piece == 'k')||(piece == 'q'))
        return 0;
    if ((piece == 'P')||(piece == 'R')||(piece == 'N')||(piece == 'B')||(piece == 'K')||(piece == 'Q'))
        return 1;
    return -1;
}

boolean isPawnMoveLegal(Location* org, Location* des){
    
}
boolean isRookMoveLegal(Location* org, Location* des){

}
boolean isKnightMoveLegal(Location* org, Location* des){

}
boolean isBishopMoveLegal(Location* org, Location* des){

}
boolean isKingMoveLegal(Location* org, Location* des){

}
boolean isQueenMoveLegal(Location* org, Location* des){

}

boolean movePiece(char** board, Location org, Location des){

}