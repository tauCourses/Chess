#include "ConsoleManager.h"
#include "GameManager.h"
#include "GameState.h"

int mainConsole()
{
	GameManager* game = NULL;
    INPUT_STATE inputState = INPUT_SETTINGS_STATE;
    SETTINGS_INPUT_STATE settingsInputState;
    GAME_INPUT_STATE gameInputState;
    SettingsCommand* SCommand = (SettingsCommand*) malloc(sizeof(SCommand));
    GameStateCommand* GCommand = (GameStateCommand*) malloc(sizeof(GCommand));
    if (SCommand == NULL || GCommand == NULL)
    {
        printf(ERR_MALLOC);
        return 0;
    }
    SCommand->type = SETTINGS_COMMAND_INVALID; //default value
    GCommand->type = GAME_STATE_COMMAND_INVALID;//default value
    Settings* settings = createSettings();

    printf(MSG_SETTING_BEGIN);
    do {
		switch (inputState)
        {
            case INPUT_SETTINGS_STATE:
                getSettingsCommandFromUser(&SCommand);
            	settingsInputState = executeSettingsCommand(&game,SCommand,settings);
                inputState = updateInputStateSetting(settingsInputState);
            	break;
            case INPUT_GAME_STATE:
                if (game->mode == TWO_PLAYERS_GAME_MODE || game->userColor == game->state->currentPlayer)
                    gameInputState = makeUserMove(&game, &GCommand, &settings);
                else //computer's turn
                    gameInputState = makeComputerMove(game);
                inputState = updateInputStateGame(gameInputState);
            	break;
            case INPUT_GAME_QUIT:
            	break;
            default:
            	break;
        }//switch
    }while(inputState != INPUT_GAME_QUIT && SCommand->type != SETTINGS_COMMAND_QUIT && GCommand->type != GAME_STATE_COMMAND_QUIT);

    free(SCommand);
    free(GCommand);
    destroySettings(settings);
	destroyGame(game);
    return 1;
}





GAME_INPUT_STATE makeUserMove(GameManager** game, GameStateCommand** GCommand, Settings** settings)
{
    GAME_INPUT_STATE gameInputState;
    if ((*game)->state->currentPlayer == WHITE_PLAYER)
        printf(MSG_NEXT_MOVE_WHITE);
    else
        printf(MSG_NEXT_MOVE_BLACK);
    getGameStateCommandFromUser(GCommand);

    gameInputState = executeGameStateCommand(*game,*GCommand);

    if ((*GCommand)->type == GAME_STATE_COMMAND_RESET) {
        resetSettings(*settings);
        *game = NULL;
        printf(MSG_SETTING_BEGIN);
    }

    return gameInputState;
}


INPUT_STATE updateInputStateSetting(SETTINGS_INPUT_STATE settingsInputState)
{
    if (settingsInputState == SETTINGS_INPUT_GAME_STATE)
        return INPUT_GAME_STATE;
    if (settingsInputState == SETTINGS_INPUT_GAME_QUIT)
        return INPUT_GAME_QUIT;
    return INPUT_SETTINGS_STATE;
}

INPUT_STATE updateInputStateGame(GAME_INPUT_STATE gameInputState)
{
    if (gameInputState == GAME_INPUT_GAME_STATE)
        return INPUT_GAME_STATE;
    if (gameInputState == GAME_INPUT_SETTINGS_STATE)
        return INPUT_SETTINGS_STATE;
    return INPUT_GAME_QUIT;
}
