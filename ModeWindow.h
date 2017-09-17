#ifndef CHESS_MODEWINDOW_H
#define CHESS_MODEWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"

#define SELECT_MODE_TITLE "images/titles/GameMode.bmp"

typedef enum {
    MODE_NEXT, MODE_START, MODE_BACK, MODE_EXIT,  MODE_ERROR, MODE_NONE
} MODE_WINDOW_EVENTS;

typedef struct  {
    SDL_Renderer* renderer;

    Button* title; //not really a button. click on not changing it
    Button* onePlayer;
    Button* twoPlayers;
    Button* back;
    Button* progress; // button for progressing
    int configurationChosen;
} ModeWindow;

ModeWindow* createModeWindow(SDL_Renderer* renderer);
void createModeButtons(ModeWindow* window);
void destroyModeWindow(ModeWindow *window);
bool drawModeWindow(ModeWindow *window);
MODE_WINDOW_EVENTS handleEventModeWindow(ModeWindow *window, SDL_Event *event);

void changeChoiceModeWindow(ModeWindow* window, int i);



#endif //CHESS_MODEWINDOW_H
