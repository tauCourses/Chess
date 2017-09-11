
#ifndef CHESS_STORAGE_H
#define CHESS_STORAGE_H

#include "Infrastructure.h"
#include <stdio.h>
#include <string.h>

bool saveGame(Game* game, char* filename);
void saveBoard(FILE* file, char** board);
bool isFileExist(char* filename);
Game* loadGame(char* filename);
char** loadBoard(FILE* file);

#endif //CHESS_STORAGE_H
