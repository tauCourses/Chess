#include "gameTests.h"

int runLegalMovesTests(){
    Game* game = createNewGame(1,1,0);
    removePawns(game);
    bool userColor = 1;
    bool x;
    Location* des;

    Location* org = createNewLocation(1,1);
    char PieceToCheck = 'M';
    game->board[org->x][org->y] = PieceToCheck; //put this in comment if want to check without putting new piece in Location

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            des = createNewLocation(i,j);
            x = isMoveLegal(game->board,org, des, userColor);
            printf(x ? "*** true ****\n" : "false\n");
        }
    }

    //out of bounds
    des = createNewLocation(0,8);
    x = isMoveLegal(game->board,org, des, userColor);
    printf(x ? "true\n" : "false\n");
    des = createNewLocation(8,7);
    x = isMoveLegal(game->board,org, des, userColor);
    printf(x ? "true\n" : "false\n");
    des = createNewLocation(-1,1);
    x = isMoveLegal(game->board,org, des, userColor);
    printf(x ? "true\n" : "false\n");
    des = createNewLocation(0,-1);
    x = isMoveLegal(game->board,org, des, userColor);
    printf(x ? "true\n" : "false\n");


    return 1;
}

void removePawns(Game* game){
    printf("      ---NO PAWNS---\n");
    for (int i=1; i<7; i=i+5){
        for (int j=0; j<8; j++){
            game->board[i][j] = '_';
        }
    }
}