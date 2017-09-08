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
#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include "GUIManager.h"

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    GUIManager* gui = managerCreate();
    if (gui == NULL ) {
        SDL_Quit();
        return 0;
    }

    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if(managerHandleEvent(gui,&event) == MANAGER_QUIT)
            break;

        managerDraw(gui);
    }
    managerDestroy(gui);
    SDL_Quit();
    return 0;
}
