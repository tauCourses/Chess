//
// Created by LenovoPc on 27-Aug-17.
//

#ifndef CHESS_INFRASTRUCTURE_H
#define CHESS_INFRASTRUCTURE_H

#include <stdbool.h>
#include <stdlib.h>
#define historySize 3
#define EMPTY_PIECE '_'
#define WHITE 0
#define BLACK 1

typedef struct Location{
    int x,y;
} Location;

typedef struct sp_array_list_t {
    Location* elements;
    int actualSize;
    int maxSize;
} SPArrayList;

typedef struct generic_array_list_t {
    void** elements;
    int actualSize;
    int maxSize;
    size_t elementSize;
    void (*destroyElement)(void *);
} genericArrayList;

/**
 * A type used for errors
 */
typedef enum sp_array_list_message_t {
    SP_ARRAY_LIST_SUCCESS,
    SP_ARRAY_LIST_INVALID_ARGUMENT,
    SP_ARRAY_LIST_FULL,
    SP_ARRAY_LIST_EMPTY
} SP_ARRAY_LIST_MESSAGE;

//typedef struct game_history {
//    genericArrayList* states;
//    char* pieces;
//} History;

typedef struct State{
    char** board;
    bool currentPlayer;
    bool hasWKingMoved;
    bool hasBKingMoved;
    Location* WKingLoc;
    Location* BKingLoc;
} State;

typedef struct Game{
    State* state;
    int mode;
    int difficulty;
    bool userColor;
    genericArrayList* historyStates ;
} Game;




#endif //CHESS_INFRASTRUCTURE_H
