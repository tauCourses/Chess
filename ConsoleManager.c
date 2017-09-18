#include "ConsoleManager.h"
#include "GameManager.h"

int mainConsole()
{
	GameManager* game = NULL;
    INPUT_STATE inputState = INPUT_SETTINGS_STATE;
    SETTINGS_INPUT_STATE settingsInputState;
    GAME_INPUT_STATE gameInputState;
    SettingsCommand* SCommand = (SettingsCommand*) malloc(sizeof(SCommand));
    GameStateCommand* GCommand = (GameStateCommand*) malloc(sizeof(GCommand));
    if (SCommand == NULL || GCommand == NULL)
        printf(ERR_MALLOC);
    SCommand->type = SETTINGS_COMMAND_INVALID;
    GCommand->type = GAME_STATE_COMMAND_INVALID;
    Settings* settings = createSettings();

    printf(MSG_SETTING_BEGIN);
    do {
		switch (inputState)
        {
            case INPUT_SETTINGS_STATE:
                free(SCommand);
                getSettingsCommandFromUser(&SCommand);
                printf("This is SCommand.type BEFORE execute %d\n",SCommand->type);
            	settingsInputState = executeSettingsCommand(&game,SCommand,settings);
                printf("This is SCommand.type AFTER execute %d\n",SCommand->type);
                inputState = updateInputStateSetting(settingsInputState);
            	break;
            case INPUT_GAME_STATE:
				if (game->mode == TWO_PLAYERS_GAME_MODE || game->userColor == game->state->currentPlayer)
                {
                    free(GCommand);
                    gameInputState = makeUserMove(&game, &GCommand, &settings);
                }
                else//computer's turn
                    gameInputState = makeComputerMove(game);
                inputState = updateInputStateGame(gameInputState);
            	break;
            case INPUT_GAME_QUIT:
            	printf("ERROR: should have quit bug 21812");
            	break;
            default:
            	break;
        }//switch
    }while(gameInputState != INPUT_GAME_QUIT && SCommand->type != SETTINGS_COMMAND_QUIT && GCommand->type != GAME_STATE_COMMAND_QUIT);
    printf(MSG_QUIT);
    free(SCommand);
    free(GCommand);
    destroySettings(settings);
	destroyGame(game);
    return 1;
}


void printBoard(Board board){
    for (int i=CHESS_BOARD_SIZE-1; i>=0; i--){
        printf("%d| ",i+1);
        for (int j=0; j<CHESS_BOARD_SIZE; j++){
            printf("%c ",board[i][j]);
        }
        printf("|\n");
    }
    printf("  -----------------\n");
    printf("   A B C D E F G H \n");
}


GAME_INPUT_STATE makeUserMove(GameManager** game, GameStateCommand** GCommand, Settings** settings)
{
    GAME_INPUT_STATE gameInputState;
    printf("PRINT BOARD execute this is turn of:%d\n", (*game)->state->currentPlayer);
    printBoard((*game)->state->board);
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
}

INPUT_STATE updateInputStateGame(GAME_INPUT_STATE gameInputState)
{
    if (gameInputState == GAME_INPUT_GAME_STATE)
        return INPUT_GAME_STATE;
    if (gameInputState == GAME_INPUT_SETTINGS_STATE)
        return INPUT_SETTINGS_STATE;
    if (gameInputState == GAME_INPUT_GAME_QUIT)
        return INPUT_GAME_QUIT;
}