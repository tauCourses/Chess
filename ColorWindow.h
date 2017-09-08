#ifndef CHESS_COLORWINDOW_H
#define CHESS_COLORWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"

typedef enum {
    COLOR_START, COLOR_BACK, COLOR_EXIT,  COLOR_INVALID_ARGUMENT, COLOR_NONE
} COLOR_WINDOW_EVENTS;

typedef struct  {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Button* title; //not really a button. click on not changing it
    Button* black;
    Button* white;

    Button* back;
    Button* start;
    int configurationChosen;
} ColorWindow;

ColorWindow* createColorWindow();
void createColorButtons(ColorWindow* window);
void destroyColorWindow(ColorWindow *window);
void drawColorWindow(ColorWindow *window);
COLOR_WINDOW_EVENTS handleEventColorWindow(ColorWindow *window, SDL_Event *event);

void hideColorWindow(ColorWindow* window);
void showColorWindow(ColorWindow* window);

void changeChoiceColorWindow(ColorWindow* window, int i);

#endif //CHESS_COLORWINDOW_H
