#ifndef CHESS_MAINCONSOLE_H
#define CHESS_MAINCONSOLE_H

#include <stdio.h>
#include "ConsoleGameState.h"
#include "ConsoleSettingsState.h"

typedef enum INPUT_STATE{
	INPUT_SETTINGS_STATE, INPUT_GAME_STATE, INPUT_GAME_QUIT
} INPUT_STATE;

int mainConsole();

void printBoard(Board board);

GAME_INPUT_STATE makeUserMove(GameManager** game, GameStateCommand* GCommand, Settings** settings);

INPUT_STATE updateInputStateSetting(SETTINGS_INPUT_STATE settingsInputState);

INPUT_STATE updateInputStateGame(GAME_INPUT_STATE gameInputState);


#endif //CHESS_MAINCONSOLE_H
