#ifndef SPSIMPLEMAINWINDOW_H_
#define SPSIMPLEMAINWINDOW_H_
#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"

/**
 * main Window summary:
 * the main Window module handle the main window
 */

typedef enum {
    MAIN_EXIT, MAIN_START, MAIN_LOAD, MAIN_ERROR, MAIN_NONE
} MAIN_WINDOW_EVENTS;

typedef struct  {
    SDL_Renderer* renderer;

    Button* newGame;
    Button* load;
    Button* exit;
} MainWindow;

/**
 *  create new main window
 *  @param renderer - the renderer for the window
 *  @return
 *  the new main window.
 */
MainWindow* createMainWindow(SDL_Renderer* renderer);

/**
 *  create new main window buttons
 *  @param window - the window to create in
 *  @return void
 */
void createMainButtons(MainWindow* window);

/**
 *  destroy new main window
 *  @param window - the window to destroy
 *  @return void
 */
void destroyMainWindow(MainWindow *window);

/**
 *  draw new main window
 *  @param window - the window to draw
 *  @return true is success, false otherwise
 */
bool drawMainWindow(MainWindow *window);


/**
 *  handle events in main window
 *  @param window - the window to handle in
 *  event - the SDL event to handle
 *  @return next state of the main window
 */
MAIN_WINDOW_EVENTS handleEventMainWindow(MainWindow *window, SDL_Event *event);
#endif
