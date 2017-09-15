#ifndef CHESS_GAMEWINDOW_H
#define CHESS_GAMEWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"
#include "GameLayout.h"
#include "Storage.h"
#include "GameManager.h"

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

    GameLayout* board;
    GameManager* game;

    bool isSaved;
} GameWindow;

GameWindow* createGameWindow(SDL_Renderer* renderer, GameManager* game);
void createGameButtons(GameWindow* window);
void destroyGameWindow(GameWindow *window);
void drawGameWindow(GameWindow *window);

GAME_WINDOW_EVENTS handleMouseUpGameWindow(GameWindow *window, SDL_Event *event);
GAME_WINDOW_EVENTS handleEventGameWindow(GameWindow *window, SDL_Event *event);

int exitConfirmationMessageBox();
int gameEndMessageBox(PLAYER_COLOR winner);

#endif //CHESS_GAMEWINDOW_H
