
#ifndef CHESS_STORAGE_H
#define CHESS_STORAGE_H


#include <stdio.h>
#include <string.h>
#include "GameManager.h"

#define MAX_NUMBER_OF_LOAD_GAMES 5
#define SlotBasicName "gameSlots/slot%d.xml"

bool saveGame(GameManager* game, char* filename);
void saveBoard(FILE* file, GameState* state);
bool isFileExist(char* filename);
GameManager* loadGame(char* filename);
void updateGameParams(GameManager* game, FILE* file);
void waitForChar(FILE* file, char c);
void updateBoardFromFile(GameState* state, FILE* file);

void addGameToGameSlots(GameManager* game);
void moveSlots();
int numberOfGameSlots();
GameManager* loadGameFromSlots(int num);

#endif //CHESS_STORAGE_H
