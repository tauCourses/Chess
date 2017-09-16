#include "ConsoleSettingsState.h"

Settings* createSettings()
{
	Settings* settings = (Settings*) malloc(sizeof(Settings));
	if (settings == NULL)
		printf(ERR_MALLOC);
	executeCommandDefaultValues(settings);
	return settings;
}

void destroySettings(Settings* settings)
{
	free(settings);
}

void resetSettings(Settings* settings)
{
	settings->difficulty = 2;
	settings->gameMode = 1;
	settings->playerColor = WHITE_PLAYER;
}

SettingsCommand getSettingsCommandFromUser()
{
	char input[MAX_LINE_LENGTH];
    fgets(input,MAX_LINE_LENGTH,stdin);

    if (input == NULL)//error in fgets
    {
        printf(ERR_FGETS);
        SettingsCommand errorCommand;
        errorCommand.type = SETTINGS_COMMAND_INVALID;
        return errorCommand;
    }
    return ParseSettingsLine(input);
}

SETTINGS_INPUT_STATE executeSettingsCommand(GameManager** game, SettingsCommand SCommand, Settings* settings)
{
	printf("TestPrint executeSettingsCommand: this is SCommand.type: |%d|\n", SCommand.type);
	switch (SCommand.type)
	{
	case SETTINGS_COMMAND_GAME_MODE:
		executeCommandGameMode(SCommand,settings);
		return SETTINGS_INPUT_SETTINGS_STATE;
	case SETTINGS_COMMAND_DIFFICULTY:
		executeCommandDifficulty(SCommand,settings);
		return SETTINGS_INPUT_SETTINGS_STATE;
	case SETTINGS_COMMAND_USER_COLOR:
		executeCommandUserColor(SCommand,settings);
		return SETTINGS_INPUT_SETTINGS_STATE;
	case SETTINGS_COMMAND_LOAD:
		executeCommandLoad(game,SCommand);
		return SETTINGS_INPUT_GAME_STATE;
	case SETTINGS_COMMAND_DEFAULT_VALUES:
		executeCommandDefaultValues(settings);
		return SETTINGS_INPUT_SETTINGS_STATE;
	case SETTINGS_COMMAND_PRINT_SETTINGS:
		executeCommandPrintSettings(settings);
		return SETTINGS_INPUT_SETTINGS_STATE;
	case SETTINGS_COMMAND_START:
		executeCommandStart(game,settings);
		return SETTINGS_INPUT_GAME_STATE;
	case SETTINGS_COMMAND_INVALID:
		printf(MSG_INVALID_IN_SETTINGS);
		return SETTINGS_INPUT_SETTINGS_STATE;
	case SETTINGS_COMMAND_QUIT:
		break;
	default:
		break;
	}
	return SETTINGS_COMMAND_INVALID;
}

SettingsCommand ParseSettingsLine(const char* str)
{
    const char delimeter[] = " \t\r\n";
    char line[MAX_LINE_LENGTH], *token;

    SettingsCommand result;
    strcpy(line, str);
    token = strtok(line, delimeter);

	printf("TestPrint ParseSettingsLine: this is token: |%s|\n", token);
    result.type = settingsCommandFromStr(token);
	printf("TestPrint ParseSettingsLine: this is ScommandType: |%d|\n", result.type);

    parseSettingsCommandWithInt(&result,token,delimeter);
    parseSettingsCommandWithPath(&result,token,delimeter);

    token = strtok(NULL, delimeter);
    if (token != NULL)
        result.type = SETTINGS_COMMAND_INVALID;

    return result;
}

void parseSettingsCommandWithInt(SettingsCommand* result, const char* token,const char delimeter[])
{
    if (result->type == SETTINGS_COMMAND_GAME_MODE || result->type == SETTINGS_COMMAND_DIFFICULTY ||
    		result->type == SETTINGS_COMMAND_USER_COLOR )
    {
        token = strtok(NULL, delimeter);
		printf("TestPrint parseSettingsCommandWithInt this isInt:%d\n", IsInt(token));
		if (IsInt(token)){
			result->value = atoi(token);
			printf("TestPrint parseSettingsCommandWithInt this is resulat.value:%d\n", result->value);
		}
        else
            result->type = SETTINGS_COMMAND_INVALID;
    }
}

