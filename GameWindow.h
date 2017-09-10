#ifndef CHESS_GAMEWINDOW_H
#define CHESS_GAMEWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"
#include "BoardLayout.h"

typedef enum {
    GAME_LOAD, GAME_MAIN, GAME_EXIT,  GAME_INVALID_ARGUMENT, GAME_NONE
} GAME_WINDOW_EVENTS;

typedef struct  {
    SDL_Renderer* renderer;

    Button* restart;
    Button* save;
    Button* load;
    Button* undo;

    Button* main;
    Button* exit;

    BoardLayout* board;
    //Pieces* pieces
    //Game* game
} GameWindow;

GameWindow* createGameWindow(SDL_Renderer* renderer);
void createGameButtons(GameWindow* window);
void destroyGameWindow(GameWindow *window);
void drawGameWindow(GameWindow *window);
//void printGameOnBoard(GameWindow *window);
GAME_WINDOW_EVENTS handleEventGameWindow(GameWindow *window, SDL_Event *event);

#endif //CHESS_GAMEWINDOW_H
