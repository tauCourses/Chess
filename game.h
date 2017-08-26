
#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include <stdbool.h>
#include <stdlib.h>
//#include <rpcndr.h>
#include "SPArrayList.h"
#include "math.h"
#define historySize 3
#define EMPTY_PIECE '_'

typedef struct Location{
    int x,y;
} Location;

typedef struct Piece{
    char type;
    bool color;
    Location location;
} Piece;


typedef struct Game{
    char** board;
    int mode;
    int difficulty;
    char userColor;
    SPArrayList *history;
} Game;

Game* createNewGame(int mode, int difficulty, char userColor);

char** createNewBoard();

bool isMoveLegal(char** board, Location* org, Location* des, bool userColor);

char getPiece(char** board, Location* loc);

bool isLocationOutOfBounds(Location* des);

bool isCoordinatesOutOfBounds(int x, int y);

bool isLegalDesPiece(char** board, char orgPiece, Location* des, bool userColor);

int getPieceColor(char piece);

bool isWhitePawnMoveLegal(char** board, Location* org, Location* des);


bool isBlackPawnMoveLegal(char** board, Location* org, Location* des);

bool isRookMoveLegal(char** board, Location* org, Location* des);

bool isKnightMoveLegal(char** board, Location* org, Location* des);

bool isBishopMoveLegal(char** board, Location* org, Location* des);

bool isKingMoveLegal(char** board, Location* org, Location* des);

bool isQueenMoveLegal(char** board, Location* org, Location* des);

bool isKingThreatened(char** board, Location* org, Location* des, bool userColor);

Location* createNewLocation(int x, int y);

bool isCoordinatesEmpty(char** board, int x, int y);

int addInt(int a, int b);

int subInt(int a, int b);

bool isBishopLegalDirection(char** board, Location* org, Location* des, int (*addOrSubX)(int,int), int (*addOrSubY)(int,int));

bool movePiece(char** board, Location org, Location des);

#endif //CHESS_GAME_H
