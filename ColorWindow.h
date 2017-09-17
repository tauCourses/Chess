#ifndef CHESS_COLORWINDOW_H
#define CHESS_COLORWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"
#include "GameManager.h"

#define SELECT_COLOR_TITLE "images/titles/selectYourColor.bmp"

typedef enum {
    COLOR_START, COLOR_BACK, COLOR_EXIT,  COLOR_ERROR, COLOR_NONE
} COLOR_WINDOW_EVENTS;

typedef struct  {
    SDL_Renderer* renderer;

    Button* title; //not really a button. click on not changing it
    Button* colorSwitch;

    Button* back;
    Button* start;
} ColorWindow;

ColorWindow* createColorWindow(SDL_Renderer* renderer);
void createColorButtons(ColorWindow* window);
void destroyColorWindow(ColorWindow *window);
bool drawColorWindow(ColorWindow *window);
COLOR_WINDOW_EVENTS handleEventColorWindow(ColorWindow *window, SDL_Event *event);

PLAYER_COLOR getColorFromColorWindow(ColorWindow *window);

#endif //CHESS_COLORWINDOW_H
