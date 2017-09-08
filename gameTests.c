#include "gameTests.h"

int runLegalMovesTests(){
    Game* game = createNewGame(1,1,0);
    printBoard(game->state->board);
    bool userColor = WHITE;
    bool x;
    Location* des;

    removePawns(game);

    Location* org = newLocation(0,1);

//    char PieceToCheck = 'K';
//    game->BKingLoc = org;


    //game->state->board[org->x][org->y] = PieceToCheck; //put this in comment if want to check without putting new piece in Location

    //moves org to all over the state->board
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
    printBoard(game->state->board);
    org = newLocation(0,0);
    des = newLocation(4,0);
    movePiece(game,org,des,userColor);
    printBoard(game->state->board);

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
            game->state->board[i][j] = '_';
        }
    }
}

void runMoveTests() {
    Game *game = createNewGame(1, 1, 0);
    printBoard(game->state->board);
    bool userColor = WHITE;
    bool x;

    removePawns(game);

    Location *org = newLocation(0, 2);
    Location *des = newLocation(4,6);

    printBoard(game->state->board);
    movePiece(game,org,des,userColor);
    printBoard(game->state->board);
    printf("is king threatend? - %d\n",isKingThreatened(game,BLACK));
    org = newLocation(4,6);
    des = newLocation(7,3);
    movePiece(game,org,des,userColor);
    printBoard(game->state->board);
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

void rungenericArrayListTests(){
    genericArrayList* list = genericArrayListCreate(4, sizeof(Location*), &free);
    Location* loc1 = newLocation(1,1);
    Location* loc2 = newLocation(2,2);
    Location* loc3 = newLocation(3,3);
    Location* loc4 = newLocation(4,4);
    Location* loc5 = newLocation(5,5);

    genericArrayListPrint(list, &printLocation);
    genericArrayListPush(list, loc1);
    //spArrayListAddLast(list, loc1);
    genericArrayListPrint(list, &printLocation);
    //spArrayListAddLast(list, loc2);
    genericArrayListPush(list, loc2);
    genericArrayListPrint(list, &printLocation);
    printf("this is <2,C> out of the stack:\n");
    printLocation(genericArrayListPop(list)) ;
    printf("\n");
    genericArrayListPrint(list, &printLocation);
    printf("Is list empty? %d\n", genericArrayListIsEmpty(list));
    genericArrayListPop(list);
    printf("Is list empty? %d\n", genericArrayListIsEmpty(list));

    //board list tests
    genericArrayList* list2 = genericArrayListCreate(2, sizeof(State*), &destroyState);
    State* sat1 = createNewState();
    State* sat2 = createNewState();
    State* sat3 = createNewState();

    printf("empty list: \n");
    genericArrayListPrint(list2, &printStateBoard);
    genericArrayListPush(list2, sat1);

    printf("1 board in list: \n");
    genericArrayListPrint(list2, &printStateBoard);
    genericArrayListPush(list2, sat2);

    printf("2 boards in lists: \n");
    genericArrayListPrint(list2, &printStateBoard);
}

void runGamePlayTests() {
    Game *game = createNewGame(1, 1, 0);
    printBoard(game->state->board);
    bool userColor = WHITE;
    bool x;

    removePawns(game);

    Location *org = newLocation(0, 2);
    Location *des = newLocation(4,6);

    printBoard(game->state->board);
   // movePiece(game,org,des,userColor);
   // printBoard(game->state->board);
    //printf("is Check for black? - %d\n",isKingThreatened(game,BLACK));
   // printf("is checkOrTie for black? - %d\n",isCheckmateOrTie(game,BLACK));
    org = newLocation(7,7);
    des = newLocation(6,7);
    movePiece(game,org,des,enemysColor(userColor));
    printBoard(game->state->board);

    org = newLocation(6,7);
    des = newLocation(6,3);
    movePiece(game,org,des,enemysColor(userColor));
    printBoard(game->state->board);
    printf("is Check for black? - %d\n",isKingThreatened(game,BLACK));
    printf("is checkOrTie for black? - %d\n",isCheckmateOrTie(game,BLACK));

    org = newLocation(0,1);
    des = newLocation(1,3);
    movePiece(game,org,des,WHITE);
    printBoard(game->state->board);


    undoMove(game);
    printBoard(game->state->board);


//    org = newLocation(0,2);
//    des = newLocation(5,7);
//    movePiece(game,org,des,userColor);
//    printBoard(game->state->board);
//    printf("is Check for WHITE? - %d\n",isKingThreatened(game,WHITE));
//    printf("is checkOrTie for WHITE? - %d\n",isCheckmateOrTie(game,WHITE));

}



void runUndoTest() {
    Game *game = createNewGame(1, 1, 0);
   // printBoard(game->state->board);
    bool userColor = WHITE;
    bool x;

    Location *org = newLocation(1,0);
    Location *des = newLocation(2,0);

    printf("\nUNDO move:\n");
    undoMove(game);

    movePiece(game,org,des,userColor);
    printBoard(game->state->board);

    org = newLocation(2,0);
    des = newLocation(3,0);
    movePiece(game,org,des,userColor);
    printBoard(game->state->board);

    printf("------This is the history of the game:-------\n");
    genericArrayListPrint(game->historyStates,&printStateBoard);

    org = newLocation(1,1);
    des = newLocation(2,1);
    movePiece(game,org,des,userColor);
    printBoard(game->state->board);

    printf("-----This is the history of the game:-------\n");
    genericArrayListPrint(game->historyStates,&printStateBoard);

    printf("\nUNDO move:\n");
    undoMove(game);

    printBoard(game->state->board);
}