/*
 * #include <stdio.h>
#include "game.h"
#include "gameTests.h"

int main() {
    //runLegalMovesTests();
    //runMoveTests();
    //runArrayListTests();
    //runGamePlayTests();
    //rungenericArrayListTests();
   //runUndoTest();
    //runCompareLocationTest();
    runShitPointersTest();
    //runGetMovesStatesTest();

    return 0;
}*/
#include <stdio.h>
#include "GUIManager.h"
#include "console.h"
#include "Infrastructure.h"

int main(int argc, char** argv)
{
    if(argc == 1)
        return mainConsole();
    if(argc == 2)
    {
        if(strncmp(argv[1], "-c", 2) == 0)
            return mainConsole();
        else if(strncmp(argv[1], "-g", 2) == 0)
            return  mainGUI();
        else
        {
            printf("Unkown argument %s\n", argv[1]);
            return 1;
        }
    }
    printf("invalid number of arguments");
    return 1;
}



