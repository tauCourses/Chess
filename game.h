
#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include <stdbool.h>
#include <stdlib.h>
//#include <rpcndr.h>
#include "SPArrayList.h"
#include "math.h"
#define historySize 3
#define EMPTY_PIECE '_'
#define WHITE 0
#define BLACK 1

typedef struct Location{
    int x,y;
} Location;

//typedef struct Piece{
//    char type;
//    bool color;
//    Location location;
//} Piece;


typedef struct Game{
    char** board;
    int mode;
    int difficulty;
    bool userColor;
    SPArrayList *history;
    Location* WKingLoc;
    Location* BKingLoc;
} Game;

Game* createNewGame(int mode, int difficulty, bool userColor);

char** createNewBoard();

bool isMoveLegal(Game* game, Location* org, Location* des, bool currentPlayerColor);

char getPiece(char** board, Location* loc);

bool isLocationOutOfBounds(Location* des);

bool isCoordinatesOutOfBounds(int x, int y);

bool isLegalDesPiece(char** board, char orgPiece, char desPiece, bool currentPlayerColor);

int getPieceColor(char piece);

bool isWhitePawnMoveLegal(char** board, Location* org, Location* des);


bool isBlackPawnMoveLegal(char** board, Location* org, Location* des);

bool isRookMoveLegal(char** board, Location* org, Location* des);

bool isKnightMoveLegal(Location* org, Location* des);

bool isBishopMoveLegal(char** board, Location* org, Location* des);

bool isKingMoveLegal(char** board, Location* org, Location* des);

bool isQueenMoveLegal(char** board, Location* org, Location* des);

bool isKingThreatened(Game* game, bool currentPlayerColor);

Location* newLocation(int x, int y);

bool isCoordinatesEmpty(char** board, int x, int y);

int addInt(int a, int b);

int subInt(int a, int b);

bool isBishopLegalDirection(char** board, Location* org, Location* des, int (*addOrSubX)(int,int), int (*addOrSubY)(int,int));

bool movePiece(Game* game, Location* org, Location* des, bool currentPlayerColor);

int getPieceColorInCoordinates(Game* game, int x, int y);

#endif //CHESS_GAME_H
