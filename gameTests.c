#include "gameTests.h"

int runLegalMovesTests(){
    Game* game = createNewGame(1,1,0);
    printBoard(game->board);
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
            x = movePiece(game,org,des,userColor);
            if (x)
                printf("*** true **** moved from from (%d,%d) to (%d,%d):\n",org->x,org->y,i,j);
            else
                printf("false\n");
        }
    }
    printBoard(game->board);
    org = newLocation(0,0);
    des = newLocation(4,0);
    movePiece(game,org,des,userColor);
    printBoard(game->board);

    printf("%c",1+'A');
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

void runMoveTests() {
    Game *game = createNewGame(1, 1, 0);
    printBoard(game->board);
    bool userColor = WHITE;
    bool x;

    removePawns(game);

    Location *org = newLocation(0, 2);
    Location *des = newLocation(4,6);

    printBoard(game->board);
    movePiece(game,org,des,userColor);
    printBoard(game->board);
    printf("is king threatend? - %d\n",isKingThreatened(game,BLACK));
    org = newLocation(4,6);
    des = newLocation(7,3);
    movePiece(game,org,des,userColor);
    printBoard(game->board);
}

void runArrayListTests(){
    SPArrayList* list = spArrayListCreate(4);
    Location* loc1 = newLocation(1,1);
    Location* loc2 = newLocation(2,2);
    Location* loc3 = newLocation(3,3);
    Location* loc4 = newLocation(4,4);
    Location* loc5 = newLocation(5,5);

    spArrayListPrint(list);
    spArrayListPush(list, loc1);
    //spArrayListAddLast(list, loc1);
    spArrayListPrint(list);
    //spArrayListAddLast(list, loc2);
    spArrayListPush(list, loc2);
    spArrayListPrint(list);
    spArrayListPop(list);
    spArrayListPrint(list);
    printf("Is list empty? %d\n", spArrayListIsEmpty(list));
    spArrayListPop(list);
    printf("Is list empty? %d\n", spArrayListIsEmpty(list));
}

void runGamePlayTests() {
    Game *game = createNewGame(1, 1, 0);
    printBoard(game->board);
    bool userColor = WHITE;
    bool x;

    removePawns(game);

    Location *org = newLocation(0, 2);
    Location *des = newLocation(4,6);

    printBoard(game->board);
   // movePiece(game,org,des,userColor);
   // printBoard(game->board);
    //printf("is Check for black? - %d\n",isKingThreatened(game,BLACK));
   // printf("is checkOrTie for black? - %d\n",isCheckmateOrTie(game,BLACK));
    org = newLocation(7,7);
    des = newLocation(6,7);
    movePiece(game,org,des,enemysColor(userColor));
    printBoard(game->board);

    org = newLocation(6,7);
    des = newLocation(6,3);
    movePiece(game,org,des,enemysColor(userColor));
    printBoard(game->board);
    printf("is Check for black? - %d\n",isKingThreatened(game,BLACK));
    printf("is checkOrTie for black? - %d\n",isCheckmateOrTie(game,BLACK));

    org = newLocation(0,2);
    des = newLocation(4,6);
    movePiece(game,org,des,userColor);
    printBoard(game->board);
    printf("is Check for black? - %d\n",isKingThreatened(game,BLACK));
    printf("is checkOrTie for black? - %d\n",isCheckmateOrTie(game,BLACK));

}