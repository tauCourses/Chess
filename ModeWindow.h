#ifndef CHESS_MODEWINDOW_H
#define CHESS_MODEWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"

/**
 * Mode Window summary:
 * the mode Window module handle the mode selection window
 */

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

/**
 *  create new mode window
 *  @param renderer - the renderer for the window
 *  @return
 *  the new mode window.
 */
ModeWindow* createModeWindow(SDL_Renderer* renderer);

/**
 *  create new mode window buttons
 *  @param window - the window to create in
 *  @return void
 */
void createModeButtons(ModeWindow* window);

/**
 *  destroy new mode window
 *  @param window - the window to destroy
 *  @return void
 */
void destroyModeWindow(ModeWindow *window);

/**
 *  draw new mode window
 *  @param window - the window to draw
 *  @return true is success, false otherwise
 */
bool drawModeWindow(ModeWindow *window);

/**
 *  handle events in mode window
 *  @param window - the window to handle in
 *  event - the SDL event to handle
 *  @return next state of the mode window
 */
MODE_WINDOW_EVENTS handleEventModeWindow(ModeWindow *window, SDL_Event *event);

/**
 *  change choice in mode window
 *  @param window - the window to change choice in
 *  i - the number of new choice
 *  @return void
 */
void changeChoiceModeWindow(ModeWindow* window, int i);



#endif //CHESS_MODEWINDOW_H
