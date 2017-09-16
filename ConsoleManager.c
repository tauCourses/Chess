#include "ConsoleManager.h"

int mainConsole()
{
	setvbuf(stdout, NULL, _IOLBF, 0);
	GameManager* game = NULL;
    INPUT_STATE inputState = INPUT_SETTINGS_STATE;

    SETTINGS_INPUT_STATE settingsInputState;
    GAME_INPUT_STATE gameInputState;
    SettingsCommand SCommand;
    GameStateCommand GCommand;

    Settings* settings = createSettings();

    do {
        switch (inputState)
        {
            case INPUT_SETTINGS_STATE:
            	SCommand = getSettingsCommandFromUser();
				printf("TestPrint mainConsole, this is Scommand.value %d\n",SCommand.value);
            	settingsInputState = executeSettingsCommand(&game,SCommand,settings);
            	if (settingsInputState == SETTINGS_INPUT_GAME_STATE)
            		inputState = INPUT_GAME_STATE;
            	if (settingsInputState == SETTINGS_INPUT_GAME_QUIT)
            		inputState = INPUT_GAME_QUIT;
            	break;
            case INPUT_GAME_STATE:
            	if (game->userColor == game->state->currentPlayer)
            	{
            		printBoard(game->state->board);
            		if (game->state->currentPlayer == WHITE_PLAYER)
            			printf(MSG_NEXT_MOVE_WHITE);
            		else
            		    printf(MSG_NEXT_MOVE_BLACK);
            		GCommand = getGameStateCommandFromUser();

            		gameInputState = executeGameStateCommand(game,GCommand);
            		if (GCommand.type == GAME_STATE_COMMAND_RESET)
            		    resetSettings(settings);
            	}
            	else
            	{
            		if (gameInputState != GAME_INPUT_GAME_QUIT && game->mode == 1)
            		            			gameInputState = makeComputerMove(game);
            	}

            	if (gameInputState == GAME_INPUT_GAME_STATE)
            	    inputState = INPUT_GAME_STATE;
            	if (gameInputState == GAME_INPUT_GAME_QUIT)
            	    inputState = INPUT_GAME_QUIT;
            	break;
            case INPUT_GAME_QUIT:
            	printf("ERROR: should have quit bug 21812");
            	break;
            default:
            	break;
        }
    }while(SCommand.type != SETTINGS_COMMAND_QUIT && GCommand.type != GAME_STATE_COMMAND_QUIT);
    printf(MSG_QUIT);
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


void executeCommandInvalid(){
	printf("Invalid command\n");
}
