#include "GameBoard.h"

Location* createLocation(int x, int y)
{
    Location* loc = (Location*) malloc(sizeof(Location));
    if(loc == NULL)
        return NULL;
    loc->x = x;
    loc->y = y;
    return loc;
}

Location* duplicateLocation(Location* location)
{
    Location* loc = (Location*) malloc(sizeof(Location));
    if(loc == NULL)
        return NULL;
    loc->x = location->x;
    loc->y = location->y;
    return loc;
}
void destroyLocation(Location* loc)
{
    free(loc);
}

void setInitialBoard(Board board)
{
    //WHITE PIECES:
    board[0][0] = WHITE_ROOK_SYMBOL;
    board[0][7] = WHITE_ROOK_SYMBOL;
    board[0][1] = WHITE_KNIGHT_SYMBOL;
    board[0][6] = WHITE_KNIGHT_SYMBOL;
    board[0][2] = WHITE_BISHOP_SYMBOL;
    board[0][5] = WHITE_BISHOP_SYMBOL;
    board[0][4] = WHITE_KING_SYMBOL;
    board[0][3] = WHITE_QUEEN_SYMBOL;
    for(int y=0;y<CHESS_BOARD_SIZE; ++y) //set white pawns line
        board[1][y] = WHITE_PAWN_SYMBOL;

    //EMPTY GAP:
    for(int x=2;x<6;++x) //set empty gap
        for(int y=0;y<CHESS_BOARD_SIZE;++y)
            board[x][y] = EMPTY_PLACE_SYMBOL;

    //BLACK PIECES:
    for(int y=0;y<CHESS_BOARD_SIZE; ++y) //set black pawns line
        board[6][y] = BLACK_PAWN_SYMBOL;
    board[7][0] = BLACK_ROOK_SYMBOL;
    board[7][7] = BLACK_ROOK_SYMBOL;
    board[7][1] = BLACK_KNIGHT_SYMBOL;
    board[7][6] = BLACK_KNIGHT_SYMBOL;
    board[7][2] = BLACK_BISHOP_SYMBOL;
    board[7][5] = BLACK_BISHOP_SYMBOL;
    board[7][4] = BLACK_KING_SYMBOL;
    board[7][3] = BLACK_QUEEN_SYMBOL;
}

bool isPieceMoveLegal(Board board, Location* org, Location* des)
{
    switch(board[org->x][org->y])
    {
        case WHITE_PAWN_SYMBOL:
            return isWhitePawnMoveLegal(board, org, des);
            break;
        case BLACK_PAWN_SYMBOL:
            return isBlackPawnMoveLegal(board, org, des);
        case WHITE_ROOK_SYMBOL:
        case BLACK_ROOK_SYMBOL:
            return isRookMoveLegal(board, org, des);
            break;
        case WHITE_KNIGHT_SYMBOL:
        case BLACK_KNIGHT_SYMBOL:
            return isKnightMoveLegal(org, des);
            break;
        case WHITE_BISHOP_SYMBOL:
        case BLACK_BISHOP_SYMBOL:
            return isBishopMoveLegal(board, org, des);
            break;
        case WHITE_KING_SYMBOL:
        case BLACK_KING_SYMBOL:
            return isKingMoveLegal(board, org, des);
            break;
        case WHITE_QUEEN_SYMBOL:
        case BLACK_QUEEN_SYMBOL:
            return isQueenMoveLegal(board, org, des);
            break;
        default:
            return false;
    }
    return false;
}

bool isLegalDesPiece(Board board, char orgPiece, char desPiece)
{
    PLAYER_COLOR desPieceColor = getPieceColor(desPiece);
    PLAYER_COLOR orgPieceColor = getPieceColor(orgPiece);
    if (orgPieceColor == desPieceColor)
        return false;
    else if (orgPieceColor == NONE_PLAYER_COLOR)
        return false;
    return true;
}

bool isWhitePawnMoveLegal(Board board, Location* org, Location* des) {
    char desPiece = board[des->x][des->y];
    if (desPiece == EMPTY_PLACE_SYMBOL && org->y == des->y) //move forward to an empty piece
    {
        if (org->x == 1 && des->x == 3 &&  //first move of pawn can be a double move
            board[2][des->y] == EMPTY_PLACE_SYMBOL) //the middle square have to be empty as well)
            return true;

        if (org->x+1 == des->x )
            return true;
    }
    if (desPiece != EMPTY_PLACE_SYMBOL && org->x+1 == des->x && (org->y+1 == des->y || org->y-1 == des->y))//eating move, piece color was checked in isLegalDesPiece
        return true;
    return false;

}

