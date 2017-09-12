#ifndef CHESS_INFRASTRUCTURE_H
#define CHESS_INFRASTRUCTURE_H

#include <stdbool.h>
#include <stdlib.h>
#define historySize 3
#define EMPTY_PIECE '_'
#define WHITE 0
#define BLACK 1
#define MAX_LINE_LENGTH 1024
#define CHESS_BOARD_SIZE 8

typedef enum {
    CHESS_GAME_ONE_PLAYER, CHESS_GAME_TWO_PLAYERS
} CHESS_GAME_TYPES;

typedef enum {
    CHESS_GAME_PLAYER_COLOR_BLACK, CHESS_GAME_PLAYER_COLOR_WHITE, CHESS_GAME_PLAYER_COLOR_NONE
} CHESS_GAME_PLAYER_COLOR;

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

typedef struct{
    char** board;
    CHESS_GAME_PLAYER_COLOR currentPlayer;
    bool hasWKingMoved;
    bool hasBKingMoved;
    Location* WKingLoc;
    Location* BKingLoc;
} State;

typedef struct{
    State* state;
    CHESS_GAME_TYPES mode;
    int difficulty;
    CHESS_GAME_PLAYER_COLOR userColor;
    genericArrayList* historyStates ;
} Game;

typedef enum PlayerColor{white, black} PlayerColor;

typedef enum GameMode {onePlayer, twoPlayers} GameMode;

typedef enum InputState{settingState, gameState} InputState;

typedef enum CommandType{gameMode, difficutly,userColor, load, defaultValues, printSetting, quit, start, move,getPossibleMoves,save,undo,reset, invalid} CommandType;

//typedef enum GameCommand{quit} GameCommand;

typedef struct Command{
    CommandType type;
    int value;
    char* path;
    Location* org;
    Location* des;
} Command;


#endif //CHESS_INFRASTRUCTURE_H
