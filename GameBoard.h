#ifndef CHESS_GAMEBOARD_H
#define CHESS_GAMEBOARD_H

#include <stdlib.h>
#include <stdbool.h>
#include "Location.h"

#define EMPTY_PLACE_SYMBOL '_'

#define BLACK_PAWN_SYMBOL 'M'
#define BLACK_ROOK_SYMBOL 'R'
#define BLACK_KNIGHT_SYMBOL 'N'
#define BLACK_BISHOP_SYMBOL 'B'
#define BLACK_QUEEN_SYMBOL 'Q'
#define BLACK_KING_SYMBOL 'K'

#define WHITE_PAWN_SYMBOL 'm'
#define WHITE_ROOK_SYMBOL 'r'
#define WHITE_KNIGHT_SYMBOL 'n'
#define WHITE_BISHOP_SYMBOL 'b'
#define WHITE_QUEEN_SYMBOL 'q'
#define WHITE_KING_SYMBOL 'k'

#define CHESS_BOARD_SIZE 8

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

typedef enum {WHITE_PLAYER, BLACK_PLAYER, NONE_PLAYER_COLOR} PLAYER_COLOR;

typedef char Board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];


void setInitialBoard(Board board);

bool isPieceMoveLegal(Board board, Location* org, Location* des);
bool isLegalDesPiece(Board board, char orgPiece, char desPiece);

bool isWhitePawnMoveLegal(Board board, Location* org, Location* des);
bool isBlackPawnMoveLegal(Board board, Location* org, Location* des);
bool isRookMoveLegal(Board board, Location* org, Location* des);
bool isKnightMoveLegal(Location* org, Location* des);
int addInt(int a, int b); /*for bishop move calc*/
int subInt(int a, int b);
bool isBishopLegalDirection(Board state, Location* org, Location* des, int (*addOrSubX)(int,int), int (*addOrSubY)(int,int));
bool isBishopMoveLegal(Board board, Location* org, Location* des);
bool isKingMoveLegal(Board board, Location* org, Location* des);
bool isQueenMoveLegal(Board board, Location* org, Location* des);

bool isCoordinatesOutOfBounds(int x, int y);
int compareLocations(const void * item1, const void * item2);
PLAYER_COLOR getPieceColor(char piece);
PLAYER_COLOR oppositeColor(PLAYER_COLOR currentPlayerColor);


#endif //CHESS_GAMEBOARD_H
