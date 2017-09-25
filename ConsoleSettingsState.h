#ifndef CHESS_CONSOLESETTINGSSTATE_H
#define CHESS_CONSOLESETTINGSSTATE_H

#include <stdio.h>
#include "GameManager.h"
#include "Storage.h"
#include "Parser.h"

/**
 * ConsoleGameState summary:
 * Handles the console setting state.
 */

typedef enum SETTINGS_COMMAND_TYPE{
	SETTINGS_COMMAND_GAME_MODE, SETTINGS_COMMAND_DIFFICULTY ,SETTINGS_COMMAND_USER_COLOR,
	SETTINGS_COMMAND_LOAD, SETTINGS_COMMAND_DEFAULT_VALUES, SETTINGS_COMMAND_PRINT_SETTINGS,
	SETTINGS_COMMAND_QUIT, SETTINGS_COMMAND_START, SETTINGS_COMMAND_INVALID
} SETTINGS_COMMAND_TYPE;

typedef struct Settings{
	GAME_MODE gameMode;
	int difficulty;
	PLAYER_COLOR playerColor;
} Settings;

typedef struct SettingsCommand{
	SETTINGS_COMMAND_TYPE type;
    char path[MAX_LINE_LENGTH];
    int value;
} SettingsCommand;


typedef enum SETTINGS_INPUT_STATE{
	SETTINGS_INPUT_SETTINGS_STATE, SETTINGS_INPUT_GAME_STATE, SETTINGS_INPUT_GAME_QUIT
} SETTINGS_INPUT_STATE;


//define messages and errors to print
#define MSG_SETTING_BEGIN "Specify game setting or type 'start' to begin a game with the current setting:\n"
#define MSG_GAME_MODE_1 "Game mode is set to 1 player\n"
#define MSG_GAME_MODE_2 "Game mode is set to 2 players\n"
#define MSG_GAME_MODE_WRONG "Wrong game mode\n"
#define MSG_EXPERT_NOT_SUPPORTED "Expert level not supported, please choose a value between 1 to 4:\n"
#define MSG_WRONG_DIFFICULTY "Wrong difficulty level. The value should be between 1 to 5\n"
#define MSG_QUIT "Exiting...\n"
#define MSG_INVALID_IN_SETTINGS "Invalid command\n"

#define ERR_FILE_CANNOT_OPEN_DONT_EXISTS "Error: File does not exist or cannot be opened\n"
#define ERR_MALLOC "ERROR: in allocating memory\n"
#define ERR_FGETS "ERROR: in receiving user input\n"

/**
 *  create new setting struct
 *  @param none
 *  @return new default setting
 */
Settings* createSettings();
/**
 *  destroy new setting struct
 *  @param settings - the settings to be destroyed.
 *  @return none
 */
void destroySettings(Settings* settings);
/**
 *  reset setting to default
 *  @param settings - the settings to be reset.
 *  @return none
 */
void resetSettings(Settings* settings);
/**
 *  get a command from the user in setting state mode.
 *  @param SCommand - the command to be updated.
 *  @return void
 */
void getSettingsCommandFromUser(SettingsCommand** SCommand);
/**
 *  execute a command from the user in setting state mode.
 *  @param game - the game to execute the game on.
 *  SCommand - the command to be execute.
 *  setting - current setting.
 *  @return the next state of console.
 */
SETTINGS_INPUT_STATE executeSettingsCommand(GameManager** game, SettingsCommand* SCommand, Settings* settings);
/**
 *  parse a command from the user in setting state mode.
 *  @param str - the input from the user
 *  @return the command from user.
 */
SettingsCommand* ParseSettingsLine(const char* str);
/**
 *  parse a command type from the user in setting state mode.
 *  @param token - the part of input from the user with command type.
 *  @return the command type from user.
 */
SETTINGS_COMMAND_TYPE settingsCommandFromStr(char* token);
/**
 *  parse a command with int parameter from the user in setting state mode.
 *  @param token - the part of input from the user with int.
 *  result - the command up be updated.
 *  delimeter - the delimeter in command.
 *  @return void
 */
void parseSettingsCommandWithInt(SettingsCommand* result, const char* token,const char delimeter[]);
/**
 *  parse a command with path parameter from the user in setting state mode.
 *  @param token - the part of input from the user with int.
 *  result - the command up be updated.
 *  delimeter - the delimeter in command.
 *  @return void
 */
void parseSettingsCommandWithPath(SettingsCommand* result, const char* token, const char delimeter[]);

/**
 *  execute a game_mode command from the user in setting state mode.
 *  @param
 *  SCommand - the command to be execute.
 *  setting - current setting.
 *  @return void
 */
void executeCommandGameMode(SettingsCommand* SCommand, Settings* settings);
/**
 *  execute a difficulty command from the user in setting state mode.
 *  @param
 *  SCommand - the command to be execute.
 *  setting - current setting.
 *  @return void
 */
void executeCommandDifficulty(SettingsCommand* SCommand, Settings* settings);
/**
 *  execute a user_color command from the user in setting state mode.
 *  @param
 *  SCommand - the command to be execute.
 *  setting - current setting.
 *  @return void
 */
void executeCommandUserColor(SettingsCommand* SCommand, Settings* settings);
/**
 *  execute a load command from the user in setting state mode.
 *  @param
 *  SCommand - the command to be execute.
 *  setting - current setting.
 *  @return void
 */
bool executeCommandLoad(GameManager** game, SettingsCommand* SCommand, Settings* settings);
/**
 *  execute a default command from the user in setting state mode.
 *  @param
 *  SCommand - the command to be execute.
 *  setting - current setting.
 *  @return void
 */
void executeCommandDefaultValues(Settings* settings);
/**
 *  execute a print_setting command from the user in setting state mode.
 *  @param
 *  SCommand - the command to be execute.
 *  setting - current setting.
 *  @return void
 */
void executeCommandPrintSettings(Settings* settings);
/**
 *  execute a start command from the user in setting state mode.
 *  @param
 *  SCommand - the command to be execute.
 *  setting - current setting.
 *  @return void
 */
void executeCommandStart(GameManager** game, Settings* settings);



#endif //CHESS_CONSOLESETTINGSSTATE_H