void parseSettingsCommandWithPath(SettingsCommand* result, const char*  token,const char delimeter[]){
    if (result->type == SETTINGS_COMMAND_LOAD)
    {
        token = strtok(NULL, delimeter);
        result->path = (char*)token;
    }
}

SETTINGS_COMMAND_TYPE settingsCommandFromStr(char* token)
{
    if(token == NULL)
        return SETTINGS_COMMAND_INVALID;
	if(strcmp(token,"start") == 0)
		return SETTINGS_COMMAND_START;
	if(strcmp(token,"game_mode") == 0)
		return SETTINGS_COMMAND_GAME_MODE;
	if(strcmp(token,"difficulty") == 0)
        return SETTINGS_COMMAND_DIFFICULTY;
    if(strcmp(token,"user_color") == 0)
        return SETTINGS_COMMAND_USER_COLOR;
    if(strcmp(token,"load") == 0)
        return SETTINGS_COMMAND_LOAD;
    if(strcmp(token,"default") == 0)
        return SETTINGS_COMMAND_DEFAULT_VALUES;
    if(strcmp(token,"print_setting") == 0)
        return SETTINGS_COMMAND_PRINT_SETTINGS;

    if(strcmp(token,"quit") == 0)
        return SETTINGS_COMMAND_QUIT;

    return SETTINGS_COMMAND_INVALID;

}


void executeCommandGameMode(SettingsCommand SCommand, Settings* settings)
{
	if (SCommand.value == 1)
	{
		printf(MSG_GAME_MODE_1);
		settings->gameMode = 1;
		return;
	}
	if (SCommand.value == 2)
	{
		printf(MSG_GAME_MODE_2);
		settings->gameMode = 2;
		return;
	}
	printf(MSG_GAME_MODE_WRONG);
}

void executeCommandDifficulty(SettingsCommand SCommand, Settings* settings)
{
	printf("TestPrint executeCommandDifficulty: this SCommand type and value <%d,%d>\n",SCommand.type, SCommand.value);
	if (settings->gameMode == 1)
	{
		if (0 < SCommand.value && SCommand.value < 5)
		{
			if ( SCommand.value == 5)
				printf(MSG_EXPERT_NOT_SUPPORTED);
			else
				settings->difficulty = SCommand.value;
		}
		else
			printf(MSG_WRONG_DIFFICULTY);
	}
	else
		printf(MSG_INVALID_IN_SETTINGS);
}

void executeCommandUserColor(SettingsCommand SCommand, Settings* settings)
{
	if (settings->gameMode == 1)
	{
		if (SCommand.value == 0)
			settings->playerColor = BLACK_PLAYER;
		if (SCommand.value == 1)
			settings->playerColor = WHITE_PLAYER;
		if (SCommand.value != 0 && SCommand.value != 1)
			printf(MSG_INVALID_IN_SETTINGS);
	}
	else
		printf(MSG_INVALID_IN_SETTINGS);
}

void executeCommandLoad(GameManager** game, SettingsCommand SCommand)
{
	if (isFileExist(SCommand.path))
	{
		GameManager* newGame = loadGame(SCommand.path);
		if (newGame != NULL)
		{
			destroyGame(*game);
			*game = newGame;
		}
		else
			printf(ERR_IN_WRITING_TO_FILE);
	}
	else
		printf(ERR_FILE_CANNOT_OPEN_DONT_EXISTS);
}

void executeCommandDefaultValues(Settings* settings)
{
	settings->gameMode = 1;
	settings->difficulty = 2;
	settings->playerColor = WHITE_PLAYER;
}

void executeCommandPrintSettings(Settings* settings)
{
	if (settings->gameMode == 1)
	{
		printf("SETTINGS:\n");
		printf("GAME_MODE: 1\n");
		printf("DIFFICULTY_LVL: %d\n",settings->difficulty);
		printf("USER_CLR: %d\n",(settings->playerColor == WHITE_PLAYER ? 1 : 0));
	}
	else
	{
		printf("SETTINGS:\n");
		printf("GAME_MODE: 2\n");
	}
}

void executeCommandStart(GameManager** game, Settings* settings)
{
	if (settings->gameMode == 1)
	{
		*game = createOnePlayerGame(settings->difficulty,settings->playerColor);
	}
	else
	{
		*game = createTwoPlayersGame();
	}
}



