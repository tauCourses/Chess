#include "mainConsole.h"

int runConsoleGame()
{
    Game* game = createNewGame(1,2,BLACK);
    InputState inputState = settingState;
    Command command;
    command = getCommand();
//    if (command.type == defaultValues)
//        inputState = gameState;
    do {
        switch (inputState)
        {
            case settingState:
                while (command.type != start){
                    //executeSettingCommand(game,command);
                    command = getCommand();
                }
                inputState = gameState;
                break;


            case gameState: {
                break;
            }
        }
        command = getCommand();
    }
    while(command.type != quit);

    destroyGame(game);

    return 1;
}

Command getCommand()
{

}

Command getCommandFromUser()
{
//    char input[MAX_LINE_LENGTH];
//    fgets(input,MAX_LINE_LENGTH,stdin);
//    if (input == NULL)//error in fgets
//    {
//        printf(ERR_FUNC_FAIL, "fgets");
//        SPCommand errorCommand;
//        errorCommand.cmd = SP_QUIT;
//        errorCommand.validArg = true; // marks command as an error
//        return errorCommand;
//    }
//    return spParserPraseLine(input);
}