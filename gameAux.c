#include "gameAux.h"

Location* newLocation(int x, int y){
    Location* newLocation = (Location*) malloc(2*sizeof(int));
    newLocation->x = x;
    newLocation->y = y;
    return newLocation;
}

void destroyLocation(void* loc){
    free((Location*)loc);
}

void printLocation(void* loc){
    printf("<%d,%c> ",((Location*)loc)->x,((Location*)loc)->y+'A');
}

State* createNewState(){
    State* state = malloc(sizeof(*state));
    state->board = createNewBoard();
    state->WKingLoc = newLocation(0,3);
    state->BKingLoc = newLocation(7,3);
    state->currentPlayer = WHITE;
    state->hasWKingMoved = 0;
    state->hasBKingMoved = 0;
}

State* duplicateState(State* state){
    State* newCopy = createNewState();

    memcpy(newCopy->board[0], state->board[0], sizeof(char) * 8 * 8);
    newCopy->WKingLoc = newLocation(state->WKingLoc->x,state->WKingLoc->y);
    newCopy->BKingLoc = newLocation(state->BKingLoc->x,state->BKingLoc->y);
    newCopy->hasBKingMoved = state->hasBKingMoved;
    newCopy->hasWKingMoved = state->hasWKingMoved;
    newCopy->currentPlayer = state->currentPlayer;

    return newCopy;
}

void destroyState(void* state){
    printf("1");
    destroyBoard(((State*)state)->board);
    printf("2");

    printf("%d", (((State*)state)->BKingLoc));

    destroyLocation(((State*)state)->BKingLoc);
    printf("3");
    destroyLocation(((State*)state)->WKingLoc);
    printf("4");
    free(((State*)state));
    printf("5");
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
    if (board != NULL){
        free(board[0]);
        free(board);
    }
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


//History* newHistory(){
//    History* history = malloc(sizeof(History));
//    history->locations = spArrayListCreate(historySize*2);
//    history->pieces = calloc(historySize*2, sizeof(char));
//    return history;
//}
//
//void destroyHistory(History* history){
//    if (history->locations != NULL)
//        spArrayListDestroy(history->locations);
//    free(history->pieces);
//}

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

bool enemysColor(bool currentPlayerColor){
    return (currentPlayerColor ? 0 : 1);
}

void updateHistory(Game* game){
    //should enter current state to history list, and move on. copy is done inside list and also free memory.
    genericArrayListPush(game->historyStates,duplicateState(game->state));
}

void updateKingLocation(Game* game, char orgPiece, Location* des){
    if (orgPiece == 'k')
        game->state->WKingLoc = des;
    if (orgPiece == 'K')
        game->state->BKingLoc = des;
}

//in destroy game should destory each state in history. should destory state on every pop.