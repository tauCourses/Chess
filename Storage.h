
#ifndef CHESS_STORAGE_H
#define CHESS_STORAGE_H


#include <stdio.h>
#include <string.h>
#include "Infrastructure.h"
#include "game.h"

#define MAX_NUMBER_OF_LOAD_GAMES 5
#define SlotBasicName "gameSlots/slot%d.xml"

bool saveGame(Game* game, char* filename);
void saveBoard(FILE* file, char** board);
bool isFileExist(char* filename);
Game* loadGame(char* filename);
void waitForChar(FILE* file, char c);
char** loadBoard(FILE* file);

void addGameToGameSlots(Game* game);
void moveSlots();
int numberOfGameSlots();
Game* loadGameFromSlots(int num);

#endif //CHESS_STORAGE_H
