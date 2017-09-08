

#ifndef CHESS_LOADGAMEWINDOW_H
#define CHESS_LOADGAMEWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"

#define MAX_NUMBER_OF_LOAD_GAMES 5

typedef enum {
    LOAD_BACK, LOAD_EXIT, LOAD_CONITNUE, LOAD_INVALID_ARGUMENT, LOAD_NONE
} LOAD_WINDOW_EVENTS;

typedef struct  {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Button* slots[MAX_NUMBER_OF_LOAD_GAMES];
    Button* back;
    Button* load;
    int slotChosed;
    int numOfSlots;
} LoadWindow;

LoadWindow* createLoadWindow();
void createLoadButtons(LoadWindow* window);
void destroyLoadWindow(LoadWindow *window);
void drawLoadWindow(LoadWindow *window);
LOAD_WINDOW_EVENTS handleEventLoadWindow(LoadWindow *window, SDL_Event *event);

void hideLoadWindow(LoadWindow* window);
void showLoadWindow(LoadWindow* window);

void changeChoiceLoadWindow(LoadWindow* window, int i);


#endif //CHESS_LOADGAMEWINDOW_H
