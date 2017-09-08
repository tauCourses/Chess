#ifndef SPSIMPLEMAINWINDOW_H_
#define SPSIMPLEMAINWINDOW_H_
#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"

typedef enum {
    MAIN_EXIT, MAIN_START, MAIN_LOAD, MAIN_INVALID_ARGUMENT, MAIN_NONE
} MAIN_WINDOW_EVENTS;

typedef struct  {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Button* newGame;
    Button* load;
    Button* exit;
} MainWindow;

MainWindow* createMainWindow();
void createMainButtons(MainWindow* window);
void destroyMainWindow(MainWindow *window);
void drawMainWindow(MainWindow *window);
void hideMainWindow(MainWindow* window);
void showMainWindow(MainWindow *window);
MAIN_WINDOW_EVENTS handleEventMainWindow(MainWindow *window, SDL_Event *event);
#endif