bool isBlackPawnMoveLegal(Board board, Location* org, Location* des){
    char desPiece = board[des->x][des->y];
    if (desPiece == EMPTY_PLACE_SYMBOL && org->y == des->y) { //move forward to an empty piece
        if (org->x == 6 && des->x == 4 &&
            board[5][des->y] == EMPTY_PLACE_SYMBOL )//the middle square have to be empty as well))  //first move of pawn can be a double move
            return true;

        if (org->x-1 == des->x)
            return true;
    }
    if (desPiece != EMPTY_PLACE_SYMBOL && org->x-1 == des->x && (org->y+1 == des->y||org->y-1 == des->y))//eating move, color wise legal has been checked already
        return true;
    return false;

}

bool isRookMoveLegal(Board board, Location* org, Location* des)
{
    if (org->x == des->x)
    {
        for (int i = MIN(org->y,des->y)+1; i< MAX(org->y,des->y); i++)
            if (board[org->x][i] != EMPTY_PLACE_SYMBOL)
                return false;

        return true;
    }
    if (org->y == des->y)
    {
        for (int i = MIN(org->x, des->x) + 1; i < MAX(org->x, des->x); i++) {
            if (board[i][org->y] != EMPTY_PLACE_SYMBOL)
                return false;
        }
        return true;
    }
    return false;

}

bool isKnightMoveLegal(Location* org, Location* des){
    if ((org->x + 2 == des->x && org->y + 1 == des->y) ||
        (org->x + 1 == des->x && org->y + 2 == des->y) ||
        (org->x - 1 == des->x && org->y + 2 == des->y) ||
        (org->x - 2 == des->x && org->y + 1 == des->y) ||
        (org->x - 2 == des->x && org->y - 1 == des->y) ||
        (org->x - 1 == des->x && org->y - 2 == des->y) ||
        (org->x + 1 == des->x && org->y - 2 == des->y) ||
        (org->x + 2 == des->x && org->y - 1 == des->y) )
        return true;
    return false;
}

/*LOCAL FUNCTION FOR BISHOP MOVE ONLY*/
int addInt(int a, int b) {
    return a+b;
}
int subInt(int a, int b) {
    return a-b;
}

bool isBishopMoveLegal(Board board, Location* org, Location* des){
    if (org->x < des->x && org->y < des->y)
        return (isBishopLegalDirection(board, org, des, &addInt, &addInt));

    if (org->x < des->x && org->y > des->y)
        return (isBishopLegalDirection(board, org, des, &addInt, &subInt));

    if (org->x > des->x && org->y > des->y)
        return (isBishopLegalDirection(board, org, des, &subInt, &subInt));

    if (org->x > des->x && org->y < des->y)
        return (isBishopLegalDirection(board, org, des, &subInt, &addInt));

    return false;
}

bool isBishopLegalDirection(Board board, Location* org, Location* des, int (*addOrSubX)(int,int), int (*addOrSubY)(int,int)){
    int i = 1;
    while (!isCoordinatesOutOfBounds(addOrSubX(org->x,i), addOrSubY(org->y,i)) &&
           (addOrSubX(org->x,i) != des->x) && (addOrSubY(org->y,i) != des->y))
    {//while in bounds and not in destination row or column
        if (board[addOrSubX(org->x, i)][addOrSubY(org->y, i)] != EMPTY_PLACE_SYMBOL) //if there is another piece in the way
            return false;
        i++;
    }
    if (addOrSubX(org->x,i) == des->x && addOrSubY(org->y,i) == des->y)//if we reached destination piece
        return true;
    else
        return false;
}

bool isKingMoveLegal(Board board, Location* org, Location* des)
{
    if (org->x != des->x || org->y != des->y)
        return (org->y == des->y || org->y+1 == des->y || org->y-1 == des->y) &&
               (org->x == des->x || org->x+1 == des->x || org->x-1 == des->x);

    return false;
}

bool isQueenMoveLegal(Board board, Location* org, Location* des)
{
    return (isBishopMoveLegal(board,org,des) || isRookMoveLegal(board,org,des));
}


PLAYER_COLOR getPieceColor(char piece)
{
    if (piece >'a' && piece<'z')
        return WHITE_PLAYER;
    else if (piece > 'A' && piece < 'Z')
        return BLACK_PLAYER;
    return NONE_PLAYER_COLOR;
}

int compareLocations(const void * item1, const void * item2)
{
    Location* loc1 = (Location*)item1;
    Location* loc2 = (Location*)item2;
    if (loc1->x > loc2->x)
        return 1;

    if (loc1->x == loc2->x)
        return loc1->y - loc2->y;

    return -1;
}

bool isCoordinatesOutOfBounds(int x, int y)
{
    return x<0 || y<0 || x >= CHESS_BOARD_SIZE | y >= CHESS_BOARD_SIZE;
}

PLAYER_COLOR oppositeColor(PLAYER_COLOR currentPlayerColor)
{
    if(currentPlayerColor == WHITE_PLAYER)
        return BLACK_PLAYER;
    if(currentPlayerColor == BLACK_PLAYER)
        return WHITE_PLAYER;
    return NONE_PLAYER_COLOR;
}

