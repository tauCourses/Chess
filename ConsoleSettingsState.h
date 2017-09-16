#ifndef CHESS_CONSOLESETTINGSSTATE_H
#define CHESS_CONSOLESETTINGSSTATE_H

#include "GameManager.h"
#include "stdio.h"
#include "parser.h"

typedef enum SETTINGS_COMMAND_TYPE{
	SETTINGS_COMMAND_GAME_MODE, SETTINGS_COMMAND_DIFFICULTY ,SETTINGS_COMMAND_USER_COLOR,
	SETTINGS_COMMAND_LOAD, SETTINGS_COMMAND_DEFAULT_VALUES, SETTINGS_COMMAND_PRINT_SETTINGS,
	SETTINGS_COMMAND_QUIT, SETTINGS_COMMAND_START, SETTINGS_COMMAND_INVALID
} SETTINGS_COMMAND_TYPE;

typedef struct Settings{
	int gameMode;
	int difficulty;
	PLAYER_COLOR playerColor;
} Settings;

typedef struct SettingsCommand{
	SETTINGS_COMMAND_TYPE type;
    char* path;
    int value;
} SettingsCommand;


typedef enum SETTINGS_INPUT_STATE{
	SETTINGS_INPUT_SETTINGS_STATE, SETTINGS_INPUT_GAME_STATE, SETTINGS_INPUT_GAME_QUIT
} SETTINGS_INPUT_STATE;


//define messages and errors to print TODO -> SHOULD NOT BE HERE! FOR SURE!
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
#define ERR_IN_WRITING_TO_FILE "ERROR: in writing to file (file does exists)"

Settings* createSettings();

void destroySettings(Settings* settings);

void resetSettings(Settings* settings);

SettingsCommand getSettingsCommandFromUser();

SETTINGS_INPUT_STATE executeSettingsCommand(GameManager** game, SettingsCommand SCommand, Settings* settings);

SettingsCommand ParseSettingsLine(const char* str);

SETTINGS_COMMAND_TYPE settingsCommandFromStr(char* token);

void parseSettingsCommandWithInt(SettingsCommand* result, const char* token,const char delimeter[]);

void parseSettingsCommandWithPath(SettingsCommand* result, const char* token,const char delimeter[]);


void executeCommandGameMode(SettingsCommand SCommand, Settings* settings);

void executeCommandDifficulty(SettingsCommand SCommand, Settings* settings);

void executeCommandUserColor(SettingsCommand SCommand, Settings* settings);

void executeCommandLoad(GameManager** game, SettingsCommand SCommand);

void executeCommandDefaultValues(Settings* settings);

void executeCommandPrintSettings(Settings* settings);

void executeCommandStart(GameManager** game, Settings* settings);



#endif //CHESS_CONSOLESETTINGSSTATE_H
