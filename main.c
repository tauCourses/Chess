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
#include "ChessMainWindow.h"

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
        printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    SPWindow* window = createSimpleWindow();
    if (window == NULL ) {
        SDL_Quit();
        return 0;
    }

    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT){
            break;
        }
        window->handleEventWindow(window,&event);
       // In this example we draw the window every time... in many case we shouldn't
        window->drawWindow(window);
    }
    destroyWindow(window);
    SDL_Quit();
    return 0;
}
