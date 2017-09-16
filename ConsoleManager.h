#ifndef CHESS_MAINCONSOLE_H
#define CHESS_MAINCONSOLE_H

#include "GameManager.h"
#include "stdio.h"
#include "Parser.h"
#include "ConsoleGameState.h"
#include "ConsoleSettingsState.h"
#include "Location.h"

typedef enum INPUT_STATE{
	INPUT_SETTINGS_STATE, INPUT_GAME_STATE, INPUT_GAME_QUIT
} INPUT_STATE;

int mainConsole();

void printBoard(Board board);

void executeCommandInvalid();


#endif //CHESS_MAINCONSOLE_H
