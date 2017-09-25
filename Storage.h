
#ifndef CHESS_STORAGE_H
#define CHESS_STORAGE_H


#include <stdio.h>
#include <string.h>
#include "GameManager.h"

/**
 * Storage summary:
 * a module that handle the save and load features related functions.
 */


#define MAX_NUMBER_OF_LOAD_GAMES 5
#define SlotBasicName "slot%d.xml"

/**
 *  saves a game to file
 *  @param game - the game to save
 *  filename - the file name to save the game to
 *  @return true is save successful, false otherwise
 */
bool saveGame(GameManager* game, char* filename);

/**
 *  saves a board to file
 *  @param file - the file to save
 *  state - the state that contains the board
 *  @return void
 */
void saveBoard(FILE* file, GameState* state);

/**
 *  check if file exists
 *  @param filename - file path to check if exists or readable
 *  @return true if file exists and readable, false otherwise
 */
bool isFileExist(char* filename);

/**
 *  loads a game from file
 *  @param
 *  filename - the file name to load the game from
 *  @return the game if loaded successfuly, null otherwise
 */
GameManager* loadGame(char* filename);


/**
 *  update game's castle state from file
 *  @param state - the state to update
 *  file - the file to update from
 *  @return true if updated successfully, false otherwise
 */
bool updateCastlesStateFromFile(GameState* state, FILE* file);
/**
 *  update game's general parameters from file
 *  @param game - the game to update
 *  file - the file to update from
 *  @return void
 */
void updateGameParams(GameManager* game, FILE* file);

/**
 *  reads the file until it reachs a certain character.
 *  @param c - the char that is search for
 *  file - the file to search ing
 *  @return the char c if found, EOF otherwise
 */
char waitForChar(FILE* file, char c);

/**
 *  update state's board from file
 *  @param state - the state to update
 *  file - the file to update from
 *  @return void
 */
void updateBoardFromFile(GameState* state, FILE* file);


/**
 *  adds game to game slots
 *  @param game - game to be added
 *  @return void
 */
void addGameToGameSlots(GameManager* game);

/**
 *  move game slots ahead.
 *  @param none
 *  @return void
 */
void moveSlots();

/**
 *  returns number of game slots
 *  @param none
 *  @return number of game slots
 */
int numberOfGameSlots();

/**
 *  load a game from a game slot
 *  @param num - number of game slot to load
 *  @return the game that was loaded
 */
GameManager* loadGameFromSlots(int num);

#endif //CHESS_STORAGE_H
