#include "gameTests.h"

int runLegalMovesTests(){
    Game* game = createNewGame(1,1,0);
    bool userColor = WHITE;
    bool x;
    Location* des;

    removePawns(game);

    Location* org = newLocation(0,1);

//    char PieceToCheck = 'K';
//    game->BKingLoc = org;


    //game->board[org->x][org->y] = PieceToCheck; //put this in comment if want to check without putting new piece in Location

    //moves org to all over the board
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            des = newLocation(i,j);
            x = movePiece(game,org,des,userColor);;
            if (x)
                printf("*** true **** moved from from (%d,%d) to (%d,%d):\n",org->x,org->y,i,j);
            else
                printf("false\n");
        }
    }

/*  //checks legal moves for org
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            des = newLocation(i,j);
            x = isMoveLegal(game,org, des, userColor);
            printf(x ? "*** true ****\n" : "false\n");
        }
    }
*/
    //printf("is King threatend? %d\n", isKingThreatened(game,userColor));

    //out of bounds
//    des = newLocation(0,8);
//    x = isMoveLegal(game,org, des, userColor);
//    printf(x ? "true\n" : "false\n");
//    des = newLocation(8,7);
//    x = isMoveLegal(game,org, des, userColor);
//    printf(x ? "true\n" : "false\n");
//    des = newLocation(-1,1);
//    x = isMoveLegal(game,org, des, userColor);
//    printf(x ? "true\n" : "false\n");
//    des = newLocation(0,-1);
//    x = isMoveLegal(game,org, des, userColor);
//    printf(x ? "true\n" : "false\n");


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