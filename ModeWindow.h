#ifndef CHESS_MODEWINDOW_H
#define CHESS_MODEWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"


typedef enum {
    MODE_NEXT, MODE_START, MODE_BACK, MODE_EXIT,  MODE_INVALID_ARGUMENT, MODE_NONE
} MODE_WINDOW_EVENTS;

typedef struct  {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Button* title; //not really a button. click on not changing it
    Button* onePlayer;
    Button* twoPlayers;
    Button* back;
    Button* progress; // button for progressing
    int configurationChosen;
} ModeWindow;

ModeWindow* createModeWindow();
void createModeButtons(ModeWindow* window);
void destroyModeWindow(ModeWindow *window);
void drawModeWindow(ModeWindow *window);
MODE_WINDOW_EVENTS handleEventModeWindow(ModeWindow *window, SDL_Event *event);

void hideModeWindow(ModeWindow* window);
void showModeWindow(ModeWindow* window);

void changeChoiceModeWindow(ModeWindow* window, int i);



#endif //CHESS_MODEWINDOW_H
