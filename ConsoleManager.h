#ifndef CHESS_MAINCONSOLE_H
#define CHESS_MAINCONSOLE_H

#include <stdio.h>
#include "ConsoleGameState.h"
#include "ConsoleSettingsState.h"

/**
 * Consolemanager summary:
 * Handles the whole console when program is run in console mode.
 */

typedef enum INPUT_STATE{
	INPUT_SETTINGS_STATE, INPUT_GAME_STATE, INPUT_GAME_QUIT
} INPUT_STATE;

/**
 *  the console main function that handles every event until program terminates.
 *  @param none
 *  @return 1 in case of success(no error), 0 otherwise.
 */
int mainConsole();
/**
 *  run the function that belongs to user move.
 *  @param game - the game to execute the game on.
 *  GCommand - the command to be updated and execute.
 *  setting - current setting of game.
 *  @return the next state of console.
 */
GAME_INPUT_STATE makeUserMove(GameManager** game, GameStateCommand** GCommand, Settings** settings);
/**
 *  updates the game input state according to last command result from setting state.
 *  @param settingsInputState - the setting next input state
 *  @return the next state of console.
 */
INPUT_STATE updateInputStateSetting(SETTINGS_INPUT_STATE settingsInputState);
/**
 *  updates the game input state according to last command result from game state.
 *  @param settingsInputState - the setting next input state
 *  @return the next state of console.
 */
INPUT_STATE updateInputStateGame(GAME_INPUT_STATE gameInputState);


#endif //CHESS_MAINCONSOLE_H
