#ifndef CHESS_GAMEBOARD_H
#define CHESS_GAMEBOARD_H

#include <stdlib.h>
#include <stdbool.h>
#include "Location.h"
/**
 * GameBoard summary:
 * Handles all the board relavent functions and defintions.
 */
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

/**
 *  Macro for max function between 2 ints.
 */
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
/**
 *  Macro for min function between 2 ints.
 */
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

typedef enum {BLACK_PLAYER, WHITE_PLAYER, NONE_PLAYER_COLOR} PLAYER_COLOR;

typedef char Board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];

/**
 *  set the initial board for start game.
 *  @param board - the board to be reset.
 *  @return void
 */
void setInitialBoard(Board board);
/**
 *  checks if certain move is legal in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isPieceMoveLegal(Board board, Location* org, Location* des);
/**
 *  checks if destination location is legal in current board.
 *  @param board - the board.
 *  orgPiece - original piece
 *  des - desired destination piece.
 *  @return true if legal, false otherwise.
 */
bool isLegalDesPiece(Board board, char orgPiece, char desPiece);

/**
 *  checks if white pawn move is legal in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isWhitePawnMoveLegal(Board board, Location* org, Location* des);
/**
 *  checks if black pawn move is legal in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isBlackPawnMoveLegal(Board board, Location* org, Location* des);
/**
 *  checks if rook move is legal in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isRookMoveLegal(Board board, Location* org, Location* des);
/**
 *  checks if knight move is legal in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isKnightMoveLegal(Location* org, Location* des);
/**
 *  does mathmetical add between two int's. for bishop move calculation
 *  @param a - first number
 *  b - second number
 *  @return the addtion of a+b
 */
int addInt(int a, int b); /*for bishop move calc*/
/**
 *  does mathmetical subtruct between two int's. for bishop move calculation
 *  @param a - first number
 *  b - second number
 *  @return the subtruct of a-b
 */
int subInt(int a, int b);
/**
 *  checks if bishop move is legal in certain direction in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isBishopLegalDirection(Board state, Location* org, Location* des, int (*addOrSubX)(int,int), int (*addOrSubY)(int,int));
/**
 *  checks if bishop move is legal in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isBishopMoveLegal(Board board, Location* org, Location* des);
/**
 *  checks if king move is legal in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isKingMoveLegal(Board board, Location* org, Location* des);
/**
 *  checks if queen move is legal in current board.
 *  @param board - the board.
 *  org - original location of piece
 *  des - desired destination location of piece.
 *  @return true if legal, false otherwise.
 */
bool isQueenMoveLegal(Board board, Location* org, Location* des);

/**
 *  checks if coordinates are out of bounds.
 *  @param x - coordinate of line
 *  y - coordinate of column
 *  @return true if legal, false otherwise.
 */
bool isCoordinatesOutOfBounds(int x, int y);
/**
 *  returns the color of certain piece.
 *  @param piece - the piece to check color to.
 *  @return the color of piece
 */
PLAYER_COLOR getPieceColor(char piece);
/**
 *  returns opposite color.
 *  @param currentPlayerColor - the color to opposite.
 *  @return the opposite color of input color
 */
PLAYER_COLOR oppositeColor(PLAYER_COLOR currentPlayerColor);
/**
 *  checks if king is in certain location.
 *  @param board - the board.
 *  loc - location to check.
 *  @return true if king is in location, false otherwise.
 */
bool isKing(Board board, Location* loc);
/**
 *  prints to console the board.
 *  @param board - the board to print.
 *  @return void
 */
void printBoard(Board board);


#endif //CHESS_GAMEBOARD_H
