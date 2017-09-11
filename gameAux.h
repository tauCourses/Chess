#ifndef CHESS_GAMEAUX_H
#define CHESS_GAMEAUX_H

#include "Infrastructure.h"
#include "SPArrayList.h"
#include "genericArrayList.h"
#include "StatesStack.h"


State* createNewState();

char** createNewBoard();

void destroyBoard(char** board);

void destroyState(void* state);

void destroyStatePointer(void** state);

char getPiece(char** board, Location* loc);

void setPiece(char** board, Location* loc, char newPiece);

char getPieceInCoordinates(char** board, int x, int y);

bool isLocationOutOfBounds(Location* des);

bool isCoordinatesOutOfBounds(int x, int y);

int getPieceColor(char piece);

Location* newLocation(int x, int y);

void destroyLocation(void* loc);

void destroyLocationPointer(void** loc);

int compareLocations(const void * item1, const void* item2);

void printLocation(void* loc);

//History* newHistory();

//void destroyHistory(History* history);

bool isCoordinatesEmpty(char** board, int x, int y);

int addInt(int a, int b);

int subInt(int a, int b);

int getPieceColorInCoordinates(char** board, int x, int y);

CHESS_GAME_PLAYER_COLOR oppositeColor(CHESS_GAME_PLAYER_COLOR currentPlayerColor);

void updateHistory(Game* game);

void updateKingLocation(Game* game, char orgPiece, Location* des);

State* duplicateState(State* state);


#endif //CHESS_GAMEAUX_H
